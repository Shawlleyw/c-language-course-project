#include "headers/hz.h"
#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void puthz(int x, int y, char *s, int flag, int part, int color)
{
  FILE *hzk_p = NULL;        //定义汉字库文件指针
  unsigned char quma, weima; //定义汉字的区码和位码
  unsigned long offset;      //定义汉字在字库中的偏移量
  unsigned char mask[] = {
      0x80, 0x40, 0x20, 0x10,
      0x08, 0x04, 0x02, 0x01}; //功能数组，用于显示汉字点阵中的亮点
  int i, j, pos;

  switch (flag)
  { //不同的flag对应不同的汉字库，实现了汉字的大小可根据需要改变
  case 16:
  {
    char mat[32]; // 16*16的汉字需要32个字节的数组来存储
    int y0 = y;
    int x0 = x;
    hzk_p = fopen("HZK/HZ16", "rb"); //使用相对路径
    if (hzk_p == NULL)
    {
      CloseSVGA();
      printf("cant open HZ16");
      getch();
      exit(1);
    }
    while (*s != NULL)
    {
      while (x < 1024 - flag && (*s != NULL))
      {
        y = y0;
        quma = s[0] - 0xa0;  //求出区码
        weima = s[1] - 0xa0; //求出位码
        offset = (94 * (quma - 1) + (weima - 1)) *
                 32L;                   //求出要显示的汉字在字库文件中的偏移
        fseek(hzk_p, offset, SEEK_SET); //重定位文件指针
        fread(mat, 32, 1, hzk_p);       //读出该汉字的具体点阵数据,1为要读入的项数

        for (i = 0; i < 16; i++)
        {
          pos = 2 * i; // 16*16矩阵中有每一行有两外字节
          for (j = 0; j < 16; j++)
          { //一行一行地扫描，将位上为了1的点显示出来
            if ((mask[j % 8] & mat[pos + j / 8]) !=
                NULL)
            { // j%8只能在0—8之间循环，j/8在0，1之间循环
              Putpixel64k(x + j, y, color);
            }
          }
          y++;
        }
        /*====================================================
              以上是一个汉字显示完
        ====================================================*/
        x += part; //给x 一个偏移量part
        s += 2;    //汉字里存放的是内码，2个字节，所以要加2
      }
      x = x0;
      y0 += flag + 10; //一行汉字显示完后,重新从左侧开始输出汉字，给y一个偏移量
    }

    break;
  }

  case 24:
  {
    char mat[72]; // 24*24矩阵要72个字节来存储
    int y0 = y;
    int x0 = x;
    hzk_p = fopen("HZK/Hzk24k", "rb");
    if (hzk_p == NULL)
    {
      CloseSVGA();
      printf("cant open HZ24");
      getch();
      exit(1);
    }
    while (*s != NULL)
    {
      while (x < 1024 - flag && (*s != NULL))
      {
        y = y0;
        quma = s[0] - 0xa0;  //求出区码
        weima = s[1] - 0xa0; //求出位码
        offset = (94 * (quma - 1) + (weima - 1)) * 72L;
        fseek(hzk_p, offset, SEEK_SET);
        fread(mat, 72, 1, hzk_p);
        for (i = 0; i < 24; i++)
        {
          pos = 3 * i; //矩阵中每一行有三个字节
          for (j = 0; j < 24; j++)
          { // 每一行有24位
            if ((mask[j % 8] & mat[pos + j / 8]) != NULL)
              Putpixel64k(x + j, y, color);
          }
          y++;
        }
        x += part;
        s += 2;
      }
      x = x0;
      y0 += flag + 10;
    }
    break;
  }

  case 32:
  {
    char mat[128]; // 32*32的汉字需要128个字节的数组来存储
    int y0 = y;
    int x0 = x;
    hzk_p = fopen("HZK/HZK32S", "rb");
    if (hzk_p == NULL)
    {
      CloseSVGA();
      printf("cant open HZ32");
      getch();
      exit(1);
    }
    while (*s != NULL)
    {
      while (x < 1024 - flag && (*s != NULL))
      {
        y = y0;
        quma = s[0] - 0xa0;  //求出区码
        weima = s[1] - 0xa0; //求出位码
        offset = (94 * (quma - 1) + (weima - 1)) * 128L;
        fseek(hzk_p, offset, SEEK_SET);
        fread(mat, 128, 1, hzk_p);
        for (i = 0; i < 32; i++)
        {
          pos = 4 * i; // 32*32矩阵中有每一行有两外字节
          for (j = 0; j < 32; j++)
          {
            if ((mask[j % 8] & mat[pos + j / 8]) != NULL)
            {
              Putpixel64k(x + j, y, color);
            }
          }
          y++;
        }
        //以上是一个汉字显示完
        x += part; //给x 一个偏移量part
        s += 2;    //汉字里存放的是内码，2个字节，所以要加2
      }
      x = x0;
      y0 += flag + 10; //一行汉字显示完后，给y一个偏移量
    }
    break;
  }

  case 48:
  {
    char mat[288]; // 48*48的汉字需要288个字节的数组来存储
    int y0 = y;
    int x0 = x;
    hzk_p = fopen("HZK/HZ48", "rb");
    if (hzk_p == NULL)
    {
      CloseSVGA();
      printf("cant open HZ48");
      getch();
      exit(1);
    }
    while (*s != NULL)
    {
      while (x < 1024 - flag && (*s != NULL))
      {
        y = y0;
        quma = s[0] - 0xa0;  //求出区码
        weima = s[1] - 0xa0; //求出位码
        offset = (94 * (quma - 1) + (weima - 1)) *
                 288L;                  //求出要显示的汉字在字库文件中的偏移
        fseek(hzk_p, offset, SEEK_SET); //重定位文件指针
        fread(mat, 288, 1, hzk_p);      //读出该汉字的具体点阵数据,1为要读入的项数

        for (i = 0; i < 48; i++)
        {
          pos = 6 * i;
          for (j = 0; j < 48; j++)
          { //一行一行地扫描，将位上为了1的点显示出来
            if ((mask[j % 8] & mat[pos + j / 8]) !=
                NULL)
            { // j%8只能在0—8之间循环，j/8在0，1之间循环
              Putpixel64k(x + j, y, color);
            }
          }
          y++;
        }
        //以上是一个汉字显示完
        x += part; //给x 一个偏移量part
        s += 2;    //汉字里存放的是内码，2个字节，所以要加2
      }
      x = x0;
      y0 += flag + 10; //一行汉字显示完后，给y一个偏移量
    }
    break;
  }

  default:
    break;
  }

  fclose(hzk_p);
}
#include "hz.h"

