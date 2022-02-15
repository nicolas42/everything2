// g++ -Wfatal-errors solar_system_simulation.cpp -framework SDL2 -framework SDL2_mixer -framework opengl && ./a.out 

// from https://gist.github.com/jordandee/94b187bcc51df9528a2f



#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#ifdef _WIN32
    #define SDL_MAIN_HANDLED // why??? why???
#endif 
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <math.h>

#ifdef __APPLE__ 
    #include <OpenGL/gl.h>
#else 
    #include <GL/gl.h>
#endif 

#include <SDL2/SDL_mixer.h>


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

void simple_orbit_demo()
{
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 1000;

    uint32_t WindowFlags = SDL_WINDOW_OPENGL;
    SDL_Window *Window = SDL_CreateWindow("OpenGL Test", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WindowFlags);
    assert(Window);
    SDL_GLContext Context = SDL_GL_CreateContext(Window);

    float cx = 0.8; float cy = 0; float i = 0; 
    int32_t running = 1;
    while (running) {
        
        // handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if ( event.type == SDL_QUIT ) running = 0;
        }

        glClearColor( 0.f, 0.f, 0.f, 1.f );
        glClear(GL_COLOR_BUFFER_BIT);
        draw_polygon(0,0,0.1,100);

        float angle = 6.28318530718f * i / 1000.f;
        float x = 0.8 * cosf(angle);
        float y = 0.8 * sinf(angle);
        draw_polygon(x,y,0.01,100);
        i += 1;

        SDL_GL_SwapWindow(Window);
        SDL_Delay(10);
    }
}

void less_simple_orbit_demo()
{
    // Basic earth orbit simulator using Newton's law of gravity

    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 1000;
    uint32_t WindowFlags = SDL_WINDOW_OPENGL;
    SDL_Window *Window = SDL_CreateWindow("OpenGL Test", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    assert(Window);
    SDL_GLContext Context = SDL_GL_CreateContext(Window);

    const double G = 6.67408e-11; // gravitational constant
    const double mass_sun = 1.989e30;
    const double dt = 24*60*60; // 1 day

    double r, angle, a, v;
    double x,y,vx,vy,ax,ay;

    // Earth
    // wikipedia research indicates that the Earth has an average distance from the sun of 
    // about 150 million km and has an average orbital speed of 29.78 km/s
    r = 150e9;
    v = 29.78e3;
    a = G * mass_sun / (r*r); 

    x = r; 
    y = 0; 
    vx = v/2.0; // set to 0 for circular
    vy = v;

    int running = 1;
    while (running) {
        
        // handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if ( event.type == SDL_QUIT ) running = 0;
        }

        r = sqrt(x*x+y*y);
        a = G * mass_sun / (r*r); 
        angle = atan2(y,x);

        // orthogonal dimensions
        ax = -a * cos(angle);
        ay = -a * sin(angle);
        vx += ax * dt;
        vy += ay * dt;
        x += vx * dt;
        y += vy * dt;


        // scale values down for drawing 
        double draw_x = x / 150e9 / 3.0;
        double draw_y = y / 150e9 / 3.0;
        glClearColor( 0.f, 0.f, 0.f, 1.f );
        glClear(GL_COLOR_BUFFER_BIT);
        draw_polygon(0,0,0.1,100); // sun
        draw_polygon(draw_x, draw_y,0.01,10);
        SDL_Log("%f %f %f %f\n", draw_x, draw_y,0.01,a);
        SDL_GL_SwapWindow(Window);
        // SDL_Delay(10); // this doesn't seem to do anything.  why?
    }
    
}




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



