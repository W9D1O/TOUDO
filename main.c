#include <stdio.h>
#include "include\raylib.h"
#include <stdlib.h>
#include "./gui.h"


int main(){
  bool vf = false; // Esta variable se encarga de que aparesca la caja de escritura
  char input[BUFFER] = {0};
  char *tareas[BUFFER/2];
  int contareas = 0;
  int pos = 0;
  int completadas = 0;
  Rectangle caja = {
    .x = INPUTBOX,
    .y = (float)CAJAY,
    .height = (float)CAJANLT,
    .width = (float)CAJANCH *0.6
  };
  Vector2 posi = {
    
    .y = caja.y + 3.f,
    .x = INPUTBOX,
  };
  InitWindow(ANCHO,ALTO,"TODOAPP con Raylib");
  SetTargetFPS(60);
  Font f = LoadFont(".\\Font\\FiraCodeNerdFont-SemiBold.ttf");
  if(!IsFontValid(f)) return -1;
  while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(GetColor(BACKGROUND));
    Interface2(&vf,caja,input,posi,f,&pos,
              tareas, &contareas,&completadas);
    EndDrawing();
  }
  UnloadFont(f);
  CloseWindow();
}
