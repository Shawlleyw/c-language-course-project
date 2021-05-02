#include "headers/info.h"
#include "headers/userdata.h"
#include "headers/status.h"
#include "headers/hz.h"
#include "headers/mouse.h"
#include "headers/draw.h"
#include "headers/stafunc.h"
#include "headers/recordop.h"
#include "headers/add.h"
#include "headers/relevant.h"
#include "headers/judge.h"
#include "headers/admini.h"
#include "headers/run.h"
#include "headers/register.h"
#include "headers/hisbox.h"
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <bios.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
void RecordTrace(UserInfo *user,int page,int line,int c)
{
  int cur = (page-1)*4+line-1;
  if(c==1) {
    Bar1(0,0,1024,768,DARKCYAN24);
    DisplayLine(user->history_lines[cur].line_no);
    DisplayTraces(user->history_lines[cur].line_no,user->history_lines[cur].start,user->history_lines[cur].end, CheckRev(user->history_lines[cur].busnum), CheckRound(user->history_lines[cur].busnum));
    Bar1(414,672,614,722,BLACK24);
    Bar1(412,670,612,720,LIGHTGRAY24);
    puthz(416,671,"发热上报",48,48,BLACK24);
    returnbut();
  } else if(c==2) {
    Bar1(0,0,1024,768,DARKCYAN24);
    DisplayLine(user->history_lines[cur].line_no);
    DisplayTraces(user->history_lines[cur].line_no,user->history_lines[cur].start,user->history_lines[cur].end, CheckRev(user->history_lines[cur].busnum), CheckRound(user->history_lines[cur].busnum));
    returnbut();
    Stak(user->history_lines[cur].line_no,500,600,1,0,0,0);
  }
}

void RecordBox(int i)
{
  if(i==0) {
    Bar1(0,560,1024,768,DARKCYAN24);
    Line_Thick(362,720,662,720,2,BLACK24);
    returnbut();
  } else if(i==1) {
    Bar1(0,560,1024,768,LIGHTGRAY24);
    returnbut();
    AddBox3();
  }
}
void OverrideUserInfo(char *useracc, UserInfo *user){
	char path[32];
	FILE *fp;
	strcpy(path, "userinfo/");
	strcat(path, useracc);
	fp = fopen(path, "wb");
	fwrite(user, sizeof(UserInfo), 1, fp);
	fclose(fp);
	fp = NULL;
	
}
void RecordFunc(UserInfo *user,int page,int line)
{
  RecordTrace(user,page,line,1);
  user->history_lines[(page-1)*4+line-1].note = Stak(user->history_lines[(page-1)*4+line-1].line_no,410,600,2,user->history_lines[(page-1)*4+line-1].note,0,1);
  OverrideUserInfo(user->account, user);
}



void RelevantF(int page,int line, UserInfo *user) /////////////////////////////////////////////////
{
  int rpage=1;
  int rline=0;
  int i;
  Route route;
  char route_name[16];

  strcpy(route_name,user->history_lines[(page-1)*4+line-1].busnum);//获取用户该条乘车记录的车号

  ReadRoute(&route,route_name);

  PuOne();
  DrawPage(rpage);
  Relevant(&route,rpage,user);
  Mouse_Init();
  while (1) {
    MouseShow(&mouse);
    if(MousePress(572,619,674,659)) {
      if(rpage==1) {
        rpage=2;
        DrawPage(rpage);
        Relevant(&route,rpage,user);
        delay(100);
      } else if(rpage==2) {
        rpage=3;
        DrawPage(rpage);
        Relevant(&route,rpage,user);
        delay(100);
      } else if(rpage==3) {
        rpage=4;
        DrawPage(rpage);
        Relevant(&route,rpage,user);
        delay(100);
      }
    } else if(MousePress(350,619,450,659)) {
      if(rpage==2) {
        rpage=1;
        DrawPage(rpage);
        Relevant(&route,rpage,user);
        delay(100);
      } else if(rpage==3) {
        rpage=2;
        DrawPage(rpage);
        Relevant(&route,rpage,user);
        delay(100);
      } else if(rpage==4) {
        rpage=3;
        DrawPage(rpage);
        Relevant(&route,rpage,user);
        delay(100);
      }
    } else if(MousePress(904,708,1024,768)) {
      MouseOff(&mouse);
      break;
    } else if(MousePress(760,152,858,186)) {
      MouseOff(&mouse);//显示当页第一条记录对应路线
      rline=1;
      if(route.npassenger>(rpage-1)*4+rline-1) {
        RPTrace(&route,rpage,rline);
        PuOne();
        Relevant(&route,rpage,user);
        DrawPage(rpage);
      }
      MouseOn(mouse);
    } else if(MousePress(760,272,858,306)) {
      MouseOff(&mouse);//显示当页第二条记录对应路线
      rline=2;
      if(route.npassenger>(rpage-1)*4+rline-1) {
        RPTrace(&route,rpage,rline);
        PuOne();
        Relevant(&route,rpage,user);
        DrawPage(rpage);
      }
      MouseOn(mouse);
    } else if(MousePress(760,392,858,426)) {
      MouseOff(&mouse);//显示当页第三条记录对应路线
      rline=3;
      if(route.npassenger>(rpage-1)*4+rline-1) {
        RPTrace(&route,rpage,rline);
        PuOne();
        Relevant(&route,rpage,user);
        DrawPage(rpage);
      }
      MouseOn(mouse);
    } else if(MousePress(760,512,858,546)) {
      MouseOff(&mouse);//显示当页第四条记录对应路线
      rline=4;
      if(route.npassenger>(rpage-1)*4+rline-1) {
        RPTrace(&route,rpage,rline);
        PuOne();
        Relevant(&route,rpage,user);
        DrawPage(rpage);
      }
      MouseOn(mouse);
    }
  }
}
