# PL_MPEG - MPEG1 Video decoder, MP2 Audio decoder, MPEG-PS demuxer 

Single-file MIT licensed library for C/C++

See [pl_mpeg.h](https://github.com/phoboslab/pl_mpeg/blob/master/pl_mpeg.h) for
the documentation.


## Build - ubuntu

    sudo apt install libsdl2-dev libopengl-dev libglew-dev

    gcc pl_mpeg_player.c -L/usr/local/lib -lSDL2 -lGLEW -lGL

I had to copy the GLEW library files from /usr/local/lib64 to /usr/local/lib to make it work

    ./a.out <video.mpg>



## Build Tips

Find library packages with apt search

    apt search libsdl2 libopengl libglew

The linking flags were found using pkg-config

    pkg-config --libs sdl2 opengl glew

You can also statically link libraries apparently, which is cool.

    pkg-config --static --libs sdl2 opengl glew


Example of static linking using local library files

    gcc pl_mpeg_player.c -L/home/nick/everything/linux/lib -I/home/nick/everything/linux/include -Wl,--enable-new-dtags -lSDL2 -lm -ldl -lpthread -lrt -lOpenGL -lGLEW -lGL -lX11 -lGLU -lm -lGL






## Why?

This is meant as a simple way to get video playback into your app or game. Other
solutions, such as ffmpeg require huge libraries and a lot of glue code.

MPEG1 is an old and inefficient codec, but it's still good enough for many use
cases. All patents related to MPEG1 and MP2 have expired, so it's completely
free now.

This library does not make use of any SIMD instructions, but because of
the relative simplicity of the codec it still manages to decode 4k60fps video
on a single CPU core (on my i7-6700k at least).


## Example Usage

- [pl_mpeg_extract_frames.c](https://github.com/phoboslab/pl_mpeg/blob/master/pl_mpeg_extract_frames.c)
extracts all frames from a video and saves them as PNG.
 - [pl_mpeg_player.c](https://github.com/phoboslab/pl_mpeg/blob/master/pl_mpeg_player.c)
implements a video player using SDL2 and OpenGL for rendering.



## Encoding for PL_MPEG

Most [MPEG-PS](https://en.wikipedia.org/wiki/MPEG_program_stream) (`.mpg`) files
containing MPEG1 Video ("mpeg1") and MPEG1 Audio Layer II ("mp2") streams should
work with PL_MPEG. Note that `.mpg` files can also contain MPEG2 Video, which is
not supported by this library.

You can encode video in a suitable format using ffmpeg:

```
ffmpeg -i input.mp4 -c:v mpeg1video -c:a mp2 -format mpeg output.mpg
```

If you just want to quickly test the library, try this file:

https://phoboslab.org/files/bjork-all-is-full-of-love.mpg


## Limitations

- no error reporting. PL_MPEG will silently ignore any invalid data.
- the pts (presentation time stamp) for packets in the MPEG-PS container is
ignored. This may cause sync issues with some files.
- bugs, probably.