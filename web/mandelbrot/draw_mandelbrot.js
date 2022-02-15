
function hue2rgb(p, q, t) {
    if (t < 0) {
        t += 1;
    }
    if (t > 1) {
        t -= 1;
    }
    if (t < 1 / 6) {
        return p + (q - p) * 6 * t;
    }
    if (t < 1 / 2) {
        return q;
    }
    if (t < 2 / 3) {
        return p + (q - p) * (2 / 3 - t) * 6;
    }
    return p;
}

function hsl_to_rgb(h, s, l) {
    let r;
    let g;
    let b;

    let q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    let p = 2 * l - q;

    if (s === 0) {
        r = 1;
        g = 1;
        b = 1; // achromatic
    } else {

        r = hue2rgb(p, q, h + 1 / 3);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1 / 3);
    }

    return [Math.round(r * 255), Math.round(g * 255), Math.round(b * 255)];
}

function pixel_coordinates_to_mandelbrot_coordinate(canvas, mandelbrot, x, y)
{
    // at a particular zoom level the pixel space is defined to have a particular size in mandelbrot space
    // the width is 4/zoom and the height is smaller than that in accordance to the aspect ratio

    var aspect_ratio = canvas.width / canvas.height 

    var offset_x = ( x - (canvas.width / 2) ) / ( canvas.width / 2 ) * ( 2 / mandelbrot.zoom );
    var offset_y = ( y - (canvas.height / 2) ) / ( canvas.height / 2 ) * ( 2 / mandelbrot.zoom ) / aspect_ratio;

    var cx = mandelbrot.x + offset_x;
    var cy = mandelbrot.y + offset_y;

    return [cx, cy]; 
}


function draw_mandelbrot(canvas, mandelbrot) {

    var im = canvas.getContext("2d").getImageData(0, 0, canvas.width, canvas.height);

    // main loop
    // x and y are the pixel coordinates which starts top left and goes down
    for (var y = 0; y < im.height; y += 1) {
        for (var x = 0; x < im.width; x += 1) {

            var cx, cy;
            [cx, cy] = pixel_coordinates_to_mandelbrot_coordinate(canvas, mandelbrot, x, y);

            var zx = 0;
            var zy = 0;

            var in_set = true;
            var num_iterations = 1;
            for ( ; num_iterations <= mandelbrot.max_iterations; num_iterations += 1 ) {
                // z = z^2 + c
                // z = (zx+izy)^2 + (cx+icy) = ((zx)^2 - (zy)^2 + cx) + i(2xy + cy)
                var zx_temp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = zx_temp;
                // if the length of complex vector exceeds 4 then assume the pixel is not in the set
                if (zx * zx + zy * zy > 4) {
                    in_set = false;
                    break;
                }
            }

            // color in pixel
            let black = [0, 0, 0, 255];
            let stride = 4;
            var pos = (y * im.width * stride) + (x * stride);
            if (in_set) {
                im.data[pos + 0] = black[0];
                im.data[pos + 1] = black[1];
                im.data[pos + 2] = black[2];
                im.data[pos + 3] = black[3];
            } else {
                // hue is determined by the number of iterations taken
                var rgb = hsl_to_rgb((num_iterations % 255) / 255, 1, 0.5);
                im.data[pos + 0] = rgb[0];
                im.data[pos + 1] = rgb[1];
                im.data[pos + 2] = rgb[2];
                im.data[pos + 3] = black[3]; // no opacity
            }


        }

    }
    canvas.getContext("2d").putImageData(im, 0, 0);

    // return img;
}



