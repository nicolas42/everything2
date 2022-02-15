http://www.opengl-tutorial.org/print/#how-do-i-create-a-quaternion-in-glsl-

Incompatible GPU/OS
Please check if you have an Intel card. You can do so using glewinfo, GPU Caps Viewer, or any other tool.
Intel cards, except recent HD4000, don’t support OpenGL 3.3. As a matter of fact, most only support OpenGL 2.1. You have to download the 2.1 version from the Downloads page instead.
The other possible reason is that you’re on a Mac, with a pre-Lion (10.7) version. Same stuff applies…



SDL and opengl
-----------------------

The imgui code seems to be the best stuff to take examples from, generally speaking, for graphical
2D code. Specifically in my case, the sdl_opengl3 stuff.  I'm not sure what version of opengl I'm currently using
but I'm afraid that it might be version 2.0.


Without this flag, my high DPI display uses pixel doubling when rendering my opengl demo.  So I imagine
that the width and height of the window are half of what they would be.  There may be some kind of 
window event that occurs when moving between normal and high DPI displays.

 | SDL_WINDOW_ALLOW_HIGHDPI




Turns out antialiasing in SDL is as simple as putting these two lines before SDL_GL_CreateContext

SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
SDL_GLContext Context = SDL_GL_CreateContext(Window);

I found antialiasing My testing with lazyfoo antialiasing and multisampling doesn't work on macos 10.12.




Opengl in SDL seems to be set to sync with the refresh rate of the monitor?
To set an update rate different from the default, the following function must be called.
SDL_GL_SetSwapInterval(0); // 0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive vsync


#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else 
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif




Predefined macros for OS
-------------------------------------
from https://stackoverflow.com/questions/142508/how-do-i-check-os-with-a-preprocessor-directive

The Predefined Macros for OS site has a very complete list of checks. Here are a few of them, with links to where they're found:
Predefined Macros for OS site: https://sourceforge.net/p/predef/wiki/OperatingSystems/


Windows

_WIN32   Both 32 bit and 64 bit
_WIN64   64 bit only
__CYGWIN__

Unix (Linux, *BSD, but not Mac OS X)

See this related question on some of the pitfalls of using this check.

unix
__unix
__unix__

Mac OS X

__APPLE__ Also used for classic
__MACH__

Both are defined; checking for either should work.

Linux

__linux__
linux Obsolete (not POSIX compliant)
__linux Obsolete (not POSIX compliant)

FreeBSD

__FreeBSD__

Android

__ANDROID__





Links

https://github.com/JoeyDeVries/LearnOpenGL

https://en.wikipedia.org/wiki/Kinetic_theory_of_gases
http://www.hunter.cuny.edu/physics/courses/physics110/repository/files/section51/15TheKineticTheoryofGasesRev2.pdf

https://www.youtube.com/watch?v=f08Y39UiC-o stress in beams


#Tkinter 

In macos, the default tkinter version has proper bugs.
I literally can't close a tkinter window properly


#Rebol

Rebol faces would be a good starting point for general interface design

http://www.rebol.com/docs/view-face-content.html



More c compiler error fun
------------------------------
Getting string type checking like golang seems to be a losing battle unless you write all the code.
C code just isn't written with explicity type conversions.

-Wsign-conversion
-Wconversion
-W-float-conversion

Wlots="-Weverything -Wno-missing-prototypes -Wno-old-style-cast -Wno-double-promotion -Wno-cast-align -Wno-reserved-id-macro -Wno-comma"


STBIMG_Load
--------------------------------
STBIMG_Load is a dropin replacement for SDL's IMG_Load() function.
Use it like this.


#define SDL_STBIMAGE_IMPLEMENTATION
#include "src/SDL_stbimage.h"

SDL_Surface* surface = STBIMG_Load( "data/button.png" );




#Make 
-----------------------------------------------------

Make seems like cleaned up shell script.


Makefile symbols 

from https://stackoverflow.com/questions/3220277/what-do-the-makefile-symbols-and-mean

$@ is the name of the target being generated, and $< the first prerequisite (usually a source file). 
You can find a list of all these special variables in the GNU Make manual.

For example, consider the following declaration:

all: library.cpp main.cpp

In this case:

    $@ evaluates to all
    $< evaluates to library.cpp
    $^ evaluates to library.cpp main.cpp




To get the terminal commands from a make file, redirect standard error to /dev/null 

    make 2>/dev/null 


make -j uses multiple processes to compile a project
However, it causes errors when making SDL, so it might be unreliable.





BUG: Unix terminals insert random characters in paste streams
-----------------------------------------------------------
Macos terminal inserts random character into terminal when pasting code.
This has happened in linux too.
This time it was different characters always at the same place. 
I have a feeling that it's because the previous process somehow writes to stdin.




Don't learn glut :)
----------------------
There's a message in imgui telling me not to learn glut lol

