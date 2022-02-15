@echo off
IF "%vcvarsall_has_been_run%"=="" (
    SET vcvarsall_has_been_run=1
    call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

cl -Zi /I "include" 21_sound_effects_and_music\21_sound_effects_and_music.cpp  /link "build_win64\SDL2.lib" "build_win64\SDL2main.lib" "build_win64\SDL2_image.lib" "build_win64\SDL2_mixer.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:build_win64\21_sound_effects_and_music.exe
del *.manifest *.ilk *.obj *.pdf *.idb *.pdb


REM # HELP
REM subsystem can also be console or posix e.g. /SUBSYSTEM:CONSOLE . more info https://docs.microsoft.com/en-us/cpp/build/reference/subsystem-specify-subsystem?view=vs-2019
REM handmade hero with simple windows build command https://youtu.be/Ee3EtYb8d1o?t=3921