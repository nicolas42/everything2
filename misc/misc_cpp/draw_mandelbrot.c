#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


float hue2rgb(float p, float q, float t) {
    if (t < 0.) {
        t += 1.;
    }
    if (t > 1.) {
        t -= 1.;
    }
    if (t < 1. / 6.) {
        return p + (q - p) * 6. * t;
    }
    if (t < 1. / 2.) {
        return q;
    }
    if (t < 2. / 3.) {
        return p + (q - p) * (2. / 3. - t) * 6.;
    }
    return p;
}

void hsl2rgb(float h, float s, float l, int rgb[3]) {

    // if (h!=0.0) printf("%f %f %f\n", h,s,l);

    float r;
    float g;
    float b;

    float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    float p = 2. * l - q;
    // printf("%f %f %f\n", p,q,h);

    if (s == 0.) {
        r = 1.;
        g = 1.;
        b = 1.; // achromatic
    } else {

        r = hue2rgb(p, q, h + 1. / 3.);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1. / 3.);
    }

    // printf("%f %f %f\n", r,g,b);
    rgb[0] = (int)(r * 255.);
    rgb[1] = (int)(g * 255.);
    rgb[2] = (int)(b * 255.);

}
    


struct image {
    // width, height, number of channels, image data
    int w;
    int h;
    int c;
    char *data;
};


void draw_mandelbrot(struct image im, double x, double y, double zoom, double max_iterations )
{
    char black[4] = {0,0,0,255};

    for (double j = 0; j < im.h; j += 1) {
        for (double i = 0; i < im.w; i += 1) {

            // get math point from image point
            // image is flipped vertically. numbers go up, pixels go down. i don't care.
            double h = 4. / zoom;
            double w = 4. / zoom;

            // z = z^2 + c
            double cx = (x - w / 2) + i * (w / im.w);
            double cy = (y - h / 2) + j * (w / im.w);
            double zx = 0;
            double zy = 0;
            double in_set = 1;
            int num_iterations = 1;
            while ( num_iterations <= max_iterations ) {
                double zxtemp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = zxtemp;
                // if length of complex vector exceeds 4 then 
                // assume the pixel is not in the set
                if (zx * zx + zy * zy > 4) {
                    in_set = 0;
                    break;
                }
                num_iterations += 1;
            }

            int pos = (j * im.w * im.c) + (i * im.c);
            if (in_set) {
                im.data[pos + 0] = black[0];
                im.data[pos + 1] = black[1];
                im.data[pos + 2] = black[2];
                im.data[pos + 3] = black[3];
            } else {
                // hue is determined by the number of iterations taken
                // double rgb = hsl_to_rgb((num_iterations % 255) / 255, 1, 0.5);
                int rgb[3];
                hsl2rgb((num_iterations % 255) / 255., 1., 0.5, rgb);
                // printf("%d %d %d\n", rgb[0], rgb[1], rgb[2] );

                im.data[pos + 0] = rgb[0];
                im.data[pos + 1] = rgb[1];
                im.data[pos + 2] = rgb[2];
                im.data[pos + 3] = black[3]; // no opacity
            }


        }
    }
}



int draw_mandelbrot_main(){


    struct image im;
    im.w = 800;
    im.h = 800;
    im.c = 4;
    im.data = malloc(im.w * im.h * im.c );

    double x,y,zoom,max_iterations;
    x = -0.6999687500000003; 
    y = -0.2901249999999999; 
    zoom = 1024; 
    max_iterations = 855;


    // Cool places in the mandelbrot image
    // { x: -0.6999687500000003, y: -0.2901249999999999, zoom: 1024 },
    // { x: -0.027285156250000026, y: 0.6443066406250001, zoom: 2048 },
    // { x: -0.027120712995529206, y: 0.6441158065199851, zoom: 67108864 },
    // { x: -0.027099643200635935, y: 0.6440290103852749, zoom: 268435456 },
    // { x: -0.02709963878151032, y: 0.6440290090395138, zoom: 4294967296 },
    // { x: 0.31923687500000003, y: -0.4990148437499999, zoom: 1024000 },
    // { x: 0.31923733207893373, y: -0.499014675590515, zoom: 8388608000 },
    // { x: 0.38715883591593053, y: -0.25874134865963394, zoom: 1073741824 },
    // { x: 0.1347109374999998, y: -0.6361328125, zoom: 2048 },
    // { x: 0.2681601562500003, y: -0.004765624999999972, zoom: 4096 },
    // { x: 0.38715883594200756, y: -0.2587413487062, zoom: 536870912 },
    // { x: 0.32898730468750015, y: -0.4237490234374998, zoom: 16384 },
    // { x: -1.7664619022752155, y: 0.041740019425749834, zoom: 1073741824, w: 800, h: 800, max_iterations: 855 },

    printf("Drawing a mandelbrot image %dx%d...\n", im.w, im.h);

    draw_mandelbrot(im, x,y,zoom,max_iterations);



//      int stbi_write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes);
//    The functions create an image file defined by the parameters. The image
//    is a rectangle of pixels stored from left-to-right, top-to-bottom.
//    Each pixel contains 'comp' channels of data stored interleaved with 8-bits
//    per channel, in the following order: 1=Y, 2=YA, 3=RGB, 4=RGBA. (Y is
//    monochrome color.) The rectangle is 'w' pixels wide and 'h' pixels tall.
//    The *data pointer points to the first byte of the top-left-most pixel.
//    For PNG, "stride_in_bytes" is the distance in bytes from the first byte of
//    a row of pixels to the first byte of the next row of pixels.
// int success = stbi_write_png("mandelbrot_image.png", im.w,im.h,im.c,im.data,im.w*im.c);
    stbi_write_png("mandelbrot_image.png", im.w,im.h,im.c,im.data,im.w*im.c);


    return 0;
}


int main()
{
    draw_mandelbrot_main();
}