// !!! GLUT/FreeGLUT IS OBSOLETE PREHISTORIC SOFTWARE. Using GLUT is not recommended unless you really miss the 90's. !!!
// !!! If someone or something is teaching you GLUT today, you are being abused. Please show some resistance. !!!
// !!! Nowadays, prefer using GLFW or SDL instead!





BUG: AddressSanitizer causes my program to crash
------------------------------------------------------

-fsanitize=address causes the image_viewer program to crash o_o .  

Reproduce:
g++ image_viewer.cpp -Iinclude -framework SDL2 -framework SDL2_image && ./a.out  => fine 
g++ image_viewer.cpp -Iinclude -framework SDL2 -framework SDL2_image -fsanitize=address && ./a.out   => crashes on drag and drop of folder 

Perhaps it's due to this 

HINT: this may be a false positive if your program uses some custom stack unwind mechanism or swapcontext
      (longjmp and C++ exceptions *are* supported)


Details of faddress error output 

==28193==ERROR: AddressSanitizer: stack-use-after-scope on address 0x7fff5add0551 at pc 0x000105010f26 bp 0x7fff5add0370 sp 0x7fff5adcfb00
READ of size 1 at 0x7fff5add0551 thread T0
    #0 0x105010f25 in wrap_strcmp (libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x15f25)
    #1 0x104e3199e in get_image_filenames(char*) image_viewer.cpp:192
    #2 0x104e34824 in main image_viewer.cpp:471
    #3 0x7fffbba6c234 in start (libdyld.dylib:x86_64+0x5234)

Address 0x7fff5add0551 is located in stack of thread T0 at offset 465 in frame
    #0 0x104e3132f in get_image_filenames(char*) image_viewer.cpp:174

  This frame has 7 object(s):
    [32, 40) 'ref.tmp.i'
    [64, 208) 'path_stat.i' (line 167)
    [272, 296) 'all_filenames' (line 180)
    [336, 360) 'ref.tmp' (line 186)
    [400, 424) 'f7' (line 189)
    [464, 488) 'ref.tmp9' (line 190) <== Memory access at offset 465 is inside this variable
    [528, 552) 'i' (line 199)
HINT: this may be a false positive if your program uses some custom stack unwind mechanism or swapcontext
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-use-after-scope (libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x15f25) in wrap_strcmp




SQLite amalgamation 
--------------------------------

SQLite is distributed as 

"an amalgamation of many separate C source files from SQLite
version 3.37.1.  By combining all the individual C code files into a
single large file, the entire code can be compiled as a single translation
unit.  This allows many compilers to do optimizations that would not be
possible if the files were compiled separately.  Performance improvements
of 5% or more are commonly seen when SQLite is compiled as a single
translation unit."



Assembly
------------------------------

It appears like the best way to use assembly is through a regular compiler like gcc or msvc.
Trying to do it piecemeal with various assemblers makes linking a nightmare.
However msvc and gcc use very different inline assembly syntax.  The SDL code has examples.

Inline assembly in GCC docs
https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html
https://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html




------------------------------------------------------------


SDL_SetRenderTarget(renderer, content);


Opengl 
https://openglbook.com/


gcc opengl3_hello.c `sdl2-config --libs --cflags` -lGL -Wall && ./a.out



Dynamic linking occurs at runtime.


In c/c++, a trailing f tells the compiler that the number is a float rather than a double as it would otherwise assume.
0.9f

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


Notes on C++ Classes
-------------------------------

* classes are the same as structs except their data is private by default
* function pointers are not stored within the struct, they're put somewhere else to save space.
* methods can be defined inside or outside of the class but prototypes are always required inside the class definition
* C++ bool is the same as an int.
* public: and private: labels can be used to specify the visibility of elements in a class which can 
enforce the usage of standard interfaces. 

* constructors combine declaration and allocation, and destructors are automatically
called at the end of scope.  However, I typically want it to be more, not less clear when 
memory is allocated and deallocated.

Cout can be used with a virtual method to make printing look slightly nicer, but that's a bit weird.

Ultimately serialization and deserialization is one thing that it makes sense to put as a method, really.



Implementing a simple GUI with c++ methods made it a bit clearer why methods
often comes bearing global variables.  C++ method style is to replace 
c-style functions, usually with loads of arguments, with C methods that have few. 
A C++ method can be made that takes many arguments like C-style but then the question 
naturally arises as to what the benefit is of pretending like there's a function pointer 
in the struct in the first place.

If a method relies on global variables I think it's an indication that the code probably 
wants to be an old-fashioned function instead.


