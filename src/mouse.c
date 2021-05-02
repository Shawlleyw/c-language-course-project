#include "mouse.h"
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "SVGA.h"
//#include "draw.h"
#define H 15
#define W 12

int mouse_shape[H][W] = { //�����״��ά����
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0},
    {1, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0},
    {1, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0},
    {1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0},
    {1, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0},
    {1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1},
    {1, 2, 2, 1, 2, 2, 2, 1, 0, 0, 0, 0},
    {1, 2, 1, 0, 1, 2, 2, 2, 1, 0, 0, 0},
    {1, 1, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0}

};

unsigned int mouse_bk[20][20]; //��ű���긲�ǵ�����
MOUSE mouse = {0, 0, 0};       //����һ�����ṹ����

/***����ʼ��***/
void Mouse_Init()
{
  MouseInit();                 //��긴λ������Ƿ�װ���
  MouseRange(0, 0, 1012, 752); //��귶Χ����
  MouseGet(&mouse);            //�õ����״̬
  MouseSpeed(6, 4);
  MouseOn(mouse); //��ʾ���
}

/***��긴λ***/
void MouseInit()
{
  union REGS regs;
  regs.x.ax = 0;
  int86(0x33, &regs, &regs);
  if (regs.x.ax == 0)
  {
    printf("mouse error");
    delay(5000);
    exit(1);
  }
}
/********************************
	����˵�������������������ر�,ֵԽ������ƶ��ٶ�Խ��
	����˵����int   vx,	������ģ�int   vy	��������
**
********************************/
void MouseSpeed(int x, int y)
{
  union REGS regs;
  regs.x.ax = 0x0f;
  regs.x.cx = x;
  regs.x.dx = y;
  int86(0x33, &regs, &regs);
}
/**********************************************************************
	����˵����������������ȣ�������걶����ֵ��
	����˵����xΪˮƽ�����ȣ�yΪ��ֱ������,vΪ��꼴���趨�ı�����ֵ
	����ֵ˵������
*********************************************************************/
void SetMouseSen(int x, int y)
{
  union REGS regs;
  regs.x.ax = 0x1a;
  regs.x.bx = x;
  regs.x.cx = y;
  // regs.x.dx=v;
  int86(51, &regs, &regs);
}
/***�õ�ĳһ�����ɫֵ***/
unsigned int Getpixel64k(int x, int y)
{
  unsigned int far *const video_buffer = (unsigned int far *)0xa0000000L;
  unsigned char page;         //Ҫ�л���ҳ���
  unsigned long int page_dev; //��Ӧ�Դ��ַƫ����
  if (x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))
  { //�жϵ��Ƿ�����Ļ��Χ�ڣ����ھ��˳�
    printf("out of range");
  }
  page_dev = ((unsigned long int)y << 10) + x; //�����Դ��ַƫ�����Ͷ�Ӧ��ҳ��ţ�����ҳ����
  page = page_dev >> 15;                       //32k����һ��ҳ������32k������㷨
  Selectpage(page);
  return video_buffer[page_dev]; //������ɫ
}

/***��귶Χ����***/
void MouseRange(int x1, int y1, int x2, int y2)
{
  union REGS mouse;
  /*���ú����귶Χ*/
  mouse.x.ax = 7;
  mouse.x.cx = x1;
  mouse.x.dx = x2;
  int86(0x33, &mouse, &mouse);
  /*���������귶Χ*/
  mouse.x.ax = 8;
  mouse.x.cx = y1;
  mouse.x.dx = y2;
  int86(0x33, &mouse, &mouse);
}

/***�õ���갴��״̬(�������������)***/
int MouseBut(MOUSE *mouse)
{
  union REGS regs;
  regs.x.ax = 3;
  int86(0x33, &regs, &regs);
  mouse->key = regs.x.bx;
  return mouse->key;
}

/***�õ����λ�ã�����״̬***/
int MouseGet(MOUSE *mouse)
{
  union REGS regs;
  regs.x.ax = 3;
  int86(0x33, &regs, &regs);
  mouse->x = regs.x.cx;
  mouse->y = regs.x.dx;
  mouse->key = regs.x.bx;
  return mouse->key;
}

/***���������ʾλ��***/
void MouseSet(int x, int y)
{
  union REGS regs;
  regs.x.ax = 4;
  regs.x.cx = x;
  regs.x.dx = y;
  int86(0x33, &regs, &regs); //������굱ǰ����
  MouseOn(mouse);            //�����
}