/*16λ�����������x,y��ʾ�������λ�ã�sΪ���ִ���color��ʾ������ɫ��
name Ϊ���ֿ��ļ�·������������Ϣ*/
void prt_hz16(int x, int y, char *s, unsigned int color, char *name)
{
  FILE *fp = NULL;
  char buffer[32] = {0}; //������ȡ16���ֵ�32λ��ģ
  int i = 0;
  int j = 0;
  unsigned char qh = 0;
  unsigned char wh = 0;     //������λ��
  unsigned long offset = 0; //��������
  unsigned char mask[] = {0x80, 0x40, 0x20,
                          0x10, 0x08, 0x04, //�������γ�ÿһλ����Ϣ
                          0x02, 0x01};
  if ((fp = fopen(name, "rb")) == NULL)
  {
    printf("Can't open hzk16!");
    getch();
    exit(0);
  }
  while (*s)
  {                //�����ִ�δ���꣬�����
    qh = *s - 160; //�õ���������
    wh = *(s + 1) - 160;
    offset = (94 * (qh - 1) + (wh - 1)) * 32L; //����λ����
    fseek(fp, offset, SEEK_SET);               //���ֿ��ļ��в�������λ��
    fread(buffer, 32, 1, fp);                  //��ȡ��Ӧλ�õ���ģ
    for (i = 0; i < 16; i++)
    { //��ָ�������һ������
      for (j = 0; j < 16; j++)
      {
        if ((mask[j % 8] & buffer[i * 2 + j / 8]) != 0)
        {
          Putpixel64k(x + j, y + i, color);
        }
      }
    }
    x += 16; //������������Ϊ16
    s += 2;  //��ȡ��һ������
  }
  fclose(fp);
}

/*(���ӳ�)24λ�����������x,y��ʾ�������λ�ã�sΪ���ִ���color��ʾ������ɫ��
name Ϊ���ֿ��ļ�·������������Ϣ*/
void prt_hz24(int x, int y, char *s, unsigned int color, char *name)
{
  FILE *fp = NULL;
  char buffer[72] = {0}; //������ȡ24���ֵ�72λ��ģ
  int i = 0;
  int j = 0;
  unsigned char qh = 0;
  unsigned char wh = 0;
  unsigned long offset = 0;
  unsigned char mask[] = {0x80, 0x40, 0x20,
                          0x10, 0x08, 0x04, //�������γ�ÿһλ����Ϣ
                          0x02, 0x01};
  if ((fp = fopen(name, "rb")) == NULL)
  {
    printf("Can't open hzk24!");
    getch();
    exit(0);
  }
  while (*s)
  {
    qh = *s - 160;
    wh = *(s + 1) - 160;
    offset = (94 * (qh - 1) + (wh - 1)) * 72L;
    fseek(fp, offset, SEEK_SET);
    fread(buffer, 72, 1, fp);
    for (i = 0; i < 24; i++) //���һ������
      for (j = 0; j < 24; j++)
      {
        if ((mask[j % 8] & buffer[i * 3 + j / 8]) != 0)
        {
          Putpixel64k(x + j, y + i, color);
        }
      }
    s += 2;
    x += 24;   //����������24
    delay(50); //ʹÿ������������̿ɼ���������Ч��������
  }
  fclose(fp);
}

