/*
gcc sobel_edge_detection.c -framework SDL2 -ISDL2 && ./a.out
*/

#include <SDL2/SDL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "src/stb_image.h"

// #include <stdio.h>
// #include "types.h"


void sobel_edge_detection(uint8_t* original_image, int width, int height, uint8_t** edge_image_arg)
{
    // make a greyscale image of floats which is centered around zero.
    double *grey_image_floats = (double*)calloc(height * width, sizeof(double));
    for (int j=0; j<height; j++ ){
        for (int i=0; i<width; i++ ){
            int pos = j*width*4 + i*4;
            char r = original_image[pos+0];
            char g = original_image[pos+1];
            char b = original_image[pos+2];
            char a = original_image[pos+3];

            char v = 0.212671f * r + 0.715160f * g + 0.072169f * b;

            grey_image_floats[j*width+i] = (double)((v-127.0)); // "centered" around zero

        }
    }

    // // actually center around zero by subtracting average from each value.
    // double average_color = -1;
    // double sum_of_colors = -1;
    // for (int j=0; j<height; j++ ){
    //     for (int i=0; i<width; i++ ){
    //         int pos = j*width + i;
    //         // printf("%f ", grey_image_floats[j*width+i]);
    //         sum_of_colors += grey_image_floats[j*width+i];
    //     }
    // }
    // average_color = sum_of_colors / (width*height);
    // printf("average color: %f\n", average_color);

    // for (int j=0; j<height; j++ ){
    //     for (int i=0; i<width; i++ ){
    //         grey_image_floats[j*width+i] -= average_color;
    //     }
    // }



    // Apply x and y sobel filters
    double *edge_image_floats = (double*)calloc(height * width, sizeof(double));
    for (int j=1; j<height-1; j++ ){
        for (int i=1; i<width-1; i++ ){

            int pos = j*width + i;

            // sobel filters 
            //    -1 0 +1     +1 +2 +1
            //    -2 0 +2      0  0  0
            //    -1 0 +1     -1 -2 -1

            // sobel filter 
            double Gx[9] = { -1,0,+1,-2,0,+2,-1,0,+1};
            double Gy[9] = { +1,+2,+1,0,0,0,-1,-2,-1};

            double x = 
            + Gx[0] * grey_image_floats[ pos-width - 1 ]
            + Gx[1] * grey_image_floats[ pos-width + 0 ]
            + Gx[2] * grey_image_floats[ pos-width + 1 ]
            + Gx[3] * grey_image_floats[ pos       - 1 ]
            + Gx[4] * grey_image_floats[ pos       + 0 ]
            + Gx[5] * grey_image_floats[ pos       + 1 ]
            + Gx[6] * grey_image_floats[ pos+width - 1 ]
            + Gx[7] * grey_image_floats[ pos+width + 0 ]
            + Gx[8] * grey_image_floats[ pos+width + 1 ];

            double y = 
            + Gy[0] * grey_image_floats[ pos-width - 1 ]
            + Gy[1] * grey_image_floats[ pos-width + 0 ]
            + Gy[2] * grey_image_floats[ pos-width + 1 ]
            + Gy[3] * grey_image_floats[ pos       - 1 ]
            + Gy[4] * grey_image_floats[ pos       + 0 ]
            + Gy[5] * grey_image_floats[ pos       + 1 ]
            + Gy[6] * grey_image_floats[ pos+width - 1 ]
            + Gy[7] * grey_image_floats[ pos+width + 0 ]
            + Gy[8] * grey_image_floats[ pos+width + 1 ];

            // x /= 9.;
            // y /= 9.;
            
            edge_image_floats[pos] = (double)sqrt( x*x + y*y );
            // edge_image_floats[pos] = (double)sqrt(x*x);

        }
    }


    double minval = edge_image_floats[0];
    double maxval = edge_image_floats[0];
    for (int j=1; j<height-1; j++ ){
        for (int i=1; i<width-1; i++ ){
            int pos = j*width + i;
            if ( edge_image_floats[pos] < minval ) minval = edge_image_floats[pos];
            if ( edge_image_floats[pos] > maxval ) maxval = edge_image_floats[pos];
        }
    }
    // printf("min %f max %f\n", minval, maxval);


    // Convert back to a regular image
    // uint8_t *edge_image = (uint8_t*)calloc(height * width * 4, sizeof(uint8_t));
    uint8_t* edge_image = *edge_image_arg;
    for (int j=1; j<height-1; j++ ){
        for (int i=1; i<width-1; i++ ){
            int pos = j*width*4 + i*4;
 
            // Rescale floats to fill color bytes
            // min value goes to zero
            // max value goes to 255
            // y = (max-min)*(x - min)
            uint8_t v = (uint8_t)(  255.0 * ( edge_image_floats[j*width+i] - minval ) / ( maxval - minval ) );

            edge_image[pos+0] = v;
            edge_image[pos+1] = v;
            edge_image[pos+2] = v;
            edge_image[pos+3] = (uint8_t)(255);
        }
    }


    free(grey_image_floats);
    free(edge_image_floats);

    // edge_image_arg = &edge_image;
}




int main( int argc, char* args[] )
{

    // This example shows how to create a SDL_Surface* with the data loaded
    // from an image file with stb_image.h (https://github.com/nothings/stb/)

    // the color format you request stb_image to output,
    // use STBI_rgb if you don't want/need the alpha channel
    int req_format = STBI_rgb_alpha;
    int width, height, orig_format;
    uint8_t* original_image = stbi_load("data/Valve_original.png", &width, &height, &orig_format, req_format);
    if (original_image == NULL) {
        SDL_Log("Loading image failed: %s", stbi_failure_reason());
        exit(1);
    }

    uint8_t *edge_image = (uint8_t*)calloc(height * width * 4, sizeof(uint8_t));
    sobel_edge_detection(original_image, width, height, &edge_image);

    uint8_t *images[2];
    int image_index = 0;
    images[0] = original_image;
    images[1] = edge_image;


    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window* window = SDL_CreateWindow("Click the image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN );
    SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_Texture* texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height );


    SDL_UpdateTexture( texture, NULL, images[image_index], width * 4 );
    // SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
    // SDL_RenderClear( renderer );
    SDL_RenderCopy( renderer, texture, NULL, NULL );
    SDL_RenderPresent( renderer );


    SDL_Event event;
    int quit = 0;
    while ( !quit )
    {
        SDL_WaitEvent( &event );
        if ( event.type == SDL_QUIT ) quit = 1;
        if ( event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN ) {
            printf("woo keydown or mouse button\n");
            if ( image_index == 0 ) image_index = 1; else image_index = 0;

            SDL_UpdateTexture( texture, NULL, images[image_index], width * 4 );
            // SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
            // SDL_RenderClear( renderer );
            SDL_RenderCopy( renderer, texture, NULL, NULL );
            SDL_RenderPresent( renderer );
        }
    }


    SDL_Quit();
    return 0;
}


