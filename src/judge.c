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

STATUS_CODE JudgeTime(char *year,char *month,char *day,int yi,int mi,int di)
{
  int i;
  int yk,mk,dk;
  yk=0;
  mk=0;
  dk=0;
  for(i=0; i<yi; i++) {
    yk=yk*10+(year[i]-'0');
  }
  for(i=0; i<mi; i++) {
    mk=mk*10+(month[i]-'0');
  }
  for(i=0; i<mi; i++) {
    dk=dk*10+(day[i]-'0');
  }
  if(yk==2021 && ( (mk==4&&(dk>=1&&dk<=30)) || (mk==5&&(dk>=1&&dk<=4)) )) {
    return SUCCESS_CODE;
  } else {
    return ERROR_CODE;
  }
}

void Connect(char *year,char *month,char *day,char *time,char *route_name,char *bnum,int c,char *btime,int page,int line)
{
  int mi;
  int di;
  mi=strlen(month);
  di=strlen(day);
  if(c==1) {//连接根据用户记录的时间
    strcpy(time,year);
    strcat(time,".");
    strcat(time,month);
    strcat(time,".");
    strcat(time,day);
  } else if(c==2) {//形成车次定位
    if(mi==1) {
      strcpy(btime,"0");
      strcat(btime,month);
    } else if(mi==2) {
      strcat(btime,month);
    }
    if(di==1) {
      strcat(btime,"0");
      strcat(btime,day);
    } else if(di==2) {
      strcat(btime,day);
    }
    strcpy(route_name,btime);

    if(line==1) {
      if(page==1) {
        strcat(route_name,"a");
      } else if(page==2) {
        strcat(route_name,"b");
      }
    } else if(line==3) {
      if(page==1) {
        strcat(route_name,"e");
      } else if(page==2) {
        strcat(route_name,"f");
      }
    } else if(line==4) {
      if(page==1) {
        strcat(route_name,"h");
      } else if(page==2) {
        strcat(route_name,"i");
      }
    } else if(line==5) {
      if(page==1) {
        strcat(route_name,"m");
      } else if(page==2) {
        strcat(route_name,"n");
      }
    }

    strcat(route_name,bnum);
  } else if(c==3) {
    if(mi==1) {
      strcpy(btime,"0");
      strcat(btime,month);
    } else if(mi==2) {
      strcat(btime,month);
    }
    if(di==1) {
      strcat(btime,"0");
      strcat(btime,day);
    } else if(di==2) {
      strcat(btime,day);
    }
    strcpy(route_name,btime);
    strcat(route_name,bnum);
  }
}

void InputError(int line,int start,int end, int rev, int round, int k)
{
  Bar1(362,400,662,550,LIGHTGRAY24);
  bar3(362,400,662,550,BLACK24);
  puthz(367,430,"输入有误",48,54,RED24);
  Bar1(462,495,562,545,CYAN24);
  bar3(462,495,562,545,BLACK24);
  puthz(464,496,"确认",48,48,BLACK24);
  Mouse_Init();
  while(1) {
    MouseShow(&mouse);
    if(MousePress(462,495,562,545)) {
      MouseOff(&mouse);
      if(k==1) {
        DisplayLine(line);
        if(start!=0&&end!=0) {
          DisplayTraces(line,start,end, rev, round);
        } else if(k==2) {
          ByBusOne();
        }
      }
      break;
    }
  }
}
