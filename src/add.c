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
#include "headers/stafunc.h"
#include "headers/status.h"
#include "headers/trvldata.h"
#include "headers/userdata.h"
#include <bios.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AddHis(char *account, int line, UserInfo *user,
            int page)
{
  int LEN1;
  int start = 0;
  int end = 0;
  int Dflag = 1;
  char year[12];
  char month[3];
  char day[3];
  char bnum[4];
  char time[10];
  char btime[16];
  char route_name[16];
  char note[64];
  HisLi temp;
  int yi, mi, di, ni, bi;
  temp.note = 3;
  year[0] = '\0';
  month[0] = '\0';
  day[0] = '\0';
  bnum[0] = '\0';
  note[0] = '\0';
  btime[0] = '\0';
  route_name[0] = '\0';
  Bar1(0, 560, 1024, 768, LIGHTGRAY24);
  AddBox1();
  Bar1(334, 717, 494, 760, BLACK24);
  Bar1(332, 716, 492, 758, DARKGRAY24);
  Bar1(534, 717, 694, 760, BLACK24);
  Bar1(532, 716, 692, 758, DARKGRAY24);
  puthz(364, 721, "上一页", 32, 32, BLACK24);
  puthz(564, 721, "下一页", 32, 32, BLACK24);
  Mouse_Init();
  while (1) {
    MouseShow(&mouse);
    if (MousePress(532, 716, 692, 758)) {
      if (Dflag == 1) {
        MouseOff(&mouse);
        AddBox2();
        Dflag++;
        delay(100);
        MouseOn(mouse);
      } else if (Dflag == 2) {
        MouseOff(&mouse);
        yi = strlen(year);
        mi = strlen(month);
        di = strlen(day);
        if (JudgeTime(year, month, day, yi, mi, di) == SUCCESS_CODE) {
          mi = strlen(month);
          di = strlen(day);
          Connect(year, month, day, time, route_name, bnum, 1, btime, page,
                  line);
          Connect(year, month, day, time, route_name, bnum, 2, btime, page,
                  line);

          if(UserExistedOnBus(route_name,user->name)==1) {
            Errortime();
            DisplayLine(line, page == 2);
            DisplayTraces(line, start, end, page == 2, line == 1);
            year[0] = '\0';
            month[0] = '\0';
            day[0] = '\0';
            bnum[0] = '\0';
            AddBox2();
            continue;
          }


          AddBox3();
          if (temp.note == 1) {
            YNbut(2);
          } else if (temp.note == 0) {
            YNbut(3);
          } else if (temp.note == 2) {
            YNbut(5);
          } else if (temp.note == 3) {
            YNbut(1);
          }
          Dflag++;
          delay(100);
        } else if (JudgeTime(year, month, day, yi, mi, di) == ERROR_CODE) {
          InputError(line, start, end, page == 2, line == 1, 1);
        }
        MouseOn(mouse);
      }
    } else if (MousePress(332, 716, 492, 758)) {
      if (Dflag == 3) {
        AddBox2();
        put_asc16_size(149, 641, 2, 2, year, BLACK24);
        put_asc16_size(337, 641, 2, 2, month, BLACK24);
        put_asc16_size(494, 641, 2, 2, day, BLACK24);
        put_asc16_size(653, 641, 2, 2, bnum, BLACK24);
        Dflag--;
        delay(100);
      } else if (Dflag == 2) {
        AddBox1();
        Dflag--;
        delay(100);
      }
    } else if (MousePress(212, 602, 458, 658) && Dflag == 1 && start == 0) {
      MouseOff(&mouse);
      Bar1(212, 602, 458, 658, LIGHTGRAY24);
      start = Stak(line, 335, 658, 3, 0, 1, 0);
      // Bar1(212,663,458,713,LIGHTGRAY24);

      if (start != 0 && end != 0) {
        if (DisplayTraces(line, start, end, page == 2, line == 1) ==
            ERROR_CODE) {
          ErrorTrace();
          DisplayLine(line, page == 2);
          AddBox1();
          Dflag = 1;
          start=0;
          end=0;
        }
      }
      MouseOn(mouse);
    } else if (MousePress(566, 602, 812, 658) && Dflag == 1 && end == 0) {
      MouseOff(&mouse);
      Bar1(566, 602, 812, 658, LIGHTGRAY24);
      end = Stak(line, 689, 658, 3, 0, 2, 0);
      // Bar1(566,663,812,713,LIGHTGRAY24);

      if (start != 0 && end != 0) {
        if (DisplayTraces(line, start, end, page == 2, line == 1) ==
            ERROR_CODE) {
          ErrorTrace();
          DisplayLine(line, page == 2);
          AddBox1();
          Dflag = 1;
          start=0;
          end=0;
        }
      }
      MouseOn(mouse);
    } else if (MousePress(906, 710, 1022, 766)) {
      Maps();
      NextPage();
      Dflag = 1;
      break;
    } else if (MousePress(145, 642, 275, 692) && Dflag == 2) {
      MouseOff(&mouse);
      yi = strlen(year);
      Getnum(149, 643, year, 4, yi);
      MouseOn(mouse);
    } else if (MousePress(333, 642, 433, 692) && Dflag == 2) {
      MouseOff(&mouse);
      mi = strlen(month);
      Getnum(337, 643, month, 2, mi);
      MouseOn(mouse);
    } else if (MousePress(491, 642, 591, 692) && Dflag == 2) {
      MouseOff(&mouse);
      di = strlen(day);
      Getnum(494, 643, day, 2, di);
      MouseOn(mouse);
    } else if (MousePress(649, 642, 810, 692) && Dflag == 2) {
      MouseOff(&mouse);
      bi = strlen(bnum);
      Getnum(653, 643, bnum, 2, bi);
      MouseOn(mouse);
    } else if (MousePress(659, 589, 709, 639) && Dflag == 3) {
      MouseOff(&mouse);
      YNbut(2);
      temp.note = 1;
      YNbut(4);
      MouseOn(mouse);
    } else if (MousePress(712, 589, 762, 639) && Dflag == 3) {
      MouseOff(&mouse);
      YNbut(3);
      temp.note = 0;
      YNbut(4);
      MouseOn(mouse);
    } else if (MousePress(759, 649, 809, 699) && Dflag == 3) {
      MouseOff(&mouse);
      YNbut(5);
      YNbut(1);
      temp.note = 2;
      MouseOn(mouse);
    } else if (MousePress(784, 710, 900, 766) && Dflag == 3) {
      strcpy(temp.time, time);
      temp.line_no = line;
      temp.start = start;
      temp.end = end;
      strcpy(temp.busnum, route_name);

      UserNewTravel(account, &temp, user);
      delay(100);
      RouteNewPassenger(line, route_name, &temp, user->name);
      Maps();
      NextPage();
      Dflag = 1;
      break;
    }
  }
}

