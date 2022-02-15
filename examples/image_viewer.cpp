/*
macos:
g++ image_viewer.cpp -framework SDL2 -framework SDL2_image -std=c++11 && ./a.out

g++ image_viewer.cpp -Iinclude -framework SDL2 -framework SDL2_image -std=c++11 -Ofast -fPIC -Wall -Wpedantic -Wextra -Wvla -Wshadow -Wfatal-errors -fsanitize=address -g && ./a.out

g++ image_viewer.cpp -Iinclude -std=c++11 \
-Ofast -Wall -Wpedantic -Wextra -Wvla -Wshadow -Wfatal-errors -fPIC -fsanitize=address -g \
-framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_mixer \
&& ./a.out


linux:
g++ -ISDL2 -lSDL2 -lSDL2_image -std=c++11 image_viewer.cpp

windows:
call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
cl /Zi /I "win64\include\SDL2" "image_viewer.cpp" /link "win64\SDL2.lib" "win64\SDL2main.lib" "win64\SDL2_image.lib" "win64\SDL2_mixer.lib" "win64\SDL2_ttf.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:"win64\image_viewer.cpp.exe" && win64\play_audio.cpp.exe

*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <errno.h>
// #include <assert.h>

#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include <string>
#include <vector>


SDL_Rect make_rect(int x, int y, int w, int h)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
    return dest;
}

void find_files (const char * dir_name, std::vector<std::string> *output)
{
    /* this function is from lemoda.net */

    // std::vector<std::string> output;
    std::string buff = "";

    DIR * d;

    /* Open the directory specified by "dir_name". */

    d = opendir (dir_name);

    /* Check it was opened. */
    if (! d) {
        fprintf (stderr, "Cannot open directory '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
    while (1) {
        struct dirent * entry;
        const char * d_name;

        /* "Readdir" gets subsequent entries from "d". */
        entry = readdir (d);
        if (! entry) {
            /* There are no more entries in this directory, so break
               out of the while loop. */
            break;
        }
        d_name = entry->d_name;
        /* Print the name of the file and directory. */
	// printf ("%s/%s\n", dir_name, d_name);

    buff = "";
    buff += dir_name;
    buff += "/";
    buff += d_name;
    // buff += "\n";
    output->push_back(buff);

#if 0
	/* If you don't want to print the directories, use the
	   following line: */

        if (! (entry->d_type & DT_DIR)) {
	    // printf ("%s/%s\n", dir_name, d_name);

        buff = "";
        buff += dir_name;
        buff += "/";
        buff += d_name;
        // buff += "\n";
        output->push_back(buff);
	}

#endif /* 0 */


        if (entry->d_type & DT_DIR) {

            /* Check that the directory is not "d" or d's parent. */
            
            if (strcmp (d_name, "..") != 0 &&
                strcmp (d_name, ".") != 0) {
                int path_length;
                char path[PATH_MAX];
 
                path_length = snprintf (path, PATH_MAX,
                                        "%s/%s", dir_name, d_name);
                // printf ("%s\n", path);

                buff = "";
                buff += path;
                // buff += "\n";
                output->push_back(buff);


                if (path_length >= PATH_MAX) {
                    fprintf (stderr, "Path length has got too long.\n");
                    exit (EXIT_FAILURE);
                }
                /* Recursively call "find_files" with the new path. */
                find_files (path,output);
            }
	}
    }
    /* After going through all the entries, close the directory. */
    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }


}

// int list_dir_main (int argc, char **argv)
// {
//     // char *dir = argv[1]; // "/Users/nick/Downloads";
//     const char *dir = "/Users/nick/Downloads";

	// std::vector<std::string> files;
	// find_files("/Users/nick/Downloads", &files);
	// for (auto f : files) {
	// 	const char *extension = f.substr(f.find_last_of(".") + 1).c_str();
	// 	if (strcmp(extension, "jpg")==0) std::cout << f << std::endl;
	// 	// std::cout << extension << std::endl;
	// 	// std::cout << f << std::endl;
	// }
// }


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int is_dir(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
    // https://pubs.opengroup.org/onlinepubs/7908799/xsh/sysstat.h.html
}