void even_less_simple_orbit_demo()
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





    int window_width = 600;
    int window_height = 600;
    uint32_t WindowFlags = SDL_WINDOW_OPENGL;
    SDL_Window *window = SDL_CreateWindow("OpenGL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
    window_width, window_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI ); //  | SDL_WINDOW_ALLOW_HIGHDPI
    assert(window);


    int err = Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    assert(!err);
	Mix_Music *music = Mix_LoadMUS( "data/Kerbal Space Program - Space Music (Track 1)-osJqbovbH2A.mp3");
    assert(music);
    play_pause_audio(music);


    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
    SDL_GLContext Context = SDL_GL_CreateContext(window);



    const double G = 6.67408e-11; // gravitational constant
    const double mass_sun = 1.989e30;
    const double dt = 24*60*60; // 1 day


    // Planet parameters, sorry pluto
    double xs[8] = { 57900e6, 108200e6, 149600e6, 227900e6, 778600e6, 1433500e6, 2872500e6, 4495100e6 };
    double ys[8] = {       0,        0,        0,        0,        0,         0,         0,         0 };
    double vys[8] = { 47.9e3, 35.0e3, 29.8e3, 24.1e3, 13.1e3, 9.7e3, 6.8e3, 5.4e3};
    double vxs[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    // The colors were very scientifically taken from some random poster
    float colors[8][3] = { {193,80,30}, {230,120,35}, {56,111,164}, {150,42,29}, {70,32,20}, {157,106,49}, {79,105,129}, {39,77,162} };

    double zoom = 1.0;
    int running = 1; 
    // To control the frequency of gl backbuffer swaps, SDL_GL_SetSwapInterval has to be set to 0, it appears.
    SDL_GL_SetSwapInterval(1); // 0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive vsync

    while (running) {

        double angle, a, r, v;
        double x,y,vx,vy,ax,ay;

        // handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if ( event.type == SDL_QUIT ) {
                running = 0;
            }
            else if ( event.type == SDL_MOUSEWHEEL ) {
                zoom = zoom * pow(1.1, event.wheel.y);
                SDL_Log("event.wheel.y %d zoom %f\n", event.wheel.y, zoom);

            }
            else if (event.type == SDL_WINDOWEVENT) {
                SDL_GetWindowSize(window, &window_width, &window_height);
                glViewport(0, 0, window_width, window_height);
            }
            if (event.type == SDL_KEYDOWN) {
                if ( event.key.keysym.sym == SDLK_m ) {
                    play_pause_audio(music);
                }
            }
        }

        // calculate planet positions
        for (int i=0; i<8; i+=1){

            x = xs[i]; y = ys[i];
            vx = vxs[i]; vy = vys[i];

            r = sqrt(x*x+y*y);
            a = G * mass_sun / (r*r); 
            angle = atan2(y,x);

            ax = -a * cos(angle);
            ay = -a * sin(angle);
            vx += ax * dt;
            vy += ay * dt;
            x += vx * dt;
            y += vy * dt;

            xs[i] = x; ys[i] = y;
            vxs[i] =vx; vys[i] = vy;
        }


        // draw stuff
        glClearColor( 0.f, 0.f, 0.f, 1.f );
        glClear(GL_COLOR_BUFFER_BIT);
        float sun_color[3] = {255,2115,9};
        glColor3f( sun_color[0]/255.0, sun_color[1]/255.0, sun_color[2]/255.0 );
        draw_polygon(0,0,0.1,100); // sun

        for (int i=0; i<8; i+=1){
            // scale values down for drawing 
            double draw_pos_x = xs[i] / 227900e6 * 0.5 * zoom;
            double draw_pos_y = ys[i] / 227900e6 * 0.5 * zoom;
            glColor3f( colors[i][0]/255.0, colors[i][1]/255.0, colors[i][2]/255.0 );
            draw_polygon( draw_pos_x, draw_pos_y, 0.005, 10 );
        }

        SDL_GL_SwapWindow(window);
        SDL_Delay(10); 
    }
    
}

int main()
{
    // simple_orbit_demo();
    // less_simple_orbit_demo();
    even_less_simple_orbit_demo();
    return 0;
}







// int a_failed_attempt_at_antialiasing(int ArgCount, char **Args)
// {

//     const int SCREEN_WIDTH = 1000;
//     const int SCREEN_HEIGHT = 1000;

//     uint32_t WindowFlags = SDL_WINDOW_OPENGL;
//     SDL_Window *Window = SDL_CreateWindow("OpenGL Test", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WindowFlags);
//     assert(Window);

//     SDL_GLContext Context = SDL_GL_CreateContext(Window);

//     //Set the viewport
//     glViewport( 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT );

//     //Initialize Projection Matrix
//     glMatrixMode( GL_PROJECTION );
//     glLoadIdentity();
//     glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0 );

//     //Initialize Modelview Matrix
//     glMatrixMode( GL_MODELVIEW );
//     glLoadIdentity();



//     //Initialize clear color
//     glClearColor( 0.f, 0.f, 0.f, 1.f );

//     //Enable texturing
//     glEnable( GL_TEXTURE_2D );

//     //Set blending
//     glEnable( GL_BLEND );
//     glDisable( GL_DEPTH_TEST );
//     glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

//     //Set antialiasing/multisampling
//     glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
//     glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
//     glDisable( GL_LINE_SMOOTH );
//     glDisable( GL_POLYGON_SMOOTH );
//     glDisable( GL_MULTISAMPLE );



        
//     //Clear color
//     glClear( GL_COLOR_BUFFER_BIT );

//             glDisable( GL_LINE_SMOOTH );
// 			glDisable( GL_POLYGON_SMOOTH );
// 			glEnable( GL_MULTISAMPLE );

//     //Render Triangle
//     glColor3f( 1.f, 1.f, 1.f );
//     glBegin( GL_TRIANGLES );
//     glVertex2f( SCREEN_WIDTH/2.f, 0.f );
//     glVertex2f( SCREEN_WIDTH, SCREEN_HEIGHT );
//     glVertex2f( 0.f, SCREEN_HEIGHT );
//     glEnd();

//     glColor3f( 1.f, 1.f, 1.f );
//     draw_polygon(100.f, 100.f, 100.f, 5);

//     //End alias mode
// 			glDisable( GL_MULTISAMPLE );

//     draw_polygon(500, 100, 100, 5);


//     // // render
//     // glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

//     // // draw background
//     // glClearColor(0.0f,0.0f,0.0f,1.0f);
//     // glClear(GL_COLOR_BUFFER_BIT);

//     // draw_polygon(-0.5, +0.5, 0.1, 100);

//     SDL_GL_SwapWindow(Window);






//     int32_t running = 1;
//     int32_t fullscreen = 0;
//     while (running) {
        
//         // handle events
//         SDL_Event event;
//         while (SDL_PollEvent(&event)){
//             if ( event.type == SDL_QUIT ) running = 0;
//         }

//         SDL_Delay(10);
//     }

//     return 0;
// }

