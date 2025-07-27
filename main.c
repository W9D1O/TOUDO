#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>



#define ANCHO 960
#define ALTO 549
/*La idea es que sea proporcional, no se si esta bien como lo estoy haciendo
pero por el momento supongo que esta bien */
#define CAJAY ALTO*0.1 
#define CAJANCH ANCHO*0.5
#define CAJANLT ALTO*0.05
#define CAJAX ANCHO*0.5 - CAJANCH/2
#define SIZELETTER ALTO*0.04
#define BUFFER 1024 // Es el tammaño max del input
#define BACKGROUND 0x181818FF
#define BOXTASKPOS CAJAX + CAJANCH/2-CAJANCH*0.75/2
#define INPUTBOX  CAJANCH - CAJANCH*0.6/2



//TODO: Cambiar los literales, quedan feos y seguro me olvide de que son


void ReadTask(Vector2 posi,Font f,char input[],int *pos){
  int i = 0;
  while(i < BUFFER){
    char get = GetCharPressed();
    if(input[i] != 0){
      posi.x += i + 16;
      DrawTextCodepoint(f,input[i],posi,SIZELETTER, RED);
    }
    if(get != 0){
      input[*pos] = get;
      *pos += 1;
    }
    i += 1;
  }
  if(*pos > 0){
    input[*pos + 1] = '\0';
  }
}


int StrLen(char input[]){
  int i = 0;
  while(i < BUFFER && input[i] != '\0'){
    i++;
  }
  return i;
}


//Agrega una tarea a una posicion de un array y de paso va limpiado la cadena
char *AddTask(char input[]){
  int len = StrLen(input);
  char *aux = (char *)malloc(len + 1);
  if(aux == NULL) return NULL;
  for(int i = 0; i < len; ++i){
    aux[i] = input[i];
    input[i] = 0;
  }
  aux[len] = '\0';
  return aux;
}


void TaskList(char *tareas[],int index, Font f){
  int LisSep = 70;
  Vector2 posi = {
      .y = CAJAY*3.7 + LisSep,
      .x =  BOXTASKPOS,
    };
  Rectangle caja = {
      .x = BOXTASKPOS,
      .y = CAJAY*3.7 + LisSep,
      .width = (float)CAJANCH*0.85,
      .height = (float)CAJANLT*1.7,

    };
  for(int i = 0;i < index; ++i){
    DrawRectangleRounded(caja,0.25,1, ColorBrightness(GetColor(BACKGROUND), 0.1f));
    DrawTextEx(f, tareas[i], posi,(float)SIZELETTER,0, BLUE);
    DrawRectangleRoundedLinesEx(caja,0.25,1,2.5f,GRAY);
    //int len = StrLen(tareas[i]);
    posi.y += LisSep;
    caja.y = posi.y;
  }
}


void InputBar( Rectangle caja, char input[], Vector2 posi, Font f, int *pos){

  Vector2 Bpos = {
      .x = ANCHO*0.68,
      .y = ALTO*0.12,
    };
  caja.y += ALTO*0.30;

  //Sentencia sacada de ChatGpt, solo se agrego el literal que esta multiplicando
  float radius =  (ANCHO < ALTO) ? (ANCHO / 2)*0.065 : (ALTO / 2)*0.065;
  //Ay! dió. Qué poronga es esto. 
  Bpos.y = (caja.y + radius)*0.98;
  //Pero quedo donde quería.


  Vector2 Fdim = MeasureTextEx(f,"+",radius,0);
  Fdim.x += Bpos.x;
  Fdim.y += Bpos.y;
  Color col = RED;
  DrawRectangleRoundedLinesEx(caja,0.85,1,4.0f,GRAY);
  DrawRectangleRounded(caja,0.6,1, ColorBrightness(GetColor(0x1D2533), 0.1));
  DrawCircleV(Bpos,radius,col);
  //Las cosas que hay que hacer por no saber propiamente matematicas
  Fdim.x *= 0.975;
  Fdim.y *= 0.87;
  DrawTextEx(f,"+",Fdim,radius*1.6,0,GetColor(BACKGROUND));
  
  //DrawText("[+]",INPUTBOX,CAJAY + 3,SIZELETTER,BLUE);
  posi.y = caja.y;
  ReadTask(posi,f,input,pos);

}
//Que cagada hacer ui LPM!!
//Contador de LPM = 1. Aumente según corresponda

void Interface(){

  }

int main(){
  bool vf = false; // Esta variable se encarga de que aparesca la caja de escritura
  char input[BUFFER] = {0};
  char *tareas[BUFFER/2];
  int contareas = 0;
  int pos = 0;
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
  SetTargetFPS(60);
  InitWindow(ANCHO,ALTO,"TODOAPP con Raylib");
  Font f = LoadFont(".\\Font\\FiraCodeNerdFont-SemiBold.ttf");
  if(!IsFontValid(f)) return -1;
  // Load font from file into GPU memory (VRAM)))
  while(!WindowShouldClose()){
    BeginDrawing();
    DrawText("TODOAPP",CAJAX + CAJANCH/2-16*7/2,CAJAY-15*2,SIZELETTER,BLUE);
    if(!vf){
      DrawText("Agregar tarea", 10, CAJAY,SIZELETTER, BLUE);
    }
    if(IsKeyPressed(KEY_ENTER)){
      vf = !vf;
    }
    if(vf){
      InputBar(caja,input,posi,f,&pos);
    }
    ClearBackground(GetColor(BACKGROUND));
    if(!vf && input[1] != 0){
      tareas[contareas] = AddTask(input);
      pos = 0;
      printf("%s\n",tareas[contareas]);
      contareas ++;
    }
    if(contareas > 0){
      TaskList(tareas,contareas,f);
    }
    EndDrawing();
  }
  UnloadFont(f);
  CloseWindow();
}
