// g++ render_chaos_demo.cpp -Iinclude -framework SDL2 -Wfatal-errors && ./a.out

#include "SDL2/SDL.h"
#include <vector>

double math_max ( double a, double b )
{
    if (a>b) return a;
    return b;
}

int main( int argc, char* args[] )
{

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    int window_width = 1200;
    int window_height = 800;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);  

    // SDL_RenderSetScale( renderer, 2,2);
    SDL_SetRenderDrawBlendMode ( renderer, SDL_BLENDMODE_BLEND );

	SDL_Event event;
	SDL_Rect rect;
    int quit = 0;

    double r_value = 3.7;

    int mouse_is_down = 0;
    int mouse_x, mouse_y;

    int needs_rendering = 1;
	while ( !quit ) {

        while ( SDL_PollEvent( &event ) != 0 ) {
            if ( SDL_QUIT == event.type ) {
                quit = 1;
            }
            else if ( SDL_MOUSEBUTTONDOWN == event.type ) {
                mouse_is_down = 1;
            }
            else if ( SDL_MOUSEMOTION == event.type ) {
                // if (mouse_is_down) {
                    SDL_GetMouseState( &mouse_x, &mouse_y );
                    r_value = ((((double)mouse_x)/ (double)window_width) * 1.5 ) + 3.0;
                    needs_rendering = 1;
                // }
            }
            else if ( SDL_MOUSEBUTTONUP == event.type ) {
                mouse_is_down = 0;

            }
        }

        if (needs_rendering) {
            // mouses state mouse_x 0..800 => 1..5

            char buf[256];
            snprintf(buf, 256, " chaos r value %f", r_value);
            SDL_SetWindowTitle( window, buf );

            SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
            SDL_RenderClear( renderer );
            SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

            int height = (int) (0.5 * window_height);
            double y0 = 0.02;
            int stride = 5;
            for ( double x = 1; x < window_width ; x += stride ){

                double y1 = r_value * y0 * ( 1 - y0 );
                y1 = math_max ( y1, 0 );
                SDL_RenderDrawLine( renderer, x-stride, height-height*y0, x, height-height*y1 );
                y0 = y1;
                // printf("%f ", y0);
            }

        
            SDL_RenderPresent( renderer );
            needs_rendering = 0;
        }
        SDL_Delay(10); // <100 Hz

    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}




