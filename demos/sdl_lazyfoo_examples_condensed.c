
// gcc lazyfoo_examples_condensed.c -I../include -framework SDL2 -framework SDL2_image -Wfatal-errors -Wall && ./a.out 


#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define SDL_STUFF_IMPLEMENTATION
#include "sdl_stuff.h"

// #include <stdio.h>
#include "PRINT_ERROR.h"



int sdl_use_surfaces( )
{
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_PNG );

    const int window_width = 800;
    const int window_height = 600;
    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN );

    SDL_Surface *surface, *lenna, *lenna_native, *nyan_cat;
    int err;
    SDL_Rect destination;
    float scaler;

    surface = SDL_GetWindowSurface( window );
    SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, 0x55,0x55,0xAA ) );

    lenna = SDL_LoadBMP( "../data/lenna.bmp" );
    if (!lenna) PRINT_ERROR_EXIT("Couldn't load file\n");
    
    SDL_BlitSurface( lenna, NULL, surface, NULL );

    // blit scaled
    scaler = 300.0 / (float)lenna->h;
    destination = make_rect(lenna->w, 0, scaler*lenna->w, scaler*lenna->h);
    lenna_native = SDL_ConvertSurface( lenna, surface->format, 0 ); // requires native format
    err = SDL_BlitScaled( lenna_native, NULL, surface, &destination );
    if (err) printf("ERROR %s %d %s\n", __FILE__, __LINE__, SDL_GetError() );

    // load png
    nyan_cat = IMG_Load( "../data/nyan_cat.png" ); 
    if (!nyan_cat) PRINT_ERROR_EXIT("Couldn't load file\n");

    scaler = 300.0 / (float)nyan_cat->h;
    destination = make_rect(0,300, scaler*nyan_cat->w, scaler*nyan_cat->h);
    err = SDL_BlitScaled( nyan_cat, NULL, surface, &destination );
    if (err) printf("ERROR %s %d %s\n", __FILE__, __LINE__, SDL_GetError() );


    SDL_UpdateWindowSurface( window );


    SDL_Event event; 
    int quit = 0;
    while ( !quit ) {
        SDL_WaitEvent(&event);
        if ( event.type == SDL_QUIT ) quit = 1;
        print_event(event);
    }


    SDL_FreeSurface(lenna);
    SDL_FreeSurface(lenna_native);
    SDL_FreeSurface(nyan_cat);
    SDL_DestroyWindow( window ); // frees surface
    SDL_Quit();
    return 0;
}



int sdl_use_renderer( )
{
    const int WINDOW_WIDTH  = 800;
    const int WINDOW_HEIGHT = 600;
    
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_PNG );

    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    
    SDL_Renderer *renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    // SDL_SetRenderDrawColor( renderer, 255,255,255,255);
    // SDL_RenderClear( renderer );

    SDL_Surface* nyan_cat = IMG_Load( "../data/nyan_cat.png" ); 
    if (!nyan_cat) PRINT_ERROR_EXIT("Couldn't load file\n");

	SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, nyan_cat );
    if (!texture) printf("ERROR %s %d %s\n", __FILE__, __LINE__, SDL_GetError() );

    float scaler = 300.0 / (float)nyan_cat->h;
    SDL_Rect destination = make_rect(0,300, scaler*nyan_cat->w, scaler*nyan_cat->h);

    SDL_RenderCopy( renderer, texture, NULL, &destination );
    SDL_RenderPresent( renderer );

    SDL_Event event;
    int quit = 0;
    while ( !quit ) {
        SDL_WaitEvent(&event);
        if ( event.type == SDL_QUIT ) quit = 1;

    }


    SDL_FreeSurface(nyan_cat);
    SDL_DestroyWindow( window );
    SDL_DestroyTexture( texture );
    SDL_DestroyRenderer( renderer );

    IMG_Quit();
    SDL_Quit();
    return 0;
}


int main()
{
    sdl_use_surfaces();
    // sdl_use_renderer();

}