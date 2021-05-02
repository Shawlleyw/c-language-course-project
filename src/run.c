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
#include "headers/admini.h"
#include "headers/hz.h"
#include "headers/svga.h"
#include "headers/run.h"


void NextPage()
{
  Bar1(435,708,589,768,DARKGRAY24);
  Bar1(437,710,587,766,LIGHTGRAY24);
  puthz(441,716,"下一页",48,48,BLACK24);
  puthz(440,715,"下一页",48,48,BLACK24);
}
int CheckRound(char *name){
	int i, len;
	len = strlen(name);
	for(i = 0; i < len; i++){
		if(name[i]>='a' && name[i] <='z'){
			if(name[i]=='a'||name[i]=='b')return 1;
			else return 0;
		}
	}
	return 0;
} 
int CheckRev(char *name){
	int i, len;
	len = strlen(name);
	for(i = 0; i < len; i++){
		if(name[i]>='a' && name[i] <='z'){
			if(name[i]=='b'||name[i]=='f'||name[i]=='i'||name[i]=='n')return 1;
			else return 0;
		}
	}
}
void Maps()
{
  int i;
  Bar1(0,0,1024,768,DARKCYAN24);
  Bar1(904,708,1024,768,DARKGRAY24);
  Bar1(906,710,1022,766,LIGHTGRAY24);
  puthz(918,716,"返回",48,48,BLACK24);
  returnbut();
  for(i=0; i<4; i++) {
    Bar1(218,96+i*170,806,174+i*170,DARKGRAY24);
    Bar1(222,100+i*170,802,170+i*170,LIGHTGRAY24);
  }
  puthz(223,113,"一路",48,48,BLACK24);
  puthz(222,112,"一路",48,48,BLACK24);
  puthz(431,126,"刘家大湾",24,24,BLACK24);
  puthz(430,125,"刘家大湾",24,24,BLACK24);
  put_asc16_size(520,115,3,3,"(   )",BLACK24);
  puthz(543,126,"外环线",24,24,BLACK24);
  puthz(542,125,"外环线",24,24,BLACK24);

  puthz(223,113+170,"二路",48,48,BLACK24);
  puthz(222,112+170,"二路",48,48,BLACK24);
  puthz(431,126+170,"刘家大湾",24,24,BLACK24);
  puthz(430,125+170,"刘家大湾",24,24,BLACK24);
  put_asc16_size(535,115+170,3,3,"-->",BLACK24);
  puthz(603,126+170,"铜花山庄",24,24,BLACK24);
  puthz(602,125+170,"铜花山庄",24,24,BLACK24);
  put_asc16_size(695,115+170,3,3,"( )",BLACK24);
  puthz(719,126+170,"外",24,24,BLACK24);
  puthz(718,125+170,"外",24,24,BLACK24);

  puthz(223,113+340,"三路",48,48,BLACK24);
  puthz(222,112+340,"三路",48,48,BLACK24);
  puthz(431,126+340,"刘家大湾",24,24,BLACK24);
  puthz(430,125+340,"刘家大湾",24,24,BLACK24);
  put_asc16_size(535,115+340,3,3,"-->",BLACK24);
  puthz(603,126+340,"铜花山庄",24,24,BLACK24);
  puthz(602,125+340,"铜花山庄",24,24,BLACK24);
  put_asc16_size(695,115+340,3,3,"( )",BLACK24);
  puthz(719,126+340,"全",24,24,BLACK24);
  puthz(718,125+340,"全",24,24,BLACK24);

  puthz(223,113+510,"四路",48,48,BLACK24);
  puthz(222,112+510,"四路",48,48,BLACK24);
  puthz(431,126+510,"刘家大湾",24,24,BLACK24);
  puthz(430,125+510,"刘家大湾",24,24,BLACK24);
  put_asc16_size(535,115+510,3,3,"-->",BLACK24);
  puthz(603,126+510,"铜花山庄",24,24,BLACK24);
  puthz(602,125+510,"铜花山庄",24,24,BLACK24);
  put_asc16_size(695,115+170*3,3,3,"( )",BLACK24);
  puthz(719,126+170*3,"内",24,24,BLACK24);
  puthz(718,125+170*3,"内",24,24,BLACK24);
}


STATUS_CODE GetUserInfo(UserInfo *user, char *user_account)
{
  char path[32];
  FILE *user_fp;
  strcpy(path, "userinfo/");
  strcat(path, user_account);
  user_fp = fopen(path, "r+");
  fread(user, sizeof(UserInfo), 1, user_fp);
  fclose(user_fp);
  user_fp = NULL;
  return SUCCESS_CODE;
}

char* CalcRoutePath(char *path, int line)
{
  int len;
  strcpy(path,"data/routes/route");
  len = strlen(path);
  path[len] = line + '0';
  path[len+1] = '\0';
  strcat(path, ".out");
  return SUCCESS_CODE;
}

char* CalcStationPath(char *path, int station)
{
  int len;
  strcpy(path,"data/stations/_");
  len = strlen(path);
  path[len] = station/100 + '0';
  path[len+1] = (station/10)%10 + '0';
  path[len+2] = station % 10 + '0';
  path[len+3] = '\0';
  return path;
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
  Circlefill(cur.x,cur.y,12,LIGHTRED24);
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
  Circlefill(cur.x,cur.y,12,LIGHTRED24);
  fclose(fp);
  fp = NULL;

}

