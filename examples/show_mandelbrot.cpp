/*
g++ -Wall -Wpedantic -Wextra -Wshadow -Wvla show_mandelbrot.cpp -framework SDL2  && ./a.out

-Wno-double-conversion -Wno-conversion 

warnings="-Wsign-conversion -Wconversion -Wall -Wpedantic -Wextra -Wvla -Wshadow"
g++ ${warnings} show_mandelbrot.cpp -framework SDL2  && ./a.out


https://stackoverflow.com/questions/33304351/sdl2-fast-pixel-manipulation
*/


#ifdef _WIN32
    #define SDL_MAIN_HANDLED
#endif 

#include <SDL2/SDL.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "src/stb_image_write.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>

#include <iostream>
#include <iomanip>
#include <vector>


double hue2rgb(double p, double q, double t) {
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

uint32_t hsl2rgba(double h, double s, double l) {

    double r,g,b;
    double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    double p = 2.0 * l - q;
    if (s == 0.0) {
        r = 1.0;
        g = 1.0;
        b = 1.0; // achromatic
    } else {
        r = hue2rgb(p, q, h + 1.0 / 3.0);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1.0 / 3.0);
    }

    // scale channels by 255.0 and combine them into a 32 bit integer
    uint32_t rgba = (uint32_t)(  
        ((uint8_t)(r*255.0))<<24 | ((uint8_t)(g*255.0))<<16 | ((uint8_t)(b*255.0))<<8 | (uint8_t)255  
    );
    return rgba;
}

SDL_Surface* sdl_draw_mandelbrot(int im_w, int im_h, double x, double y, double zoom, double max_iterations )
{

    uint32_t *im_data = (uint32_t*)malloc(im_w * im_h * sizeof(uint32_t));

    double ii,jj,h,w,cx,cy,zx,zy,zxtemp,hue;
    int in_set,num_iterations,pos;

    for (jj = 0; jj < im_h; jj += 1) {
        for (ii = 0; ii < im_w; ii += 1) {

            h = 4.0 / zoom;
            w = 4.0 / zoom;
            // z = z^2 + c
            cx = (x - w / 2) + ii * (w / im_w);
            cy = (y - h / 2) + jj * (w / im_w);
            zx = 0;
            zy = 0;

            in_set = 1;
            num_iterations = 1;
            while ( num_iterations <= max_iterations ) {
                zxtemp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = zxtemp;
                if (zx * zx + zy * zy > 4) {
                    in_set = 0;
                    break;
                }
                num_iterations += 1;
            }
            pos = (jj * im_w) + (ii);
            if (in_set) {
                im_data[pos] = 255; // black (just alpha channel)
            } else {
                hue = (num_iterations % 255) / 255.0;
                im_data[pos] = hsl2rgba(hue, 1.0, 0.5);
            }
        }
    }

    // image to surface
    uint32_t pitch, depth, rmask, gmask, bmask, amask;
    pitch = 4 * im_w; // image pitch is the length of a row in bytes
    depth = 32;
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
    return SDL_CreateRGBSurfaceFrom((void*)im_data, im_w, im_h, depth, pitch, rmask, gmask, bmask, amask);

}