There's data hiding, which enforces the use of standard interfaces, which could be useful.


    // C++ style requires globals
    // now it's a little clearer why everyone uses them.

    SDL_Texture *textures[4];
    enum { MOUSEOUT, MOUSEOVER, MOUSEDOWN, MOUSEUP };
    SDL_Renderer *renderer;

    struct Face { 
        SDL_Rect r;
        SDL_Texture *texture;
        void render()
        {
            SDL_RenderCopy(renderer, texture, NULL, &r );
        }
        void handle(SDL_Event event)
        {
            int mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            if ( !is_inside( mouse_x, mouse_y, r ) ) {
                texture = textures[MOUSEOUT];
            } else {
                if ( event.type == SDL_MOUSEMOTION ) texture = textures[MOUSEOVER];
                if ( event.type == SDL_MOUSEBUTTONUP ) texture = textures[MOUSEUP];
                if ( event.type == SDL_MOUSEBUTTONDOWN ) texture = textures[MOUSEDOWN];
            } 
        }
    };





How to disable the crash dialog from terminal applications in macos
-----------------------------------------------------------------------------

To disable the dialog, enter the following command in the Terminal:

    defaults write com.apple.CrashReporter DialogType none

Enable crash dialog

defa    ults write com.apple.CrashReporter DialogType prompt

https://www.loekvandenouweland.com/content/disable-python-quit-unexpectedly.html




Building SDL faster
-----------------------------
Experiment in trying to amalgamate source for faster builds from source.
SDL has its own standard library implementations for things like malloc, math, qsort.

Basically I was able to get everything working except the video stuff.

// rm *.o 

// for f in src src/atomic src/audio/coreaudio src/core src/core/unix src/cpuinfo src/dynapi src/events src/file src/file/cocoa src/filesystem src/filesystem/cocoa src/filesystem/unix src/haptic src/hidapi src/joystick src/joystick/darwin src/libm src/loadso src/locale/macosx src/main src/misc src/misc/macosx src/power src/power/macosx src/render src/render/opengl src/sensor src/stdlib src/test src/thread src/timer src/timer/unix src/video src/video/cocoa src/video/x11 src/video/khronos/EGL 
// do 
//     if [ ! -z "$(ls $f/*.c 2>/dev/null)" ] 
//     then 
//         echo $f
//         gcc -c $f/*.c -Isrc/include -Iinclude  -Isrc -Isrc/hidapi/hidapi -Isrc/video -Isrc/video/cocoa 
//     fi
// done 

// ar rcs lib.a *.o 
// gcc src/mystuff/main.c lib.a -Iinclude -Isrc/include && ./a.out



#include <stdio.h>

double SDL_uclibc_atan(double x);
double SDL_uclibc_atan2(double y, double x);    
double SDL_uclibc_copysign(double x, double y);       
double SDL_uclibc_cos(double x);         
double SDL_uclibc_exp(double x);
double SDL_uclibc_fabs(double x);        
double SDL_uclibc_floor(double x);
double SDL_uclibc_fmod(double x, double y);
double SDL_uclibc_log(double x);
double SDL_uclibc_log10(double x);
double SDL_uclibc_pow(double x, double y);    
double SDL_uclibc_scalbn(double x, int n);
double SDL_uclibc_sin(double x);
double SDL_uclibc_sqrt(double x);
double SDL_uclibc_tan(double x);


int main()
{
    printf("omgomg %f\n", SDL_uclibc_sqrt(0.234) );
    return 0;
}





file descriptors
---------------------------

Input-output system calls in C | Create, Open, Close, Read, Write
* https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
* https://en.wikipedia.org/wiki/File_descriptor
* https://beej.us/guide/bgipc/html/multi/mmap.html


Limited HTML markup can be inserted directly into markdown files, have only tested IMG, A, and HR tags.


links

* https://github.com/veandco/go-sdl2
* https://github.com/felix-pb/cpu_caches
* https://beej.us/guide/bgipc/html/multi/mmap.html



Learn about

* file descriptors, memory mapped files
* how to use emscripten to generate webassembly
* compare and swap for concurrency


* batch rename program
* n-body simulation in SDL.
* render a triangle in openGL



To Do / Ideas
--------------------------------
OS 

Extend the OS so that it can use more memory.  Currently the bootloader can only read three pages of 512 bytes of code.  Why?  Plus there are truly weird things that happen if I try to allocate more than 300*300 pixels.  I guess because the data is displacing code???

stripe

implement payment processing system using stripe
https://github.com/stripe-samples/accept-a-payment/tree/main/prebuilt-checkout-page


file system

Make a "file system" - storing many files in one file, in a particular format


SDL GUI
* make a button
* basic text editing
* archie quasimode leap interface :)


Make networked chat program
* modify netcat so it automatically listens if an initial connection attempt fails

Netcat can currently be used as an instant messenger like this

    ./a.out -l 127.0.0.1 3490
    ./a.out 127.0.0.1 3490


html wiki  
* creates,edits html pages - done
* sha1 version control, files stored like YYYYMMDD_<fixed_length_hash>_filename

Basic file sharing program

like https://wormhole.app/




#Awesome
-------------------------------------------


* SDL_stbimage.h  This single header file allows stb_image.h to be used easily with SDL code.
        https://github.com/DanielGibson/Snippets/blob/master/SDL_stbimage.h

