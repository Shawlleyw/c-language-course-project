#include "headers/hisbox.h"
#include "headers/add.h"
#include "headers/admini.h"
#include "headers/calcpath.h"
#include "headers/draw.h"
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
#include "headers/userdata.h"
#include <bios.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void RouteWrite(int x,int y,UserInfo *user,int i,int page)
{
	if(user->history_lines[(page-1)*4+i].line_no==1) {
		puthz(x,y,"线路一",32,32,WHITE24);
	} else if(user->history_lines[(page-1)*4+i].line_no==3) {
		puthz(x,y,"线路二",32,32,WHITE24);
	} else if(user->history_lines[(page-1)*4+i].line_no==4) {
		puthz(x,y,"线路三",32,32,WHITE24);
	} else if(user->history_lines[(page-1)*4+i].line_no==5) {
		puthz(x,y,"线路四",32,32,WHITE24);
	}  
} 
void Hisbox(int page, UserInfo *user)
{
  int i;
  prt_hz16_size(257,32,4,4,"用户历史行程记录",DARKGRAY24,"HZK\\hzk16");
  prt_hz16_size(255,30,4,4,"用户历史行程记录",BLACK24,"HZK\\hzk16");
  Bar1(0,0,150,50,DARKGRAY24);
  Bar1(2,2,148,48,LIGHTGRAY24);
  put_asc16_size(12,9,2,2,user->name,BLACK24);
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
  for (i = 0; i < 4; i++)
  {
    if (user->history_lines[(page - 1) * 4 + i].note == 0 &&
        user->nhistory > (page - 1) * 4 + i)
    {
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
    }
    else if (user->history_lines[(page - 1) * 4 + i].note == 1 &&
             user->nhistory > (page - 1) * 4 + i)
    {
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
    }
    else if (user->history_lines[(page - 1) * 4 + i].note == 2 &&
             user->nhistory > (page - 1) * 4 + i)
    {
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

void HisBoxFunc(UserInfo *user)
{
  int page = 1;
  int line = 0;
  PuOne();
  DrawPage(page);
  Hisbox(page, user);
  Mouse_Init();
  while (1)
  {
    MouseShow(&mouse);
    if (MousePress(572, 619, 674, 659))
    {
      if (page == 1)
      {
        page = 2;
        DrawPage(page);
        Hisbox(page, user);
        delay(100);
      }
      else if (page == 2)
      {
        page = 3;
        DrawPage(page);
        Hisbox(page, user);
        delay(100);
      }
      else if (page == 3)
      {
        page = 4;
        DrawPage(page);
        Hisbox(page, user);
        delay(100);
      }
    }
    else if (MousePress(350, 619, 450, 659))
    {
      if (page == 2)
      {
        page = 1;
        DrawPage(page);
        Hisbox(page, user);
        delay(100);
      }
      else

          if (page == 3)
      {
        page = 2;
        DrawPage(page);
        Hisbox(page, user);
        delay(100);
      }
      else if (page == 4)
      {
        page = 3;
        DrawPage(page);
        Hisbox(page, user);
        delay(100);
      }
    }
    else if (MousePress(904, 708, 1024, 768))
    {
      MouseOff(&mouse);
      DrawMainPage();
      MouseOn(mouse);
      break;
    }
    else if (MousePress(760, 152, 858, 186))
    {
      MouseOff(&mouse);
      line = 1;
      if (user->nhistory > (page - 1) * 4 + line - 1)
      {
        RecordFunc(user, page, line);
        PuOne();
        Hisbox(page, user);
        DrawPage(page);
      }
      MouseOn(mouse); 
    }
    else if (MousePress(760, 272, 858, 306))
    {
      MouseOff(&mouse);
      line = 2;
      if (user->nhistory > (page - 1) * 4 + line - 1)
      {
        RecordFunc(user, page, line);
        PuOne();
        Hisbox(page, user);
        DrawPage(page);
      }
      MouseOn(mouse); 
    }
    else if (MousePress(760, 392, 858, 426))
    {
      MouseOff(&mouse);
      line = 3;
      if (user->nhistory > (page - 1) * 4 + line - 1)
      {
        RecordFunc(user, page, line);
        PuOne();
        Hisbox(page, user);
        DrawPage(page);
      }
      MouseOn(mouse); 
    }
    else if (MousePress(760, 512, 858, 546))
    {
      MouseOff(&mouse);
      line = 4;
      if (user->nhistory > (page - 1) * 4 + line - 1)
      {
        RecordFunc(user, page, line);
        PuOne();
        Hisbox(page, user);
        DrawPage(page);
      }
      MouseOn(mouse); 
    }
    else if (MousePress(760, 207, 858, 241))
    {
      MouseOff(&mouse);
      line = 1;
      if (user->nhistory > (page - 1) * 4 + line - 1)
      {
        RelevantF(page, line, user);
        PuOne();
        Hisbox(page, user);
        DrawPage(page);
      }
      MouseOn(
          mouse); 
    }
    else if (MousePress(760, 327, 858, 361))
    {
      MouseOff(&mouse);
      line = 2;
      if (user->nhistory > (page - 1) * 4 + line - 1)
      {
        RelevantF(page, line, user);
        PuOne();
        Hisbox(page, user);
        DrawPage(page);
      }
      MouseOn(
          mouse); 
    }
    else if (MousePress(760, 447, 858, 481))
    {
      MouseOff(&mouse);
      line = 3;
      if (user->nhistory > (page - 1) * 4 + line - 1)
      {
        RelevantF(page, line, user);
        PuOne();
        Hisbox(page, user);
        DrawPage(page);
      }
      MouseOn(
          mouse);
    }
    else if (MousePress(760, 567, 858, 601))
    {
      MouseOff(&mouse);
      line = 4;
      if (user->nhistory > (page - 1) * 4 + line - 1)
      {
        RelevantF(page, line, user);
        PuOne();
        Hisbox(page, user);
        DrawPage(page);
      }
      MouseOn(
          mouse); 
    }
  }
}
