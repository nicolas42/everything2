@REM First call vsvarall.bat. This is only needed once per terminal session.
@REM call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
@REM then
@REM make.bat <program.cpp> && windows\a


@set OUT_DIR=windows
@set OUT_EXE=a

@set INCLUDES=/Iwindows\include
@set SOURCES=%1%
@set LIBS=/libpath:windows SDL2.lib SDL2main.lib SDL2_mixer.lib SDL2_ttf.lib opengl32.lib shell32.lib

cl /nologo /Zi /MD %INCLUDES% %SOURCES% /Fe%OUT_DIR%/%OUT_EXE%.exe /Fo%OUT_DIR%/ /link %LIBS% /subsystem:console
