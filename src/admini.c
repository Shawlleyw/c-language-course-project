#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <string.h>
#include "headers/info.h"
#include "headers/putbmp.h"
#include "headers/status.h"
#include "headers/traveldata.h"
#include "headers/userdata.h"
#include "headers/mouse.h"
#include "headers/run.h"
#include "headers/admini.h"
#include "headers/hz.h"
#include "headers/svga.h"



void DrawPage(int page)
{
  Bar1(484,620,570,670,DARKCYAN24);
  if(page==1) {
    put_asc16_size(485,115+510,2,2,"1/4",BLACK24);
  } else if(page==2) {
    put_asc16_size(485,115+510,2,2,"2/4",BLACK24);
  } else if(page==3) {
    put_asc16_size(485,115+510,2,2,"3/4",BLACK24);
  } else if(page==4) {
    put_asc16_size(485,115+510,2,2,"4/4",BLACK24);
  }
}
void PuOne()
{
  Bar1(0,0,1024,768,CYAN24);
  Bar1(110,120,914,670,DARKCYAN24);
  Bar1(352,621,452,661,DARKGRAY24);
  Bar1(574,621,674,661,DARKGRAY24);
  Bar1(350,619,450,659,LIGHTGRAY24);
  Bar1(572,619,674,659,LIGHTGRAY24);
  puthz(352,623,"上一页",32,32,WHITE24);
  puthz(574,623,"下一页",32,32,WHITE24);
  Bar1(904,708,1024,768,DARKGRAY24);
  Bar1(906,710,1022,766,LIGHTGRAY24);
  puthz(918,716,"返回",48,48,BLACK24);
  puthz(917,715,"返回",48,48,BLACK24);
}
/*void DisPlayR()
{
  int i,rows;
  char time[16]= {0};
  UserInfo user;
  FILE *fp;
  Bar1(130,140,894,250,LIGHTGRAY24);
  Bar1(130,260,894,370,LIGHTGRAY24);
  Bar1(130,380,894,490,LIGHTGRAY24);
  Bar1(130,500,894,610,LIGHTGRAY24);
  Bar1(132,142,892,248,NAVY24);
  Bar1(132,262,892,368,NAVY24);
  Bar1(132,382,892,488,NAVY24);
  Bar1(132,502,892,608,NAVY24);
  for(i=0; i<4; i++) {
    puthz(139,149+(i*120),"时间",32,32,DARKGRAY24);
    puthz(139,199+(i*120),"起点站",32,32,DARKGRAY24);
    puthz(451,199+(i*120),"终点站",32,32,DARKGRAY24);
    puthz(138,148+(i*120),"时间",32,32,WHITE24);
    puthz(138,198+(i*120),"起点站",32,32,WHITE24);
    puthz(450,198+(i*120),"终点站",32,32,WHITE24);
    Bar1(760,152+i*120,858,186+i*120,DARKGRAY24);
    Bar1(757,150+i*120,856,184+i*120,LIGHTGRAY24);
    puthz(760,155+i*120,"显示路径",24,24,DARKGRAY24);
    puthz(759,154+i*120,"显示路径",24,24,BLACK24);
    Bar1(760,207+i*120,858,241+i*120,DARKGRAY24);
    Bar1(757,205+i*120,856,239+i*120,LIGHTGRAY24);
    puthz(760,155+i*120,"删除记录",24,24,DARKGRAY24);
    puthz(759,154+i*120,"删除记录",24,24,BLACK24);
    StaName(user.history_lines[i].start,258,199+(i*120));
    StaName(user.history_lines[i].end,570,199+(i*120));
    ShowTime(time,250,149+i*120);
  }

}*/
void SPeople(int x,int y)
{
  int x1,y1;
  char name[6];
  Circlefill(x,y,25,WHITE24);
  Circle(x,y,25,BLACK24);
  Circle(x,y,26,BLACK24);
  Circlefill(x,y-5,10,BLUE24);
  for(y1=y+25; y1>y+5; y1--) {
    for(x1=x; x1>=x-15; x1--) {
      if((x-x1)*(x-x1)+(y-y1)*(y-y1)==625) {
        Line_Thick(x,y,x1,y1-2,4,BLUE24);
      }
    }
    for(x1=x; x1<=x+15; x1++) {

      if(((x1-x)*(x1-x)+(y-y1)*(y-y1)==625)) {
        Line_Thick(x,y,x1,y1-2,4,BLUE24);
      }
    }
  }
  puthz(x+40,y-24,"用户",48,48,BLACK24);
}

