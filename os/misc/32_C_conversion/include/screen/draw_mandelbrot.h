// 
// clear_screen.h: clears screen by writing to video memory 
//
#pragma once

void draw_mandelbrot(int *image, int w, int h)
{

    double xcenter = 0;
    double ycenter = 0;
    double width = 4;
    double height = 4;

    const unsigned char black[4] = {0, 0, 0, 255};
    const unsigned char white[4] = {255, 255, 255, 255};
    
    for (int y = 0; y < h ; y += 1) {
        for (int x = 0; x < w; x += 1) {

            double zx, zxtmp, zy, cx, cy;
            int is_in_set, num_iterations;
            const int max_iterations = 40;

            // image is flipped vertically
            cx = x * (width / w) - (xcenter + width/2);
            cy = y * (height / h) - (ycenter + height/2);
            zx = 0;
            zy = 0;
            is_in_set = 1;

            for(num_iterations = 1; num_iterations <= max_iterations; num_iterations += 1){
                zxtmp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = zxtmp;
                if(zx * zx + zy * zy > 4){
                    is_in_set = 0;
                    break;
                }
            }
            
            int pos = y*w + x;
            if (is_in_set) {
				image[pos] = 0xFF000000; // ABGR
            } else {
                unsigned char color = white[0] * num_iterations / max_iterations;
				image[pos] = (255<<24) + (color<<16) + (color<<8) + (color);
			}
        }
    }


}


void draw_mandelbrot_demo(void)
{
    // Get 32bit pointer to framebuffer value in VBE mode info block, 
    //   dereference to get the 32bit value,
    //   get 32bit pointer to that value - memory address of framebuffer
    uint32_t *framebuffer = (uint32_t *)*(uint32_t *)0x9028; 

    for (uint32_t i = 0; i < 1920*1080; i++)
        framebuffer[i] = 0x000000FF;    // Write 32bit ARGB pixel to screen



    // texture width and height
    const unsigned int w = 300;
    const unsigned int h = 300;
    unsigned int image[w*h];

    draw_mandelbrot(image, w,h);

    for (uint32_t j = 0; j < h; j++){
        for (uint32_t i = 0; i < w; i++){
            framebuffer[j*1920+i+500] = image[j*w+i];    // Write 32bit ARGB pixel to screen
        }
    }



}
