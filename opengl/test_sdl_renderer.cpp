// g++ -Wfatal-errors test_sdl_renderer.cpp -framework SDL2 -framework SDL2_mixer -framework opengl && ./a.out 

// from https://gist.github.com/jordandee/94b187bcc51df9528a2f



#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/gl.h>
#include <math.h>
#include "../cpp/include/SDL2/SDL_mixer.h"


void draw_polygon( float cx, float cy, float r, int num_segments )
{
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


int main()
{

    // Basic solar system simulator
    // Just circular orbits currently but it should also work with 
    // elliptical ones given the proper initial conditions.


    // Orbital speeds
    // ---------------------
    // Planet 	Orbital
    // velocity
    // Mercury 	47.9e3
    // Venus 	35.0e3
    // Earth 	29.8e3
    // Mars 	24.1e3
    // Jupiter 	13.1e3
    // Saturn 	9.7e3
    // Uranus 	6.8e3
    // Neptune 	5.4e3

    // Planet Distance from Sun (m)
    // --------------------------------
    // Mercury  57900e6
    // Venus    108200e6
    // Earth    149600e6
    // Mars     227900e6
    // Jupiter  778600e6
    // Saturn   1433500e6
    // Uranus   2872500e6
    // Neptune  4495100e6

    int window_width = 1000;
    int window_height = 1000;
    uint32_t WindowFlags = SDL_WINDOW_OPENGL;
    SDL_Window *Window = SDL_CreateWindow("OpenGL Test", 0, 0, 
    window_width, window_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    assert(Window);


    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

    SDL_GLContext Context = SDL_GL_CreateContext(Window);


    //Set the viewport
    glViewport( 0.f, 0.f, window_width, window_height );

    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, window_width, window_height, 0.0, 1.0, -1.0 );

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    // //Enable texturing
    // glEnable( GL_TEXTURE_2D );

    // //Set blending
    // glEnable( GL_BLEND );
    // glDisable( GL_DEPTH_TEST );
    // glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    // //Set antialiasing/multisampling
    // glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    // glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    // glDisable( GL_LINE_SMOOTH );
    // glDisable( GL_POLYGON_SMOOTH );
    // glDisable( GL_MULTISAMPLE );

    glClear( GL_COLOR_BUFFER_BIT );

    //         glDisable( GL_LINE_SMOOTH );
	// 		glDisable( GL_POLYGON_SMOOTH );
	// 		glEnable( GL_MULTISAMPLE );

	//Render Triangle
	glColor3f( 1.f, 1.f, 1.f );
	glBegin( GL_TRIANGLES );
	 glVertex2f( window_width/3.0, 0.f );
	 glVertex2f( window_width, window_height );
	 glVertex2f( 0.f, window_height );
	glEnd();


	// glDisable( GL_MULTISAMPLE );

        SDL_GL_SwapWindow(Window);


    int running = 1; 
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if ( event.type == SDL_QUIT ) {
                running = 0;
            }
        }
        SDL_Delay(10); 
    }

}