int main()
{
    const int window_w  = 500;
    const int window_h = 500;

    const int image_w  = 500;
    const int image_h = 500;

    const double image_scale_w = double(window_w) / double(image_w);
    const double image_scale_h = double(window_h) / double(image_h);


    // initialize
    SDL_Init( SDL_INIT_VIDEO );
    SDL_Window *window = SDL_CreateWindow( "Click me", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_w, window_h, SDL_WINDOW_SHOWN );
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    int quit = 0;
    int render = 1;
    SDL_Event event;
    int mousex,mousey;


    double x = -0.6999687500000003;
    double y = -0.2901249999999999;
    double zoom = 1000;

    while( !quit )
    {
        while( SDL_PollEvent( &event ) != 0 )
        {
            if ( event.type == SDL_QUIT ) quit = 1;
            // if ( event.type == SDL_KEYDOWN ) render = 1;
            if ( event.type == SDL_MOUSEBUTTONDOWN ) {
                SDL_GetMouseState(&mousex,&mousey);

                double w = 4.0/zoom;
                double h = 4.0/zoom;
                // the canvas goes from x+-w/2, y+-h/2
                double top = y - h/2.0;
                double left = x - w/2.0;

                x = left + ( (double(mousex)/image_scale_w) / double(image_w) * w);
                y = top + ( (double(mousey)/image_scale_h) / double(image_h) * h);

                if ( event.button.button == SDL_BUTTON_LEFT ) {
                    printf("SDL_BUTTON_LEFT\n");
                    zoom *= 2.0;
                } else if ( event.button.button == SDL_BUTTON_RIGHT ) {
                    printf("SDL_BUTTON_RIGHT\n");
                    zoom /= 2.0;
                }
                
                SDL_Log("image_w, image_h, x, y, zoom: %.20f, %.20f, %.20f, %.20f, %.20f\n", image_w, image_h, x, y, zoom );
                render = 1;
            }
        }

        if (render){
            SDL_PumpEvents();
            SDL_FlushEvents(0x101, 0xFFFF);
            render = 0;
            SDL_Surface *surface = sdl_draw_mandelbrot(image_w, image_h, x,y, zoom, 1000);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_RenderCopy(renderer, texture, NULL, NULL );
            SDL_RenderPresent( renderer );
        }
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();




    // // print surface pixel format
    // SDL_Log("SDL_GetPixelFormatName %s", SDL_GetPixelFormatName(window_surface->format->format));

    // SDL_Event event;
    // int quit = 0;
    // int render = 0;
    // while ( !quit ) {
    //     while (SDL_PollEvent(&event)){
    //         if ( event.type == SDL_QUIT ) quit = 0;
    //         if ( event.type == SDL_KEYDOWN ) render = 1;
    //         if ( event.type == SDL_MOUSEBUTTONDOWN ) render = 1;
    //     }

    //     if (render){
    //         SDL_Log("Render!\n");
    //         render = 0;
    //         SDL_Surface *surface = sdl_draw_mandelbrot(800, 800, -0.6999687500000003, -0.2901249999999999, 1000, 1000);
    //         SDL_BlitSurface( surface, NULL, window_surface, NULL );
    //         SDL_UpdateWindowSurface(window);
    //     }
    //     SDL_Delay(10);
    // }

    // SDL_DestroyWindow( window );
    // SDL_Quit();
    return 0;
}



// // Write image
// for(i=0;i<s->w*s->h;++i) ((uint32_t*)s->pixels)[i] = SDL_Swap32(((uint32_t*)s->pixels)[i]);
// int success = stbi_write_png("mandy.png", s->w, s->h, 4, s->pixels, s->w * 4);
// if (success) { SDL_Log("You wrote the png!"); }









// int texture_main(int argc, char ** argv)
// {
//     int WINDOW_WIDTH = 800;
//     int WINDOW_HEIGHT = 800;
//     SDL_Init( SDL_INIT_EVERYTHING );
//     SDL_Window* window_surface = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
//     SDL_Renderer* window_renderer = SDL_CreateRenderer( window_surface, -1, SDL_RENDERER_ACCELERATED );

//     Image image;
//     SDL_Texture* texture;


//     image = make_image(WINDOW_WIDTH, WINDOW_HEIGHT, 4); // width, height, number of channels
//     draw_mandelbrot_rgba(image, -0.6999687500000003, -0.2901249999999999, 1000, 1000); // x,y,zoom,max_iterations

//     texture = SDL_CreateTexture( window_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, image.w, image.h );
//     SDL_SetRenderDrawColor( window_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
//     SDL_UpdateTexture( texture, NULL, image.data, image.w * image.c );
//     SDL_RenderClear( window_renderer );
//     SDL_RenderCopy( window_renderer, texture, NULL, NULL );
//     SDL_RenderPresent( window_renderer );

//     SDL_Event event;
//     bool running = true;
//     int i = 0;
//     while ( running )
//     {
//         SDL_WaitEvent(&event);
//         if ( event.type == SDL_QUIT ) running = false;
//         printf("event %d\n", i++);
//     }

//     SDL_DestroyTexture(texture);
//     free(image.data);
//     SDL_Quit();
 
//     return 0;
// }





// void reverse_pixel_order(Image im)
// {
//     // rbga <=> gbra, doesn't move alpha
//     double i,j;
//     int pos;
//     char r,g,b;

//     for(j=0;j<im.h;++j){
//         for(i=0;i<im.h;++i){

//             pos = (j * im.w * im.c) + (i * im.c);

//             r = im.data[pos+0];
//             g = im.data[pos+1];
//             b = im.data[pos+2];

//             im.data[pos + 0] = b;
//             im.data[pos + 1] = g;
//             im.data[pos + 2] = r;
//             im.data[pos + 3] = (char)255;

//         }
//     }
// }






    
// typedef struct {
//     // width, height, number of channels, image data
//     uint32_t w,h,c,*data;
// } Image;

// Image make_image(double w, double h, double c)
// {
//     Image im;
//     im.w = w;
//     im.h = h;
//     im.c = c;
//     im.data = (uint32_t*)malloc(im.w * im.h * sizeof(uint32_t));
//     return im;
// }

// void draw_mandelbrot_rgba(Image im, double x, double y, double zoom, double max_iterations )
// {
//     double i,j,h,w,cx,cy,zx,zy,zxtemp,hue;
//     uint32_t in_set,num_iterations,pos,rgba,black;

//     for (j = 0; j < im.h; j += 1) {
//         for (i = 0; i < im.w; i += 1) {
//             h = 4.0 / zoom;
//             w = 4.0 / zoom;
//             // z = z^2 + c
//             cx = (x - w / 2) + i * (w / im.w);
//             cy = (y - h / 2) + j * (w / im.w);
//             zx = 0;
//             zy = 0;
//             in_set = 1;
//             num_iterations = 1;
//             while ( num_iterations <= max_iterations ) {
//                 zxtemp = zx * zx - zy * zy + cx;
//                 zy = 2 * zx * zy + cy;
//                 zx = zxtemp;
//                 if (zx * zx + zy * zy > 4) {
//                     in_set = 0;
//                     break;
//                 }
//                 num_iterations += 1;
//             }
//             pos = (j * im.w) + (i);
//             if (in_set) {
//                 im.data[pos] = 255; // black
//             } else {
//                 hue = (num_iterations % 255) / 255.0;
//                 im.data[pos] = hsl2rgba(hue, 1.0, 0.5);
//             }
//         }
//     }
// }





