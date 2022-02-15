// g++ misc_sdl.cpp -framework SDL2 && ./a.out

// https://wiki.libsdl.org/SDL_CreateTexture

#ifdef __APPLE__
#include "SDL2/SDL_config_macosx.h"
#endif 

#include <SDL2/SDL.h>

#define SDL_TOOLS_IMPLEMENTATION
#include "src/sdl_tools.h"

#define SDL_STBIMAGE_IMPLEMENTATION
#include "src/SDL_stbimage.h"




int is_inside( int x, int y, SDL_Rect r )
{
    return r.x < x && x < (r.x + r.w) && r.y < y && y < (r.y + r.h);
}


typedef struct { 
    SDL_Rect r;
    SDL_Texture *texture;
} Face;



int main(int argc, char *argv[])
{
    int face_width = 300;
    int face_height = 200;
    int faces_length = 4;

    int window_width = face_width * 4;
    int window_height = 800;

    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("ERROR %s:%d %s\n",__FILE__,__LINE__, SDL_GetError());
        return 3;
    }

    window = SDL_CreateWindow("omgomg a title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);



    // show_moving_rectangle( window );



    SDL_Texture *textures[4];
    enum { MOUSEOUT, MOUSEOVER, MOUSEDOWN, MOUSEUP };

    // read image into texture
    SDL_Surface* surface = STBIMG_Load( "data/button.png" );
    if( !surface ) {
        printf( "ERROR %s %d %s\n", __FILE__,__LINE__,SDL_GetError() );
        exit(1);
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, surface );


    // separate into individual textures
    for( int i = 0; i < 4; ++i ) {
        SDL_Rect srcrect = make_rect( 0, i * face_height, face_width, face_height ); 
        textures[i] = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, face_width, face_height );
        SDL_SetRenderTarget(renderer, textures[i]);
        SDL_RenderCopy(renderer, texture, &srcrect, NULL);
    }
    SDL_SetRenderTarget(renderer, NULL); // reset render target



    // setup interfaces
    Face faces[4];
    for (int i=0;i<4;i+=1) {
        faces[i].r = make_rect( i * face_width, 0, face_width, face_height );
        faces[i].texture = textures[MOUSEOUT];
    }


    int mouse_x, mouse_y;
    int quit = 0;
    SDL_Event event;
    while( !quit )
    {
        // handle input
        while( SDL_PollEvent( &event ) != 0 )
        {
            if( event.type == SDL_QUIT ) quit = 1;
            
            for(int i=0; i < faces_length; i+=1 ) {
                SDL_GetMouseState(&mouse_x, &mouse_y);
                if ( !is_inside( mouse_x, mouse_y, faces[i].r ) ) {
                    faces[i].texture = textures[MOUSEOUT];
                } else {
                    if ( event.type == SDL_MOUSEMOTION ) faces[i].texture = textures[MOUSEOVER];
                    if ( event.type == SDL_MOUSEBUTTONUP ) faces[i].texture = textures[MOUSEUP];
                    if ( event.type == SDL_MOUSEBUTTONDOWN ) faces[i].texture = textures[MOUSEDOWN];
                } 
            }
        }

        // render
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        for( int i = 0; i < faces_length; ++i ) {
            SDL_RenderCopy(renderer, faces[i].texture, NULL, &(faces[i].r) );
        }
        SDL_RenderPresent( renderer );
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}







void show_moving_rectangle( SDL_Window *window )
{
    SDL_Renderer *renderer = SDL_GetRenderer(window);
    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height );

    SDL_Rect r;

    SDL_Rect block_rect = make_rect( 0, 0, 100, 50 );
    SDL_Texture *block = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, block_rect.w, block_rect.h );

    SDL_Rect menu_rect = make_rect(0,0, window_width, 100);
    SDL_Texture *menu = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, menu_rect.w, menu_rect.h );
    SDL_SetRenderTarget(renderer, menu);
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    SDL_Rect content_rect = make_rect(0, 100, window_width, window_height - 100 );
    SDL_Texture *content = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, content_rect.w, content_rect.h );
    SDL_SetRenderTarget(renderer, content);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, block);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, content);
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 0xFF);
    SDL_RenderClear(renderer);

    SDL_Event event;
    while (1) {
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT) break;

            block_rect.x=rand()%(content_rect.w - block_rect.w);
            block_rect.y=rand()%(content_rect.h - block_rect.h);


            SDL_SetRenderTarget(renderer, content);
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, block, NULL, &block_rect);

            SDL_SetRenderTarget(renderer, NULL);
            SDL_RenderCopy(renderer, menu, NULL, &menu_rect);
            SDL_RenderCopy(renderer, content, NULL, &content_rect);

            SDL_RenderPresent(renderer);

            SDL_Delay(100);
    }

}




