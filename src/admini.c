#include "headers/admini.h"
#include "headers/add.h"
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


void SPeople(int x, int y)
{
  int x1, y1;
  char name[6];
  Circlefill(x, y, 25, WHITE24);
  Circle(x, y, 25, BLACK24);
  Circle(x, y, 26, BLACK24);
  Circlefill(x, y - 5, 10, BLUE24);
  for (y1 = y + 25; y1 > y + 5; y1--) {
    for (x1 = x; x1 >= x - 15; x1--) {
      if ((x - x1) * (x - x1) + (y - y1) * (y - y1) == 625) {
        Line_Thick(x, y, x1, y1 - 2, 4, BLUE24);
      }
    }
    for (x1 = x; x1 <= x + 15; x1++) {

      if (((x1 - x) * (x1 - x) + (y - y1) * (y - y1) == 625)) {
        Line_Thick(x, y, x1, y1 - 2, 4, BLUE24);
      }
    }
  }
  puthz(x + 40, y - 24, "用户", 48, 48, BLACK24);
}

void ShUsers(char users[][16])
{
  int i;
  int j;
  /*Bar1(110,120,914,670,DARKCYAN24);*/
  prt_hz16_size(382, 32, 4, 4, "用户列表", DARKGRAY24, "HZK\\hzk16");
  prt_hz16_size(384, 30, 4, 4, "用户列表", BLACK24, "HZK\\hzk16");
  for (j = 0; j < 2; j++) {
    for (i = 0; i < 8; i++) {
      Bar1(111 + j * 400, 130 + i * 60, 511 + j * 400, 190 + i * 60, BLACK24);

      Bar1(113 + j * 400, 132 + i * 60, 509 + j * 400, 188 + i * 60,
           LIGHTGRAY24);

      SPeople(140 + j * 400, 160 + 60 * i);
      if(*users[i+j*8]) {
        put_asc16_size(300 + j * 400, 136 + 60 * i, 3, 3, users[i + j * 8],
                       BLACK24);
      }
    }
  }
}

void UserHis(UserInfo *user, int page)
{
  int i, rows;
  put_asc16_size(120, 32, 4, 4, user->name, BLACK24);
  prt_hz16_size(273, 32, 4, 4, "的行程记录", DARKGRAY24, "HZK\\hzk16");
  prt_hz16_size(271, 30, 4, 4, "的行程记录", BLACK24, "HZK\\hzk16");
  Bar1(130, 140, 894, 250, LIGHTGRAY24);
  Bar1(130, 260, 894, 370, LIGHTGRAY24);
  Bar1(130, 380, 894, 490, LIGHTGRAY24);
  Bar1(130, 500, 894, 610, LIGHTGRAY24);
  Bar1(132, 142, 892, 248, NAVY24);
  Bar1(132, 262, 892, 368, NAVY24);
  Bar1(132, 382, 892, 488, NAVY24);
  Bar1(132, 502, 892, 608, NAVY24);
  for (i = 0; i < 4; i++) {
    if (user->history_lines[(page - 1) * 4 + i].note == 0 &&
        user->nhistory > (page - 1) * 4 + i) {
      InfoName(0, i);
      RouteWrite(450,149+i*120,user,i,page);
      StaName(user->history_lines[(page - 1) * 4 + i].start, 258,
              199 + (i * 120));
      StaName(user->history_lines[(page - 1) * 4 + i].end, 570,
              199 + (i * 120));
      ShowTime(user->history_lines[(page - 1) * 4 + i].time, 250,
               149 + i * 120);
      ShowTime(user->history_lines[(page - 1) * 4 + i].busnum , 570,
               149 + i * 120);
    } else if (user->history_lines[(page - 1) * 4 + i].note == 1 &&
               user->nhistory > (page - 1) * 4 + i) {
      InfoName(1, i);
      RouteWrite(450,149+i*120,user,i,page);
      StaName(user->history_lines[(page - 1) * 4 + i].start, 258,
              199 + (i * 120));
      StaName(user->history_lines[(page - 1) * 4 + i].end, 570,
              199 + (i * 120));
      ShowTime(user->history_lines[(page - 1) * 4 + i].time, 250,
               149 + i * 120);
      ShowTime(user->history_lines[(page - 1) * 4 + i].busnum , 570,
               149 + i * 120);
    } else if (user->history_lines[(page - 1) * 4 + i].note == 2 &&
               user->nhistory > (page - 1) * 4 + i) {
      InfoName(5, i);
      RouteWrite(450,149+i*120,user,i,page);
      StaName(user->history_lines[(page - 1) * 4 + i].start, 258,
              199 + (i * 120));
      StaName(user->history_lines[(page - 1) * 4 + i].end, 570,
              199 + (i * 120));
      ShowTime(user->history_lines[(page - 1) * 4 + i].time, 250,
               149 + i * 120);
      ShowTime(user->history_lines[(page - 1) * 4 + i].busnum , 570,
               149 + i * 120);
    }
  }
}

