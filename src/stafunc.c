#include "headers/stafunc.h"
#include "headers/add.h"
#include "headers/admini.h"
#include "headers/draw.h"
#include "headers/hisbox.h"
#include "headers/hz.h"
#include "headers/info.h"
#include "headers/judge.h"
#include "headers/mouse.h"
#include "headers/recordop.h"
#include "headers/register.h"
#include "headers/relevant.h"
#include "headers/run.h"
#include "headers/status.h"
#include "headers/userdata.h"
#include <bios.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ClickStation(int x, int y)
{
  int l = 0;
  Comfirm(x, y);
  while (1)
  {
    MouseShow(&mouse);
    if (MousePress(806, 528, 826, 548) == 1)
    {
      l = 1;
    }
    else if (MousePress(629, 480, 649, 500) == 1)
    {
      l = 2;
    }
    else if (MousePress(443, 389, 463, 409) == 1)
    {
      l = 3;
    }
    else if (MousePress(250, 355, 270, 375) == 1)
    {
      l = 4;
    }
    else if (MousePress(55, 353, 75, 373) == 1)
    {
      l = 5;
    }
    else if (MousePress(130, 166, 150, 186) == 1)
    {
      l = 6;
    }
    else if (MousePress(192, 62, 212, 82) == 1)
    {
      l = 7;
    }
    else if (MousePress(337, 8, 357, 28) == 1)
    {
      l = 8;
    }
    else if (MousePress(469, 7, 489, 27) == 1)
    {
      l = 9;
    }
    else if (MousePress(620, 5, 640, 25) == 1)
    {
      l = 10;
    }
    else if (MousePress(801, 2, 821, 22) == 1)
    {
      l = 11;
    }
    else if (MousePress(998, 77, 1018, 97) == 1)
    {
      l = 12;
    }
    else if (MousePress(996, 225, 1016, 245) == 1)
    {
      l = 13;
    }
    else if (MousePress(996, 375, 1016, 395) == 1)
    {
      l = 14;
    }
    else if (MousePress(943, 497, 963, 517) == 1)
    {
      l = 15;
    }
    else if (MousePress(379, 282, 399, 302) == 1)
    {
      l = 16;
    }
    else if (MousePress(377, 72, 397, 92) == 1)
    {
      l = 17;
    }
    else if (MousePress(549, 114, 569, 134) == 1)
    {
      l = 18;
    }
    else if (MousePress(678, 213, 698, 233) == 1)
    {
      l = 19;
    }
    else if (MousePress(847, 270, 867, 290) == 1)
    {
      l = 20;
    }
    else if (MousePress(886, 380, 906, 400) == 1)
    {
      l = 21;
    }
    else if (MousePress(884, 467, 904, 487) == 1)
    {
      l = 22;
    }
    else if (MousePress(19, 200, 39, 220) == 1)
    {
      l = 23;
    }
    else if (MousePress(204, 208, 224, 228) == 1)
    {
      l = 24;
    }
    else if (MousePress(335, 209, 355, 229) == 1)
    {
      l = 25;
    }
    else if (MousePress(532, 312, 552, 332) == 1)
    {
      l = 26;
    }
    else if (MousePress(471, 210, 491, 230) == 1)
    {
      l = 27;
    }
    else if (MousePress(276, 101, 296, 121) == 1)
    {
      l = 28;
    }
    else if (MousePress(x - 60, y + 20, x - 20, y + 60))
    {
      MouseOff(&mouse);
      return l;
    }
    else if (MousePress(x + 20, y + 20, x + 60, y + 60))
    {
      MouseOff(&mouse);
      return 0;
    }
  }
}

void StakInfo(int x, int y, char *name)
{
  Bar1(x - 2, y - 2, x + 300, y + 50, DARKCYAN24);
  puthz(x + 1, y + 1, name, 48, 48, BLACK24);
  puthz(x, y, name, 48, 48, BLACK24);
}