* pl_mpeg mpeg1 player https://github.com/phoboslab/pl_mpeg
    pl_mpeg is an mpeg_1 video player that uses SDL and opengl.  
    File sizes seem to be 2-3 times bigger than usual.
* netcat https://github.com/guzlewski/netcat
* suckless http://dwm.suckless.org/
* aes https://github.com/kokke/tiny-AES-c
* beej's guide to network sockets http://beej.us/guide/bgnet/html/
* single file libraries in C/C++  https://github.com/nothings/single_file_libs
* sqlite https://sqlite.org/ is an SQL engine that is released as an amalgamated (single) c file.  I love them so much.
* busybox https://github.com/mirror/busybox/
* lemoda.net https://www.lemoda.net/  lots of C and other code

* How 3D video games do graphics - Jonathan Blow https://youtu.be/bGe-d09Nc_M?t=3600
* Mr P Solver https://www.youtube.com/c/MrPSolver/videos
* Tired Amateur https://www.youtube.com/channel/UCeT6NdimLKHXlkQgrbcg6XQ
* jdh - made bootable tetris https://www.youtube.com/channel/UCUzQJ3JBuQ9w-po4TXRJHiA

* ganga.js  geometric algebra in javascript and other languages
* three.js  javascript 3d graphics
* http://underscorejs.org/  seems like a good javascript library

* electron quick start https://github.com/electron/electron-quick-start

* handmade hero
* imgui   small c++ GUI library
* stb
* darknet
* uwimg
* nanogui-sdl
* wyoos
* mkernel
* exfat
* fasm - good community
* fabrice bellard - made FFmpeg, QEMU, and the Tiny C Compiler







-------------------------------------------------------------------
#C/C++ Programming, #GCC #Clang #C 
-------------------------------------------------------------------

The details of a c compiler can be found like this 

g++ -dM -E -x c++  /dev/null

This works for clang, gcc, and g++

source: https://stackoverflow.com/questions/44734397/which-c-standard-is-the-default-when-compiling-with-g



Notable compiler options
---------------------------------

    -Wall               more errors 
    -Wpedantic          more errors 
    -Wextra             also more errors?

    -Werror             make warnings errors

    -Wfatal-errors      stop at the first error
    -Wvla               warn about c99 variable length arrays 
    -Wshadow            warn when a local variable replaces a variable in a higher scope. 
                        This is good for catching nested for loops that use the same variable, e.g. 'i'.
                        Programming in a c89 style avoids this error, basically.

    -fPIC               position independent code. relative jumps are generated rather than absolute ones.  
                        code can be loaded into memory without recalculating jump addresses

    -fsanitize=address  print out run-time errors in cryptic hex-speak
    -g                  include debug info  

    -Ofast              make it fast 




Clang's -Weverything is kind of awesome.  

    -Weverything -Wno-missing-prototypes -Wno-old-style-cast -Wno-double-promotion




Stack size limitations:

I'm going to assume that a reasonably cross platform stack size is 1MB.  Apparently this is how much it is on windows.  Incidentally it's 8MiB on my laptop.  source: https://softwareengineering.stackexchange.com/questions/310658/how-much-stack-usage-is-too-much



Lessons learnt from turning on all compiler warnings
----------------------------------------------------

There was one legitimate bug found where a nested for loop was using the same variable 'i'.
I'm surprised I didn't notice it.  The -Wshadow warning finds this kind of thing.

There were a lot of type and sign type warnings, particularly comparing integers and size_t.
On my system size_t is basically uint64_t.  I often do a for loop over an array of some particular size.  This compares a signed int32_t with a uin64_t.

Amusing overflows:
In c, integer literals are assumed to be integers and decimal numbers are assumed to be doubles.
So using floats with number literals combines floats and doubles.  And doing mathematics with integer literals
suffers overflows over about 2 billion.


Perhaps -Wconversion is a good idea.  C doesn't make a fuss when a 64 bit number is assigned to an 8 bit number without a cast.
o_o 



#C89 can be specified basically without a standard library.
-------------------------------------------------------------

C89 allows two types of compilers: hosted and freestanding. The basic difference is that a 
hosted compiler provides all of the C89 library, while a freestanding compiler need only 
provide <float.h>, <limits.h>, <stdarg.h>, and <stddef.h>. If you limit yourself to these headers, 
your code will be portable to any C89 compiler.


#AR 
-----------------------------------------------

The 'ar' archive? tool can be used to combine object files.

    ar rcs lib.a object1.o object2.o object3.o ...

Afterwards the single .a file can be linked to the project like this
    
    gcc main.c lib.a 





#XCode doesn't allow pointers to be cast to smaller values
---------------------------------------------------------------

