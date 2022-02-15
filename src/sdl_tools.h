#ifndef SDL_TOOLS_HEADER_GUARD
#define SDL_TOOLS_HEADER_GUARD

#include <SDL2/SDL.h>

void print_event(SDL_Event event);
SDL_Rect make_rect(int x, int y, int w, int h);


#endif // SDL_TOOLS_HEADER_GUARD
#ifdef SDL_TOOLS_IMPLEMENTATION
#ifndef SDL_TOOLS_IMPLEMENTATION_GUARD
#define SDL_TOOLS_IMPLEMENTATION_GUARD




void print_event(SDL_Event event)
{
    if ( event.type == SDL_AUDIODEVICEADDED ) printf("SDL_AUDIODEVICEADDED\n");
    if ( event.type == SDL_AUDIODEVICEREMOVED ) printf("SDL_AUDIODEVICEREMOVED\n");
    if ( event.type == SDL_CONTROLLERAXISMOTION ) printf("SDL_CONTROLLERAXISMOTION\n");
    if ( event.type == SDL_CONTROLLERBUTTONDOWN ) printf("SDL_CONTROLLERBUTTONDOWN\n");
    if ( event.type == SDL_CONTROLLERBUTTONUP ) printf("SDL_CONTROLLERBUTTONUP\n");
    if ( event.type == SDL_CONTROLLERDEVICEADDED ) printf("SDL_CONTROLLERDEVICEADDED\n");
    if ( event.type == SDL_CONTROLLERDEVICEREMOVED ) printf("SDL_CONTROLLERDEVICEREMOVED\n");
    if ( event.type == SDL_CONTROLLERDEVICEREMAPPED ) printf("SDL_CONTROLLERDEVICEREMAPPED\n");
    if ( event.type == SDL_DOLLARGESTURE ) printf("SDL_DOLLARGESTURE\n");
    if ( event.type == SDL_DOLLARRECORD ) printf("SDL_DOLLARRECORD\n");
    if ( event.type == SDL_DROPFILE ) printf("SDL_DROPFILE\n");
    if ( event.type == SDL_DROPTEXT ) printf("SDL_DROPTEXT\n");
    if ( event.type == SDL_DROPBEGIN ) printf("SDL_DROPBEGIN\n");
    if ( event.type == SDL_DROPCOMPLETE ) printf("SDL_DROPCOMPLETE\n");
    if ( event.type == SDL_FINGERMOTION ) printf("SDL_FINGERMOTION\n");
    if ( event.type == SDL_FINGERDOWN ) printf("SDL_FINGERDOWN\n");
    if ( event.type == SDL_FINGERUP ) printf("SDL_FINGERUP\n");
    if ( event.type == SDL_KEYDOWN ) printf("SDL_KEYDOWN\n");
    if ( event.type == SDL_KEYUP ) printf("SDL_KEYUP\n");
    if ( event.type == SDL_JOYAXISMOTION ) printf("SDL_JOYAXISMOTION\n");
    if ( event.type == SDL_JOYBALLMOTION ) printf("SDL_JOYBALLMOTION\n");
    if ( event.type == SDL_JOYHATMOTION ) printf("SDL_JOYHATMOTION\n");
    if ( event.type == SDL_JOYBUTTONDOWN ) printf("SDL_JOYBUTTONDOWN\n");
    if ( event.type == SDL_JOYBUTTONUP ) printf("SDL_JOYBUTTONUP\n");
    if ( event.type == SDL_JOYDEVICEADDED ) printf("SDL_JOYDEVICEADDED\n");
    if ( event.type == SDL_JOYDEVICEREMOVED ) printf("SDL_JOYDEVICEREMOVED\n");
    if ( event.type == SDL_MOUSEMOTION ) printf("SDL_MOUSEMOTION ");
    if ( event.type == SDL_MOUSEBUTTONDOWN ) printf("SDL_MOUSEBUTTONDOWN\n");
    if ( event.type == SDL_MOUSEBUTTONUP ) printf("SDL_MOUSEBUTTONUP\n");
    if ( event.type == SDL_MOUSEWHEEL ) printf("SDL_MOUSEWHEEL\n");
    if ( event.type == SDL_MULTIGESTURE ) printf("SDL_MULTIGESTURE\n");
    if ( event.type == SDL_QUIT ) printf("SDL_QUIT\n");
    if ( event.type == SDL_SYSWMEVENT ) printf("SDL_SYSWMEVENT\n");
    if ( event.type == SDL_TEXTEDITING ) printf("SDL_TEXTEDITING\n");
    if ( event.type == SDL_TEXTINPUT ) printf("SDL_TEXTINPUT\n");
    if ( event.type == SDL_USEREVENT ) printf("SDL_USEREVENT\n");
    if ( event.type == SDL_WINDOWEVENT ) printf("SDL_WINDOWEVENT\n");

    if ( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP ) printf("%s\n", SDL_GetKeyName(event.key.keysym.sym));

    fflush(stdout);
}


SDL_Rect make_rect(int x, int y, int w, int h)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
    return dest;
}






#endif // SDL_TOOLS_IMPLEMENTATION_GUARD 
#endif // #ifdef SDL_TOOLS_IMPLEMENTATION