void ByBusOne()
{
  Maps();
  ;
  Bar1(145, 20, 275, 70, WHITE24);
  bar3(145, 20, 275, 70, BLACK24);
  puthz(280, 21, "年", 48, 48, BLACK24);
  Bar1(333, 20, 433, 70, WHITE24);
  bar3(333, 20, 433, 70, BLACK24);
  puthz(438, 21, "月", 48, 48, BLACK24);
  Bar1(491, 20, 591, 70, WHITE24);
  bar3(491, 20, 591, 70, BLACK24);
  puthz(596, 21, "日", 48, 48, BLACK24);
  Bar1(649, 20, 810, 70, WHITE24);
  bar3(649, 20, 810, 70, BLACK24);
  puthz(815, 21, "车次", 48, 48, BLACK24);
  Bar1(864, 608, 964, 658, BLACK24);
  Bar1(862, 606, 962, 656, LIGHTGRAY24);
  puthz(866, 608, "确认", 48, 48, BLACK24);
  puthz(865, 607, "确认", 48, 48, BLACK24);
}
void AChoose()
{
  Bar1(0, 0, 1024, 768, CYAN24);
  Bar1(354, 242, 674, 302, BLACK24);
  Bar1(352, 240, 672, 300, LIGHTGRAY24);
  puthz(363, 253, "按车次查询", 48, 60, BLACK24);
  puthz(362, 252, "按车次查询", 48, 60, BLACK24);
  Bar1(354, 332, 674, 392, BLACK24);
  Bar1(352, 330, 672, 390, LIGHTGRAY24);
  puthz(363, 343, "按用户查询", 48, 48, BLACK24);
  puthz(362, 342, "按用户查询", 48, 48, BLACK24);
  Bar1(354, 422, 674, 482, BLACK24);
  Bar1(352, 420, 672, 480, LIGHTGRAY24);
  puthz(363, 433, "数据统计", 48, 48, BLACK24);
  puthz(362, 432, "数据统计", 48, 48, BLACK24);
  Bar1(864, 718, 964, 768, BLACK24);
  Bar1(862, 716, 962, 766, LIGHTGRAY24);
  puthz(866, 720, "退出", 48, 48, BLACK24);
  puthz(865, 719, "退出", 48, 48, BLACK24);
}
void ShowTime(char *time, int x, int y)
{
  put_asc16_size(x + 1, y + 1, 2, 2, time, BLACK24);
  put_asc16_size(x, y, 2, 2, time, WHITE24);
}
void StaName(int num, int x, int y)
{
  int i;
  staname station[28] = {
    {1,"刘家大湾"},
    {2,"银河湾"},
    {3,"龙湾一品"},
    {4,"金广厦"},
    {5,"万达广场"},
    {6,"中心医院"},
    {7,"鲇鱼墩"},
    {8,"长湾"},
    {9,"磁湖梦"},
    {10,"汇金花园"},
    {11,"武夷花园"},
    {12,"妇幼保健院"},
    {13,"明秀山庄"},
    {14,"琥珀山庄"},
    {15,"湖景花园"},
    {16,"肖铺"},
    {17,"杭州公馆"},
    {18,"康乐小区"},
    {19,"白马山"},
    {20,"二中"},
    {21,"新区口"},
    {22,"宏维星都"},
    {23,"铜花山庄"},
    {24,"庙儿咀"},
    {25,"玉家里"},
    {26,"怡康花园"},
    {27,"牧羊湖"},
    {28,"袁仓"}
  };
  for (i = 0; i < 28; i++) {
    if (station[i].name == num) {
      puthz(x + 1, y + 1, station[i].stationname, 32, 32, BLACK24);
      puthz(x, y, station[i].stationname, 32, 32, WHITE24);
    }
  }
}
void ByBusTwo(Route *route, int page)
{
  int i;
  prt_hz16_size(305, 32, 4, 4, "乘客行程管理", DARKGRAY24, "HZK\\hzk16");
  prt_hz16_size(303, 30, 4, 4, "乘客行程管理", BLACK24, "HZK\\hzk16");
  Bar1(130, 140, 894, 250, LIGHTGRAY24);
  Bar1(130, 260, 894, 370, LIGHTGRAY24);
  Bar1(130, 380, 894, 490, LIGHTGRAY24);
  Bar1(130, 500, 894, 610, LIGHTGRAY24);
  /* bar(100,250,540,290);
   bar(100,300,540,340);
   bar(100,350,540,390);
   bar(100,400,540,440);*/
  Bar1(132, 142, 892, 248, NAVY24);
  Bar1(132, 262, 892, 368, NAVY24);
  Bar1(132, 382, 892, 488, NAVY24);
  Bar1(132, 502, 892, 608, NAVY24);
  for (i = 0; i < 4; i++) {
    if (route->ps[(page - 1) * 4 + i].note == 0 &&
        route->npassenger > (page - 1) * 4 + i) {
      InfoName(2, i);
      readmessage(route,page,i);
    } else if (route->ps[(page - 1) * 4 + i].note == 1 &&
               route->npassenger > (page - 1) * 4 + i) {
      InfoName(3, i);
      readmessage(route,page,i);
    } else if (route->ps[(page - 1) * 4 + i].note == 2 &&
               route->npassenger > (page - 1) * 4 + i) {
      InfoName(4, i);
      readmessage(route,page,i);
    }
  }
}


