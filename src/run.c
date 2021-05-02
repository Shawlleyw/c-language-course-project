#include "headers/run.h"
#include "headers/add.h"
#include "headers/admini.h"
#include "headers/calcpath.h"
#include "headers/draw.h"
#include "headers/hisbox.h"
#include "headers/hz.h"
#include "headers/info.h"
#include "headers/judge.h"
#include "headers/mouse.h"
#include "headers/recordop.h"
#include "headers/register.h"
#include "headers/relevant.h"
#include "headers/stafunc.h"
#include "headers/status.h"
#include "headers/userdata.h"
#include <bios.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CheckRound(char *name)
{
  int i, len;
  len = strlen(name);
  for (i = 0; i < len; i++)
  {
    if (name[i] >= 'a' && name[i] <= 'z')
    {
      if (name[i] == 'a' || name[i] == 'b')
        return 1;
      else
        return 0;
    }
  }
  return 0;
}
int CheckRev(char *name)
{
  int i, len;
  len = strlen(name);
  for (i = 0; i < len; i++)
  {
    if (name[i] >= 'a' && name[i] <= 'z')
    {
      if (name[i] == 'b' || name[i] == 'f' || name[i] == 'i' || name[i] == 'n')
        return 1;
      else
        return 0;
    }
  }
  return 0;
}

void ReadLineInfo(Lines *l, int line)
{
  char path[32];
  FILE *fp;
  CalcRoutePath(path, line);
  fp = fopen(path, "rb");
  fread(l, sizeof(Lines), 1, fp);
  fclose(fp);
  fp = NULL;
}

void DrawStart(int start)
{
  char path[32];
  Sta cur;
  FILE *fp;
  CalcStationPath(path, start);
  fp = fopen(path, "rb");
  fread(&cur, sizeof(Sta), 1, fp);
  Circlefill(cur.x, cur.y, 9, LIGHTRED24);
  fclose(fp);
  fp = NULL;
}

void DrawEnd(int end)
{
  char path[32];
  Sta cur;
  FILE *fp;
  CalcStationPath(path, end);
  fp = fopen(path, "rb");
  fread(&cur, sizeof(Sta), 1, fp);
  Circlefill(cur.x, cur.y, 9, LIGHTRED24);
  fclose(fp);
  fp = NULL;
}

void ReverseRoute(Lines *l)
{
  Lines temp;
  int i;
  temp.n = l->n;
  for (i = 1; i <= l->n; i++)
    temp.station_numbers[i] = l->station_numbers[l->n + 1 - i];
  *l = temp;
}
STATUS_CODE DrawTraces(Lines *l, int ids, int ide)
{
  int i;
  Sta cur, pre;
  char path[32];
  FILE *fp;
  for (i = ids; i <= ide; i++)
  {
    CalcStationPath(path, l->station_numbers[i]);
    fp = fopen(path, "rb");
    if (fp == NULL)
    {
      CloseSVGA();
      fprintf(stderr, "fopen error\n");
      // while(1);
      return ERROR_CODE;
    }
    fread(&cur, sizeof(cur), 1, fp);
    fclose(fp);
    fp = NULL;
    if (i != ids)
      Line_Thick(cur.x, cur.y, pre.x, pre.y, 6, LIGHTGRAY24);
    pre = cur;
  }
  return SUCCESS_CODE;
}

STATUS_CODE PaintStations(Lines *l, int ids, int ide)
{
  char path[32];
  int i;
  FILE *fp;
  Sta cur;
  for (i = ids + 1; i < ide; i++)
  {
    fp = fopen(CalcStationPath(path, l->station_numbers[i]), "rb");
    fread(&cur, sizeof(cur), 1, fp);
    if (cur.number < 50)
      Circlefill(cur.x, cur.y, 9, LIGHTRED24);
    fclose(fp);
    fp = NULL;
  }
  return SUCCESS_CODE;
}

STATUS_CODE DisplayTraces(int line, int start, int end, int rev, int round)
{
  int ids = -1, ide = -1, i, circle = 0;
  Lines l;
  ReadLineInfo(&l, line);
  if (rev == 1)
    ReverseRoute(&l);
  for (i = 1; i <= l.n; i++)
  {
    if (l.station_numbers[i] == start)
      ids = i;
    if (l.station_numbers[i] == end)
      ide = i;
  }
  if (ids >= ide)
  {
    if (!round)
      return ERROR_CODE;
    else
      circle = 1;
  }
  if (circle)
  {
    l.station_numbers[++l.n] = l.station_numbers[1];
    DrawTraces(&l, ids, l.n);
    PaintStations(&l, ids, l.n);
    DrawTraces(&l, 1, ide);
    PaintStations(&l, 0, ide);
  }
  else
  {
    DrawTraces(&l, ids, ide);
    PaintStations(&l, ids, ide);
  }
  DrawStart(start);
  DrawEnd(end);
  return SUCCESS_CODE;
}

char *CalcMapName(char *path, int line)
{
  int len;
  strcpy(path, "data/maps/ditu");
  len = strlen(path);
  path[len] = line + '0';
  path[len + 1] = '\0';
  strcat(path, ".bmp");
  return path;
}

STATUS_CODE DisplayLine(int line)
{
  char path[32];
  Bar1(0, 0, 1024, 560, DARKCYAN24);
  CalcMapName(path, line);
  Readbmp64k(0, 0, path);
  return SUCCESS_CODE;
}

STATUS_CODE RunFunc(char *user_account)
{
  STATUS_CODE flag;
  UserInfo user;
  GetUserInfo(&user, user_account);
  DrawMainPage();
  Mouse_Init();
  while (1)
  {
    MouseShow(&mouse);
    if (MousePress(322, 198, 704, 272))
    {
      MouseOff(&mouse);
      SelectMap();
      MouseOn(mouse);
    }
    else if (MousePress(322, 328, 704, 402))
    {
      MouseOff(&mouse);
      AddFunc(&user);
      MouseOn(mouse);
    }
    else if (MousePress(322, 458, 704, 532))
    {
      MouseOff(&mouse);
      HisBoxFunc(&user);
      MouseOn(mouse);
    }
    else if (MousePress(904, 708, 1024, 768))
    {
      MouseOff(&mouse);
      break;
    }
  }

  return SUCCESS_CODE;
}
