#ifndef __HZ_H__
#define __HZ_H__
#include <stdio.h>

#include <dos.h>
#include <fcntl.h>
#include <io.h>

#include <bios.h>
#include <stdlib.h>
#include <string.h>

#include "mouse.h"
#include "svga.h"
#include <conio.h>

#define ENTER 0x1c0d

/***�û���Ϣ�ṹ��***/
typedef struct person {
  char user[10];
  char password[10];
  struct person *next;
} person;

void puthz(int x, int y, char *s, int flag, int part, int color);

/*����16���ֿ����16*16������*/
void prt_hz16(int x, int y, char *s, unsigned int color, char *name);

/*����24���ֿ����24*24��������*/
void prt_hz24(int x, int y, char *s, unsigned int color, char *name);

/*����24���ֿ����24*24�������֣����ӳ٣�*/
void prt_hz24d(int x, int y, char *s, unsigned int color, char *name);

/*����16���ֿ����16*xsize*16*ysize�����֣�x,y��ʾ�������λ�ã�xsize,ysizeΪ�Ŵ�����
sΪ���ִ���color��ʾ������ɫ��name Ϊ���ֿ��ļ�·������������Ϣ*/
void prt_hz16_size(int x, int y, int xsize, int ysize, char *s,
                   unsigned int color, char *name);

/*����asc16����ַ�*/
void prt_asc16(int x, int y, char *s, unsigned int color);

/*����asc16����ַ�*/
void prt_asc16_ch(int x, int y, char s, unsigned int color);

/*��ȡASCII��ģ*/
void Read_Asc16(char key, unsigned char *buf);

/*����asc16����ַ�*/
void Put_Asc16(int cx, int cy, char key, unsigned int color);

/*����asc16����Ŵ��ַ�*/
void Put_Asc16_Size(int cx, int cy, int xsize, int ysize, char key,
                    unsigned int color);

/*����asc16����Ŵ��ַ���*/
void put_asc16_size(int cx, int cy, int xsize, int ysize, char *s,
                    unsigned int color);

/*�������16*xsize*16*ysize��������16*xsize*16*ysize
asc�ַ����ַ���������x,y��ʾ�������λ�ã�
xsize,ysizeΪ�Ŵ�����sΪ����ַ�����color��ʾ������ɫ��name Ϊ���ֿ��ļ�·������������Ϣ*/
void prt_hz16_asc16_size(int x, int y, int xsize, int ysize, char *s,
                         unsigned int color, char *name);

/*�������24*24��������32*32 asc�ַ����ַ���������x,y��ʾ�������λ��
��sΪ����ַ�����color��ʾ������ɫ��name Ϊ���ֿ��ļ�·������������Ϣ*/
void prt_hz24_asc32(int x, int y, char *s, unsigned int color, char *name);

/*��������12*24����ҷ��ţ�����*/
void RMB(int x, int y, int xsize, int ysize, unsigned color);

/***����꺯��***/
void show_gb(int x, int y);
/***��Ϣ����ʱ��������ͬ����***/
void Getinfo(int x1, int y1, char *pm, int num, int i);
/***��������ʱ��������ͬ����***/
void Getcode(int x1, int y1, char *code, int num, int i);
void Getnum(int x1, int y1, char *name, int num, int i);
#endif
