@REM Build for Visual Studio compiler. Run your copy of vcvars32.bat or vcvarsall.bat to setup command-line compiler.
@REM call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

@set OUT_DIR=c:\users\nick\everything\cpp\win64
@set OUT_EXE=a

@set INCLUDES=/Ic:\users\nick\everything\cpp\win64\include
@set SOURCES=solar_system_simulation.cpp 
@set LIBS=/LIBPATH:c:\users\nick\everything\cpp\win64 SDL2.lib SDL2main.lib SDL2_mixer.lib opengl32.lib shell32.lib

cl /nologo /Zi /MD %INCLUDES% %SOURCES% /Fe%OUT_DIR%/%OUT_EXE%.exe /Fo%OUT_DIR%/ /link %LIBS% /subsystem:console