/*x,y��ʾ�������λ�ã�sΪ���ִ���color��ʾ������ɫ��
name Ϊ���ֿ��ļ�·������������Ϣ*/
void prt_hz24d(int x, int y, char *s, unsigned int color, char *name)
{
  FILE *fp = NULL;
  char buffer[72] = {0}; //������ȡ24���ֵ�72λ��ģ
  int i = 0;
  int j = 0;
  unsigned char qh = 0;
  unsigned char wh = 0;
  unsigned long offset = 0;
  unsigned char mask[] = {0x80, 0x40, 0x20,
                          0x10, 0x08, 0x04, //�������γ�ÿһλ����Ϣ
                          0x02, 0x01};
  if ((fp = fopen(name, "rb")) == NULL)
  {
    printf("Can't open hzk24d!");
    getch();
    exit(0);
  }
  while (*s)
  {
    qh = *s - 160;
    wh = *(s + 1) - 160;
    offset = (94 * (qh - 1) + (wh - 1)) * 72L;
    fseek(fp, offset, SEEK_SET);
    fread(buffer, 72, 1, fp);
    for (i = 0; i < 24; i++) //���һ������
      for (j = 0; j < 24; j++)
      {
        if ((mask[j % 8] & buffer[i * 3 + j / 8]) != 0)
        {
          Putpixel64k(x + j, y + i, color);
        }
      }
    s += 2;
    x += 24; //����������24
  }
  fclose(fp);
}

void prt_asc16(int x, int y, char *s, unsigned int color) //���һ��Ӣ�ĺ���
{

  FILE *fp = NULL;
  int i = 0;
  int j = 0;
  unsigned long offset = 0;
  char buffer[16] = {0};
  if ((fp = fopen("hzk\\ASC16", "rb")) == NULL)
  {
    printf("asc16 wrong!");
    exit(1);
  }
  while (*s)
  {
    offset = *s * 16L; //����λ����
    fseek(fp, offset, 0);
    fread(buffer, 16, 1, fp); //������ģ��Ϣ

    for (i = 0; i < 16; i++)
    {
      for (j = 0; j < 8; j++)
      {
        if ((buffer[i] >> (7 - j)) & 0x1)
        { //Ϊ1��λ��ʾ
          Putpixel64k(x + j, y + i, color);
        }
      }
    }
    s++;
    x += 10;
  }
  fclose(fp);
}

void prt_asc16_ch(int x, int y, char s, unsigned int color) //���һ��Ӣ�ĺ���
{

  FILE *fp = NULL;
  int i = 0;
  int j = 0;
  unsigned long offset = 0;
  char buffer[16] = {0};
  unsigned char mask[] = {0x80, 0x40, 0x20,
                          0x10, 0x08, 0x04, //�������γ�ÿһλ����Ϣ
                          0x02, 0x01};
  if ((fp = fopen("hzk\\ASC16", "rb")) == NULL)
  {
    printf("asc16 wrong!");
    getch();
    exit(1);
  }
  offset = s * 16L; //����λ����
  fseek(fp, offset, 0);
  fread(buffer, 16, 1, fp); //������ģ��Ϣ
  for (i = 0; i < 16; i++)
  {
    for (j = 0; j < 8; j++)
    {
      if ((mask[j] & buffer[i]) != 0)
      {
        Putpixel64k(x + j, y + i, color);
      }
    }
  }
  fclose(fp);
}

void Read_Asc16(char key, unsigned char *buffer)
{
  unsigned long offset = 0;
  FILE *fp = NULL;
  if ((fp = fopen("hzk\\ASC16", "rb")) == NULL)
  {
    printf("asc16 wrong!");
    getch();
    exit(1);
  }
  offset = key * 16L; //����λ����
  fseek(fp, offset, 0);
  fread(buffer, 16, 1, fp); //������ģ��Ϣ
  fclose(fp);
}

