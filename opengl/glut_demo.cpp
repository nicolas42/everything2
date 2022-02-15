// g++ glut_demo.cpp -Wfatal-errors -framework OpenGL -framework GLUT && ./a.out


#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4505) // unreferenced local function has been removed
#endif

#include <stdio.h>




//Screen constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

//Color modes
const int COLOR_MODE_CYAN = 0;
const int COLOR_MODE_MULTI = 1;


//The current color rendering mode
int gColorMode = COLOR_MODE_CYAN;

//The projection scale
GLfloat gProjectionScale = 1.f;

bool initGL()
{
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0 );

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    return true;
}

void update()
{

}

void render()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );

    //Reset modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Move to center of the screen
    glTranslatef( SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f );

    //Render quad
    if( gColorMode == COLOR_MODE_CYAN )
    {
        //Solid Cyan
        glBegin( GL_QUADS );
            glColor3f( 0.f, 1.f, 1.f );
            glVertex2f( -50.f, -50.f );
            glVertex2f(  50.f, -50.f );
            glVertex2f(  50.f,  50.f );
            glVertex2f( -50.f,  50.f );
        glEnd();
    }
    else
    {
        //RYGB Mix
        glBegin( GL_QUADS );
            glColor3f( 1.f, 0.f, 0.f ); glVertex2f( -50.f, -50.f );
            glColor3f( 1.f, 1.f, 0.f ); glVertex2f(  50.f, -50.f );
            glColor3f( 0.f, 1.f, 0.f ); glVertex2f(  50.f,  50.f );
            glColor3f( 0.f, 0.f, 1.f ); glVertex2f( -50.f,  50.f );
        glEnd();
    }

    //Update screen
    glutSwapBuffers();
}

void handleKeys( unsigned char key, int x, int y )
{
    //If the user presses q
    if( key == 'q' )
    {
        //Toggle color mode
        if( gColorMode == COLOR_MODE_CYAN )
        {
            gColorMode = COLOR_MODE_MULTI;
        }
        else
        {
            gColorMode = COLOR_MODE_CYAN;
        }
    }
    else if( key == 'e' )
    {
        //Cycle through projection scales
        if( gProjectionScale == 1.f )
        {
            //Zoom out
            gProjectionScale = 2.f;
        }
        else if( gProjectionScale == 2.f )
        {
            //Zoom in
            gProjectionScale = 0.5f;
        }
        else if( gProjectionScale == 0.5f )
        {
            //Regular zoom
            gProjectionScale = 1.f;
        }

        //Update projection matrix
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( 0.0, SCREEN_WIDTH * gProjectionScale, SCREEN_HEIGHT * gProjectionScale, 0.0, 1.0, -1.0 );
    }
}


void runMainLoop( int val )
{
    //Frame logic
    update();
    render();

    //Run frame one more time
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, val );
}



int main( int argc, char* args[] )
{
    //Initialize FreeGLUT
    glutInit( &argc, args );

    //Create OpenGL 2.1 context
    // glutInitContextVersion( 2, 1 );

    //Create Double Buffered Window
    glutInitDisplayMode( GLUT_DOUBLE );
    glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
    glutCreateWindow( "OpenGL. Try pressing the 'e' or 'q' buttons" );

    //Do post window/context creation initialization
    if( !initGL() )
    {
        printf( "Unable to initialize graphics library!\n" );
        return 1;
    }

    //Set keyboard handler
    glutKeyboardFunc( handleKeys );

    //Set rendering function
    glutDisplayFunc( render );

    //Set main loop
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, 0 );

    //Start GLUT main loop
    glutMainLoop();

    return 0;
}

