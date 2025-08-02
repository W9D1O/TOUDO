#include "..\include\raylib.h"
#include <stdlib.h>
#include "gui.h"



//TODO: Cambiar los literales, quedan feos y seguro me olvide de que son




void ReadTask(Vector2 posi,Font f,char input[],int *pos){
  int i = 0;
  while(i < BUFFER){
    char get = GetCharPressed();
    if(input[i] != 0){
      Vector2 Fdim = MeasureTextEx(f,&input[i],SIZELETTER,0);
      posi.x +=  16;
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

void Buttom(Vector2 Bpos,Vector2 Fdim,float radius,float ps,Color col,Font f,char c){

  DrawCircleV(Bpos,radius,col);
  DrawTextEx(f,&c,Fdim,ps,0,GetColor(BACKGROUND));
}

void TaskList(char *tareas[],int index, Font f){
  int LisSep = 70;
  Vector2 posi = {
    .y = CAJAY*5.55 + LisSep,
    .x =  BOXTASKPOS,
  };
  Rectangle caja = {
    .x = ANCHO/2-CAJANCH/2*0.85,
    .y = CAJAY*5.55 + LisSep,
    .width = (float)CAJANCH*0.85,
    .height = (float)CAJANLT*1.7,

  };
  int TaskPadding = caja.width *0.25;
  posi.x += TaskPadding;
  Vector2 Fdim = MeasureTextEx(f,"a",SIZELETTER,0);
  for(int i = 0;i < index; ++i){
    DrawRectangleRounded(caja,0.25,1, ColorBrightness(GetColor(BACKGROUND), 0.1f));
    posi.y += Fdim.y/2;
    DrawTextEx(f, tareas[i], posi,(float)SIZELETTER,0, BLUE);
    DrawRectangleRoundedLinesEx(caja,0.25,1,2.5f,GetColor(BORDES));
    posi.y += LisSep;
    caja.y = posi.y;
  }
}


void InputBar( Rectangle caja, char input[], Vector2 posi, Font f, int *pos){

  Vector2 Bpos = {
    .x = ANCHO*0.68,
    .y = ALTO*0.12,
  };
  caja.y += ALTO*0.40;

  //Sentencia sacada de ChatGpt, solo se agrego el literal que esta multiplicando
  float radius =  (ANCHO < ALTO) ? (ANCHO / 2)*0.065 : (ALTO / 2)*0.065;
  //Ay! dió. Qué poronga es esto. 
  Bpos.y = (caja.y + radius)*0.98;
  //Pero quedo donde quería.


  Vector2 Fdim = MeasureTextEx(f,"+",radius,0);
  Fdim.x += Bpos.x;
  Fdim.y += Bpos.y;
  Color col = RED;
  DrawRectangleRoundedLinesEx(caja,0.85,1,4.0f,GetColor(BORDES));
  DrawRectangleRounded(caja,0.6,1, ColorBrightness(GetColor(0x1D2533), 0.1));
  //Las cosas que hay que hacer por no saber propiamente matematicas
  Fdim.x *= 0.975;
  Fdim.y *= 0.90;
  float PaddinSim = radius*1.6;
  Buttom(Bpos,Fdim,radius,PaddinSim, col,f,*"+");

  posi.y = caja.y;
  ReadTask(posi,f,input,pos);

}


//Que cagada hacer ui LPM!!
//Contador de LPM = 1. Aumente según corresponda

void TaskDone(int *contareas,int *completadas){
  char *t = "Todo Done";
  Rectangle caja = {
    .x =  ANCHO/2-CAJANCH*0.85/2,
    .y = (float)CAJAY-SIZELETTER,
    .height = (float)ALTO*0.4,
    .width = (float)CAJANCH *0.85
  };
  //DrawRectangleRounded(caja,0.25,1, ColorBrightness(GetColor(BACKGROUND), 0.1f));
  DrawRectangleRoundedLinesEx(caja,0.25,1,BORDESIZE/2,GetColor(BORDES));
}

void Interface2(bool *vf,Rectangle caja,char input[],Vector2 posi,Font f,int *pos,
    char *tareas[],int *contareas,int *completadas){

  DrawText("TODOAPP",CAJAX + CAJANCH/2-16*7/2,CAJAY-15*2,SIZELETTER,BLUE);
  TaskDone(contareas,completadas);
  if(!vf){
    DrawText("Agregar tarea", 10, CAJAY,SIZELETTER, BLUE);
  }
  if(IsKeyPressed(KEY_ENTER)){
    *vf = !*vf;
  }
  if(*vf){
    InputBar(caja,input,posi,f,pos);
  }
  if(!*vf && input[1] != 0){
    tareas[*contareas] = AddTask(input);
    *pos = 0;
    *contareas += 1;
  }
  if(*contareas > 0){
    TaskList(tareas,*contareas,f);
  }
}
