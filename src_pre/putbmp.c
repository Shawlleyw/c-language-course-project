#include "headers/status.h"
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char col_val[16];
typedef const float col_weight;
col_weight R_w = 0.299;
col_weight G_w = 0.587;
col_weight B_w = 0.144;

// bmp 256
int EstimateColor(float x)
{
  int up, down;
  float eps, delta;
  eps = 0.5;
  down = floor(x);
  up = down + 1;
  delta = x - down;
  if (delta > eps)
    return up;
  else
    return down;
}

int CalcColor(int r, int g, int b)
{
  float res;
  res = R_w * r + G_w * g + B_w * b;
  return EstimateColor(res);
}

STATUS_CODE PutBmp(int x, int y, char *s)
{
  FILE *fp;
  char ch;
  long begin, w, h;
  unsigned char k;
  unsigned char color[256], R, G, B;
  unsigned int i, j, bit;
  if ((fp = fopen(s, "rb")) == NULL)
  {
    closegraph();
    fprintf(stderr, "%s: not open\n", s);
    ch = getchar();
    return ERROR_CODE;
  }
  fseek(fp, 10l, 0);
  fread(&begin, 4, 1, fp);
  fseek(fp, 18l, 0);
  fread(&w, 4, 1, fp);
  fread(&h, 4, 1, fp);
  fseek(fp, 28l, 0);
  fread(&bit, 2, 1, fp);
  if (bit != 8)
  {
    fclose(fp);
    printf("bit:%d,not 8", bit);
    return 2;
  }
  fseek(fp, 54l, 0);
  for (i = 0; i < 256; i++)
  {
    fread(&B, 1, 1, fp);
    fread(&G, 1, 1, fp);
    fread(&R, 1, 1, fp);
    color[i] = CalcColor(R, G, B);

    fseek(fp, 1, 1);
  }
  for (i = 0; i < h; i++)
  {

    fseek(fp, begin + (w + 3) / 4 * i * 4, 0);

    for (j = 0; j < w; j++)
    {

      fread(&k, 1, 1, fp);
      putpixel(x + j, y + h - i - 1, color[k]);
    }
  }
  fclose(fp);
  return SUCCESS_CODE;
}