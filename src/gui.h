
#define ANCHO 1280
#define ALTO 720
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
#define BORDES 0x8C8374FF
#define BORDESIZE 4.5

#ifndef GUI_H_


#define GUI_H_

typedef struct Circle{
          Vector2 center;
          float radius;
          float start;
          float end;
          int segment;
          Color colo;
}Circle;

void ReadTask(Vector2 posi,Font f,char input[],int *pos);

char *AddTask(char input[]);

void Buttom(Vector2 Bpos,Vector2 Fdim,float radius,float ps,Color col,Font f,char c);

void TaskList(char *tareas[],int index, Font f);

void InputBar( Rectangle caja, char input[], Vector2 posi, Font f, int *pos);

void TaskDone(int *contareas,int *completadas, Font f);

void Interface2(bool *vf,Rectangle caja,char input[],Vector2 posi,Font f,int *pos,
    char *tareas[],int *contareas,int *completadas);

int StrLen(char input[]);

int IntLen(int n);

char *IntToChar(int n);

#endif //GUI_H_
