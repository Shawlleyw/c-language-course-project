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
void readmessage(Route *temp_route,int rpage,int i)
{
  StaName(temp_route->ps[(rpage-1)*4+i].start,258,199+(i*120));
  StaName(temp_route->ps[(rpage-1)*4+i].end,570,199+(i*120));
  ShowTime(temp_route->ps[(rpage-1)*4+i].name,250,149+i*120);
  ShowTime(temp_route->ps[(rpage-1)*4+i].time,561,149+i*120);
}

void rRead(Route *route,UserInfo *user,int rpage)
{
  int i;
  int k;
  Route *temp_route;
  temp_route = route;

  for(i=0; i<temp_route->npassenger; i++) {
    if(strcmp(temp_route->ps[i].name,user->name)==0) {
      k=i;

      while(k + 1 < temp_route->npassenger) {

        temp_route->ps[k]=temp_route->ps[k+1];
        k++;

      }

      temp_route->npassenger--;
    }
  }
  for(i=0; i<4; i++) {
    if(temp_route->ps[(rpage-1)*4+i].note==0&&temp_route->npassenger>(rpage-1)*4+i) {
      InfoName(2,i);
      readmessage(temp_route,rpage,i);
    } else if(temp_route->ps[(rpage-1)*4+i].note==1&&temp_route->npassenger>(rpage-1)*4+i) {
      InfoName(3,i);
      readmessage(temp_route,rpage,i);
    } else if(temp_route->ps[(rpage-1)*4+i].note==2&&temp_route->npassenger>(rpage-1)*4+i) {
      InfoName(4,i);
      readmessage(temp_route,rpage,i);
    }
  }
}

void Relevant(Route *route,int rpage,UserInfo *user)
{
  prt_hz16_size(193,32,4,4,"同车乘客行程记录查询",DARKGRAY24,"HZK\\hzk16");
  prt_hz16_size(191,30,4,4,"同车乘客行程记录查询",BLACK24,"HZK\\hzk16");
  Bar1(130,140,894,250,LIGHTGRAY24);
  Bar1(130,260,894,370,LIGHTGRAY24);
  Bar1(130,380,894,490,LIGHTGRAY24);
  Bar1(130,500,894,610,LIGHTGRAY24);
  Bar1(132,142,892,248,NAVY24);
  Bar1(132,262,892,368,NAVY24);
  Bar1(132,382,892,488,NAVY24);
  Bar1(132,502,892,608,NAVY24);

  rRead(route,user,rpage);
}

void RPTrace(Route *route,int page,int line)
{
  Bar1(0,0,1024,768,DARKCYAN24);
  DisplayLine(route->line);
  DisplayTraces(route->line,route->ps[(page-1)*4+line-1].start,route->ps[(page-1)*4+line-1].end, CheckRev(route->route_name), CheckRound(route->route_name));
  returnbut();
  Stak(route->line,500,600,1,0,0,0);
}
