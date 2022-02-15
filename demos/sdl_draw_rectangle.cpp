/*

g++ draw_rectangle.cpp -I../include -framework SDL2 -framework SDL2_mixer -framework SDL2_image -framework SDL2_ttf -Wfatal-errors -fsanitize=address && ./a.out

based on draw_geometry by thenumbat https://thenumbat.github.io/cpp-course/sdl2/04/04.html

*/

#include <iostream>
#include "SDL2/SDL.h"

int main( int argc, char* args[] )
{
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    int window_width = 400;
    int window_height = 400;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);  

	SDL_Event e;
	SDL_Rect r;
	// For mouse rectangle
	int mx0 = -1, my0 = -1, mx1 = -1, my1 = -1;
    int mouse_is_down = 0;
    int render_mouse_rectangle = 0;
    int quit = 0;


	while ( !quit ) {

        while ( SDL_PollEvent( &e ) != 0 ) {
            if ( SDL_QUIT == e.type ) {
                quit = 1;
            }
            else if ( SDL_MOUSEBUTTONDOWN == e.type ) {
                mx0 = e.button.x;
                my0 = e.button.y;
                mouse_is_down = 1;
            }
            else if ( SDL_MOUSEMOTION == e.type ) {
                mx1 = e.button.x;
                my1 = e.button.y;
                if (mouse_is_down ) render_mouse_rectangle = 1;
            }
            else if ( SDL_MOUSEBUTTONUP == e.type ) {
                mouse_is_down = 0;
                render_mouse_rectangle = 0;
            }
        }
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

        if ( render_mouse_rectangle ) {
            r.x = mx0;
            r.y = my0;
            r.w = mx1 - mx0;
            r.h = my1 - my0;
            SDL_RenderDrawRect( renderer, &r );
        }


        SDL_RenderPresent( renderer );
        SDL_Delay(10); // <100 Hz

    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

