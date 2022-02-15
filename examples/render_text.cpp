/*
 g++ render_text.cpp -Iinclude -framework SDL2 -framework SDL2_image -framework SDL2_ttf && ./a.out


 call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

 cl /EHsc /Zi /I "win64\include\SDL2" "render_text.cpp" /link "win64\SDL2.lib" "win64\SDL2main.lib" "win64\SDL2_image.lib" "win64\SDL2_mixer.lib" "win64\SDL2_ttf.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:"win64\render_text.cpp.exe"

 /EHsc is to use vectors.  they need exceptions or something
 The SDL free functions take a long time.  Their overall duration is decreased if I put all the surface and texture pointers into a big array 
 and then free them all at the same time.  But calling free within a loop is bloody slow.
 The way to go appears to be to store textures for future use.  There's not that many glyphs to render after all.

*/

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

// #include <stdio.h>
// #include <stdlib.h>
#include <vector>
#include <string>
#include <map>

void render_text(SDL_Window *window, TTF_Font *font, const char *text, int y_offset, std::map<char, SDL_Texture*> *text_textures )
{

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    int window_width;
    int window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);

    SDL_Color text_color = {20,20,20,0};
    SDL_Color background_color = {255,255,255,0};


    int x = 0;
    int y = y_offset;

    int i;
    char glyph[2] = {'\0','\0'};

    uint32_t start_time = SDL_GetTicks();

    for(i=0; text[i]!='\0'; i+=1){


        SDL_Texture *text_texture = (*text_textures)[text[i]];
        SDL_Surface *text_surface;

        glyph[0] = text[i];
        if (text_texture == NULL) {
            SDL_Log("Add character to font texture map: %c",text[i]);

            text_surface = TTF_RenderText_Shaded(font, glyph, text_color, background_color); 
            if (!text_surface) {
                SDL_Log("ERROR %s %d %s\n", __FILE__,__LINE__,SDL_GetError());
            }
            text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
            if (!text_texture) {
                SDL_Log("ERROR %s %d %s\n", __FILE__,__LINE__,SDL_GetError());
            }
            SDL_FreeSurface(text_surface);
            (*text_textures)[text[i]] = text_texture;
        }


        int w, h;
        SDL_QueryTexture(text_texture, NULL, NULL, &w, &h);

        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        
        // wrap
        if ( glyph[0] == '\n' || rect.x + w > window_width ) {
            x = 0;
            y += h;
            rect.x = x;
            rect.y = y;
        } 
        if ( glyph[0] != '\n') {
            SDL_RenderCopy(renderer, text_texture, NULL, &rect);
            x += w;
        }

    }

    SDL_RenderPresent(renderer);

    SDL_Log("rendering time %d\n", SDL_GetTicks() - start_time );

}



int main(int argc, char **argv) {

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    int window_width = 800;
    int window_height = 800;
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);

    SDL_SetWindowTitle(window, "Scroll text using the mouse wheel or arrow keys.");

    TTF_Init();
    char font_path[] = "data/Sans.ttf"; // "c:/windows/fonts/verdana.ttf"; 
    int font_size = 20;
    TTF_Font *font = TTF_OpenFont(font_path, font_size);
    if (!font) { SDL_Log("ERROR %s %d %s\n", __FILE__, __LINE__, SDL_GetError()); exit(1); }


    const char *text = 
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    
    std::map<char, SDL_Texture*> text_textures;    
    int y_offset = 0;
    render_text(window, font, text, y_offset, &text_textures);

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) == 1) {

            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            if (e.type == SDL_MOUSEWHEEL){
                y_offset += 50*e.wheel.y;
                SDL_Log("y_offset, mouse_wheel_offset: %d %d\n", y_offset, e.wheel.y);
                render_text(window, font, text , y_offset, &text_textures);
            }
            if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_q) {
                    quit = 1;
                }
                if (e.key.keysym.sym == SDLK_UP){
                y_offset += 30;
                }
                if (e.key.keysym.sym == SDLK_DOWN){
                y_offset -= 30;
                }
                
                render_text(window, font, text , y_offset, &text_textures);

            }
        }
        SDL_Delay(10);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}