void ByBusF(Route *route, int line)
{
  int page = 1;
  int rline=0;
  if(line<0)line=0;
  PuOne();
  ByBusTwo(route, page);
  DrawPage(page);
  Mouse_Init();
  while (1) {
    MouseShow(&mouse);
    if (MousePress(906, 710, 1022, 766)) {
      MouseOff(&mouse);
      break;
    }
    if (MousePress(572, 619, 674, 659)) {
      if (page == 1) {
        page = 2;
        DrawPage(page);
        ByBusTwo(route, page);
        delay(100);
      } else if (page == 2) {
        page = 3;
        DrawPage(page);
        ByBusTwo(route, page);
        delay(100);
      } else if (page == 3) {
        page = 4;
        DrawPage(page);
        ByBusTwo(route, page);
        delay(100);
      }
    } else if (MousePress(350, 619, 450, 659)) {
      if (page == 2) {
        page = 1;
        DrawPage(page);
        ByBusTwo(route, page);
        delay(100);
      } else

        if (page == 3) {
          page = 2;
          DrawPage(page);
          ByBusTwo(route, page);
          delay(100);
        } else if (page == 4) {
          page = 3;
          DrawPage(page);
          ByBusTwo(route, page);
          delay(100);
        }
    } else if (MousePress(760, 152, 858, 186)) {
      MouseOff(&mouse);
      rline=1;
      if (route->npassenger > (page - 1) * 4 + rline - 1) {
        RPTrace(route, page, rline);
        PuOne();
        DrawPage(page);
        ByBusTwo(route, page);
      }
      MouseOn(mouse);
    } else if (MousePress(760, 272, 858, 306)) {
      MouseOff(&mouse);
      rline=2;
      if (route->npassenger > (page - 1) * 4 + rline - 1) {
        RPTrace(route, page, rline);
        PuOne();
        DrawPage(page);
        ByBusTwo(route, page);
      }
      MouseOn(mouse);
    } else if (MousePress(760, 392, 858, 426)) {
      MouseOff(&mouse);
      rline=3;
      if (route->npassenger > (page - 1) * 4 + rline - 1) {
        RPTrace(route, page, rline);
        PuOne();
        DrawPage(page);
        ByBusTwo(route, page);
      }
      MouseOn(mouse);
    } else if (MousePress(760, 512, 858, 546)) {
      MouseOff(&mouse);
      rline=4;
      if (route->npassenger > (page - 1) * 4 + rline - 1) {
        RPTrace(route, page, rline);
        PuOne();
        DrawPage(page);
        ByBusTwo(route, page);
      }
      MouseOn(mouse);
    }
    /*else if (MousePress(760, 207, 858, 241))
    {
      MouseOff(&mouse);
      rline = 1;
      route->ps[(page - 1) * 4 + rline - 1].note = 2;
      ByBusTwo(route, page);

      MouseOn(mouse);
    }
    else if (MousePress(760, 327, 858, 361))
    {
      MouseOff(&mouse);
      rline = 2;
      route->ps[(page - 1) * 4 + rline - 1].note = 2;
      ByBusTwo(route, page);

      MouseOn(mouse);
    }
    else if (MousePress(760, 447, 858, 481))
    {
      MouseOff(&mouse);
      rline = 3;
      route->ps[(page - 1) * 4 + rline - 1].note = 2;
      ByBusTwo(route, page);

      MouseOn(mouse);
    }
    else if (MousePress(760, 567, 858, 601))
    {
      MouseOff(&mouse);
      rline = 4;
      route->ps[(page - 1) * 4 + rline - 1].note = 2;
      ByBusTwo(route, page);

      MouseOn(mouse);
    }*/
  }
}
void ByBusNum()
{
  int Bflag = 1;
  int line = 0;
  int start = 0;
  int end = 0;
  char year[12];
  char month[3];
  char day[3];
  char time[10];
  char btime[10];
  char bnum[4];
  char route_name[16];
  Route route;
  int yi, mi, di, bi;
  year[0] = '\0';
  month[0] = '\0';
  day[0] = '\0';
  bnum[0] = '\0';
  btime[0] = '\0';
  ByBusOne();
  Mouse_Init();
  while (1) {
    MouseShow(&mouse);
    if (MousePress(145, 20, 275, 70) && Bflag == 1) {
      MouseOff(&mouse);
      yi = strlen(year);
      Getinfo(146, 21, year, 11, yi);
      MouseOn(mouse);
    } else if (MousePress(333, 20, 433, 70) && Bflag == 1) {
      MouseOff(&mouse);
      mi = strlen(month);
      Getinfo(334, 21, month, 11, mi);
      MouseOn(mouse);
    } else if (MousePress(491, 20, 591, 70) && Bflag == 1) {
      MouseOff(&mouse);
      di = strlen(day);
      Getinfo(492, 21, day, 11, di);
      MouseOn(mouse);
    } else if (MousePress(649, 20, 810, 70) && Bflag == 1) {
      MouseOff(&mouse);
      bi = strlen(bnum);
      Getinfo(650, 21, bnum, 4, bi);
      MouseOn(mouse);
    } else if (MousePress(906, 710, 1022, 766) && Bflag == 1) {
      AChoose();
      break;
    } else if (MousePress(218, 96, 806, 174) && Bflag == 1) {
      line = 1;
    } else if (MousePress(218, 96 + 170, 806, 174 + 170) && Bflag == 1) {
      line = 3;
    } else if (MousePress(218, 96 + 340, 806, 174 + 340) && Bflag == 1) {
      line = 4;
    } else if (MousePress(218, 96 + 510, 806, 174 + 510) && Bflag == 1) {
      line = 5;
    } else if (MousePress(862, 606, 962, 656) && Bflag == 1) {
      MouseOff(&mouse);
      yi = strlen(year);
      mi = strlen(month);
      di = strlen(day);
      if (JudgeTime(year, month, day, yi, mi, di) == SUCCESS_CODE) {
        Connect(year, month, day, time, route_name, bnum, 3, btime, 0, 0);
        ReadRoute(&route, route_name);
        delay(100);
        ByBusF(&route, line);
      } else if (JudgeTime(year, month, day, yi, mi, di) == ERROR_CODE) {
        InputError(line, start, end, 0, 0, 2);
        put_asc16_size(149, 21, 2, 2, year, BLACK24);
        put_asc16_size(337, 21, 2, 2, month, BLACK24);
        put_asc16_size(494, 21, 2, 2, day, BLACK24);
        put_asc16_size(653, 21, 2, 2, bnum, BLACK24);
      }
    }
  }
}
void UseHisF(UserInfo *user)
{
  int page = 1;
  int line = 0;
  PuOne();
  UserHis(user, page);
  DrawPage(page);
  Mouse_Init();
  while (1) {
    MouseShow(&mouse);
    if (MousePress(906, 710, 1022, 766)) {
      MouseOff(&mouse);
      break;
    } else if (MousePress(572, 619, 674, 659)) {
      if (page == 1) {
        page = 2;
        DrawPage(page);
        UserHis(user, page);
        delay(100);
      } else if (page == 2) {
        page = 3;
        DrawPage(page);
        UserHis(user, page);
        delay(100);
      } else if (page == 3) {
        page = 4;
        DrawPage(page);
        UserHis(user, page);
        delay(100);
      }
    } else if (MousePress(350, 619, 450, 659)) {
      if (page == 2) {
        page = 1;
        DrawPage(page);
        UserHis(user, page);
        delay(100);
      } else if (page == 3) {
        page = 2;
        DrawPage(page);
        UserHis(user, page);
        delay(100);
      } else if (page == 4) {
        page = 3;
        DrawPage(page);
        UserHis(user, page);
        delay(100);
      }
    } else if (MousePress(760, 152, 858, 186)) {
      MouseOff(&mouse);
      line = 1;
      if (user->nhistory > (page - 1) * 4 + line - 1) {
        RecordTrace(user, page, line, 2);
        PuOne();
        DrawPage(page);
        UserHis(user, page);
      }
      MouseOn(mouse);
    } else if (MousePress(760, 272, 858, 306)) {
      MouseOff(&mouse);
      line = 2;
      if (user->nhistory > (page - 1) * 4 + line - 1) {
        RecordTrace(user, page, line, 2);
        PuOne();
        DrawPage(page);
        UserHis(user, page);
      }
      MouseOn(mouse);
    } else if (MousePress(760, 392, 858, 426)) {
      MouseOff(&mouse);
      line = 3;
      if (user->nhistory > (page - 1) * 4 + line - 1) {
        RecordTrace(user, page, line, 2);
        PuOne();
        DrawPage(page);
        UserHis(user, page);
      }
      MouseOn(mouse);
    } else if (MousePress(760, 512, 858, 546)) {
      MouseOff(&mouse);
      line = 4;
      if (user->nhistory > (page - 1) * 4 + line - 1) {
        RecordTrace(user, page, line, 2);
        PuOne();
        DrawPage(page);
        UserHis(user, page);
      }
      MouseOn(mouse);
    } else if (MousePress(760, 207, 858, 241)) {
      MouseOff(&mouse);
      line = 1;
      if (user->nhistory > (page - 1) * 4 + line - 1) {
        RelevantF(page, line, user);
        PuOne();
        DrawPage(page);
        UserHis(user, page);
      }
      MouseOn(mouse);
    } else if (MousePress(760, 327, 858, 361)) {
      MouseOff(&mouse);
      line = 2;
      if (user->nhistory > (page - 1) * 4 + line - 1) {
        RelevantF(page, line, user);
        PuOne();
        DrawPage(page);
        UserHis(user, page);
      }
      MouseOn(mouse);
    } else if (MousePress(760, 447, 858, 481)) {
      MouseOff(&mouse);
      line = 3;
      if (user->nhistory > (page - 1) * 4 + line - 1) {
        RelevantF(page, line, user);
        PuOne();
        DrawPage(page);
        UserHis(user, page);
      }
      MouseOn(mouse);
    } else if (MousePress(760, 567, 858, 601)) {
      MouseOff(&mouse);
      line = 4;
      if (user->nhistory > (page - 1) * 4 + line - 1) {
        RelevantF(page, line, user);
        PuOne();
        DrawPage(page);
        UserHis(user, page);
      }
      MouseOn(mouse);
    }
  }
}