This is annoying since void pointers are used to represent all types. :(

    error: cast from pointer to smaller type 'int' loses
        information
        for(i=0;i<100;++i) printf("%d ", (int)arr4.data[i]);
                                        ^~~~~~~~~~~~~~~~~

The solution is to do two casts like this.  :((((((((((

    (int)(u64)arr4.data[i]

This behaviour is only seen in the c++ compiler.  sigh... 

more info: 
https://stackoverflow.com/questions/22419063/error-cast-from-pointer-to-smaller-type-int-loses-information-in-eaglview-mm/28987357



Joining strings in a #macro 
------------------------------

The token ## joins two strings in a macro

TYPENAME ## _array => TYPENAME_array


#std::vector is slow
----------------------------------------------

std::vector was almost 3 times slower than a 10 line expanding array implementation. Optimising with -Ofast didn't make any difference.


#Endianness
--------------------------------------


Pointers point to the first byte of a 'type'. A 'type' occupies that byte and possibly bytes to the right of it.
Most modern systems are little endian, meaning that the bytes are stored in the reverse order to how numbers are 
usually written.  

    The two integers 01020304 01020304 
    are represented in memory as 04 03 02 01 04 03 02 01 

Little endianness has the benefit that a value is independent of its type size.  That is to say 
because bytes are stored from left to right, its value doesn't change if the type size is
increased.

https://uynguyen.github.io/2018/04/30/Big-Endian-vs-Little-Endian/
https://stackoverflow.com/questions/57154009/how-do-pointers-reference-multi-byte-variables




Endianness in SDL and stb
--------------------------------------

The *INTEGER* rgba is stored in memory as abgr in little-endian systems, 
however a byte array is stored exactly as it appears in the program.

So, when casting an array from bytes to integers or vice versa, one has 
to take care.

SDL functions operate on images as a series of integers whereas 
stb image functions operate on the data as a series of bytes 




Header only libraries
----------------------------------------------

A header only library of the sort used by the stb library works by only 
including implementation of a header library if a particular define is set.
Usually it's called XX_IMPLEMENTATION.  The idea being that the header file 
can still be used normally.  Importantly in *ONE* file and only one file 
the previously mentioned define is set.  And that is the file that actually
includes the implementation.


Only define BASIC_IMPLEMENTATION in *ONE* file, like this.

    #define BASIC_IMPLEMENTATION
    #include "basic.h"


The header only file will look like this.  In addition to header guards to 
prevent multiple includes, there is an ifdef on BASIC_IMPLEMENTATION.
There's also a header guard for the implementation, because why not.



A header only file should look like this 


    #ifndef BASIC_HEADER_GUARD
    #define BASIC_HEADER_GUARD


    .......


    #endif // BASIC_HEADER_GUARD
    #ifdef BASIC_IMPLEMENTATION
    #ifndef BASIC_IMPLEMENTATION_GUARD
    #define BASIC_IMPLEMENTATION_GUARD


    .......


    #endif // BASIC_IMPLEMENTATION_GUARD 
    #endif // #ifdef BASIC_IMPLEMENTATION



source: https://github.com/nothings/stb/blob/master/docs/stb_howto.txt



#Windows and #Visual Studio
----------------------------------------------------------------------------------------

Calling visual studio from the command line (cl) requires a script be run beforehand.
It's called vcvarsall.bat and it moves around every new version so you'll have to find it.
It's buried somewhere in the visual studio folder, which itself will change. yay :)

Here are the commands from the last time that I used them.

    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    cl /Zi /MD main.c


source: https://hero.handmade.network/forums/code-discussion/t/2691-day_001_with_visual_studio_2017

An example with linking 

    cl /Zi /I "win64\include" "%1" /link "win64\SDL2.lib" "win64\SDL2main.lib" "win64\SDL2_image.lib" "win64\SDL2_mixer.lib" "win64\SDL2_ttf.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:"win64\%1.exe"

Example from imgui

    mkdir Debug
    cl /nologo /Zi /MD /I .. /I ..\.. /I "%WindowsSdkDir%Include\um" /I "%WindowsSdkDir%Include\shared" /I "%DXSDK_DIR%Include" /D UNICODE /D _UNICODE *.cpp ..\imgui_impl_win32.cpp ..\imgui_impl_dx10.cpp ..\..\imgui*.cpp /FeDebug/example_win32_directx10.exe /FoDebug/ /link /LIBPATH:"%DXSDK_DIR%/Lib/x86" d3d10.lib d3dcompiler.lib
    del *.pdb *.ilk *.obj 



Setting the PATH environmental variable in windows
-------------------------------------------------------
SET PATH=%PATH%;c:\users\nick\bin



Cross platform defines
---------------------------------------------------

Cross platform defines can be used to make portable code using the c preprocessor.

    #ifdef _SUNOS
    //code
    #elseif _LINUX
    //code
    #elseif _HPUX
    //code
    #elseif _WIN32
    //code
    #else
    #error OS not supported
    #endif






#Linking
-------------------------------------------------------------------------

Macos uses -framework

   g++ main.cpp -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_net -framework SDL2_ttf


Linux uses -l<lib name> where the library name is the filename without its "lib" prefix 
and without its file extension.  

    g++ main.cpp -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf


pkg-config is a useful utility that gives the linking flags that are required for different libraries, if they're more complicated.
It can also output the flags necessary to statically link libraries, which is cool.

    pkg-config --libs sdl2 opengl





#Beej's Guide to C Programming 
-------------------------------------------------------------------

from https://beej.us/guide/bgc/html/


7.4 String Initializers
---------------------------------

Importantly, in c, initializing a string as a pointer is interpreted 
as a pointer directly to the string literal.  And string literals apparently are immutable.  
However if the string is declared as an array, char s[] = 'string', then the program includes 
a pointer to a COPY of the string literal which is mutable.  
So basically 

char *s = "immutable"; !!!!!!!!
char s[] = "mutable";

Attempting to change an immutable string will result in the program crashing, which I have done many times.



16.1.1.1 const and Pointers
---------------------------------

Const makes things unmodifiable but it's a little confusing how the keyword actually works.  The general rule appears to be that const applies to the operator to its left.
But, if it's the leftmost token then it applies to the type on the right (this is the most common way that it's used actually).

Both of these examples result in the content itself being unmodifiable.

    const int *p;  // Can't modify what p points to
    int const *p;  // Can't modify what p points to, just like the previous line

A constant pointer is made like this.

    int *const p;   // We can't modify "p" with pointer arithmetic
    p++;  // Compiler error!

Both 

    const int *const p;  // Can't modify p or *p!

Multiple levels of indirection

    char *const *const p;
    p++;     // Error!
    (*p)++;  // Error!






C Operator Precedence
-------------------------------------------------------------------------

How am I supposed to remember this?  It's better just to use parentheses.
from https://en.cppreference.com/w/c/language/operator_precedence






ctype.h
--------------------------------

This library checks whether characters are in particular sets including 
whitespace, alphanumeric, numeric, alpha (a-z), printable, punctuation, hexidecimal,
upper or lowercase, and printable.  It also converts uppercase and lowercase letters
into one another.

#include <ctype.h>

isalpha isalphanum isdigit islower isupper isspace tolower toupper isxdigit, and others

all take an integer 














#VSCode sane ctrl+tab functionality
-------------------------------------
    // ctrl+` pulls up terminal
    // Place your key bindings in this file to override the defaults
    [
        // ...
        {
            "key": "ctrl+tab",
            "command": "workbench.action.nextEditor"
        },
        {
            "key": "ctrl+shift+tab",
            "command": "workbench.action.previousEditor"
        },
    ]





#Emacs
--------------------
in file explorer
   g refreshes page
   d selects files for deletion, 
   x deletes files
   undo deletion marks with the regular undo
   ~ selects ~ files for deletion
   The token # selects # files for deletion
   
m-x (un)comment-region




What is a "block device"
------------------------------
It appears the main distinction is between a "character device" where a single character can be read
versus a "block device" where only a block of information can be read, comprising multiple bytes,
like a 512 byte sector.
https://unix.stackexchange.com/questions/259193/what-is-a-block-device





#Python
---------------------------------------------------------------

make an executable

    pyinstaller --onefile --hidden-import=configparser script.py

--one-file seems to be slower than not, but it is more convenient


python SSL
-----------------
Okay for some reason I had to do this to make python SSL work on my old macos

    /Applications/Python\ 3.9/Install\ Certificates.command

https://stackoverflow.com/questions/27835619/urllib-and-ssl-certificate-verify-failed-error




#Cryptography
-----------------------

RSA (Rivest–Shamir–Adleman) is a public-key cryptosystem that is widely used for secure data transmission. 

Diffie Helman: 
RSA DH is an asymmetric algorithm used to establish a shared secret for a symmetric key algorithm.




Network Socket Programming #sockets
--------------------------------------------

    SERVER          CLIENT
    socket()        socket()
    bind()          
    listen()        
    accept()   <-   connect()
    recv()     <-   send()
    send()     ->   recv()
    close()    <-   close()

Can both parties be made symmetrical?
Could they both start as clients and then 
if they can't connect to the other then start as a server 
and wait for an incoming connection.





------------------------------------------------------------------
#MacOS
------------------------------------------------------------------

Making a macos .app application
----------------------------------------
Create a folder named "YourApplication.app". 
Put your script file directly in this folder.  Its name must be the same name as the application folder 
but without extension. In the case described here the script file must be named "YourApplication".
https://apple.stackexchange.com/questions/224394/how-to-make-a-mac-os-x-app-with-a-shell-script

My script didn't run when it attempted to access terminal input like argc or argv.


Show/hide hidden files in macos
-------------------------------------------
In Finder, open up your Macintosh HD folder. Press Command+Shift+Dot. Your hidden files will become visible. Repeat step 2 to hide them again



Alert from macos terminal 
--------------------------

Put this after a long command to be alerted when it's done.

osascript -e 'tell app "System Events" to display dialog "Hello World"'

source: https://stackoverflow.com/questions/5588064/how-do-i-make-a-mac-terminal-pop-up-alert-applescript








#Lorem Ipsum 
----------------------

This passage is commonly used so text content doesn't distract from design.

"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."

source https://www.lipsum.com/



#Git tricks
-------------------

Remove all files from staging area 

    git reset

Clone a repo with ssh 

    git clone git@github.com:username/repo





Resize and center an image
-----------------------------

To fit an image box inside another box while maintaining its aspect ratio it can be scaled (multiplied)
by the minimum ratio of the (max_width / image_width) or the (max_height / image_height).

    var scaler = Math.min(canvas.width / img.naturalWidth, canvas.height / img.naturalHeight);
    img_size = { width: img.naturalWidth*scaler, height: img.naturalHeight*scaler };

    offset_y = (canvas.height - img_size.height)/2;
    offset_x = (canvas.width - img_size.width)/2;



Regular Expressions #regex
----------------------------

    abc…	Letters
    123…	Digits
    \d	Any Digit
    \D	Any Non-digit character
    .	Any Character
    \.	Period
    [abc]	Only a, b, or c
    [^abc]	Not a, b, nor c
    [a-z]	Characters a to z
    [0-9]	Numbers 0 to 9
    \w	Any Alphanumeric character
    \W	Any Non-alphanumeric character
    {m}	m Repetitions
    {m,n}	m to n Repetitions
    *	Zero or more repetitions
    +	One or more repetitions
    ?	Optional character
    \s	Any Whitespace
    \S	Any Non-whitespace character
    ^…$	Starts and ends
    (…)	Capture Group
    (a(bc))	Capture Sub-group
    (.*)	Capture all
    (abc|def)	Matches abc or def

refer to a match using \1 \2...

Laziness and greediness:

To make a matching sequence non-greedy (lazy?), put '?' after it.

This will make the subsequent rule takes precedence over the current one. For instance in 

    ".*?\d*"

(\d*) will take precedence over the lazy wildcard characters (.*?).


reference: https://regexone.com/












#HTML
--------------------------------------------------------------


#Flexbox
-----------------------------------------------------------
Flexbox actually lays out elements reasonably on the #web.

The flex-grow attribute can be used on child elements
to make them take up the remaining space in a box.

parent { display: flex; flex-direction: column; } 
parent > child { flex-grow: 1; /* default 0 */ }

For all my playing with box-sizing: border-box and the like, I haven't found 
a way to layout html elements in a sane way using CSS.  The only thing that appears 
to work properly is flexbox.  



HTML Forms
------------------

HTML forms make GET and POST requests.  

A server can be made to respond appropriately to this information.
The information itself is encoded as name=value pairs that come from the form.

The html tags in the form must have name attribute and value attributes.

The action is just a string which the server determines how to use along with the name=value information. 

    <form action="/action_page.php" method="get">
    <label for="fname">First name:</label>
    <input type="text" id="fname" name="fname"><br><br>
    <label for="lname">Last name:</label>
    <input type="text" id="lname" name="lname"><br><br>
    <input type="submit" value="Submit">
    </form>


POST requests have no limitations on data length https://www.w3schools.com/tags/ref_httpmethods.asp.

https://www.w3schools.com/tags/att_form_method.asp


CSS link tag
----------------------
I always forget how to add a css file in html.

    <LINK rel="stylesheet" href="../css/reset.css">


HTML element ids automatically become global variables in javascript. !!!!!!!!!!
https://stackoverflow.com/questions/3434278/do-dom-tree-elements-with-ids-become-global-variables










#Bash 
-------------------------------

time a process

    time ./a.out

Screen

The command "screen" makes a new process with a new terminal screen. 
* detatch using ctrl+a d. 
* exit using exit.
* list the screens (with their ids) with "screen -ls". 
* reattach with "screen -r <id>". 
* a partial id can be used in place of the full id.

    screen
    screen -ls
    screen -r <screen id>


Nohup

Nohup runs a processes in the background

    nohup <command> & 

Its stdout is redirected to a file called nohup.out.  
The process should be killed when the nohup.out file is deleted.



#Netcat (nc)
---------------------------
Net cat is a handy utility for tcp and udp stuff.
The examples below were tested on macos 10.12

main options: 
* -l listen
* -u udp
* -v verbose 

To Do: Make a version of netcat that doesn't care whether it's a client or a server.
The program should start of as a client then if it fails to connect then it becomes a server
and waits for someone else to connect.

1. Chat program

    nc -l 127.0.0.1 8888
    nc 127.0.0.1 8888


2. port scanner

    nc -v <your public IP address> 1-1000


3. HTTP

    nc google.com 80
    GET / HTTP/1.1

    nc www.rssweather.com 80
    GET /wx/in/kanpur/wx.php HTTP/1.0
    Host: www.rssweather.com



Make an #SSH key 
--------------------------------------------

    ssh-keygen -o

follow the prompts
give the public ssh key to the other party

In windows, git bash can be used for this.

https://git-scm.com/book/en/v2/Git-on-the-Server-Generating-Your-SSH-Public-Key





-------------------------------------------------------------------
#Misc
-------------------------------------------------------------------

I think finaly, the key here is just to define the interfaces to the operating system so they can be redefined later

musl libc can't install on macos it only works on linux distros. 
tcc appeared to have a standard library, that worked some of the time?
maybe it was just using the standard one though.

I'm basically just looking for the most basic file IO that can be built upon.


https://suckless.org/
Unix Specification https://pubs.opengroup.org/onlinepubs/7908799/






Linux Packages I was using (Debian)   #linux
---------------------------------------------------------------------------------

    sudo apt install nasm qemu-system-x86 xorriso pkg-config emacs

    sudo apt install libsdl2-dev libsdl2-gfx-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev
    sudo apt install libopengl-dev libglew-dev
    sudo apt install libssl-dev






Does a global signal flag need to be atomic?
------------------------------------------------

    static int sigflag = 0;
    sig_atomic_t sigflag = 0;

sig_atomic_t is an integer type which can be accessed as an atomic entity even in the presence of asynchronous interrupts made by signals.
could I just use a mutex?
It appears that atomic things are more efficient than mutexes

"Atomic operations leverage processor support (compare and swap instructions) and don't use locks at all, whereas locks are more OS-dependent and perform differently on, for example, Win and Linux.
Locks actually suspend thread execution, freeing up cpu resources for other tasks, but incurring in obvious context-switching overhead when stopping/restarting the thread. On the contrary, threads attempting atomic operations don't wait and keep trying until success (so-called busy-waiting), so they don't incur in context-switching overhead, but neither free up cpu resources.
Summing up, in general atomic operations are faster if contention between threads is sufficiently low. You should definitely do benchmarking as there's no other reliable method of knowing what's the lowest overhead between context-switching and busy-waiting."
https://stackoverflow.com/questions/15056237/which-is-more-efficient-basic-mutex-lock-or-atomic-integer




Plan 9
-------------------------------------------
from https://aiju.de/plan_9/plan9-syscalls

plan 9 was what unix wanted to be.  
it took the metaphor of devices as being represented as a heirarchical system of files 
to its extreme 
networking is done through a file like interface
proceedures have their own filespace
some of these ideas have been picked up by other systems, like the proc directory 
for proceedure information 
It also had a low number of system calls.


https://en.wikipedia.org/wiki/C_POSIX_library
fcnt

https://en.wikipedia.org/wiki/File_descriptor

https://en.wikipedia.org/wiki/Unistd.h
In the C and C++ programming languages, unistd.h is the name of the header file that provides access to the POSIX operating system API. It is defined by the POSIX.1 standard, the base of the Single Unix Specification, and should therefore be available in any POSIX-compliant operating system and compiler. For instance, this includes Unix and Unix-like operating systems, such as GNU variants, distributions of Linux and BSD, and macOS, and compilers such as GCC and LLVM.

On Unix-like systems, the interface defined by unistd.h is typically made up largely of system call wrapper functions such as fork, pipe and I/O primitives (read, write, close, etc.).


Jonathan Blow on how an operating system should work
https://www.youtube.com/watch?v=k0uE_chSnV8
programs are sandboxed by default 
can't look at hte file system 
basic communication mechanism between processes 
processes communicat by direct memory mapping 
map a mutual buffer 
memcpy data into 


Where's the standard library in macos?

there's also a libc.a under a gcc subdirectory.
/usr/include/c++/4.2.1/cstdio




Nuklear GUI single header file library
-----------------------------------------------------

Nuklear is a single header library GUI toolkit written in C89 with no dependencies.
https://github.com/Immediate-Mode-UI/Nuklear

The demo section works well but the large example requires glew which I couldn't install.




Misc 
--------------


The SDL renderer has a VSYNC option which I should try
gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );


What are these libraries?  I'm pretty sure this came from pkg-config --static 

    gcc 1_open_a_window.c ~/lib/libSDL2.a -ldl -lm -ldl -lpthread -lrt




__declspec(naked)
-------------------------
void __declspec(naked) fname()
Placing this before a function stops the compiler from adding the usual stack code before and after a function call.

"Basically the function prologue sets up a stack frame for local variables and the epilogue takes care of cleaning it up. This is usually done automatically by the compiler. If you use __declspec(naked), setting up this stack frame will be up to you so it gives you more flexibility."
https://stackoverflow.com/questions/3021513/could-someone-explain-declspecnaked-please









macos take screenshtos as jpgs
--------------------------------
defaults write com.apple.screencapture type jpg;killall SystemUIServer


Make ctrl+tab work properly in vscode
------------------------------------------

// Place your key bindings in keybindings.json to override the defaults
[
    // ...
    {
        "key": "ctrl+tab",
        "command": "workbench.action.nextEditor"
    },
    {
        "key": "ctrl+shift+tab",
        "command": "workbench.action.previousEditor"
    }
]