/***�ж�����Ƿ���ָ�������ڲ�***/
int MouseIn(int x1, int y1, int x2, int y2)
{
  MOUSE mouse = {0, 0, 0}; //very important������һ�����ṹ���������ٶ������ṹ�ĵ���
  MouseGet(&mouse);
  if ((mouse.x >= x1) && (mouse.x <= x2) && (mouse.y >= y1) && (mouse.y <= y2))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/***�ж��������Ƿ���ָ�������ڰ���***/
int MousePress(int x1, int y1, int x2, int y2)
{
  MOUSE mouse = {0, 0, 0};
  MouseGet(&mouse);
  if ((mouse.x >= x1) && (mouse.x <= x2) && (mouse.y >= y1) && (mouse.y <= y2) && ((mouse.key & 1) == 1))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/***�����ʾ***/
void MouseOn(MOUSE mouse)
{
  int i, j;
  for (i = 0; i < H; i++)
  {
    for (j = 0; j < W; j++)
    {

      mouse_bk[i][j] = Getpixel64k(j + mouse.x, i + mouse.y); //�洢��긲����
      /***�����***/
      if (mouse_shape[i][j] == 1)
        Putpixel64k(mouse.x + j, mouse.y + i, 0);
      else if (mouse_shape[i][j] == 2)
        Putpixel64k(mouse.x + j, mouse.y + i, 0xffff);
    }
  }
}

/***���ÿ���ƶ�������ʾ***/
void MouseShow(MOUSE *mouse)
{
  int i, j;  //ѭ������
  int color; //���ĳ����ɫ
  int x, y;
  x = mouse->x; //���ԭλ������
  y = mouse->y;
  MouseGet(mouse); //�õ������״̬
  if (mouse->x != x || mouse->y != y)
  { //����ƶ������»����
    for (i = 0; i < H; i++)
    {
      for (j = 0; j < W; j++)
      {
        if (mouse_shape[i][j] == 0)
          continue;
        Putpixel64k(x + j, y + i, mouse_bk[i][j]); //����ԭ��긲����
      }
    }
    MouseOn(*mouse); //����λ����ʾ���
  }
}

/***�������***/
void MouseOff(MOUSE *mouse)
{
  int i, j;
  int x, y;
  x = mouse->x;
  y = mouse->y;
  for (i = 0; i < H; i++)
    for (j = 0; j < W; j++)
    {
      if (mouse_shape[i][j] == 0)
        continue;
      Putpixel64k(x + j, y + i, mouse_bk[i][j]); //����ԭ��긲����
    }
}

/*��ʼ����꣬����ˮƽ��ֱ�������ر����*/
void Curinit(void)
{
  _AX = 0;
  geninterrupt(0x33);
  if (_AX == 0)
    puts("mouse init fail!");
  _AX = 7;
  _CX = 10;
  _DX = 1000;
  geninterrupt(0x33);
  _AX = 8;
  _CX = 10;
  _DX = 750;
  geninterrupt(0x33);
}

void draw_mouse(int mx, int my)
{
  int i, j;
  for (i = 0; i < H; i++)
  {
    for (j = 0; j < W; j++)
    {
      /***�����***/
      if (mouse_shape[i][j] == 1)
        Putpixel64k(mx + j, my + i, 0);
      else if (mouse_shape[i][j] == 2)
        Putpixel64k(mx + j, my + i, 0xffff);
    }
  }
}

void CurShow(void)
{
  Cursor(500, 500, 2);
}

void Curhide(void)
{
  Cursor(500, 500, 1);
}

void Cursor(int x, int y, int flag)
{
  static unsigned int far *tempgraph;
  static int mx, my;
  if (tempgraph == NULL)
  {
    tempgraph = malloc(1000);
  }
  if (1 <= x && x <= 1000 && 1 <= y && y <= 750)
  {
    switch (flag)
    {
    case 1: //hidemouse
      Put_image(mx, my, mx + 16, my + 15, tempgraph);
      //delay(20);
      break;
    case 2: //showmouse
      do
      {
        _AX = 3;
        geninterrupt(0x33);
        mx = _CX;
        my = _DX;
      } while (1 >= mx || mx >= 1000 || 1 >= my || my >= 750);
      Get_image(mx, my, mx + 16, my + 15, tempgraph);
      draw_mouse(mx, my);
      break;
    }
  }
}

void getmouse(int *button, int *x, int *y)
{
  static int mx, my, mbutton;
  _AX = 3;
  geninterrupt(0x33);
  mbutton = _BL;
  mx = _CX;
  my = _DX;
  Cursor(mx, my, 0);
  if (button != NULL)
    *button = mbutton;
  if (x != NULL && y != NULL)
  {
    *x = mx;
    *y = my;
  }
}