int Stak(int line, int x, int y, int func, int note, int Sflag, int lim)
{
  Sta stations[28] = {
  		{1,816,538,"刘家大湾"},
        {2,639,490,"银河湾"},
        {3,453,399,"龙湾一品"},
        {4,260,365,"金广厦"},
        {5,65,363,"万达广场"},
        {6,140,176,"中心医院"},
        {7,202,72,"鲇鱼墩"},
        {8,347,18,"长湾"},
        {9,479,17,"磁湖梦"},
        {10,630,15,"汇金花园"},
        {11,811,12,"武夷花园"},
        {12,1008,87,"妇幼保健院"},
        {13,1006,235,"明秀山庄"},
        {14,1006,385,"琥珀山庄"},
        {15,953,507,"湖景花园"},
        {16,389,292,"肖铺"},
        {17,387,82,"杭州公馆"},
        {18,559,124,"康乐小区"},
        {19,688,223,"白马山"},
        {20,857,280,"二中"},
        {21,896,390,"新区口"},
        {22,894,477,"宏维星都"},
        {23,29,210,"铜花山庄"},
        {24,214,218,"庙儿咀"},
        {25,345,219,"玉家里"},
        {26,542,322,"怡康花园"},
        {27,481,220,"牧羊湖"},
        {28,286,111,"袁仓"}
  };

  int l = 0;
  int choose = 0;
  int temp_note;
  int cur_station = 0;
  char Dflag[5];
  temp_note = note;
  Mouse_Init();
  while (1)
  {
    MouseShow(&mouse);
    if (MouseIn(806, 528, 826, 548) == 1 &&
        (line == 1 || line == 3 || line == 4 || line == 5 || func != 3) &&
        choose == 0)
    {
      l = 1;
      if (MousePress(806, 528, 826, 548) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        // MouseOff(&mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(629, 480, 649, 500) == 1 && (line == 1 || func != 3) &&
             choose == 0)
    {
      l = 2;
      if (MousePress(629, 480, 649, 500) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(443, 389, 463, 409) == 1 &&
             (line == 1 || line == 4 || line == 5 || func != 3) &&
             choose == 0)
    {
      l = 3;
      if (MousePress(443, 389, 463, 409) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(250, 355, 270, 375) == 1 &&
             (line == 1 || line == 4 || func != 3) && choose == 0)
    {
      l = 4;
      if (MousePress(250, 355, 270, 375) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(55, 353, 75, 373) == 1 &&
             (line == 1 || line == 4 || line == 5 || func != 3) &&
             choose == 0)
    {
      l = 5;
      if (MousePress(55, 353, 75, 373) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(130, 166, 150, 186) == 1 && (line == 1 || func != 3) &&
             choose == 0)
    {
      l = 6;
      if (MousePress(130, 166, 150, 186) && func == 3)
      {
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(192, 62, 212, 82) == 1 && (line == 1 || func != 3) &&
             choose == 0)
    {
      l = 7;
      if (MousePress(192, 62, 212, 82) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(337, 8, 357, 28) == 1 &&
             (line == 1 || line == 3 || func != 3) && choose == 0)
    {
      l = 8;
      if (MousePress(337, 8, 357, 28) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(469, 7, 489, 27) == 1 &&
             (line == 1 || line == 3 || line == 4 || func != 3) &&
             choose == 0)
    {
      l = 9;
      if (MousePress(469, 7, 489, 27) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(620, 5, 640, 25) == 1 &&
             (line == 1 || line == 4 || func != 3) && choose == 0)
    {
      l = 10;
      if (MousePress(620, 5, 640, 25) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(801, 2, 821, 22) == 1 &&
             (line == 1 || line == 4 || func != 3) && choose == 0)
    {
      l = 11;
      if (MousePress(801, 2, 821, 22) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(998, 77, 1018, 97) == 1 &&
             (line == 1 || line == 4 || func != 3) && choose == 0)
    {
      l = 12;
      if (MousePress(998, 77, 1018, 97) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(996, 225, 1016, 245) == 1 &&
             (line == 1 || line == 4 || func != 3) && choose == 0)
    {
      l = 13;
      if (MousePress(996, 225, 1016, 245) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(996, 375, 1016, 395) == 1 &&
             (line == 1 || line == 4 || func != 3) && choose == 0)
    {
      l = 14;
      if (MousePress(996, 375, 1016, 395) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(943, 497, 963, 517) == 1 &&
             (line == 1 || line == 4 || func != 3) && choose == 0)
    {
      l = 15;
      if (MousePress(943, 497, 963, 517) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(379, 282, 399, 302) == 1 && (line == 5 || func != 3) &&
             choose == 0)
    {
      l = 16;
      if (MousePress(379, 282, 399, 302) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(377, 72, 397, 92) == 1 && (line == 4 || func != 3) &&
             choose == 0)
    {
      l = 17;
      if (MousePress(377, 72, 397, 92) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(549, 114, 569, 134) == 1 && (line == 3 || func != 3) &&
             choose == 0)
    {
      l = 18;
      if (MousePress(549, 114, 569, 134) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(678, 213, 698, 233) == 1 &&
             (line == 3 || line == 5 || func != 3) && choose == 0)
    {
      l = 19;
      if (MousePress(678, 213, 698, 233) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(847, 270, 867, 290) == 1 &&
             (line == 3 || line == 5 || func != 3) && choose == 0)
    {
      l = 20;
      if (MousePress(847, 270, 867, 290) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(886, 380, 906, 400) == 1 &&
             (line == 3 || line == 5 || func != 3) && choose == 0)
    {
      l = 21;
      if (MousePress(886, 380, 906, 400) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(884, 467, 904, 487) == 1 &&
             (line == 3 || line == 5 || func != 3) && choose == 0)
    {
      l = 22;
      if (MousePress(884, 467, 904, 487) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(19, 200, 39, 220) == 1 &&
             (line == 3 || line == 4 || line == 5 || func != 3) &&
             choose == 0)
    {
      l = 23;
      if (MousePress(19, 200, 39, 220) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(204, 208, 224, 228) == 1 &&
             (line == 3 || line == 5 || func != 3) && choose == 0)
    {
      l = 24;
      if (MousePress(204, 208, 224, 228) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(335, 209, 355, 229) == 1 && (line == 5 || func != 3) &&
             choose == 0)
    {
      l = 25;
      if (MousePress(335, 209, 355, 229) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(532, 312, 552, 332) == 1 &&
             (line == 4 || line == 5 || func != 3) && choose == 0)
    {
      l = 26;
      if (MousePress(532, 312, 552, 332) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(471, 210, 491, 230) == 1 && (line == 4 || func != 3) &&
             choose == 0)
    {
      l = 27;
      if (MousePress(471, 210, 491, 230) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MouseIn(276, 101, 296, 121) == 1 && (line == 3 || func != 3) &&
             choose == 0)
    {
      l = 28;
      if (MousePress(276, 101, 296, 121) && func == 3)
      {
        MouseOff(&mouse);
        return l;
      }
      if (cur_station == l)
      {
        continue;
      }
      else if (cur_station != l)
      {
        cur_station = l;
        MouseOff(&mouse);
        Circlefill(stations[l - 1].x, stations[l - 1].y, 9, GREEN24);
        MouseOn(mouse);
        StakInput(func, stations[l - 1].name, l, x, y, Sflag);
      }
    }
    else if (MousePress(906, 710, 1022, 766) && choose == 0)
    {
      MouseOff(&mouse);
      return temp_note;
    }
    else if (MousePress(412, 670, 612, 720) && func == 2 && choose == 0 &&
             lim == 1)
    {
      RecordBox(1);
      choose = 1;
    }
    else if (MousePress(659, 589, 709, 639) && func == 2 && choose == 1 &&
             lim == 1)
    {
      MouseOff(&mouse);
      YNbut(2);
      temp_note = 1;
      YNbut(4);
      MouseOn(mouse);
    }
    else if (MousePress(712, 589, 762, 639) && func == 2 && choose == 1 &&
             lim == 1)
    {
      MouseOff(&mouse);
      YNbut(3);
      temp_note = 0;
      YNbut(4);
      MouseOn(mouse);
    }
    else if (MousePress(759, 649, 809, 699) && func == 2 && choose == 1 &&
             lim == 1)
    {
      MouseOff(&mouse);
      YNbut(5);
      temp_note = 2;
      YNbut(1);
      MouseOn(mouse);
    }
    else if (MousePress(784, 710, 900, 766) && func == 2 && choose == 1 &&
             lim == 1)
    {
      MouseOff(&mouse);
      note = temp_note;
      Bar1(0, 560, 1024, 768, DARKCYAN24);
      Bar1(414, 672, 614, 722, BLACK24);
      Bar1(412, 670, 612, 720, LIGHTGRAY24);
      CirclePoint(16,600,GREEN24);
      Bar1(32,586,106,614,DARKGRAY24);
      puthz(33,588,"起点站",24,24,LIGHTGRAY24);
      CirclePoint(16,640,NAVY24);
      Bar1(32,626,106,654,DARKGRAY24);
      puthz(33,628,"终点站",24,24,LIGHTGRAY24);
      puthz(416, 671, "发热上报", 48, 48, BLACK24);
      returnbut();
      choose = 0;
      MouseOn(mouse);
    }
    else if (MousePress(906, 710, 1022, 766) && func == 2 && choose == 1 &&
             lim == 1)
    {
      MouseOff(&mouse);
      note = temp_note;
      Bar1(0, 560, 1024, 768, DARKCYAN24);
      Bar1(414, 672, 614, 722, BLACK24);
      Bar1(412, 670, 612, 720, LIGHTGRAY24);
      CirclePoint(16,600,GREEN24);
      Bar1(32,586,106,614,DARKGRAY24);
      puthz(33,588,"起点站",24,24,LIGHTGRAY24);
      CirclePoint(16,640,NAVY24);
      Bar1(32,626,106,654,DARKGRAY24);
      puthz(33,628,"终点站",24,24,LIGHTGRAY24);
      puthz(416, 671, "发热上报", 48, 48, BLACK24);
      returnbut();
      choose = 0;
      MouseOn(mouse);
    }
    else if (choose == 0 &&
             MouseIn(stations[l - 1].x - 10, stations[l - 1].y - 10,
                     stations[l - 1].x + 10, stations[l - 1].y + 10) == 0)
    {
      Circlefill(stations[l - 1].x, stations[l - 1].y, 9, LIGHTRED24);
      cur_station = 0;
    }
  }
}

void StationName(int Sflag, int Station, char *name)
{
  if (Station < 0)
    return;
  if (Sflag == 1)
  { 
    Bar1(208, 598, 462, 662, BLACK24);
    Bar1(212, 602, 458, 658, LIGHTGRAY24);
    puthz(217, 606, name, 48, 48, BLACK24);
  }
  else if (Sflag == 2)
  { 
    Bar1(562, 598, 816, 662, BLACK24);
    Bar1(566, 602, 812, 658, LIGHTGRAY24);
    puthz(571, 606, name, 48, 48, BLACK24);
  }
}

void ShowSta(int line)
{

  puthz(301, 601, "站名", 48, 48, BLACK24);
  puthz(300, 600, "站名", 48, 48, BLACK24);
  put_asc16_size(405, 600, 3, 3, ":", BLACK24);
  Stak(line, 450, 600, 1, 0, 0, 0);
}

void StakInput(int func, char *name, int station, int x, int y, int Sflag)
{
  if (func == 3)
  {
    StationName(Sflag, station, name);
  }
  else if (func == 1 || func == 2)
  {
    StakInfo(x, y, name);
  }
}