std::vector<std::string> get_image_filenames (char *f)
{
    // get image filenames
    std::vector<std::string> filenames;
    if (!strcmp(f,"")) return filenames;

	const char *desired_extensions[] = {"jpg", "png", "bmp", "jpeg"};
	std::vector<std::string> all_filenames;

    if ( is_dir(f) ) { 
        find_files(f, &all_filenames); 
    } else {
        // assume it's an image file
        filenames.push_back(f);
    }

	for (auto f : all_filenames) {
		const char *extension = f.substr(f.find_last_of(".") + 1).c_str();
		for (auto desired_extension : desired_extensions ){
			if (strcmp(extension, desired_extension)==0) {
				filenames.push_back(f);
				// std::cout << f << std::endl;
				break;
			}
		}
	}
	for (auto i:filenames) std::cout << i << std::endl;
    return filenames;
    
}



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
    if ( event.type == SDL_MOUSEMOTION ) printf("SDL_MOUSEMOTION "); // no newline
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

void print_window_event(const SDL_Event * event)
{
    if (event->type == SDL_WINDOWEVENT) {
        switch (event->window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            SDL_Log("Window %d shown", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            SDL_Log("Window %d hidden", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_Log("Window %d exposed", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MOVED:
            SDL_Log("Window %d moved to %d,%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            SDL_Log("Window %d resized to %dx%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            SDL_Log("Window %d size changed to %dx%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            SDL_Log("Window %d minimized", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            SDL_Log("Window %d maximized", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            SDL_Log("Window %d restored", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_ENTER:
            SDL_Log("Mouse entered window %d",
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            SDL_Log("Mouse left window %d", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            SDL_Log("Window %d gained keyboard focus",
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            SDL_Log("Window %d lost keyboard focus",
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            SDL_Log("Window %d closed", event->window.windowID);
            break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            SDL_Log("Window %d is offered a focus", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_HIT_TEST:
            SDL_Log("Window %d has a special hit test", event->window.windowID);
            break;
#endif
        default:
            SDL_Log("Window %d got unknown event %d",
                    event->window.windowID, event->window.event);
            break;
        }
    }
}



double min(double a, double b)
{
    if (a<b) return a;
    return b;
}

void show_using_surfaces( SDL_Window *window, std::vector<std::string> filenames, int filenames_index ) 
{
    if (filenames.size() == 0) return;
    std::cout << "show: " << filenames[filenames_index] << std::endl;

    SDL_Surface *window_surface = SDL_GetWindowSurface( window );
    SDL_Surface* image_surface;
    SDL_Surface *optimised_image_surface;

    // set title to filename
    SDL_SetWindowTitle(window, filenames[filenames_index].c_str());

    // optimise image
    image_surface = IMG_Load( filenames[filenames_index].c_str() );
    if(!image_surface) { 
        printf("ERROR %s %d %s\n", __FILE__, __LINE__, SDL_GetError());
        return;
    }

    optimised_image_surface = SDL_ConvertSurface( image_surface, window_surface->format, 0 );
    SDL_FreeSurface(image_surface);

    // draw optimised
    SDL_FillRect(window_surface, NULL, SDL_MapRGB(window_surface->format, 0, 0, 0));

    // resize to fit inside window
    double width_scaler = ((double)window_surface->w) / ((double)image_surface->w);
    double height_scaler = ((double)window_surface->h) / ((double)image_surface->h);
    double scaler = min(width_scaler, height_scaler);
    
    SDL_Rect image_size;
    image_size.w = (int)(scaler * image_surface->w);
    image_size.h = (int)(scaler * image_surface->h);
    image_size.y = (window_surface->h - image_size.h)/2;
    image_size.x = (window_surface->w - image_size.w)/2;

    SDL_BlitScaled( optimised_image_surface, NULL, window_surface, &image_size );
    SDL_FreeSurface(optimised_image_surface);
    SDL_UpdateWindowSurface( window );
    
}

void show_using_renderer( SDL_Window *window, std::vector<std::string> filenames, int filenames_index ) 
{
    if (filenames.size() == 0) return;
    std::cout << "show: " << filenames[filenames_index] << std::endl;
    SDL_SetWindowTitle(window, filenames[filenames_index].c_str());

    SDL_Renderer *renderer = SDL_GetRenderer(window);

    SDL_Surface* image = IMG_Load( filenames[filenames_index].c_str() );
    if(!image) { 
        printf("ERROR %s %d %s\n", __FILE__, __LINE__, SDL_GetError());
        return;
    }
	SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, image );
    if (!texture) { 
        printf("ERROR %s %d %s\n", __FILE__, __LINE__, SDL_GetError());
        return;
    }

    int w,h;
    SDL_GetWindowSize(window, &w, &h);

    // resize to fit inside window
    double width_scaler = ((double)w) / ((double)image->w);
    double height_scaler = ((double)h) / ((double)image->h);
    double scaler = min(width_scaler, height_scaler);
    
    SDL_Rect image_size;
    image_size.w = (int)(scaler * image->w);
    image_size.h = (int)(scaler * image->h);
    image_size.y = (h - image_size.h)/2;
    image_size.x = (w - image_size.w)/2;


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, NULL);

    SDL_RenderCopy( renderer, texture, NULL, &image_size );
    SDL_RenderPresent( renderer );
    
}


int main( int argc, char* argv[] )
{
    int window_width = 800;
    int window_height = 800;
	bool time_to_quit = false;
	bool is_fullscreen = false;


	SDL_Window* window;
	SDL_Event event;
	SDL_Init( SDL_INIT_VIDEO );
	IMG_Init( IMG_INIT_PNG & IMG_INIT_JPG );
	window = SDL_CreateWindow( "Drag a directory onto the window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE ); 

    const int use_renderer = 1;

    void (*show)( SDL_Window *window, std::vector<std::string> filenames, int filenames_index );
    if (use_renderer) {
        // An SDL_Renderer and a window_surface can not live in the same universe.  They are like antimatter.
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        show = show_using_renderer;
    } else {
        show = show_using_surfaces;
    }
    // 

    SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

    std::vector<std::string> filenames;
    int filenames_index;
    char* dropped_filename;


    // terminal
   	char *dir = (char*)"";
	// char *dir = (char*)"/Users/nick/Downloads";

    // if (argc == 1) printf("show_images <dir>\n");
	// if (argc==2){
	// 	dir = argv[1];
	// }
    
    filenames = get_image_filenames(dir);
	filenames_index = 0;
	show( window, filenames, filenames_index );

    bool do_show = false;
    while (!time_to_quit)
    {
        // SDL_WaitEvent(&event);
        while( SDL_PollEvent(&event) ) { 
            // print_event(event);


            if (event.type == SDL_DROPFILE) {
                dropped_filename = event.drop.file;
                filenames = get_image_filenames(dropped_filename);
                filenames_index = 0;
                do_show = true;

                SDL_free(dropped_filename);    // Free dropped_filename memory
            }

            if (event.type == SDL_QUIT) {
                time_to_quit = true;
            }

            if (event.type == SDL_WINDOWEVENT) {
                // printf("window event %d\n", (int)(event.window.event) );
                if ( 
                    event.window.event == SDL_WINDOWEVENT_RESIZED || 
                    event.window.event == SDL_WINDOWEVENT_MINIMIZED || 
                    event.window.event == SDL_WINDOWEVENT_MAXIMIZED || 
                    event.window.event == SDL_WINDOWEVENT_RESTORED
                ){
                    print_window_event(&event);
                    printf("omg show\n");
                    do_show = true; 
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                filenames_index += 1;
                if ( filenames_index >= filenames.size() ) filenames_index = 0;
                do_show = true;
            }

            if (event.type == SDL_KEYDOWN) {

                if ( event.key.keysym.sym == SDLK_RIGHT ) {
                    filenames_index += 1;
                    if ( filenames_index >= filenames.size() ) filenames_index = 0;
                    do_show = true;
                }

                if ( event.key.keysym.sym == SDLK_LEFT ) {
                    filenames_index += -1;
                    if ( filenames_index < 0 ) filenames_index = filenames.size()-1;
                    do_show = true;
                }
                
                if ( event.key.keysym.sym == SDLK_f ) {
                    SDL_SetWindowFullscreen( window, SDL_WINDOW_FULLSCREEN_DESKTOP );
                }

                if ( event.key.keysym.sym == SDLK_ESCAPE ) {
                    SDL_SetWindowFullscreen(window, 0);
                }
            }
        }


        if (do_show) show( window, filenames, filenames_index );
        do_show = false;
        SDL_Delay(10);

    }

	// SDL_FreeSurface( window_surface );
	// SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}



// SDL_Log("Window %d resized to %dx%d",
//     event.window.windowID, event.window.data1,
//     event.window.data2);
// window_width = event.window.data1;
// window_height = event.window.data2;
