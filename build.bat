::gcc -DBUILDING_DLL -c gui.c -o gui.o -IC:\mingw64\x86_64-w64-mingw32\include
::gcc -shared -o gui.dll gui.o -LC:\mingw64\x86_64-w64-mingw32\lib -lraylib -lopengl32 -lgdi32 -lwinmm


::gcc main.c -o main.exe ^
::-IC:\mingw64\x86_64-w64-mingw32\include ^
::-LC:\mingw64\x86_64-w64-mingw32\lib ^
::-lraylib -lopengl32 -lgdi32 -lwinmm
::gcc main.c -o main -lraylib -lopengl32 -lgdi32 -lwinmm
::gcc -shared -o gui.dll gui.o gui.def -LC:\mingw64\x86_64-w64-mingw32\lib -lraylib -lopengl32 -lgdi32 -lwinmm
::gcc main.c gui.c -o main.exe -lraylib -lopengl32 -lgdi32 -lwinmm

::gcc main.c gui.c -o main.exe -lraylib -lgdi32 -lwinmm
::gcc -o raylibhelloworld.exe raylibhelloworld.c  -I include -L lib -lraylib -lgdi32 -lwinmm
gcc -o main.exe src/main.c src/gui.c  -I include -L lib -lraylib -lgdi32 -lwinmm