void ReverseRoute(Lines *l)
{
  Lines temp;
  int i, nsta = l->n;
  temp.n = l->n;
  for(i = 1; i <= l->n; i++)
	temp.station_numbers[i] = l->station_numbers[l->n+1-i];
  *l = temp;
}
STATUS_CODE DrawTraces(Lines *l, int ids, int ide){
    int i;
	Sta cur, pre;
	char path[32];
	FILE *fp;
	for(i = ids; i <= ide; i++) {
    CalcStationPath(path, l->station_numbers[i]);
    fp = fopen(path, "rb");
    if(fp == NULL) {
      CloseSVGA();
      fprintf(stderr, "fopen error\n");
      while(1);
    }
    fread(&cur, sizeof(cur), 1, fp);
    fclose(fp);
    fp = NULL;
    if(i != ids)Line_Thick(cur.x, cur.y, pre.x, pre.y, 6, LIGHTGRAY24);
    pre = cur;
  }
}

STATUS_CODE PaintStations(Lines *l, int ids, int ide){
	char path[32];
    int i;
	FILE *fp;
	Sta cur;
	for(i = ids + 1; i < ide; i++) {
    fp = fopen(CalcStationPath(path, l->station_numbers[i]), "rb");
    fread(&cur, sizeof(cur), 1, fp);
    if(cur.number < 50)Circlefill(cur.x, cur.y, 9, LIGHTRED24);
    fclose(fp);
    fp = NULL;
  }
}

STATUS_CODE DisplayTraces(int line, int start, int end, int rev, int round)
{
  int ids = -1, ide = -1, i, circle = 0;
  Lines l;
  ReadLineInfo(&l, line);
  if(rev == 1)ReverseRoute(&l);
  for(i = 1; i <= l.n; i++) {
    if(l.station_numbers[i] == start) 
      ids = i;  
    if(l.station_numbers[i] == end) 
      ide = i;
  }
  if(ids>=ide){
  	if(!round)return ERROR_CODE;
  	else circle = 1;
  }
  if(circle){
  	l.station_numbers[++l.n] = l.station_numbers[1];
  	DrawTraces(&l, ids, l.n);
  	PaintStations(&l, ids, l.n);
  	DrawTraces(&l, 1, ide);
  	PaintStations(&l, 0, ide);
  }
  else{
  	DrawTraces(&l, ids, ide);
  	PaintStations(&l, ids, ide);
  }
  DrawStart(start);
  DrawEnd(end);
  return SUCCESS_CODE;
}


void Comfirm(int x,int y)
{
  Circlefill(x-40,y+30,20,GREEN24);
  Circlefill(x+40,y+30,20,RED24);
  Circle(x-40,y+30,20,BLACK24);
  Circle(x+40,y+30,20,BLACK24);
  Line_Thick(x-52,y+34,x-40,y+45,2,WHITE24);
  Line_Thick(x-40,y+45,x-30,y+22,2,WHITE24);
  Line_Thick(x+32,y+22,x+48,y+38,2,WHITE24);
  Line_Thick(x+32,y+38,x+48,y+22,2,WHITE24);
}

int ClickStation(int x,int y)
{
  int l = 0;
  Comfirm(x,y);
  while(1) {
    MouseShow(&mouse);
    if (MousePress(806, 528, 826, 548) == 1) {
      l=1;
    } else if (MousePress(629, 480, 649, 500) == 1) {
      l=2;
    } else if (MousePress(443, 389, 463, 409) == 1) {
      l=3;
    } else if (MousePress(250, 355, 270, 375) == 1) {
      l=4;
    } else if (MousePress(55, 353, 75, 373) == 1) {
      l=5;
    } else if (MousePress(130, 166, 150, 186) == 1) {
      l=6;
    } else if (MousePress(192, 62, 212, 82) == 1) {
      l=7;
    } else if (MousePress(337, 8, 357, 28) == 1) {
      l=8;
    } else if (MousePress(469, 7, 489, 27) == 1) {
      l=9;
    } else if (MousePress(620, 5, 640, 25) == 1) {
      l=10;
    } else if (MousePress(801, 2, 821, 22) == 1) {
      l=11;
    } else if (MousePress(998, 77, 1018, 97) == 1) {
      l=12;
    } else if (MousePress(996, 225, 1016, 245) == 1) {
      l=13;
    } else if (MousePress(996, 375, 1016, 395) == 1) {
      l=14;
    } else if (MousePress(943, 497, 963, 517) == 1) {
      l=15;
    } else if (MousePress(379, 282, 399, 302) == 1) {
      l=16;
    } else if (MousePress(377, 72, 397, 92) == 1) {
      l=17;
    } else if (MousePress(549, 114, 569, 134) == 1) {
      l=18;
    } else if (MousePress(678, 213, 698, 233) == 1) {
      l=19;
    } else if (MousePress(847, 270, 867, 290) == 1) {
      l=20;
    } else if (MousePress(886, 380, 906, 400) == 1) {
      l=21;
    } else if (MousePress(884, 467, 904, 487) == 1) {
      l=22;
    } else if (MousePress(19, 200, 39, 220) == 1) {
      l=23;
    } else if (MousePress(204, 208, 224, 228) == 1) {
      l=24;
    } else if (MousePress(335, 209, 355, 229) == 1) {
      l=25;
    } else if (MousePress(532, 312, 552, 332) == 1) {
      l=26;
    } else if (MousePress(471, 210, 491, 230) == 1) {
      l=27;
    } else if (MousePress(276, 101, 296, 121) == 1) {
      l=28;
    } else if (MousePress(x-60,y+20,x-20,y+60)) {
      MouseOff(&mouse);
      return l;
    } else if (MousePress(x+20,y+20,x+60,y+60)) {
      MouseOff(&mouse);
      return 0;
    }
  }
}

char *CalcMapName(char *path, int line)
{
  int len;
  strcpy(path, "data/maps/ditu");
  len = strlen(path);
  path[len] = line + '0';
  path[len+1] = '\0';
  strcat(path, ".bmp");
  return path;
}

