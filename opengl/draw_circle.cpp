// g++ draw_circle.cpp -framework SDL2 -framework opengl && ./a.out 

// from https://gist.github.com/jordandee/94b187bcc51df9528a2f



#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/gl.h>

void draw_circle( float cx, float cy, float r, int num_segments )
{
    // float cx = 0.0f; float cy = 0.0f; float r = 0.2f; int num_segments = 100;
    // https://stackoverflow.com/questions/22444450/drawing-circle-with-opengl

    glBegin(GL_TRIANGLE_FAN);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glVertex2f(x + cx, y + cy); //output vertex

    }
    glEnd();
}



int main (int ArgCount, char **Args)
{

    const int window_width = 1000;
    const int window_height = 1000;

    uint32_t WindowFlags = SDL_WINDOW_OPENGL;
    SDL_Window *Window = SDL_CreateWindow("OpenGL Test", 0, 0, window_width, window_height, WindowFlags);
    assert(Window);

    SDL_GLContext Context = SDL_GL_CreateContext(Window);

    int32_t running = 1;
    int32_t fullscreen = 0;
    while (running) {
        
        // handle events
        SDL_Event event;
        SDL_WaitEvent(&event);
        if ( event.type == SDL_QUIT ) running = 0;
        if ( event.type == SDL_KEYDOWN) {
            char key = event.key.keysym.sym;
            if ( key == SDLK_ESCAPE ) {
                running = 0;
            }
            else if ( key == 'f' ) {
                fullscreen = !fullscreen;
                if (fullscreen) {
                    SDL_SetWindowFullscreen(Window, WindowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                } else {
                    SDL_SetWindowFullscreen(Window, WindowFlags);
                }
            }
        }


        // glViewport(0, 0, window_width, window_height);
        // glClearColor(0.0f,0.0f,0.0f,0.0f);
        // glClear(GL_COLOR_BUFFER_BIT);

        glColor3f( 1.f, 1.f, 1.f );
        draw_circle(-0.5, +0.5, 0.1, 100);
        draw_circle(+0.5, +0.5, 0.1, 100);
        draw_circle(+0.5, -0.5, 0.1, 100);
        draw_circle(-0.5, -0.5, 0.1, 100);



        glBegin( GL_QUADS );
            glColor3f( 1.f, 0.f, 0.f ); glVertex2f( -0.5f, -0.5f );
            glColor3f( 1.f, 1.f, 0.f ); glVertex2f(  0.5f, -0.5f );
            glColor3f( 0.f, 1.f, 0.f ); glVertex2f(  0.5f,  0.5f );
            glColor3f( 0.f, 0.f, 1.f ); glVertex2f( -0.5f,  0.5f );
        glEnd();



        // //Render quad
        // glBegin( GL_LINE_LOOP ); // GL_QUADS );
        //     glVertex2f( -0.5f, -0.5f );
        //     glVertex2f(  0, -0.5f );
        //     glVertex2f(  0,  0 );
        //     glVertex2f( -0.5f,  0 );
        // glEnd();


        // // draw a triangle  https://stackoverflow.com/questions/43494563/draw-a-triangle-with-opengl?rq=1
        // glBegin(GL_LINE_LOOP); // GL_TRIANGLES fills it in
        // glVertex3f(0, 0, 0);
        // glVertex3f(0.5, 0, 0);
        // glVertex3f(0, 0.7, 0);
        // glEnd();










        // https://lazyfoo.net/tutorials/OpenGL/01_hello_opengl/index2.php

        

        // https://lazyfoo.net/tutorials/OpenGL/02_matrices_and_coloring_polygons/index.php

        // glOrtho( 0.0, window_width, window_height, 0.0, 1.0, -1.0 );

        // //Solid Cyan
        // glBegin( GL_QUADS );
        //     glColor3f( 0.f, 1.f, 1.f );
        //     glVertex2f( -50.f, -50.f );
        //     glVertex2f(  50.f, -50.f );
        //     glVertex2f(  50.f,  50.f );
        //     glVertex2f( -50.f,  50.f );
        // glEnd();

        // //RYGB Mix
        // glBegin( GL_QUADS );
        //     glColor3f( 1.f, 0.f, 0.f ); glVertex2f( -50.f, -50.f );
        //     glColor3f( 1.f, 1.f, 0.f ); glVertex2f(  50.f, -50.f );
        //     glColor3f( 0.f, 1.f, 0.f ); glVertex2f(  50.f,  50.f );
        //     glColor3f( 0.f, 0.f, 1.f ); glVertex2f( -50.f,  50.f );
        // glEnd();


        SDL_GL_SwapWindow(Window);

    }

    return 0;
}