void FetchAllAccount(char acc[][16])
{
  FILE *fp;
  int cnt, len;
  cnt = 0;
  memset(acc, 0, sizeof(acc));
  fp = fopen("userinfo/account.txt", "rt");

  while (fgets(acc[cnt], 16, fp) != NULL) {
    len = strlen(acc[cnt]);
    acc[cnt][len - 1] = '\0';
    cnt++;
  }
  fclose(fp);
  fp = NULL;
}

void ByUser()
{
  int page = 1;
  int line = 0;
  UserInfo user;
  char user_account[100][16];
  memset(user_account,0,sizeof(user_account));
  FetchAllAccount(user_account);
  PuOne();
  ShUsers(user_account);
  DrawPage(page);
  Mouse_Init();
  while (1) {
    MouseShow(&mouse);
    if (MousePress(572, 619, 674, 659)) {
      if (page == 1) {
        page = 2;
        DrawPage(page);
        ShUsers(user_account);
        delay(100);
      } else if (page == 2) {
        page = 3;
        DrawPage(page);
        ShUsers(user_account);
        delay(100);
      } else if (page == 3) {
        page = 4;
        DrawPage(page);
        ShUsers(user_account);
        delay(100);
      }
    } else if (MousePress(350, 619, 450, 659)) {
      if (page == 2) {
        page = 1;
        DrawPage(page);
        ShUsers(user_account);
        delay(100);
      } else

        if (page == 3) {
          page = 2;
          DrawPage(page);
          ShUsers(user_account);
          delay(100);
        } else if (page == 4) {
          page = 3;
          DrawPage(page);
          ShUsers(user_account);
          delay(100);
        }
    } else if (MousePress(113, 132, 509, 188)) {
      MouseOff(&mouse);
      line = 1;
      if(*user_account[(page - 1) + line - 1]) {
        memset(&user, 0, sizeof(UserInfo));
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(113, 192, 509, 248)) {
      MouseOff(&mouse);
      line = 2;
      if(*user_account[(page - 1) + line - 1]) {
        memset(&user, 0, sizeof(UserInfo));
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(113, 252, 509, 308)) {
      MouseOff(&mouse);
      line = 3;
      if(*user_account[(page - 1) + line - 1]) {
        memset(&user, 0, sizeof(UserInfo));
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(113, 312, 509, 368)) {
      MouseOff(&mouse);
      line = 4;
      if(*user_account[(page - 1) + line - 1]) {
        memset(&user, 0, sizeof(UserInfo));
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(113, 372, 509, 428)) {
      MouseOff(&mouse);
      line = 5;
      if(*user_account[(page - 1) + line - 1]) {
        memset(&user, 0, sizeof(UserInfo));
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(113, 432, 509, 488)) {
      MouseOff(&mouse);
      line = 6;
      if(*user_account[(page - 1) + line - 1]) {
        memset(&user, 0, sizeof(UserInfo));
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(113, 492, 509, 548)) {
      MouseOff(&mouse);
      line = 7;
      if(*user_account[(page - 1) + line - 1]) {
        memset(&user, 0, sizeof(UserInfo));
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(113, 552, 509, 608)) {
      MouseOff(&mouse);
      line = 8;
      if(*user_account[(page - 1) + line - 1]) {
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(515, 132, 911, 188)) {
      MouseOff(&mouse);
      line = 9;
      if(*user_account[(page - 1) + line - 1]) {
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(515, 192, 911, 248)) {
      MouseOff(&mouse);
      line = 10;
      if(*user_account[(page - 1) + line - 1]) {
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(515, 252, 911, 308)) {
      MouseOff(&mouse);
      line = 11;
      if(*user_account[(page - 1) + line - 1]) {
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(515, 312, 911, 368)) {
      MouseOff(&mouse);
      line = 12;
      if(*user_account[(page - 1) + line - 1]) {
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(515, 372, 911, 428)) {
      MouseOff(&mouse);
      line = 13;
      if(*user_account[(page - 1) + line - 1]) {
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(515, 432, 911, 488)) {
      MouseOff(&mouse);
      line = 14;
      if(*user_account[(page - 1) + line - 1]) {
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(515, 492, 911, 548)) {
      MouseOff(&mouse);
      line = 15;
      if(*user_account[(page - 1) + line - 1]) {
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(515, 552, 911, 608)) {
      MouseOff(&mouse);
      line = 16;
      if(*user_account[(page - 1) + line - 1]) {
        GetUserInfo(&user, user_account[(page - 1) + line - 1]);
        UseHisF(&user);
        PuOne();
        DrawPage(page);
        ShUsers(user_account);
      }
    } else if (MousePress(906, 710, 1022, 766)) {
      MouseOff(&mouse);
      AChoose();
      break;
    }
  }
}
void Statistics()
{
  int health,fever,infect,all,i,j;
  char h[10];
  char f[10];
  char in[10];
  char a[10];
  char user_account[40][16];
  UserInfo user;
  health=0;
  fever=0;
  infect=0;
  h[0] = '\0';
  f[0] = '\0';
  in[0] = '\0';
  a[0] = '\0';
  i=0;
  memset(user_account,0,sizeof(user_account));
  FetchAllAccount(user_account);
  while(*user_account[i]) {
    memset(&user, 0, sizeof(UserInfo));
    GetUserInfo(&user,user_account[i]);
    for(j=0; j<user.nhistory; j++) {
      if(user.history_lines[j].note==0) {
        health++;
      } else if((user.history_lines[j].note==1)) {
        fever++;
      } else if((user.history_lines[j].note==2)) {
        infect++;
      }
    }
    i++;
  }
  all=health+fever+infect;
  itoa(health,h,10);
  itoa(fever,f,10);
  itoa(infect,in,10);
  itoa(all,a,10);
  Bar1(0,0,1024,768,DARKCYAN24);
  Bar1(332,20,432,60,GREEN24);
  puthz(334,24,"未发热",32,32,BLACK24);
  Bar1(462,20,562,60,YELLOW24);
  puthz(477,24,"发热",32,35,BLACK24);
  Bar1(592,20,692,60,LIGHTRED24);
  puthz(597,24,"确诊",32,35,BLACK24);
  returnbut();
  Line_Thick(150,150,150,600,2,BLACK24);
  puthz(350,620,"共计",32,32,BLACK24);
  put_asc16_size(420,620,2,2,a,WHITE24);
  puthz(500,620,"条上报的行程记录",32,32,BLACK24);
  Bar1(150,195,150+health*5,255,GREEN24);
  put_asc16_size(160+health*5,209,2,2,h,WHITE24);
  Bar1(150,345,150+fever*5,405,YELLOW24);
  put_asc16_size(160+fever*5,359,2,2,f,WHITE24);
  Bar1(150,495,150+infect*5,555,LIGHTRED24);
  put_asc16_size(160+infect*5,509,2,2,in,WHITE24);
  Mouse_Init();
  while(1) {
    MouseShow(&mouse);
    if(MousePress(906, 710, 1022, 766)) {
      MouseOff(&mouse);
      break;
    }
  }
}
void AdminiFunc()
{
  AChoose();
  Mouse_Init();
  while (1) {
    MouseShow(&mouse);
    if (MousePress(352, 240, 672, 300)) {
      MouseOff(&mouse);
      ByBusNum();
    } else if (MousePress(352, 330, 672, 390)) {
      MouseOff(&mouse);
      ByUser();
    } else if(MousePress(352,420,672,480)) {
      MouseOff(&mouse);
      Statistics();
      MouseOff(&mouse);
      AChoose();
    } else if (MousePress(862, 716, 962, 766)) {
      MouseOff(&mouse);
      break;
    }
  }
}