void ShowSta(int line)
{

  puthz(301,601,"站名",48,48,BLACK24);
  puthz(300,600,"站名",48,48,BLACK24);
  Stak(line,400,600,1,0,0,0);
}
void StakInput(int func,char *name,int station,int x,int y,int Sflag)
{
  if(func==3) {
    StationName(Sflag,station,name);
  } else if(func==1||func==2) {
    StakInfo(x,y,name);
  }
}
void StakInfo(int x,int y,char *name)
{
  Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
  puthz(x+1,y+1,name,48,48,BLACK24);
  puthz(x,y,name,48,48,BLACK24);
}

int Stak(int line,int x,int y,int func,int note,int Sflag,int lim)
{
  Sta stations[28]= {
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

  int l=0;
  int choose=0;
  int temp_note=note;
  int cur_station = 0;
  int k=0;
  char Dflag[5];
  Mouse_Init();
  while(1) {
    MouseShow(&mouse);
    if (MouseIn(806, 528, 826, 548) == 1 && (line==1||line==3||line==4||line==5) ) {
      l=1;
      if(MousePress(806, 528, 826, 548) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        MouseOff(&mouse);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(629, 480, 649, 500) == 1 && (line==1) ) {
      l=2;
      if(MousePress(629, 480, 649, 500) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        MouseOff(&mouse);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }


    } else if (MouseIn(443, 389, 463, 409) == 1 && (line==1||line==4||line==5) ) {
      l=3;
      if(MousePress(443, 389, 463, 409) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        MouseOff(&mouse);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(250, 355, 270, 375) == 1 && (line==1||line==4) ) {
      l=4;
      if(MousePress(250, 355, 270, 375) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(55, 353, 75, 373) == 1 && (line==1||line==4||line==5) ) {
      l=5;
      if(MousePress(55, 353, 75, 373) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if ( MouseIn(130, 166, 150, 186) == 1 && (line==1) ) {
      l=6;
      if(MousePress(130, 166, 150, 186) && func==3) {
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(192, 62, 212, 82) == 1 && (line==1) ) {
      l=7;
      if(MousePress(192, 62, 212, 82) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(337, 8, 357, 28) == 1 && (line==1||line==3) ) {
      l=8;
      if(MousePress(337, 8, 357, 28) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(469, 7, 489, 27) == 1 && (line==1||line==3||line==4) ) {
      l=9;
      if(MousePress(469, 7, 489, 27) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(620, 5, 640, 25) == 1 && (line==1||line==4) ) {
      l=10;
      if(MousePress(620, 5, 640, 25) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(801, 2, 821, 22) == 1 && (line==1||line==4) ) {
      l=11;
      if(MousePress(801, 2, 821, 22) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(998, 77, 1018, 97) == 1 && (line==1||line==4) ) {
      l=12;
      if(MousePress(998, 77, 1018, 97) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(996, 225, 1016, 245) == 1 && (line==1||line==4) ) {
      l=13;
      if(MousePress(996, 225, 1016, 245) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(996, 375, 1016, 395) == 1 && (line==1||line==4) ) {
      l=14;
      if(MousePress(996, 375, 1016, 395) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(943, 497, 963, 517) == 1 && (line==1||line==4) ) {
      l=15;
      if(MousePress(943, 497, 963, 517) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(379, 282, 399, 302) == 1 && (line==5) ) {
      l=16;
      if(MousePress(379, 282, 399, 302) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(377, 72, 397, 92) == 1 && (line==4) ) {
      l=17;
      if(MousePress(377, 72, 397, 92) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(549, 114, 569, 134) == 1 && (line==3) ) {
      l=18;
      if(MousePress(549, 114, 569, 134) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(678, 213, 698, 233) == 1 && (line==3||line==5) ) {
      l=19;
      if(MousePress(678, 213, 698, 233) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(847, 270, 867, 290) == 1 && (line==3||line==5) ) {
      l=20;
      if(MousePress(847, 270, 867, 290) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(886, 380, 906, 400) == 1 && (line==3||line==5) ) {
      l=21;
      if(MousePress(886, 380, 906, 400) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(884, 467, 904, 487) == 1 && (line==3||line==5) ) {
      l=22;
      if(MousePress(884, 467, 904, 487) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(19, 200, 39, 220) == 1 && (line==3||line==4||line==5) ) {
      l=23;
      if(MousePress(19, 200, 39, 220) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(204, 208, 224, 228) == 1 && (line==3||line==5) ) {
      l=24;
      if(MousePress(204, 208, 224, 228) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(335, 209, 355, 229) == 1 && (line==5) ) {
      l=25;
      if(MousePress(335, 209, 355, 229) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(532, 312, 552, 332) == 1 && (line==4||line==5) ) {
      l=26;
      if(MousePress(532, 312, 552, 332) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(471, 210, 491, 230) == 1 && (line==4) ) {
      l=27;
      if(MousePress(471, 210, 491, 230) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if (MouseIn(276, 101, 296, 121) == 1 && (line==3) ) {
      l=28;
      if(MousePress(276, 101, 296, 121) && func==3) {
        MouseOff(&mouse);
        return l;
      }
      if(cur_station == l) {
        continue;
      } else if(cur_station!=l) {
        cur_station = l;
        Circlefill(stations[l-1].x,stations[l-1].y,9,GREEN24);
        StakInput(func,stations[l-1].name,l,x,y,Sflag);
      }

    } else if(MousePress(906,710,1022,766)&&choose==0) {
      MouseOff(&mouse);
      if(temp_note!=3) {
        return temp_note;
      } else break;

    } else if(MousePress(412,670,612,720)&&func==2&&choose==0&&lim==1) {
      RecordBox(1);
      choose=1;

    } else if(MousePress(639,589,689,639)&&func==2&&choose==1&&lim==1) {
      MouseOff(&mouse);
      YNbut(2);
      temp_note=1;
      YNbut(4);
      MouseOn(mouse);

    } else if(MousePress(692,589,742,639)&&func==2&&choose==1&&lim==1) {
      MouseOff(&mouse);
      YNbut(3);
      temp_note=0;
      YNbut(4);
      MouseOn(mouse);
    } else if(MousePress(739,649,789,699)&&func==2&&choose==1&&lim==1) {
      MouseOff(&mouse);
      YNbut(5);
      temp_note=2;
      YNbut(1);
      MouseOn(mouse);
    } else if(MousePress(784,710,900,766)&&func==2&&choose==1&&lim==1) {
      MouseOff(&mouse);
      note=temp_note;
      Bar1(0,560,1024,768,DARKCYAN24);
      Bar1(414,672,614,722,BLACK24);
      Bar1(412,670,612,720,LIGHTGRAY24);
      puthz(416,671,"发热上报",48,48,BLACK24);
      returnbut();
      choose=0;
      MouseOn(mouse);
    } else if(MousePress(906,710,1022,766)&&func==2&&choose==1&&lim==1) {
      MouseOff(&mouse);
      note=temp_note;
      Bar1(0,560,1024,768,DARKCYAN24);
      Bar1(414,672,614,722,BLACK24);
      Bar1(412,670,612,720,LIGHTGRAY24);
      puthz(416,671,"发热上报",48,48,BLACK24);
      returnbut();
      choose=0;
      MouseOn(mouse);
    } else if(choose==0&&MouseIn(stations[l-1].x-10,stations[l-1].y-10,stations[l-1].x+10,stations[l-1].y+10)==0) {
      Circlefill(stations[l-1].x,stations[l-1].y,9,LIGHTRED24);
      cur_station = 0;
    }
  }
}
STATUS_CODE DisplayLine(int line)
{
  char path[32];
  Bar1(0,0,1024,560,DARKCYAN24);
  CalcMapName(path, line);
  Readbmp64k(0, 0, path);
  //	while(1);
  return SUCCESS_CODE;
}

STATUS_CODE DrawMainPage()
{
  int i;
  Bar1(0,0,1024,768,DARKCYAN24);
  for(i=0; i<3; i++) {
    Bar1(320,198+i*130,704,272+i*130,DARKGRAY24);
    Bar1(322,200+i*130,702,270+i*130,LIGHTGRAY24);
  }
  puthz(391,212,"路线查询",48,64,BLACK24);
  puthz(390,211,"路线查询",48,64,BLACK24);
  puthz(371,212+130,"添加行程记录",48,50,BLACK24);
  puthz(370,211+130,"添加行程记录",48,50,BLACK24);
  puthz(371,212+260,"查看历史记录",48,50,BLACK24);
  puthz(370,211+260,"查看历史记录",48,50,BLACK24);
  Bar1(904,708,1024,768,DARKGRAY24);
  Bar1(906,710,1022,766,LIGHTGRAY24);
  puthz(918,716,"返回",48,48,BLACK24);
  returnbut();
  return SUCCESS_CODE;
}

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



void Hisbox(int page, UserInfo *user)
{
  int i;
  prt_hz16_size(257,32,4,4,"用户历史行程记录",DARKGRAY24,"HZK\\hzk16");
  prt_hz16_size(255,30,4,4,"用户历史行程记录",BLACK24,"HZK\\hzk16");
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
void InfoN(int c,int i)
{
  if(c==1) {
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
    puthz(760,211+i*120,"同车乘客",24,24,DARKGRAY24);
    puthz(759,210+i*120,"同车乘客",24,24,WHITE24);
  } else if(c==2) {
    puthz(139,149+(i*120),"姓名",32,32,DARKGRAY24);
    puthz(451,149+(i*120),"时间",32,32,DARKGRAY24);
    puthz(139,199+(i*120),"起点站",32,32,DARKGRAY24);
    puthz(451,199+(i*120),"终点站",32,32,DARKGRAY24);
    puthz(138,148+(i*120),"姓名",32,32,WHITE24);
    puthz(450,148+(i*120),"时间",32,32,WHITE24);
    puthz(138,198+(i*120),"起点站",32,32,WHITE24);
    puthz(450,198+(i*120),"终点站",32,32,WHITE24);
    Bar1(760,152+i*120,858,186+i*120,DARKGRAY24);
    Bar1(757,150+i*120,856,184+i*120,LIGHTGRAY24);
    puthz(760,155+i*120,"显示路径",24,24,DARKGRAY24);
    puthz(759,154+i*120,"显示路径",24,24,BLACK24);
  }
}
void InfoName(int c,int i)
{
  if(c==0) {
    InfoN(1,i);
  } else if(c==1) {
    Bar1(130,140+i*120,894,250+i*120,LIGHTRED24);
    bar3(130,140+i*120,894,250+i*120,BLACK24);
    InfoN(1,i);
  } else if(c==2) {
    InfoN(2,i);
  } else if(c==3) {
    Bar1(130,140+i*120,894,250+i*120,LIGHTRED24);
    bar3(130,140+i*120,894,250+i*120,BLACK24);
    InfoN(2,i);
  } else if(c==4) {
    Bar1(130,140+i*120,894,250+i*120,RED24);
    bar3(130,140+i*120,894,250+i*120,BLACK24);
    InfoN(2,i);
  } else if(c==5) {
    Bar1(130,140+i*120,894,250+i*120,RED24);
    bar3(130,140+i*120,894,250+i*120,BLACK24);
    InfoN(1,i);
  }
}
void returnbut()
{
  Bar1(904,708,1024,768,DARKGRAY24);
  Bar1(906,710,1022,766,LIGHTGRAY24);
  puthz(918,716,"返回",48,48,BLACK24);
  puthz(917,715,"返回",48,48,BLACK24);
}

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
void RPTrace(Route *route,int page,int line)
{
  Bar1(0,0,1024,768,DARKCYAN24);
  DisplayLine(route->line);
  DisplayTraces(route->line,route->ps[(page-1)*4+line-1].start,route->ps[(page-1)*4+line-1].end, CheckRev(route->route_name), CheckRound(route->route_name));
  returnbut();
  Stak(route->line,500,600,1,0,0,0);
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
void RecordFunc(UserInfo *user,int page,int line)
{
  RecordTrace(user,page,line,1);
  user->history_lines[(page-1)*4+line-1].note = Stak(user->history_lines[(page-1)*4+line-1].line_no,410,600,2,0,0,1);
}
void HisBoxFunc(UserInfo *user)
{
  int page = 1;
  int line=0;
  PuOne();
  DrawPage(page);
  Hisbox(page, user);
  Mouse_Init();
  while (1) {
    MouseShow(&mouse);
    if(MousePress(572,619,674,659)) {
      if(page==1) {
        page=2;
        DrawPage(page);
        Hisbox(page, user);
        delay(100);
      } else if(page==2) {
        page=3;
        DrawPage(page);
        Hisbox(page, user);
        delay(100);
      } else if(page==3) {
        page=4;
        DrawPage(page);
        Hisbox(page, user);
        delay(100);
      }
    } else if(MousePress(350,619,450,659)) {
      if(page==2) {
        page=1;
        DrawPage(page);
        Hisbox(page, user);
        delay(100);
      } else

        if(page==3) {
          page=2;
          DrawPage(page);
          Hisbox(page, user);
          delay(100);
        } else if(page==4) {
          page=3;
          DrawPage(page);
          Hisbox(page, user);
          delay(100);
        }
    } else if(MousePress(904,708,1024,768)) {
      MouseOff(&mouse);
      DrawMainPage();
      MouseOn(mouse);
      break;
    } else if(MousePress(760,152,858,186)) {
      MouseOff(&mouse);
      line=1;
      if(user->nhistory>(page-1)*4+line-1) {
        RecordFunc(user,page,line);
        PuOne();
        Hisbox(page,user);
        DrawPage(page);
      }
      MouseOn(mouse);//显示当页第一条路径
    } else if(MousePress(760,272,858,306)) {
      MouseOff(&mouse);
      line=2;
      if(user->nhistory>(page-1)*4+line-1) {
        RecordFunc(user,page,line);
        PuOne();
        Hisbox(page,user);
        DrawPage(page);
      }
      MouseOn(mouse);//显示当页第二条路径
    } else if(MousePress(760,392,858,426)) {
      MouseOff(&mouse);
      line=3;
      if(user->nhistory>(page-1)*4+line-1) {
        RecordFunc(user,page,line);
        PuOne();
        Hisbox(page,user);
        DrawPage(page);
      }
      MouseOn(mouse);//显示当页第三条路经
    } else if(MousePress(760,512,858,546)) {
      MouseOff(&mouse);
      line=4;
      if(user->nhistory>(page-1)*4+line-1) {
        RecordFunc(user,page,line);
        PuOne();
        Hisbox(page,user);
        DrawPage(page);
      }
      MouseOn(mouse);//显示当页第四条路径
    } else if(MousePress(760,207,858,241)) {
      MouseOff(&mouse);
      line=1;
      if(user->nhistory>(page-1)*4+line-1) {
        RelevantF(page,line,user);
        PuOne();
        Hisbox(page,user);
        DrawPage(page);
      }
      MouseOn(mouse);//查看当页第一条记录对应乘客乘车记录
    } else if(MousePress(760,327,858,361)) {
      MouseOff(&mouse);
      line=2;
      if(user->nhistory>(page-1)*4+line-1) {
        RelevantF(page,line,user);
        PuOne();
        Hisbox(page,user);
        DrawPage(page);
      }
      MouseOn(mouse);//查看当页第二条记录对应乘客乘车记录
    } else if(MousePress(760,447,858,481)) {
      MouseOff(&mouse);
      line=3;
      if(user->nhistory>(page-1)*4+line-1) {
        RelevantF(page,line,user);
        PuOne();
        Hisbox(page,user);
        DrawPage(page);
      }
      MouseOn(mouse);//查看当页第三条记录对应乘客乘车记录
    } else if(MousePress(760,567,858,601)) {
      MouseOff(&mouse);
      line=4;
      if(user->nhistory>(page-1)*4+line-1) {
        RelevantF(page,line,user);
        PuOne();
        Hisbox(page,user);
        DrawPage(page);
      }
      MouseOn(mouse);//查看当页第四条记录对应乘客乘车记录
    }
  }
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

void RSelectMaps()
{
  int i;
  Bar1(0,0,1024,768,DARKCYAN24);
  Bar1(904,708,1024,768,DARKGRAY24);
  Bar1(906,710,1022,766,LIGHTGRAY24);
  puthz(918,716,"返回",48,48,BLACK24);
  returnbut();
  for(i=0; i<4; i++) {
    Bar1(218,96+i*170,806,174+i*170,DARKGRAY24);
    Bar1(222,100+i*170,802,170+i*170,LIGHTGRAY24);
  }
  puthz(223,113,"一路",48,48,BLACK24);
  puthz(222,112,"一路",48,48,BLACK24);
  puthz(431,126,"刘家大湾",24,24,BLACK24);
  puthz(430,125,"刘家大湾",24,24,BLACK24);
  put_asc16_size(520,115,3,3,"(   )",BLACK24);
  puthz(543,126,"外环线",24,24,BLACK24);
  puthz(542,125,"外环线",24,24,BLACK24);

  /*	puthz(223,113+130,"线路二",48,48,BLACK24);
  	puthz(222,112+130,"线路二",48,48,BLACK24);
  	puthz(431,126+130,"刘家大湾",24,24,BLACK24);
  	puthz(430,125+130,"刘家大湾",24,24,BLACK24);
  	put_asc16_size(520,115+130,3,3,"(   )",BLACK24);
  	puthz(543,126+130,"内环线",24,24,BLACK24);
  	puthz(542,125+130,"内环线",24,24,BLACK24);*/

  puthz(223,113+170,"二路",48,48,BLACK24);
  puthz(222,112+170,"二路",48,48,BLACK24);
  puthz(431,126+170,"铜花山庄",24,24,BLACK24);
  puthz(430,125+170,"铜花山庄",24,24,BLACK24);
  put_asc16_size(535,115+170,3,3,"-->",BLACK24);
  puthz(603,126+170,"刘家大湾",24,24,BLACK24);
  puthz(602,125+170,"刘家大湾",24,24,BLACK24);
  put_asc16_size(695,115+170,3,3,"( )",BLACK24);
  puthz(719,126+170,"外",24,24,BLACK24);
  puthz(718,125+170,"外",24,24,BLACK24);

  puthz(223,113+340,"三路",48,48,BLACK24);
  puthz(222,112+340,"三路",48,48,BLACK24);
  puthz(431,126+340,"铜花山庄",24,24,BLACK24);
  puthz(430,125+340,"铜花山庄",24,24,BLACK24);
  put_asc16_size(535,115+340,3,3,"-->",BLACK24);
  puthz(603,126+340,"刘家大湾",24,24,BLACK24);
  puthz(602,125+340,"刘家大湾",24,24,BLACK24);
  put_asc16_size(695,115+340,3,3,"( )",BLACK24);
  puthz(719,126+340,"全",24,24,BLACK24);
  puthz(718,125+340,"全",24,24,BLACK24);

  puthz(223,113+510,"四路",48,48,BLACK24);
  puthz(222,112+510,"四路",48,48,BLACK24);
  puthz(431,126+510,"铜花山庄",24,24,BLACK24);
  puthz(430,125+510,"铜花山庄",24,24,BLACK24);
  put_asc16_size(535,115+510,3,3,"-->",BLACK24);
  puthz(603,126+510,"刘家大湾",24,24,BLACK24);
  puthz(602,125+510,"刘家大湾",24,24,BLACK24);
  put_asc16_size(695,115+170*3,3,3,"( )",BLACK24);
  puthz(719,126+170*3,"内",24,24,BLACK24);
  puthz(718,125+170*3,"内",24,24,BLACK24);
  Bar1(435,708,589,768,DARKGRAY24);
  Bar1(437,710,587,766,LIGHTGRAY24);
  puthz(441,716,"上一页",48,48,BLACK24);
  puthz(440,715,"上一页",48,48,BLACK24);
}


void AddBox1()
{
  Bar1(0,560,1024,705,LIGHTGRAY24);
  Bar1(782,708,902,768,LIGHTGRAY24);
  Bar1(0,560,1024,705,LIGHTGRAY24);
  Bar1(208,598,462,662,BLACK24);
  Bar1(212,602,458,658,LIGHTGRAY24);
  puthz(215,605,"添加起点站",48,48,BLACK24);
  put_asc16_size(478,610,3,3,"-->",BLACK24);
  Bar1(562,598,816,662,BLACK24);
  Bar1(566,602,812,658,LIGHTGRAY24);
  puthz(569,605,"添加终点站",48,48,BLACK24);
  Bar1(904,708,1024,768,DARKGRAY24);
  Bar1(906,710,1022,766,LIGHTGRAY24);
  puthz(918,716,"返回",48,48,BLACK24);
  returnbut();
}


void StationName(int Sflag,int Station,char *name)
{
  if(Sflag==1) { //起点站
    Bar1(208,598,462,662,BLACK24);
    Bar1(212,602,458,658,LIGHTGRAY24);
    puthz(217,606,name,48,48,BLACK24);
  } else if(Sflag==2) { //终点站
    Bar1(562,598,816,662,BLACK24);
    Bar1(566,602,812,658,LIGHTGRAY24);
    puthz(571,606,name,48,48,BLACK24);
  }
}

void AddBox2()
{
  Bar1(0,560,1024,705,LIGHTGRAY24);
  Bar1(782,708,902,768,LIGHTGRAY24);
  puthz(369,566,"录入上车时间",48,48,BLACK24);
  puthz(368,565,"录入上车时间",48,48,NAVY24);
  Bar1(145,642,275,692,WHITE24);
  bar3(145,642,275,692,BLACK24);
  puthz(280,643,"年",48,48,BLACK24);
  Bar1(333,642,433,692,WHITE24);
  bar3(333,642,433,692,BLACK24);
  puthz(438,643,"月",48,48,BLACK24);
  Bar1(491,642,591,692,WHITE24);
  bar3(491,642,591,692,BLACK24);
  puthz(596,643,"日",48,48,BLACK24);
  Bar1(649,642,810,692,WHITE24);
  bar3(649,642,810,692,BLACK24);
  puthz(815,643,"车次",48,48,BLACK24);
}
void YNbut(int cho)
{
  if(cho==1) {
    Bar1(639,589,689,639,LIGHTGRAY24);
    bar3(639,589,689,639,WHITE24);
    puthz(640,590,"是",48,48,BLACK24);
    Bar1(692,589,742,639,LIGHTGRAY24);
    bar3(692,589,742,639,WHITE24);
    puthz(693,590,"否",48,48,BLACK24);
  } else if(cho==2) {
    Bar1(639,589,689,639,DARKGRAY24);
    puthz(640,590,"是",48,48,RED24);
    Bar1(692,589,742,639,LIGHTGRAY24);
    bar3(692,589,742,639,WHITE24);
    puthz(693,590,"否",48,48,BLACK24);
  } else if(cho==3) {
    Bar1(639,589,689,639,LIGHTGRAY24);
    bar3(639,589,689,639,WHITE24);
    puthz(640,590,"是",48,48,BLACK24);
    Bar1(692,589,742,639,DARKGRAY24);
    puthz(693,590,"否",48,48,GREEN24);
  } else if(cho==4) {
    Bar1(739,649,789,699,LIGHTGRAY24);
    bar3(739,649,789,699,WHITE24);
    puthz(740,650,"是",48,48,BLACK24);
  } else if(cho==5) {
    Bar1(739,649,789,699,DARKGRAY24);
    puthz(740,650,"是",48,48,RED24);
  }
}
void AddBox3()
{
  Bar1(0,560,1024,705,LIGHTGRAY24);
  puthz(100,590,"近十四天是否有发热症状",48,48,BLACK24);
  YNbut(1);
  puthz(100,650,"乘车至今是否确诊为新冠患者",48,48,BLACK24);
  YNbut(4);
  Bar1(782,708,902,768,DARKGRAY24);
  Bar1(784,710,900,766,LIGHTGRAY24);
  puthz(795,716,"确认",48,48,BLACK24);
  puthz(794,715,"确认",48,48,BLACK24);
}
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
void AddHis(char *account, int line, UserInfo *user,int page)   //page==1正向page==2反向
{
  int LEN1;
  int start=0;
  int end=0;
  int Dflag=1;
  char year[12];
  char month[3];
  char day[3];
  char bnum[4];
  char time[10];
  char btime[16];
  char route_name[16];
  char note[64];
  HisLi temp;
  int yi,mi,di,ni,bi;
  temp.note=3;
  year[0] = '\0';
  month[0] = '\0';
  day[0] = '\0';
  bnum[0] = '\0';
  note[0] = '\0';
  btime[0] = '\0';
  route_name[0] = '\0';
  Bar1(0,560,1024,768,LIGHTGRAY24);
  AddBox1();
  Bar1(334,717,494,760,BLACK24);
  Bar1(332,716,492,758,DARKGRAY24);
  Bar1(534,717,694,760,BLACK24);
  Bar1(532,716,692,758,DARKGRAY24);
  puthz(364,721,"上一页",32,32,BLACK24);
  puthz(564,721,"下一页",32,32,BLACK24);
  Mouse_Init();
  while(1) {
    MouseShow(&mouse);
    if(MousePress(532,716,692,758)) {
      if(Dflag==1) {
        MouseOff(&mouse);
        AddBox2();//添加时间
        Dflag++;
        delay(100);
        MouseOn(mouse);
      } else if(Dflag==2) {
        MouseOff(&mouse);
        yi=strlen(year);
        mi=strlen(month);
        di=strlen(day);
        if(JudgeTime(year,month,day,yi,mi,di)==SUCCESS_CODE) {
          mi = strlen(month);
          di = strlen(day);
          Connect(year,month,day,time,route_name,bnum,1,btime,page,line);//生成时间
          Connect(year,month,day,time,route_name,bnum,2,btime,page,line);//生成车次 日期+车号
          AddBox3();//添加注释
          if(temp.note==1) {
            YNbut(2);
          } else if(temp.note==0) {
            YNbut(3);
          } else if(temp.note==2) {
            YNbut(5);
          } else if(temp.note==3) {
            YNbut(1);
          }
          Dflag++;
          delay(100);
        } else if(JudgeTime(year,month,day,yi,mi,di)==ERROR_CODE) {
          InputError(line,start,end, page == 2, line == 1, 1);
        }
        MouseOn(mouse);
      }
    } else if(MousePress(332,716,492,758)) {
      if(Dflag==3) {
        AddBox2();
        put_asc16_size(149,641,2,2,year,BLACK24);
        put_asc16_size(337,641,2,2,month,BLACK24);
        put_asc16_size(494,641,2,2,day,BLACK24);
        put_asc16_size(653,641,2,2,bnum,BLACK24);
        Dflag--;
        delay(100);
      } else if(Dflag==2) {
        AddBox1();
        Dflag--;
        delay(100);
      }
    } else if(MousePress(212,602,458,658) && Dflag==1 && start==0) {
      MouseOff(&mouse);
      start=Stak(line,335,658,3,0,1,0);
      //Bar1(212,663,458,713,LIGHTGRAY24);

      if(start!=0&&end!=0) {
        DisplayTraces(line,start,end, page==2, line==1);
      }
      MouseOn(mouse);
    } else if(MousePress(566,602,812,658) && Dflag==1 && end==0) {
      MouseOff(&mouse);
      end=Stak(line,689,658,3,0,2,0);
      //Bar1(566,663,812,713,LIGHTGRAY24);

      if(start!=0&&end!=0) {
        DisplayTraces(line,start,end, page==2, line==1);
      }
      MouseOn(mouse);
    } else if(MousePress(906,710,1022,766)) {
      Maps();
      NextPage();
      Dflag=1;
      break;
    } else if(MousePress(145,642,275,692)&&Dflag==2) {
      MouseOff(&mouse);
      yi=strlen(year);
      Getnum(149,643,year,4,yi);
      MouseOn(mouse);
    } else if(MousePress(333,642,433,692)&&Dflag==2) {
      MouseOff(&mouse);
      mi=strlen(month);
      Getnum(337,643,month,2,mi);
      MouseOn(mouse);
    } else if(MousePress(491,642,591,692)&&Dflag==2) {
      MouseOff(&mouse);
      di=strlen(day);
      Getnum(494,643,day,2,di);
      MouseOn(mouse);
    } else if(MousePress(649,642,810,692)&&Dflag==2) {
      MouseOff(&mouse);
      bi=strlen(bnum);
      Getnum(653,643,bnum,2,bi);
      MouseOn(mouse);
    }  else if(MousePress(639,589,689,639)&&Dflag==3) {
      MouseOff(&mouse);
      YNbut(2);
      temp.note=1;
      YNbut(4);
      MouseOn(mouse);
    } else if(MousePress(692,589,742,639)&&Dflag==3) {
      MouseOff(&mouse);
      YNbut(3);
      temp.note=0;
      YNbut(4);
      MouseOn(mouse);
    } else if(MousePress(739,649,789,699)&&Dflag==3) {
      MouseOff(&mouse);
      YNbut(5);
      YNbut(1);
      temp.note=2;
      MouseOn(mouse);
    } else if(MousePress(784,710,900,766)&&Dflag==3) {
      //完成输入
      strcpy(temp.time,time);
      temp.line_no=line;
      temp.start=start;
      temp.end=end;
      strcpy(temp.busnum,route_name);
      UserNewTravel(account, &temp, user);
      delay(100);
      RouteNewPassenger(line,route_name,&temp,user->name);
      Maps();
      NextPage();
      Dflag=1;
      break;
    }
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
void AddFunc(UserInfo *user)
{
  int page=1;
  int line=0;//page=1正向 page=2反向
  Maps();
  NextPage();
  Mouse_Init();
  while (1) {
    MouseShow(&mouse);
    if(MousePress(218,96,806,174)) {
      MouseOff(&mouse);
      line=1;
      DisplayLine(line);
      AddHis(user->account, line, user, page);
      page=1;
      MouseOn(mouse);
    }
    /*	else if(MousePress(218,226,806,304))
    		{
    			MouseOff(&mouse);
    			DisplayLine(2);
    			AddHis(2, user);
    			MouseOn(mouse);
    		}*/
    else if(MousePress(218,96+170,806,174+170)) {
      MouseOff(&mouse);
      line=3;
      DisplayLine(line);
      AddHis(user->account, line, user, page);
      page=1;
      MouseOn(mouse);
    } else if(MousePress(218,96+340,806,174+340)) {
      MouseOff(&mouse);
      line=4;
      DisplayLine(line);
      AddHis(user->account, line, user, page);
      page=1;
      MouseOn(mouse);
    } else if(MousePress(218,96+510,806,174+510)) {
      MouseOff(&mouse);
      line=5;
      DisplayLine(line);
      AddHis(user->account, line, user, page);
      page=1;
      MouseOn(mouse);
    } else if(MousePress(437,710,587,766)) {
      MouseOff(&mouse);
      if(page==2) {
        Maps();
        NextPage();
        page=1;
      } else if(page==1) {
        RSelectMaps();
        page=2;
      }
      MouseOn(mouse);
    } else if(MousePress(906,710,1022,766)) {
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
    if(MousePress(218,96,806,174)) {
      MouseOff(&mouse);
      Bar1(0,0,1024,768,DARKCYAN24);
      returnbut();
      DisplayLine(1);
      ShowSta(1);
      Maps();
      MouseOn(mouse);
    }
    /*	else if(MousePress(218,226,806,304)&&Page==0)
    		{
    			MouseOff(&mouse);
    			DisplayLine(2);
    			MouseOn(mouse);
    			Page=1;
    		}*/
    else if(MousePress(218,96+170,806,174+170)) {
      MouseOff(&mouse);
      Bar1(0,0,1024,768,DARKCYAN24);
      returnbut();
      DisplayLine(3);
      ShowSta(3);
      Maps();
      MouseOn(mouse);
    } else if(MousePress(218,96+340,806,174+340)) {
      MouseOff(&mouse);
      Bar1(0,0,1024,768,DARKCYAN24);
      returnbut();
      DisplayLine(4);
      ShowSta(4);
      Maps();
      MouseOn(mouse);
    } else if(MousePress(218,96+510,806,174+510)) {
      MouseOff(&mouse);
      Bar1(0,0,1024,768,DARKCYAN24);
      returnbut();
      DisplayLine(5);
      ShowSta(5);
      Maps();
      MouseOn(mouse);
    } else if(MousePress(906,710,1022,766)) {
      MouseOff(&mouse);
      DrawMainPage();
      break;
      MouseOn(mouse);
    }
  }
}
STATUS_CODE RunFunc(char *user_account)
{
  STATUS_CODE flag;
  UserInfo user;
  GetUserInfo(&user, user_account);
  DrawMainPage();
  Mouse_Init();
  while (1) {
    MouseShow(&mouse);
    if(MousePress(322,198,704,272)) {
      //路线查询功能
      MouseOff(&mouse);
      SelectMap();
      MouseOn(mouse);
    } else if(MousePress(322,328,704,402)) {
      //添加历史记录
      MouseOff(&mouse);
      AddFunc(&user);
      //AdminiFunc();
      MouseOn(mouse);
    } else if(MousePress(322,458,704,532)) {
      //历史行程记录查询
      MouseOff(&mouse);
      HisBoxFunc(&user);
      MouseOn(mouse);
    } else if(MousePress(904,708,1024,768)) {
      MouseOff(&mouse);
      break;
    }
  }

  return SUCCESS_CODE;
}