void Put_Asc16(int x, int y, char key, unsigned int color)
{
  int i = 0;
  int j = 0;
  unsigned char buffer[16];
  unsigned char mask[] = {0x80, 0x40, 0x20,
                          0x10, 0x08, 0x04, //�������γ�ÿһλ����Ϣ
                          0x02, 0x01};
  Read_Asc16(key, buffer);
  for (i = 0; i < 16; i++)
    for (j = 0; j < 8; j++)
      if ((mask[j] & buffer[i]) != 0)
        Putpixel64k(x + i, y + j, color);
}

/*��ʾ�Ŵ���Ӣ���ַ�*/
void Put_Asc16_Size(int x, int y, int xsize, int ysize, char key,
                    unsigned int color)
{
  int i = 0;
  int j = 0;
  int m = 0;
  int n = 0;
  unsigned char buffer[16] = {0};
  unsigned char mask[] = {0x80, 0x40, 0x20,
                          0x10, 0x08, 0x04, //�������γ�ÿһλ����Ϣ
                          0x02, 0x01};
  Read_Asc16(key, buffer);
  for (i = 0; i < 16; i++)
    for (j = 0; j < 8; j++)
      for (m = 1; m <= ysize; m++)
        for (n = 1; n <= xsize; n++)
          if ((mask[j] & buffer[i]) != 0)
            Putpixel64k(x + j * xsize + n, y + m + i * ysize, color);
}

/*��ʾ�Ŵ���Ӣ�ĺ������ַ���*/
void put_asc16_size(int x, int y, int xsize, int ysize, char *s,
                    unsigned int color)
{
  int i = 0;
  for (i = 0; s[i] != 0; i++)
  {
    Put_Asc16_Size(x + i * xsize * 8, y, xsize, ysize, s[i], color);
  }
}

/*x,y��ʾ�������λ�ã�xsize,ysizeΪ�Ŵ�����sΪ���ִ���color��ʾ������ɫ��name
 * Ϊ���ֿ��ļ�·������������Ϣ*/
void prt_hz16_size(int x, int y, int xsize, int ysize, char *s,
                   unsigned int color, char *name)
{
  FILE *fp;
  char buffer[32]; //������ȡ16���ֵ�32λ��ģ
  int i = 0;
  int j = 0;
  int m = 0;
  int n = 0;
  unsigned char qh = 0; //�������㺺��λ�ź�����
  unsigned char wh = 0;
  unsigned long offset = 0; //��¼λ����
  unsigned char mask[] = {0x80, 0x40, 0x20,
                          0x10, 0x08, 0x04, //�������γ�ÿһλ����Ϣ
                          0x02, 0x01};
  if ((fp = fopen(name, "rb")) == NULL)
  {
    printf("Can't open hzk16!");
    getch();
    exit(0);
  }
  while (*s != 0)
  {                //�����ִ�δ���꣬�����
    qh = *s - 160; //�������ź�λ��
    wh = *(s + 1) - 160;
    offset = (94L * (qh - 1) + (wh - 1)) * 32; //���㺺�ֵĵ�ַ��
    fseek(fp, offset, 0);                      //���ֿ��ļ��в�������λ��
    fread(buffer, 32, 1, fp);                  //��ȡ��Ӧλ�õ���ģ
    for (i = 0; i < 16; i++)
    { //��ָ�������һ������
      for (j = 0; j < 16; j++)
      {
        if ((mask[j % 8] & buffer[i * 2 + j / 8]) != 0)
        {
          for (m = 0; m < xsize; m++)
          {
            for (n = 0; n < ysize; n++)
            {
              Putpixel64k(x + j * xsize + m, y + i * ysize + n, color);
            }
          }
        }
      }
    }
    x += 16 * xsize; //������������Ϊ16*xsize
    s += 2;          //��ȡ��һ������
  }
  fclose(fp);
}

