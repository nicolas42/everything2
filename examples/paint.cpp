// g++ paint.cpp -framework SDL2 && ./a.out

// from https://bitbucket.org/dandago/gigilabs/src/master/Sdl2LineDrawing/Sdl2LineDrawing/main.cpp

#include <list>
#include <SDL2/SDL.h>

struct Line
{
    int x1;
    int y1;
    int x2;
    int y2;
};

int main(int argc, char ** argv)
{
    // variables

    bool quit = false;
    SDL_Event event;
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    bool drawing = false;
    std::list<Line> lines;

    // init SDL

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("SDL2 line drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    // handle events

    while (!quit)
    {
        SDL_Delay(10);
        SDL_PollEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        x1 = event.motion.x;
                        y1 = event.motion.y;
                        x2 = event.motion.x;
                        y2 = event.motion.y;
                        drawing = true;
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        drawing = false;
                        Line line = { x1, y1, x2, y2 };
                        lines.push_back(line);
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                if (drawing)
                {
                    x2 = event.motion.x;
                    y2 = event.motion.y;
                }
                break;
        }

        // clear window

        SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
        SDL_RenderClear(renderer);

        // draw stored lines

        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

        for (std::list<Line>::const_iterator i = lines.begin(); i != lines.end(); ++i)
        {
            Line line = *i;
            SDL_RenderDrawLine(renderer, line.x1, line.y1, line.x2, line.y2);
        }

        // draw current line

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        if (drawing)
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

        // render window

        SDL_RenderPresent(renderer);
    }

    // cleanup SDL

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}