void ShUsers(char users[][16])
{
  int i;
  int j;
  /*Bar1(110,120,914,670,DARKCYAN24);*/
  prt_hz16_size(382,32,4,4,"用户列表",DARKGRAY24,"HZK\\hzk16");
  prt_hz16_size(384,30,4,4,"用户列表",BLACK24,"HZK\\hzk16");
  for(j=0;j<2;j++) {
  	for(i=0;i<8;i++) {
  		Bar1(111+j*400,130+i*60,511+j*400,190+i*60,BLACK24);

        Bar1(113+j*400,132+i*60,509+j*400,188+i*60,LIGHTGRAY24);

        SPeople(140+j*400,160+60*i);
		put_asc16_size(300+j*400,136+60*i,3,3,users[i+j*8],BLACK24);
	  }
  } 
}

void UserHis(UserInfo *user,int page)
{
  int i,rows;
  put_asc16_size(120,32,4,4,user->name,BLACK24);
  prt_hz16_size(273,32,4,4,"的行程记录",DARKGRAY24,"HZK\\hzk16");
  prt_hz16_size(271,30,4,4,"的行程记录",BLACK24,"HZK\\hzk16");

  //可封装为一个函数
  Bar1(130,140,894,250,LIGHTGRAY24);
  Bar1(130,260,894,370,LIGHTGRAY24);
  Bar1(130,380,894,490,LIGHTGRAY24);
  Bar1(130,500,894,610,LIGHTGRAY24);
  Bar1(132,142,892,248,NAVY24);
  Bar1(132,262,892,368,NAVY24);
  Bar1(132,382,892,488,NAVY24);
  Bar1(132,502,892,608,NAVY24);
  for(i=0; i<4; i++) {
  	if(user->history_lines[(page-1)*4+i].note==0&&user->nhistory>(page-1)*4+i) {
      InfoName(0,i);
      StaName(user->history_lines[(page-1)*4+i].start,258,199+(i*120));
      StaName(user->history_lines[(page-1)*4+i].end,570,199+(i*120));
      ShowTime(user->history_lines[(page-1)*4+i].time,250,149+i*120);
    } else if(user->history_lines[(page-1)*4+i].note==1&&user->nhistory>(page-1)*4+i) {
      InfoName(1,i);
      StaName(user->history_lines[(page-1)*4+i].start,258,199+(i*120));
      StaName(user->history_lines[(page-1)*4+i].end,570,199+(i*120));
      ShowTime(user->history_lines[(page-1)*4+i].time,250,149+i*120);
    } else if(user->history_lines[(page-1)*4+i].note==2&&user->nhistory>(page-1)*4+i) {
      InfoName(5,i);
      StaName(user->history_lines[(page-1)*4+i].start,258,199+(i*120));
      StaName(user->history_lines[(page-1)*4+i].end,570,199+(i*120));
      ShowTime(user->history_lines[(page-1)*4+i].time,250,149+i*120);
	}
  }
}