/*�������16*16��������16*16asc�ַ����ַ���������x,y��ʾ�������λ�ã�xsize,ysizeΪ�Ŵ�����sΪ����ַ�����
color��ʾ�ַ���ɫ��name Ϊ���ֿ��ļ�·������������Ϣ*/
void prt_hz16_asc16_size(int x, int y, int xsize, int ysize, char *s,
                         unsigned int color, char *name)
{
  FILE *fp1 = NULL;
  FILE *fp2 = NULL;
  char buffer1[16] = {0}; //������ȡ16ascll�ַ���16λ��ģ
  char buffer2[32] = {0}; //������ȡ16���ֵ�32λ��ģ
  int i = 0;
  int j = 0;
  int m = 0;
  int n = 0; //ѭ������
  unsigned char qh = 0;
  unsigned char wh = 0;     //�������㺺����λ��
  unsigned long offset = 0; //��¼λ����
  unsigned char mask[] = {0x80, 0x40, 0x20,
                          0x10, 0x08, 0x04, //�������γ���ģÿһλ����Ϣ
                          0x02, 0x01};
  if ((fp1 = fopen("hzk\\ASC16", "rb")) == NULL)
  {
    CloseSVGA();
    printf("asc16 wrong!");
    getch();
    exit(1);
  }
  if ((fp2 = fopen(name, "rb")) == NULL)
  {
    CloseSVGA();
    printf("Can't open hzk16!");
    getch();
    exit(0);
  }

  while (*s != 0)
  { //������ַ���δ���꣬�����
    if ((*s & 0x80) == 0)
    {                    //�����ַ��ֽ����λΪ0���������ֽ�ASCII�룬����ַ�
      offset = *s * 16L; //����λ����
      fseek(fp1, offset, 0);
      fread(buffer1, 16, 1, fp1); //������ģ��Ϣ
      for (i = 0; i < 16; i++)
      { //��ָ�������һ���Ŵ����ַ�
        for (j = 0; j < 8; j++)
        {
          if (mask[j] & buffer1[i])
          {
            for (m = 0; m < xsize; m++)
            {
              for (n = 0; n < ysize; n++)
              {
                Putpixel64k(x + j * xsize + m, y + 2 * ysize + i * ysize + n,
                            color); // y+2*ysize��Ϊ��ƽ�⺺����Ӣ���ַ��ĸ߶�
              }
            }
          }
        }
      }
      x += 8 * xsize; //������������Ϊ8*xsize
      s++;            //��ȡ��һ���ַ�
    }
    else if ((*s & 0x80) !=
             0)
    {                //�����ַ��ֽ����λΪ1���������ֽ�Ϊ��������һ���֣��������
      qh = *s - 160; //�������ź�λ��
      wh = *(s + 1) - 160;
      offset = (94L * (qh - 1) + (wh - 1)) * 32; //���㺺�ֵĵ�ַ��
      fseek(fp2, offset, 0);                     //���ֿ��ļ��в�������λ��
      fread(buffer2, 32, 1, fp2);                //��ȡ��Ӧλ�õ���ģ
      for (i = 0; i < 16; i++)
      { //��ָ�������һ���Ŵ��ĺ���
        for (j = 0; j < 16; j++)
        {
          if ((mask[j % 8] & buffer2[i * 2 + j / 8]) != 0)
          {
            for (m = 0; m < xsize; m++)
            {
              for (n = 0; n < ysize; n++)
              {
                Putpixel64k(x + j * xsize + m, y + i * ysize + n, color);
              }
            }
          }
        }
      }
      x += 16 * xsize; //������������Ϊ16*xsize
      s += 2;          //��ȡ��һ���ַ�
    }
  }
  fclose(fp1);
  fclose(fp2);
}

/*�������24*24��������32*32 asc�ַ����ַ���������x,y��ʾ�������λ�ã�sΪ����ַ�����
color��ʾ�ַ���ɫ��name Ϊ���ֿ��ļ�·������������Ϣ*/
void prt_hz24_asc32(int x, int y, char *s, unsigned int color, char *name)
{
  FILE *fp1 = NULL;
  FILE *fp2 = NULL;
  char buffer1[16] = {0}; //������ȡ12ascll�ַ���12λ��ģ
  char buffer2[72] = {0}; //������ȡ24���ֵ�72λ��ģ
  int i = 0;
  int j = 0;
  int m = 0;
  int n = 0; //ѭ������
  unsigned char qh = 0;
  unsigned char wh = 0;     //�������㺺����λ��
  unsigned long offset = 0; //��¼λ����
  unsigned char mask[] = {0x80, 0x40, 0x20,
                          0x10, 0x08, 0x04, //�������γ���ģÿһλ����Ϣ
                          0x02, 0x01};
  if ((fp1 = fopen("hzk\\ASC16", "rb")) == NULL)
  {
    CloseSVGA();
    printf("asc16 wrong!");
    getch();
    exit(1);
  }
  if ((fp2 = fopen(name, "rb")) == NULL)
  {
    CloseSVGA();
    printf("Can't open hzk24!");
    getch();
    exit(0);
  }
  while (*s != 0)
  { //������ַ���δ���꣬�����
    if ((*s & 0x80) == 0)
    {                    //�����ַ��ֽ����λΪ0���������ֽ�ASCII�룬����ַ�
      offset = *s * 16L; //����λ����
      fseek(fp1, offset, 0);
      fread(buffer1, 16, 1, fp1); //������ģ��Ϣ
      for (i = 0; i < 16; i++)
      { //��ָ�������һ��32*32�ַ�
        for (j = 0; j < 8; j++)
        {
          if (mask[j] & buffer1[i])
          {
            for (m = 0; m < 2; m++)
            {
              for (n = 0; n < 2; n++)
              {
                Putpixel64k(x + j * 2 + m, y - 2 + i * 2 + n,
                            color); // y-2��Ϊ��ƽ�⺺����Ӣ���ַ��ĸ߶�
              }
            }
          }
        }
      }
      x += 8 * 2; //������������Ϊ16
      s++;        //��ȡ��һ���ַ�
    }
    else if ((*s & 0x80) !=
             0)
    {                //�����ַ��ֽ����λΪ1���������ֽ�Ϊ��������һ���֣��������
      qh = *s - 160; //�������ź�λ��
      wh = *(s + 1) - 160;
      offset = (94L * (qh - 1) + (wh - 1)) * 72; //���㺺�ֵĵ�ַ��
      fseek(fp2, offset, 0);                     //���ֿ��ļ��в�������λ��
      fread(buffer2, 72, 1, fp2);                //��ȡ��Ӧλ�õ���ģ
      for (i = 0; i < 24; i++)
      { //��ָ�������һ���Ŵ��ĺ���
        for (j = 0; j < 24; j++)
        {
          if ((mask[j % 8] & buffer2[i * 3 + j / 8]) != 0)
          {
            Putpixel64k(x + j, y + i, color);
          }
        }
      }
      x += 24; //������������Ϊ24
      s += 2;  //��ȡ��һ���ַ�
    }
  }
  fclose(fp1);
  fclose(fp2);
}