void AddFunc(UserInfo *user)
{
  int page = 1;
  int line = 0;
  Maps();
  NextPage();
  Mouse_Init();
  while (1) {
    MouseShow(&mouse);
    if (MousePress(218, 96, 806, 174)) {
      MouseOff(&mouse);
      line = 1;
      DisplayLine(line, page == 2);
      AddHis(user->account, line, user, page);
      page = 1;
      MouseOn(mouse);
    } else if (MousePress(218, 96 + 170, 806, 174 + 170)) {
      MouseOff(&mouse);
      line = 3;
      DisplayLine(line, page == 2);
      AddHis(user->account, line, user, page);
      page = 1;
      MouseOn(mouse);
    } else if (MousePress(218, 96 + 340, 806, 174 + 340)) {
      MouseOff(&mouse);
      line = 4;
      DisplayLine(line, page == 2);
      AddHis(user->account, line, user, page);
      page = 1;
      MouseOn(mouse);
    } else if (MousePress(218, 96 + 510, 806, 174 + 510)) {
      MouseOff(&mouse);
      line = 5;
      DisplayLine(line, page == 2);
      AddHis(user->account, line, user, page);
      page = 1;
      MouseOn(mouse);
    } else if (MousePress(377, 710, 647, 766)) {
      MouseOff(&mouse);
      if (page == 2) {
        Maps();
        NextPage();
        page = 1;
      } else if (page == 1) {
        RSelectMaps();
        page = 2;
      }
      MouseOn(mouse);
    } else if (MousePress(906, 710, 1022, 766)) {
      MouseOff(&mouse);
      DrawMainPage();
      break;
    }
  }
}

STATUS_CODE SelectMap()
{
  Maps();
  Mouse_Init();
  while (1) {
    MouseShow(&mouse);
    if (MousePress(218, 96, 806, 174)) {
      MouseOff(&mouse);
      Bar1(0, 0, 1024, 768, DARKCYAN24);
      returnbut();
      DisplayLine(1, 0);
      ShowSta(1);
      Maps();
      MouseOn(mouse);
    } else if (MousePress(218, 96 + 170, 806, 174 + 170)) {
      MouseOff(&mouse);
      Bar1(0, 0, 1024, 768, DARKCYAN24);
      returnbut();
      DisplayLine(3, 0);
      ShowSta(3);
      Maps();
      MouseOn(mouse);
    } else if (MousePress(218, 96 + 340, 806, 174 + 340)) {
      MouseOff(&mouse);
      Bar1(0, 0, 1024, 768, DARKCYAN24);
      returnbut();
      DisplayLine(4, 0);
      ShowSta(4);
      Maps();
      MouseOn(mouse);
    } else if (MousePress(218, 96 + 510, 806, 174 + 510)) {
      MouseOff(&mouse);
      Bar1(0, 0, 1024, 768, DARKCYAN24);
      returnbut();
      DisplayLine(5, 0);
      ShowSta(5);
      Maps();
      MouseOn(mouse);
    } else if (MousePress(906, 710, 1022, 766)) {
      MouseOff(&mouse);
      DrawMainPage();
      break;
    }
  }
  return SUCCESS_CODE;
}