void ByBusOne()
{
  Maps();																																				;
  Bar1(145,20,275,70,WHITE24);
  bar3(145,20,275,70,BLACK24);
  puthz(280,21,"年",48,48,BLACK24);
  Bar1(333,20,433,70,WHITE24);
  bar3(333,20,433,70,BLACK24);
  puthz(438,21,"月",48,48,BLACK24);
  Bar1(491,20,591,70,WHITE24);
  bar3(491,20,591,70,BLACK24);
  puthz(596,21,"日",48,48,BLACK24);
  Bar1(649,20,810,70,WHITE24);
  bar3(649,20,810,70,BLACK24);
  puthz(815,21,"车次",48,48,BLACK24);
  Bar1(864,608,964,658,BLACK24);
  Bar1(862,606,962,656,LIGHTGRAY24);
  puthz(866,608,"确认",48,48,BLACK24);
  puthz(865,607,"确认",48,48,BLACK24);
}
void AChoose()
{
  Bar1(0,0,1024,768,CYAN24);
  Bar1(354,242,674,302,BLACK24);
  Bar1(352,240,672,300,LIGHTGRAY24);
  puthz(363,253,"按车次管理",48,60,BLACK24);
  puthz(362,252,"按车次管理",48,60,BLACK24);
  Bar1(354,332,674,392,BLACK24);
  Bar1(352,330,672,390,LIGHTGRAY24);
  puthz(363,343,"按用户管理",48,48,BLACK24);
  puthz(362,342,"按用户管理",48,48,BLACK24);


  Bar1(864,718,964,768,BLACK24);
  Bar1(862,716,962,766,LIGHTGRAY24);
  puthz(866,720,"退出",48,48,BLACK24);
  puthz(865,719,"退出",48,48,BLACK24);


}
void ShowTime(char *time,int x,int y)
{
  put_asc16_size(x+1,y+1,2,2,time,BLACK24);
  put_asc16_size(x,y,2,2,time,WHITE24);
}
void StaName(int num,int x,int y)
{
  int i;
  staname station[28]= {
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
  for(i=0; i<28; i++) {
    if(station[i].name==num) {
      puthz(x+1,y+1,station[i].stationname,32,32,BLACK24);
      puthz(x,y,station[i].stationname,32,32,WHITE24);
    }
  }
}
void ByBusTwo(Route *route,int page)
{
  int i;
  prt_hz16_size(305,32,4,4,"乘客行程管理",DARKGRAY24,"HZK\\hzk16");
  prt_hz16_size(303,30,4,4,"乘客行程管理",BLACK24,"HZK\\hzk16");
  Bar1(130,140,894,250,LIGHTGRAY24);
  Bar1(130,260,894,370,LIGHTGRAY24);
  Bar1(130,380,894,490,LIGHTGRAY24);
  Bar1(130,500,894,610,LIGHTGRAY24);
  /* bar(100,250,540,290);
   bar(100,300,540,340);
   bar(100,350,540,390);
   bar(100,400,540,440);*/
  Bar1(132,142,892,248,NAVY24);
  Bar1(132,262,892,368,NAVY24);
  Bar1(132,382,892,488,NAVY24);
  Bar1(132,502,892,608,NAVY24);
  for(i=0; i<4; i++) {
    if(route->ps[(page-1)*4+i].note==0&&route->npassenger>(page-1)*4+i) {
        InfoName(2,i);
        StaName(route->ps[(page-1)*4+i].start,258,199+(i*120));
        StaName(route->ps[(page-1)*4+i].end,570,199+(i*120));
        ShowTime(route->ps[(page-1)*4+i].name,250,149+i*120);
	} else if(route->ps[(page-1)*4+i].note==1&&route->npassenger>(page-1)*4+i) {
		InfoName(3,i);
        StaName(route->ps[(page-1)*4+i].start,258,199+(i*120));
        StaName(route->ps[(page-1)*4+i].end,570,199+(i*120));
        ShowTime(route->ps[(page-1)*4+i].name,250,149+i*120);
	} else if(route->ps[(page-1)*4+i].note==2&&route->npassenger>(page-1)*4+i) {
		InfoName(4,i);
        StaName(route->ps[(page-1)*4+i].start,258,199+(i*120));
        StaName(route->ps[(page-1)*4+i].end,570,199+(i*120));
        ShowTime(route->ps[(page-1)*4+i].name,250,149+i*120);
	}
  }
  /*	Bar1(352,621,452,661,DARKGRAY24);
  	Bar1(574,621,674,661,DARKGRAY24);
  	Bar1(350,619,450,659,LIGHTGRAY24);
  	Bar1(572,619,674,659,LIGHTGRAY24);
  	puthz(352,623,"上一页",32,32,WHITE24);
  	put_asc16_size(485,115+510,2,2,"1/4",BLACK24);
  	puthz(574,623,"下一页",32,32,WHITE24);
  	Bar1(904,708,1024,768,DARKGRAY24);
  	Bar1(906,710,1022,766,LIGHTGRAY24);
  	puthz(918,716,"返回",48,48,BLACK24);
  	puthz(917,715,"返回",48,48,BLACK24);*/
}


/*void SBasic()
{
  Bar1(0,565,1024,768,DARKCYAN24);
  puthz(30,570,"上车时间",48,48,BLACK24);
  puthz(30,630,"起点站",48,48,BLACK24);
  puthz(540,630,"终点站",48,48,BLACK24);
  puthz(540,570,"下车时间",48,48,BLACK24);
  Bar1(434,717,594,760,BLACK24);
  Bar1(432,716,592,758,LIGHTGRAY24);
  Bar1(434,717,594,760,BLACK24);
  Bar1(432,716,592,758,LIGHTGRAY24);
  puthz(465,722,"下一步",32,32,BLACK24);
  puthz(464,721,"下一步",32,32,BLACK24);

  Bar1(904,708,1024,768,DARKGRAY24);
  Bar1(906,710,1022,766,LIGHTGRAY24);
  puthz(918,716,"返回",48,48,BLACK24);
  puthz(917,715,"返回",48,48,BLACK24);
}
void SNote()
{
  Bar1(0,565,1024,768,DARKCYAN24);
  Bar1(434,717,594,760,DARKCYAN24);
  Bar1(434,717,594,760,BLACK24);
  Bar1(432,716,592,758,LIGHTGRAY24);
  puthz(465,722,"上一步",32,32,BLACK24);
  puthz(464,721,"上一步",32,32,BLACK24);
  Bar1(904,708,1024,768,DARKGRAY24);
  Bar1(906,710,1022,766,LIGHTGRAY24);
  puthz(918,716,"返回",48,48,BLACK24);
  puthz(917,715,"返回",48,48,BLACK24);
}
void SUTrace(int line)
{
  int page=1;
  Bar1(0,0,1024,768,DARKCYAN24);
  DisplayLine(line);
  //DisplayTraces(line,start,end);
  SBasic();
  Mouse_Init();
  while(1) {
    MouseShow(&mouse);
    if(MousePress(432,716,592,758)) {
      MouseOff(&mouse);
      if(page==1) {
        SNote();
        page=2;
      } else if(page==2) {
        SBasic();
      }
    } else if(MousePress(906,710,1022,766)) {
      MouseOff(&mouse);
      break;
    }
  }
}*/

/***************************************************
显示对应车次的信息
***************************************************/
void ByBusF(Route *route,int line)//根据车次，时间来读取相应的记录按次序显示
{
  int page=1;
  PuOne();
  ByBusTwo(route,page);
  DrawPage(page);
  Mouse_Init();
  while (1) {
    MouseShow(&mouse);
    if(MousePress(906,710,1022,766)) {
      MouseOff(&mouse);
      break;
    }
    if(MousePress(572,619,674,659)) {
      if(page==1) {
        page=2;
        DrawPage(page);
        ByBusTwo(route,page);//显示四条记录
        delay(100);
      } else if(page==2) {
        page=3;
        DrawPage(page);
        ByBusTwo(route,page);//显示四条记录
        delay(100);
      } else if(page==3) {
        page=4;
        DrawPage(page);
        ByBusTwo(route,page);//显示四条记录
        delay(100);
      }
    } else if(MousePress(350,619,450,659)) {
      if(page==2) {
        page=1;
        DrawPage(page);
        ByBusTwo(route,page);//显示四条记录
        delay(100);
      } else

        if(page==3) {
          page=2;
          DrawPage(page);
          ByBusTwo(route,page);//显示四条记录
          delay(100);
        } else if(page==4) {
          page=3;
          DrawPage(page);
          ByBusTwo(route,page);//显示四条记录
          delay(100);
        }
    } else if(MousePress(760,152,858,186)) {
      MouseOff(&mouse);
	  RPTrace(route,page,line);//显示当页第一条记录对应用户路线 及注释
      PuOne();
      DrawPage(page);
      ByBusTwo(route,page);
      MouseOn(mouse);
    } else if(MousePress(760,272,858,306)) {
      MouseOff(&mouse);
      RPTrace(route,page,line);//显示当页第二条记录对应用户路线 及注释
      PuOne();
      DrawPage(page);
      ByBusTwo(route,page);
      MouseOn(mouse);
    } else if(MousePress(760,392,858,426)) {
      MouseOff(&mouse);
      RPTrace(route,page,line);//显示当页第三条记录对应用户路线 及注释
      PuOne();
      DrawPage(page);
      ByBusTwo(route,page);
      MouseOn(mouse);
    } else if(MousePress(760,512,858,546)) {
      MouseOff(&mouse);
      RPTrace(route,page,line);//显示当页第四条记录对应用户路线 及注释
      PuOne();
      DrawPage(page);
      ByBusTwo(route,page);
      MouseOn(mouse);
    } else if(MousePress(760,207,858,241)) {
      MouseOff(&mouse);
      line=1;
      route->ps[(page-1)*4+line-1].note=2;
      ByBusTwo(route,page);
      //标记为确诊人员 
      MouseOn(mouse);
    } else if(MousePress(760,327,858,361)) {
      MouseOff(&mouse);
      line=2;
      route->ps[(page-1)*4+line-1].note=2;
      ByBusTwo(route,page);
      //标记为确诊人员 
      MouseOn(mouse);
    } else if(MousePress(760,447,858,481)) {
      MouseOff(&mouse);
      line=3;
      route->ps[(page-1)*4+line-1].note=2;
      ByBusTwo(route,page);
      //标记为确诊人员 
      MouseOn(mouse);
    } else if(MousePress(760,567,858,601)) {
      MouseOff(&mouse);
      line=4;
      route->ps[(page-1)*4+line-1].note=2;
      ByBusTwo(route,page);
      //标记为确诊人员 
      MouseOn(mouse);
    }
  }
}
void ByBusNum()
{
  int Bflag=1;
  int Sflag=1;
  int line=0;
  int start=0;
  int end=0;
  char year[12];
  char month[3];
  char day[3];
  char time[10];
  char btime[10];
  char bnum[4];
  char route_name[16];
  Route route;
  int yi,mi,di,bi;
  year[0] = '\0';
  month[0] = '\0';
  day[0] = '\0';
  bnum[0] = '\0';
  btime[0] = '\0';
  ByBusOne();
  Mouse_Init();
  while(1) {
	MouseShow(&mouse);
	if(MousePress(145,20,275,70)&&Bflag==1) {
	  MouseOff(&mouse);
	  yi=strlen(year);
	  Getinfo(146,21,year,11,yi);
	  MouseOn(mouse);
	} else if(MousePress(333,20,433,70)&&Bflag==1) {
	  MouseOff(&mouse);
	  mi=strlen(month);
	  Getinfo(334,21,month,11,mi);
	  MouseOn(mouse);
	} else if(MousePress(491,20,591,70)&&Bflag==1) {
	  MouseOff(&mouse);
	  di=strlen(day);
	  Getinfo(492,21,day,11,di);
	  MouseOn(mouse);
	} else if(MousePress(649,20,810,70)&&Bflag==1) {
	  MouseOff(&mouse);
	  bi=strlen(bnum);
	  Getinfo(650,21,bnum,4,bi);
	  MouseOn(mouse);
	} else if(MousePress(906,710,1022,766)&&Bflag==1) {
	  AChoose();
	  break;
	} else if(MousePress(218,96,806,174)&&Bflag==1) {
	  line=1;
	} else if(MousePress(218,96+170,806,174+170)&&Bflag==1) {
	  line=3;
	} else if(MousePress(218,96+340,806,174+340)&&Bflag==1) {
	  line=4;
	} else if(MousePress(218,96+510,806,174+510)&&Bflag==1) {
      line=5;
	} else if(MousePress(862,606,962,656)&&Bflag==1) {
		MouseOff(&mouse);
		yi=strlen(year);
		mi=strlen(month);
		di=strlen(day);
		if(JudgeTime(year,month,day,yi,mi,di)==SUCCESS_CODE) {
		  Connect(year,month,day,time,route_name,bnum,3,btime,0,0);
          ReadRoute(&route,route_name);
          delay(100);
          ByBusF(&route,line);
      } else if(JudgeTime(year,month,day,yi,mi,di)==ERROR_CODE) {
          InputError(line,start,end,2);
          put_asc16_size(149,21,2,2,year,BLACK24);
          put_asc16_size(337,21,2,2,month,BLACK24);
          put_asc16_size(494,21,2,2,day,BLACK24);
          put_asc16_size(653,21,2,2,bnum,BLACK24);
        }
    }
  }
}
void UseHisF(UserInfo *user)
{
  int page=1;
  int line=0;
  PuOne();
  UserHis(user,page);
  DrawPage(page);
  Mouse_Init();
  while(1) {
    MouseShow(&mouse);
    if(MousePress(906,710,1022,766)) {
      MouseOff(&mouse);
      break;
    } else if(MousePress(572,619,674,659)) {
      if(page==1) {
        page=2;
        DrawPage(page);
        UserHis(user,page);
        delay(100);
      } else if(page==2) {
        page=3;
        DrawPage(page);
        UserHis(user,page);
        delay(100);
      } else if(page==3) {
        page=4;
        DrawPage(page);
        UserHis(user,page);
        delay(100);
      }
    } else if(MousePress(350,619,450,659)) {
      if(page==2) {
        page=1;
        DrawPage(page);
        UserHis(user,page);
        delay(100);
      } else if(page==3) {
          page=2;
          DrawPage(page);
          UserHis(user,page);
          delay(100);
        } else if(page==4) {
          page=3;
          DrawPage(page);
          UserHis(user,page);
          delay(100);
        }
    } else if(MousePress(760,152,858,186)) {
      MouseOff(&mouse);
      line=1;
      RecordTrace(user,page,line,2);
      PuOne();
      DrawPage(page);
      UserHis(user,page);//显示当页第一条记录对应用户路线 及注释
      MouseOn(mouse);
    } else if(MousePress(760,272,858,306)) {
      MouseOff(&mouse);
      line=2;
      RecordTrace(user,page,line,2);
      PuOne();
      DrawPage(page);
      UserHis(user,page);//显示当页第二条记录对应用户路线 及注释
      MouseOn(mouse);
    } else if(MousePress(760,392,858,426)) {
      MouseOff(&mouse);
      line=3;
      RecordTrace(user,page,line,2);
      PuOne();
      DrawPage(page);
      UserHis(user,page);//显示当页第三条记录对应用户路线 及注释
      MouseOn(mouse);
    } else if(MousePress(760,512,858,546)) {
      MouseOff(&mouse);
      line=4;
      RecordTrace(user,page,line,2);
      PuOne();
      DrawPage(page);
      UserHis(user,page);//显示当页第四条记录对应用户路线 及注释
      MouseOn(mouse);
    } else if(MousePress(760,207,858,241)) {
      MouseOff(&mouse);
      line=1;
      RelevantF(page,line,user);
      UserHis(user,page);
      MouseOn(mouse);
    } else if(MousePress(760,327,858,361)) {
      MouseOff(&mouse);
      line=2;
      RelevantF(page,line,user);
      UserHis(user,page);
      MouseOn(mouse);
    } else if(MousePress(760,447,858,481)) {
      MouseOff(&mouse);
      line=3;
      RelevantF(page,line,user);
      UserHis(user,page);
      MouseOn(mouse);
    } else if(MousePress(760,567,858,601)) {
      MouseOff(&mouse);
      line;
      RelevantF(page,line,user);
      UserHis(user,page);
      MouseOn(mouse);
      }
  }
}

void FetchAllAccount(char acc[][16]){
	FILE *fp;
	int cnt,len;
	cnt = 0;
	memset(acc, 0, sizeof(acc));
	fp = fopen("userinfo/account.txt","rt");
	
	while(fgets(acc[cnt], 16, fp) != NULL){
		len = strlen(acc[cnt]);
		acc[cnt][len-1] = '\0';
		cnt++;
	}
	fclose(fp);
	fp = NULL;
}

void ByUser()
{
  int page=1;
  int line=0;
  UserInfo user;
  char user_account[100][16];
  FetchAllAccount(user_account);
  PuOne();
  ShUsers(user_account);
  DrawPage(page);
  Mouse_Init();
  while (1) {
    MouseShow(&mouse);
    if(MousePress(572,619,674,659)) {
      if(page==1) {
        page=2;
        DrawPage(page);
        ShUsers(user_account);
        delay(100);
      } else if(page==2) {
        page=3;
        DrawPage(page);
        ShUsers(user_account);
        delay(100);
      } else if(page==3) {
        page=4;
        DrawPage(page);
        ShUsers(user_account);
        delay(100);
      }
    } else if(MousePress(350,619,450,659)) {
      if(page==2) {
        page=1;
        DrawPage(page);
        ShUsers(user_account);
        delay(100);
      } else

        if(page==3) {
          page=2;
          DrawPage(page);
          ShUsers(user_account);
          delay(100);
        } else if(page==4) {
          page=3;
          DrawPage(page);
          ShUsers(user_account);
          delay(100);
        }
    } else if(MousePress(113,132,509,188)) {
      MouseOff(&mouse);
      line==1; 
      GetUserInfo(&user, user_account);
      UseHisF(&user);
      PuOne();
      DrawPage(page);
      ShUsers(user_account);//查询当页第一列第一条记录
    } else if(MousePress(113,192,509,248)) {
      MouseOff(&mouse);
      line==2;
      GetUserInfo(&user, user_account);
	  UseHisF(&user);
      PuOne();
      DrawPage(page);
      ShUsers(user_account);//查询当页第一列第二条记录
    } else if(MousePress(113,252,509,308)) {
      MouseOff(&mouse);
      GetUserInfo(&user, user_account);
      UseHisF(&user);
      PuOne();
      DrawPage(page);
      ShUsers(user_account);//查询当页第一列第三条记录
    } else if(MousePress(113,312,509,368)) {
      MouseOff(&mouse);
      GetUserInfo(&user, user_account);
      UseHisF(&user);
      PuOne();
      DrawPage(page);
      ShUsers(user_account);//查询当页第一列第四条记录
    } else if(MousePress(113,372,509,428)) {
      MouseOff(&mouse);
      GetUserInfo(&user, user_account);
      UseHisF(&user);
      PuOne();
      DrawPage(page);
      ShUsers(user_account);//查询当页第一列第五条记录
    } else if(MousePress(113,432,509,488)) {
      MouseOff(&mouse);
      GetUserInfo(&user, user_account);
      UseHisF(&user);
      PuOne();
      DrawPage(page);
      ShUsers(user_account);//查询当页第一列第六条记录
    } else if(MousePress(113,492,509,548)) {
      MouseOff(&mouse);
      GetUserInfo(&user, user_account);
      UseHisF(&user);
      PuOne();
      ShUsers(user_account);//查询当页第一列第七条记录
    } else if(MousePress(113,552,509,608)) {
      MouseOff(&mouse);
      GetUserInfo(&user, user_account);
      UseHisF(&user);
      PuOne();
      DrawPage(page);
      ShUsers(user_account);//查询当页第一列第八条记录
    } else if(MousePress(515,132,911,188)) {
      MouseOff(&mouse);
      GetUserInfo(&user, user_account);
      UseHisF(&user);
      PuOne();
      DrawPage(page);
      ShUsers(user_account);//查询当页第二列第一条记录
    } else if(MousePress(515,192,911,248)) {
      MouseOff(&mouse);
      GetUserInfo(&user, user_account);
      UseHisF(&user);
      PuOne();
      DrawPage(page);
      ShUsers(user_account);//查询当页第二列第二条记录
    } else if(MousePress(515,252,911,308)) {
      MouseOff(&mouse);
      GetUserInfo(&user, user_account);
      UseHisF(&user);
      PuOne();
      DrawPage(page);
      ShUsers(user_account);//查询当页第二列第三条记录
    } else if(MousePress(515,312,911,368)) {
      MouseOff(&mouse);
      GetUserInfo(&user, user_account);
      UseHisF(&user);
      PuOne();
      DrawPage(page);
      ShUsers(user_account);//查询当页第二列第四条记录
    } else if(MousePress(515,372,911,428)) {
      MouseOff(&mouse);
      GetUserInfo(&user, user_account);
      UseHisF(&user);
      PuOne();
      DrawPage(page);
      ShUsers(user_account);//查询当页第二列第五条记录
    } else if(MousePress(515,432,911,488)) {
      MouseOff(&mouse);
      GetUserInfo(&user, user_account);
      UseHisF(&user);
      PuOne();
      DrawPage(page);
      ShUsers(user_account);//查询当页第二列第六条记录
    } else if(MousePress(515,492,911,548)) {
      MouseOff(&mouse);
      GetUserInfo(&user, user_account);
      UseHisF(&user);
      PuOne();
      DrawPage(page);
      ShUsers(user_account);//查询当页第二列第七条记录
    } else if(MousePress(515,552,911,608)) {
      MouseOff(&mouse);
	  GetUserInfo(&user, user_account);
      UseHisF(&user);
      PuOne();
      DrawPage(page);
      ShUsers(user_account);//查询当页第二列第八条记录
    } else if(MousePress(906,710,1022,766)) {
      MouseOff(&mouse);
      AChoose();
      break;
    }
  }
}

void AdminiFunc()
{
  AChoose();
  Mouse_Init();
  while(1) {
	MouseShow(&mouse);
    if(MousePress(352,240,672,300)) {
      MouseOff(&mouse);
      ByBusNum();
    } else if(MousePress(352,330,672,390)) {
      MouseOff(&mouse);
      ByUser();
    } else if(MousePress(862,716,962,766)) {
      MouseOff(&mouse);
      //登陆界面
      break;
    }
  }
}