/*��������12*24����ҷ��ţ�����*/
void RMB(int x, int y, int xsize, int ysize, unsigned color)
{
  int i = 0;
  int j = 0;
  int m = 0;
  int n = 0; //ѭ������
  int RMB[24][12] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
                     {0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0},
                     {0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                     {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
                     {0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
                     {0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},
                     {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
                     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                     {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
                     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                     {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
                     {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0}}; //���������ͼ�������

  for (i = 0; i < 24; i++)
  {
    for (j = 0; j < 12; j++)
    {
      if (RMB[i][j] != 0)
        for (m = 0; m < xsize; m++)
        {
          for (n = 0; n < ysize; n++)
          {
            Putpixel64k(x + j * xsize + m, y + i * ysize + n, color);
          }
        }
    }
  }
}
/***����꺯��***/
void show_gb(int x, int y) { Line1(x, y, x, y + 32, 0); }

void Getnum(int x1, int y1, char *name, int num, int i)
{
  char showtemp[2] = {0, 0};
  int key; //����ֵ
  int k, temp;
  int border = x1 + 4; // border��ʾ��ʾͼƬ����߽�
  x1 = x1 + 4;
  y1 = y1 + 5;
  /*	for(i=strlen(name)-1;i>=0;i--)
        {
                *showtemp=name[i];
                prt_asc16_ch(x1+i*16,y1-2,showtemp[0],0);
        }*/
  i = strlen(name);
  while (bioskey(1))
  { //������뻺����
    bioskey(0);
  }
  border += 16 * i;
  while (1)
  {                      //�����»س���ʱ��ʾ������ϣ��س���ֵΪ13��
    show_gb(border, y1); //�����˸
    if (bioskey(1) == 0 ||
        !MouseGet(&mouse))
    { //��ʱ������ʹ�����˸���ڵ������������ʱ�˳�
      for (k = 0; k < 100; k++)
      { //��ʱ��ͬʱ���������
        delay(2);
        if (bioskey(1) || MouseGet(&mouse))
        {
          break;
        }
      }
    }
    if (bioskey(1))
    {
      temp = bioskey(0) & 0x00ff;
      if (temp != '\r' && temp != '\n')
      { //������벻Ϊ�س�����������������������
        if (('0' <= temp && temp <= '9') && i < num)
        { //���Ϊ���ֻ���ĸ���»��ߣ����¼
          Bar1(border, y1, border + 16, y1 + 32, 0xffff);
          name[i] = temp; //�ַ���������ַ���
          *showtemp = temp;
          put_asc16_size(border, y1 - 2, 2, 2, showtemp,
                         0); //��ʾ�µ��ַ����ﵽ������ʵ�������ͬ��
          i++;
          name[i] = '\0'; //����ַ�����β
          border += 16;
          show_gb(border, y1);
        }
        else if (temp == '\b' && i > 0)
        { //����Ƿ�Ϊ�˸������������ǰһ���ַ�
          border -= 16;
          Bar1(border, y1, border + 16, y1 + 32, 0xffff);
          i--;
          name[i] = '\0';
          Bar1(border, y1, border + 16, y1 + 32, 0xffff);
          show_gb(border, y1);
        }
      }
      else
      {
        break;
      }
    }
    if (!MouseIn(378, 296, 724, 322) &&
        MouseGet(&mouse))
    { //���������������Ĳ��֣��˳�
      break;
    }
    Bar1(border, y1, border + 16, y1 + 32, 0xffff);
    if (bioskey(1) == 0 ||
        !MouseGet(&mouse))
    { //��ʱ������ʹ�����˸���ڵ������������ʱ�˳�
      for (k = 0; k < 100; k++)
      { //��ʱ��ͬʱ���������
        delay(2);
        if (bioskey(1) || MouseGet(&mouse))
        {
          break;
        }
      }
    }
  }
  Bar1(border, y1, border + 16, y1 + 32, 0xffff);
}
/***��Ϣ����ʱ��������ͬ����***/
void Getinfo(int x1, int y1, char *name, int num, int i)
{
  char showtemp[2] = {0, 0};
  int key; //����ֵ
  int k, temp;
  int border = x1 + 4; // border��ʾ��ʾͼƬ����߽�
  x1 = x1 + 4;
  y1 = y1 + 5;
  /*	for(i=strlen(name)-1;i>=0;i--)
        {
                *showtemp=name[i];
                prt_asc16_ch(x1+i*16,y1-2,showtemp[0],0);
        }*/
  i = strlen(name);
  while (bioskey(1))
  { //������뻺����
    bioskey(0);
  }
  border += 16 * i;
  while (1)
  {                      //�����»س���ʱ��ʾ������ϣ��س���ֵΪ13��
    show_gb(border, y1); //�����˸
    if (bioskey(1) == 0 ||
        !MouseGet(&mouse))
    { //��ʱ������ʹ�����˸���ڵ������������ʱ�˳�
      for (k = 0; k < 100; k++)
      { //��ʱ��ͬʱ���������
        delay(2);
        if (bioskey(1) || MouseGet(&mouse))
        {
          break;
        }
      }
    }
    if (bioskey(1))
    {
      temp = bioskey(0) & 0x00ff;
      if (temp != '\r' && temp != '\n')
      { //������벻Ϊ�س�����������������������
        if (('0' <= temp && temp <= '9' || ('a' <= temp && temp <= 'z') ||
             temp == '_') &&
            i < num)
        { //���Ϊ���ֻ���ĸ���»��ߣ����¼
          Bar1(border, y1, border + 16, y1 + 32, 0xffff);
          name[i] = temp; //�ַ���������ַ���
          *showtemp = temp;
          put_asc16_size(border, y1 - 2, 2, 2, showtemp,
                         0); //��ʾ�µ��ַ����ﵽ������ʵ�������ͬ��
          i++;
          name[i] = '\0'; //����ַ�����β
          border += 16;
          show_gb(border, y1);
        }
        else if ('A' <= temp && temp <= 'Z' &&
                 i < num)
        { //�����ļ��������ִ�Сд����������ļ�����Ҫ���û������ļ���
          //����ע��ʱ�Ͳ����ִ�Сд��
          Bar1(border, y1, border + 16, y1 + 32, 0xffff);
          temp += 32;
          name[i] = temp;   //�ַ���������ַ���
          *showtemp = temp; //��ʾ�µ��ַ����ﵽ������ʵ�������ͬ��
          put_asc16_size(border, y1 - 2, 2, 2, showtemp, 0);
          i++;
          name[i] = '\0'; //����ַ�����β
          border += 16;
          show_gb(border, y1);
        }
        else if (temp == '\b' && i > 0)
        { //����Ƿ�Ϊ�˸������������ǰһ���ַ�
          border -= 16;
          Bar1(border, y1, border + 16, y1 + 32, 0xffff);
          i--;
          name[i] = '\0';
          Bar1(border, y1, border + 16, y1 + 32, 0xffff);
          show_gb(border, y1);
        }
      }
      else
      {
        break;
      }
    }
    if (!MouseIn(378, 296, 724, 322) &&
        MouseGet(&mouse))
    { //���������������Ĳ��֣��˳�
      break;
    }
    Bar1(border, y1, border + 16, y1 + 32, 0xffff);
    if (bioskey(1) == 0 ||
        !MouseGet(&mouse))
    { //��ʱ������ʹ�����˸���ڵ������������ʱ�˳�
      for (k = 0; k < 100; k++)
      { //��ʱ��ͬʱ���������
        delay(2);
        if (bioskey(1) || MouseGet(&mouse))
        {
          break;
        }
      }
    }
  }
  Bar1(border, y1, border + 16, y1 + 32, 0xffff);
}

/***��������ʱ��������ͬ����***/
void Getcode(int x1, int y1, char *code, int num, int i)
{
  int key; //����ֵ
  int k, temp;
  int border = x1 + 4; // border��ʾ��ʾͼƬ����߽�
  x1 = x1 + 4;
  y1 = y1 + 5;
  /*	for(i=strlen(code)-1;i>=0;i--)
        {
                *showtemp=code[i];
                prt_asc16_ch(x1+i*8,y1-2,'*',0);
        }*/
  i = strlen(code);
  while (bioskey(1))
  { //������뻺����
    bioskey(0);
  }
  border += 16 * i;
  while (1)
  { //�����»س���ʱ��ʾ������ϣ��س���ֵΪ13��
    show_gb(border, y1);
    if (bioskey(1) == 0 ||
        !MouseGet(&mouse))
    { //��ʱ������ʹ�����˸���ڵ������������ʱ�˳�
      for (k = 0; k < 100; k++)
      { //��ʱ��ͬʱ���������
        delay(2);
        if (bioskey(1) || MouseGet(&mouse))
        {
          break;
        }
      }
    }
    if (bioskey(1))
    {
      temp = bioskey(0) & 0x00ff;
      if (temp != '\r' && temp != '\n')
      { //������벻Ϊ�س�����������������������
        // if('0'<=temp&&temp<='9'||'a'<=temp&&temp<='z'||'A'<=temp&&temp<='Z')
        // //���Ϊ���ֻ���ĸ�����¼
        if (('0' <= temp && temp <= '9' || 'a' <= temp && temp <= 'z' ||
             temp == '_') &&
            i < num)
        { //���Ϊ���ֻ���ĸ���»��ߣ����¼
          Bar1(border, y1, border + 16, y1 + 32, 0xffff);
          code[i] = temp; //�ַ���������ַ���

          //��ʾ�µ��ַ����ﵽ������ʵ�������ͬ��
          // delay(150);
          Bar1(border, y1, border + 16, y1 + 32, 0xffff);
          put_asc16_size(border, y1 - 2, 2, 2, "_", 0);
          delay(50);
          Bar1(border, y1, border + 16, y1 + 32, 0xffff);
          put_asc16_size(border, y1 - 2, 2, 2, "*", 0);
          i++;
          code[i] = 0; //����ַ�����β
          border += 16;
          show_gb(border, y1);
        }
        else if ('A' <= temp && temp <= 'Z' &&
                 i < num)
        { //�����ļ��������ִ�Сд����������ļ�����Ҫ���û������ļ���
          //����ע��ʱ�Ͳ����ִ�Сд��
          Bar1(border, y1, border + 16, y1 + 32, 0xffff);
          temp += 32;
          code[i] = temp; //�ַ���������ַ���
          //��ʾ�µ��ַ����ﵽ������ʵ�������ͬ��

          // delay(300);
          Bar1(border, y1, border + 16, y1 + 32, 0xffff);
          put_asc16_size(border, y1 - 2, 2, 2, "_", 0);
          delay(100);
          Bar1(border, y1, border + 16, y1 + 32, 0xffff);
          put_asc16_size(border, y1 - 2, 2, 2, "*", 0);
          i++;
          code[i] = 0; //����ַ�����β
          border += 8;
          show_gb(border, y1);
        }
        else if (temp == '\b' && i > 0)
        { //����Ƿ�Ϊ�˸������������ǰһ���ַ�
          border -= 16;
          Bar1(border, y1, border + 16, y1 + 32, 0xffff);
          i--;
          code[i] = 0;
          Bar1(border, y1, border + 16, y1 + 32, 0xffff);
          show_gb(border, y1);
        }
      }
      else
      {
        break;
      }
    }
    if (!MouseIn(378, 296, 724, 322) &&
        MouseGet(&mouse))
    { //���������������Ĳ��֣��˳�
      break;
    }
    Bar1(border, y1, border + 16, y1 + 32, 0xffff);
    if (bioskey(1) == 0 ||
        !MouseGet(&mouse))
    { //��ʱ������ʹ�����˸���ڵ������������ʱ�˳�
      for (k = 0; k < 100; k++)
      { //��ʱ��ͬʱ���������
        delay(2);
        if (bioskey(1) || MouseGet(&mouse))
        {
          break;
        }
      }
    }
  }
  Bar1(border, y1, border + 16, y1 + 32, 0xffff);
}
