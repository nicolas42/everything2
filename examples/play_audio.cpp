/*
g++ play_audio.cpp -Iinclude -framework SDL2 -framework SDL2_mixer -framework SDL2_image -framework SDL2_ttf -Wfatal-errors -g -fsanitize=address -Wall -Wpedantic  && ./a.out

call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
cl /Zi /I "win64\include\SDL2" "play_audio.cpp" /link "win64\SDL2.lib" "win64\SDL2main.lib" "win64\SDL2_image.lib" "win64\SDL2_mixer.lib" "win64\SDL2_ttf.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:"win64\play_audio.cpp.exe" && win64\play_audio.cpp.exe
del *.obj *.pdb

based on code by the lazyfoo
*/

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include "src/libc.h"


void stop_audio(Mix_Music *music)
{
    Mix_HaltMusic(); // stop
}

void play_pause_audio(Mix_Music *music)
{
    // If there is no music playing then play the music.
    // If the music is in being "played" then check whether the piece is paused of not
    // if it is paused then resume it, if it's not paused then pause it.
    // "Playing" music appears to be music that is loaded into the subsystem.

    //If there is no music playing
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( music, -1 );
    }
    //If music is being played
    else
    {
        //If the music is paused
        if( Mix_PausedMusic() == 1 )
        {
            //Resume the music
            Mix_ResumeMusic();
        } else
        {
            //Pause the music
            Mix_PauseMusic();
        }
    }
}

void play_sound_effect(Mix_Chunk *sound_effect)
{
    Mix_PlayChannel( -1, sound_effect, 0 );
}

int main( int argc, char* args[] )
{

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    int window_width = 400;
    int window_height = 400;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);  

    //Initialize SDL_mixer
    int err = Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    if (err) { 
        printf("%s %d %s",__FILE__,__LINE__,Mix_GetError()); 
        exit(1); 
    }

    Mix_Music *music; 
    Mix_Chunk *scratch, *high;

	music = Mix_LoadMUS( "data/beat.wav");
	if( !music ) { 
        printf("%s %d %s",__FILE__,__LINE__,Mix_GetError()); 
        exit(1); 
    }
	scratch = Mix_LoadWAV( "data/scratch.wav" );
	if( !scratch ) { 
        printf("%s %d %s",__FILE__,__LINE__,Mix_GetError()); 
        exit(1); 
    }
	high = Mix_LoadWAV( "data/high.wav" );
	if( !high ) { 
        printf("%s %d %s",__FILE__,__LINE__,Mix_GetError()); 
        exit(1); 
    }


    TTF_Init();
    char* font_path = (char*)"data/Sans.ttf";
    int font_size = 16;
    TTF_Font *font = TTF_OpenFont(font_path, font_size);
    if (!font) { 
        printf("ERROR %s %d %s\n", __FILE__, __LINE__, SDL_GetError());
        exit(1);
    }


    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);


    char text[] = 
        "SDLK_1 play_pause_audio(music)\n"
        "SDLK_2 stop_audio(music)\n"
        "SDLK_3 play_sound_effect(scratch)\n"
        "SDLK_4 play_sound_effect(high)\n";

    int char_pos_x = 0;
    int char_pos_y = 0;

    for ( const char *line = strtok(text, "\n"); line != NULL; line = strtok(NULL, "\n") ) {

        const SDL_Color text_color = {20,20,20,0};
        const SDL_Color background_color = {255,255,255,0};

        SDL_Surface *text_surface = TTF_RenderText_Shaded(font, line, text_color, background_color); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_Rect rect;
        rect.x = char_pos_x;
        rect.y = char_pos_y;
        rect.w = text_surface->w;
        rect.h = text_surface->h;
        
        SDL_RenderCopy(renderer, texture, NULL, &rect);

        char_pos_y += text_surface->h;

        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(texture);

    }

    SDL_RenderPresent(renderer);




    SDL_Event e;
    int quit = 0;
    while (!quit) {
        SDL_WaitEvent(&e);
        if (e.type == SDL_QUIT) {
            quit = 1;
        }
        if (e.type == SDL_KEYDOWN) {

            if (e.key.keysym.sym == SDLK_1) { play_pause_audio(music); }
            if (e.key.keysym.sym == SDLK_2) { stop_audio(music); }

            if (e.key.keysym.sym == SDLK_3) { play_sound_effect(scratch); }
            if (e.key.keysym.sym == SDLK_4) { play_sound_effect(high); }

        }
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	Mix_FreeMusic( music );
	Mix_FreeChunk( scratch );
	Mix_FreeChunk( high );
	Mix_Quit();
    SDL_Quit();

	return 0;
}
