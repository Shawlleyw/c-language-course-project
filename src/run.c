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
  puthz(441,716,"��һҳ",48,48,BLACK24);
  puthz(440,715,"��һҳ",48,48,BLACK24);
}

void Maps()
{
  int i;
  Bar1(0,0,1024,768,DARKCYAN24);
  Bar1(904,708,1024,768,DARKGRAY24);
  Bar1(906,710,1022,766,LIGHTGRAY24);
  puthz(918,716,"����",48,48,BLACK24);
  returnbut();
  for(i=0; i<4; i++) {
    Bar1(218,96+i*170,806,174+i*170,DARKGRAY24);
    Bar1(222,100+i*170,802,170+i*170,LIGHTGRAY24);
  }
  puthz(223,113,"һ·",48,48,BLACK24);
  puthz(222,112,"һ·",48,48,BLACK24);
  puthz(431,126,"���Ҵ���",24,24,BLACK24);
  puthz(430,125,"���Ҵ���",24,24,BLACK24);
  put_asc16_size(520,115,3,3,"(   )",BLACK24);
  puthz(543,126,"�⻷��",24,24,BLACK24);
  puthz(542,125,"�⻷��",24,24,BLACK24);

  puthz(223,113+170,"��·",48,48,BLACK24);
  puthz(222,112+170,"��·",48,48,BLACK24);
  puthz(431,126+170,"���Ҵ���",24,24,BLACK24);
  puthz(430,125+170,"���Ҵ���",24,24,BLACK24);
  put_asc16_size(535,115+170,3,3,"-->",BLACK24);
  puthz(603,126+170,"ͭ��ɽׯ",24,24,BLACK24);
  puthz(602,125+170,"ͭ��ɽׯ",24,24,BLACK24);
  put_asc16_size(695,115+170,3,3,"( )",BLACK24);
  puthz(719,126+170,"��",24,24,BLACK24);
  puthz(718,125+170,"��",24,24,BLACK24);

  puthz(223,113+340,"��·",48,48,BLACK24);
  puthz(222,112+340,"��·",48,48,BLACK24);
  puthz(431,126+340,"���Ҵ���",24,24,BLACK24);
  puthz(430,125+340,"���Ҵ���",24,24,BLACK24);
  put_asc16_size(535,115+340,3,3,"-->",BLACK24);
  puthz(603,126+340,"ͭ��ɽׯ",24,24,BLACK24);
  puthz(602,125+340,"ͭ��ɽׯ",24,24,BLACK24);
  put_asc16_size(695,115+340,3,3,"( )",BLACK24);
  puthz(719,126+340,"ȫ",24,24,BLACK24);
  puthz(718,125+340,"ȫ",24,24,BLACK24);

  puthz(223,113+510,"��·",48,48,BLACK24);
  puthz(222,112+510,"��·",48,48,BLACK24);
  puthz(431,126+510,"���Ҵ���",24,24,BLACK24);
  puthz(430,125+510,"���Ҵ���",24,24,BLACK24);
  put_asc16_size(535,115+510,3,3,"-->",BLACK24);
  puthz(603,126+510,"ͭ��ɽׯ",24,24,BLACK24);
  puthz(602,125+510,"ͭ��ɽׯ",24,24,BLACK24);
  put_asc16_size(695,115+170*3,3,3,"( )",BLACK24);
  puthz(719,126+170*3,"��",24,24,BLACK24);
  puthz(718,125+170*3,"��",24,24,BLACK24);
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
  return path;
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

void DisplayTraces(int line, int start, int end)
{
  int ids = -1, ide = -1, i, reverse = 0;
  char ch;
  FILE *fp;
  Lines l;
  Sta cur, pre;
  char path[32];
  ReadLineInfo(&l, line);
  for(i = 1; i <= l.n; i++) {
    if(l.station_numbers[i] == start) {
      ids = i;
      if(ide != -1)reverse = 1;
    }
    if(l.station_numbers[i] == end) {
      ide = i;
    }
  }
  //DrawStart(start);
  //DrawEnd(end);
  if(reverse == 1) {
    i = ide;
    ide = ids;
    ids = i;
  }
  for(i = ids; i <= ide; i++) {
    CalcStationPath(path, l.station_numbers[i]);
    fp = fopen(path, "rb");
    if(fp == NULL) {
      CloseSVGA();
      fprintf(stderr, "fopen error: file %s dose not exist\n station: %d\n", path, l.station_numbers[i]);
      ch = getchar();
      exit(ERROR_CODE);
    }
    fread(&cur, sizeof(cur), 1, fp);
    fclose(fp);
    fp = NULL;
    if(i != ids)Line_Thick(cur.x, cur.y, pre.x, pre.y, 6, BLACK24);
    pre = cur;
  }
  for(i = ids + 1; i < ide; i++) {
    fp = fopen(CalcStationPath(path, l.station_numbers[i]), "rb");
    fread(&cur, sizeof(cur), 1, fp);
    if(cur.number < 50)Circlefill(cur.x, cur.y, 9, RED24);
    fclose(fp);
    fp = NULL;
  }
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
  
  puthz(301,601,"վ��",48,48,BLACK24);
  puthz(300,600,"վ��",48,48,BLACK24);
  Stak(line,400,600,1,0);
}

void Stak(int line,int x,int y,int func,int note)
{
  int l=0;
  int choose=0;
  int temp_note;
  int cur_station = 0;
  staname station[28]= {
    {1,"���Ҵ���"},
    {2,"������"},
    {3,"����һƷ"},
    {4,"�����"},
    {5,"���㳡"},
    {6,"����ҽԺ"},
    {7,"�����"},
    {8,"����"},
    {9,"�ź���"},
    {10,"���԰"},
    {11,"���Ļ�԰"},
    {12,"���ױ���Ժ"},
    {13,"����ɽׯ"},
    {14,"����ɽׯ"},
    {15,"������԰"},
    {16,"Ф��"},
    {17,"���ݹ���"},
    {18,"����С��"},
    {19,"����ɽ"},
    {20,"����"},
    {21,"������"},
    {22,"��ά�Ƕ�"},
    {23,"ͭ��ɽׯ"},
    {24,"�����"},
    {25,"�����"},
    {26,"������԰"},
    {27,"�����"},
    {28,"Ԭ��"}
  };
  Mouse_Init();
  while(1) {
    MouseShow(&mouse);
    if (MouseIn(806, 528, 826, 548) == 1 ) {
      l=1;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);

    } else if (MouseIn(629, 480, 649, 500) == 1 ) {
      l=2;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);

    } else if (MouseIn(443, 389, 463, 409) == 1 ) {
      l=3;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);

    } else if (MouseIn(250, 355, 270, 375) == 1 ) {
      l=4;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(55, 353, 75, 373) == 1 ) {
      l=5;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(130, 166, 150, 186) == 1 ) {
      l=6;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(192, 62, 212, 82) == 1 ) {
      l=7;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(337, 8, 357, 28) == 1 ) {
      l=8;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(469, 7, 489, 27) == 1 ) {
      l=9;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(620, 5, 640, 25) == 1 ) {
      l=10;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(801, 2, 821, 22) == 1 ) {
      l=11;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(998, 77, 1018, 97) == 1 ) {
      l=12;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(996, 225, 1016, 245) == 1 ) {
      l=13;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(996, 375, 1016, 395) == 1 ) {
      l=14;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(943, 497, 963, 517) == 1 ) {
      l=15;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(379, 282, 399, 302) == 1 ) {
      l=16;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(377, 72, 397, 92) == 1 ) {
      l=17;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(549, 114, 569, 134) == 1 ) {
      l=18;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(678, 213, 698, 233) == 1 ) {
      l=19;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(847, 270, 867, 290) == 1 ) {
      l=20;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(886, 380, 906, 400) == 1 ) {
      l=21;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(884, 467, 904, 487) == 1 ) {
      l=22;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(19, 200, 39, 220) == 1 ) {
      l=23;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(204, 208, 224, 228) == 1 ) {
      l=24;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(335, 209, 355, 229) == 1 ) {
      l=25;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);


    } else if (MouseIn(532, 312, 552, 332) == 1 ) {
      l=26;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);

    } else if (MouseIn(471, 210, 491, 230) == 1 ) {
      l=27;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);

    } else if (MouseIn(276, 101, 296, 121) == 1 ) {
      l=28;
      if(cur_station == l)continue;
      else cur_station = l;
      Bar1(x-2,y-2,x+300,y+50,DARKCYAN24);
      puthz(x+1,y+1,station[l-1].stationname,48,48,BLACK24);
      puthz(x,y,station[l-1].stationname,48,48,BLACK24);

    } else if(MousePress(906,710,1022,766)&&choose==0) {
      MouseOff(&mouse);
      break;
      
    } else if(MousePress(412,670,612,720)&&func==2&&choose==0) {
	    RecordBox(1);
	    choose=1;
		  
	} else if(MousePress(639,589,689,639)&&func==2&&choose==1) {
	    MouseOff(&mouse);
	    YNbut(2);
	    temp_note=1;
	    YNbut(4);
	    MouseOn(mouse);
		  
	} else if(MousePress(692,589,742,639)&&func==2&&choose==1) {
		MouseOff(&mouse);
		YNbut(3);
		temp_note=0;
		YNbut(4);
		MouseOn(mouse);		  
	} else if(MousePress(739,649,789,699)&&func==2&&choose==1) {
		MouseOff(&mouse);
        YNbut(5);
        temp_note=2;
        YNbut(1);
        MouseOn(mouse);
    } else if(MousePress(784,710,900,766)&&func==2&&choose==1) {
    	note=temp_note;
    	Bar1(0,560,1024,768,DARKCYAN24); 	
        Bar1(414,672,614,722,BLACK24);
	    Bar1(412,670,612,720,LIGHTGRAY24);
	    puthz(416,671,"�����ϱ�",48,48,BLACK24);
        returnbut();
        choose=0;
	} else if(MousePress(906,710,1022,766)&&func==2&&choose==1) {
		Bar1(0,560,1024,768,DARKCYAN24); 	
        Bar1(414,672,614,722,BLACK24);
	    Bar1(412,670,612,720,LIGHTGRAY24);
	    puthz(416,671,"�����ϱ�",48,48,BLACK24);
        returnbut();
        choose=0;
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
  puthz(391,212,"·�߲�ѯ",48,64,BLACK24);
  puthz(390,211,"·�߲�ѯ",48,64,BLACK24);
  puthz(371,212+130,"����г̼�¼",48,50,BLACK24);
  puthz(370,211+130,"����г̼�¼",48,50,BLACK24);
  puthz(371,212+260,"�鿴��ʷ��¼",48,50,BLACK24);
  puthz(370,211+260,"�鿴��ʷ��¼",48,50,BLACK24);
  Bar1(904,708,1024,768,DARKGRAY24);
  Bar1(906,710,1022,766,LIGHTGRAY24);
  puthz(918,716,"����",48,48,BLACK24);
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
    
	for(i=0;i<temp_route->npassenger;i++) {
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
  prt_hz16_size(193,32,4,4,"ͬ���˿��г̼�¼��ѯ",DARKGRAY24,"HZK\\hzk16");
  prt_hz16_size(191,30,4,4,"ͬ���˿��г̼�¼��ѯ",BLACK24,"HZK\\hzk16");
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
  prt_hz16_size(257,32,4,4,"�û���ʷ�г̼�¼",DARKGRAY24,"HZK\\hzk16");
  prt_hz16_size(255,30,4,4,"�û���ʷ�г̼�¼",BLACK24,"HZK\\hzk16");
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
	  puthz(139,149+(i*120),"ʱ��",32,32,DARKGRAY24);
      puthz(139,199+(i*120),"���վ",32,32,DARKGRAY24);
      puthz(451,199+(i*120),"�յ�վ",32,32,DARKGRAY24);
      puthz(138,148+(i*120),"ʱ��",32,32,WHITE24);
      puthz(138,198+(i*120),"���վ",32,32,WHITE24);
      puthz(450,198+(i*120),"�յ�վ",32,32,WHITE24);
      Bar1(760,152+i*120,858,186+i*120,DARKGRAY24);
      Bar1(757,150+i*120,856,184+i*120,LIGHTGRAY24);
      puthz(760,155+i*120,"��ʾ·��",24,24,DARKGRAY24);
      puthz(759,154+i*120,"��ʾ·��",24,24,BLACK24);
      Bar1(760,207+i*120,858,241+i*120,DARKGRAY24);
      Bar1(757,205+i*120,856,239+i*120,LIGHTGRAY24);
      puthz(760,211+i*120,"ͬ���˿�",24,24,DARKGRAY24);
      puthz(759,210+i*120,"ͬ���˿�",24,24,WHITE24);
	} else if(c==2) {
	  puthz(139,149+(i*120),"����",32,32,DARKGRAY24);
	  puthz(451,149+(i*120),"ʱ��",32,32,DARKGRAY24);
      puthz(139,199+(i*120),"���վ",32,32,DARKGRAY24);
      puthz(451,199+(i*120),"�յ�վ",32,32,DARKGRAY24);
      puthz(138,148+(i*120),"����",32,32,WHITE24);
      puthz(450,148+(i*120),"ʱ��",32,32,WHITE24);
      puthz(138,198+(i*120),"���վ",32,32,WHITE24);
      puthz(450,198+(i*120),"�յ�վ",32,32,WHITE24);
      Bar1(760,152+i*120,858,186+i*120,DARKGRAY24);
      Bar1(757,150+i*120,856,184+i*120,LIGHTGRAY24);
      puthz(760,155+i*120,"��ʾ·��",24,24,DARKGRAY24);
      puthz(759,154+i*120,"��ʾ·��",24,24,BLACK24); 	
	} 
}
void InfoName(int c,int i)
{
	if(c==0)
	{
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
    puthz(918,716,"����",48,48,BLACK24);
    puthz(917,715,"����",48,48,BLACK24);
}

void RecordTrace(UserInfo *user,int page,int line,int c)
{
	if(c==1) {
	   Bar1(0,0,1024,768,DARKCYAN24);
       DisplayLine(user->history_lines[(page-1)*4+line-1].line_no);
	   DisplayTraces(user->history_lines[(page-1)*4+line-1].line_no,user->history_lines[(page-1)*4+line-1].start,user->history_lines[(page-1)*4+line-1].end);
	   Bar1(414,672,614,722,BLACK24);
	   Bar1(412,670,612,720,LIGHTGRAY24);
	   puthz(416,671,"�����ϱ�",48,48,BLACK24);
       returnbut();
	} else if(c==2) {
		Bar1(0,0,1024,768,DARKCYAN24);
    	DisplayLine(user->history_lines[(page-1)*4+line-1].line_no);
    	DisplayTraces(user->history_lines[(page-1)*4+line-1].line_no,user->history_lines[(page-1)*4+line-1].start,user->history_lines[(page-1)*4+line-1].end);
        returnbut();
        Stak(user->history_lines[(page-1)*4+line-1].line_no,500,600,1,0);
	}
}
void RPTrace(Route *route,int page,int line)
{
	Bar1(0,0,1024,768,DARKCYAN24);
	DisplayLine(route->line);
	DisplayTraces(route->line,route->ps[(page-1)*4+line-1].start,route->ps[(page-1)*4+line-1].end);
    returnbut();
    Stak(route->line,500,600,1,0);
}
void RecordBox(int i)
{
	if(i==0){
	Bar1(0,560,1024,768,DARKCYAN24);
	Line_Thick(362,720,662,720,2,BLACK24);
    returnbut();
	}else if(i==1){
	Bar1(0,560,1024,768,LIGHTGRAY24);
    returnbut();
	AddBox3();
	}
}
void RecordFunc(UserInfo *user,int page,int line)
{
   int note;
   RecordTrace(user,page,line,1);
   Stak(line,410,600,2,note);
   delay(100);
   user->history_lines[(page-1)*4+line-1].note=note;
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
	  MouseOn(mouse);//��ʾ��ҳ��һ��·��
	} else if(MousePress(760,272,858,306)) {
	  MouseOff(&mouse);
	  line=2;
	  if(user->nhistory>(page-1)*4+line-1) {
	  	RecordFunc(user,page,line);
	    PuOne();
	    Hisbox(page,user);
	    DrawPage(page);
	  }
	  MouseOn(mouse);//��ʾ��ҳ�ڶ���·��
	} else if(MousePress(760,392,858,426)) {
	  MouseOff(&mouse);
	  line=3;
	  if(user->nhistory>(page-1)*4+line-1) {
	  	RecordFunc(user,page,line);
	    PuOne();
	    Hisbox(page,user);
	    DrawPage(page);
	  }
      MouseOn(mouse);//��ʾ��ҳ������·��
    } else if(MousePress(760,512,858,546)) {
      MouseOff(&mouse);
      line=4;
	  if(user->nhistory>(page-1)*4+line-1) {
	  	RecordFunc(user,page,line);
	    PuOne();
	    Hisbox(page,user);
	    DrawPage(page);
	  }
	  MouseOn(mouse);//��ʾ��ҳ������·��
	} else if(MousePress(760,207,858,241)) {
      MouseOff(&mouse);
      line=1;
      if(user->nhistory>(page-1)*4+line-1) {
      	RelevantF(page,line,user);
        PuOne();
	    Hisbox(page,user);
	    DrawPage(page);
	  }
      MouseOn(mouse);//�鿴��ҳ��һ����¼��Ӧ�˿ͳ˳���¼
    } else if(MousePress(760,327,858,361)) {
      MouseOff(&mouse);
      line=2;
      if(user->nhistory>(page-1)*4+line-1) {
      	RelevantF(page,line,user);
        PuOne();
	    Hisbox(page,user);
	    DrawPage(page);
	  }
      MouseOn(mouse);//�鿴��ҳ�ڶ�����¼��Ӧ�˿ͳ˳���¼
    } else if(MousePress(760,447,858,481)) {
      MouseOff(&mouse);
      line=3;
      if(user->nhistory>(page-1)*4+line-1) {
      	RelevantF(page,line,user);
        PuOne();
	    Hisbox(page,user);
	    DrawPage(page);
	  }
      MouseOn(mouse);//�鿴��ҳ��������¼��Ӧ�˿ͳ˳���¼
    } else if(MousePress(760,567,858,601)) {
      MouseOff(&mouse);
      line=4;
      if(user->nhistory>(page-1)*4+line-1) {
      	RelevantF(page,line,user);
        PuOne();
	    Hisbox(page,user);
	    DrawPage(page);
	  }
      MouseOn(mouse);//�鿴��ҳ��������¼��Ӧ�˿ͳ˳���¼
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
   
  strcpy(route_name,user->history_lines[(page-1)*4+line-1].busnum);//��ȡ�û������˳���¼�ĳ���
   
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
      MouseOff(&mouse);//��ʾ��ҳ��һ����¼��Ӧ·��
      rline=1;
      if(route.npassenger>(rpage-1)*4+rline-1) {
      	RPTrace(&route,rpage,rline);
      	PuOne();
      	Relevant(&route,rpage,user);
      	DrawPage(rpage);
	  }
      MouseOn(mouse);
    } else if(MousePress(760,272,858,306)) {
      MouseOff(&mouse);//��ʾ��ҳ�ڶ�����¼��Ӧ·��
      rline=2;
      if(route.npassenger>(rpage-1)*4+rline-1) {
      	RPTrace(&route,rpage,rline);
      	PuOne();
      	Relevant(&route,rpage,user);
      	DrawPage(rpage);
	  }
      MouseOn(mouse);
    } else if(MousePress(760,392,858,426)) {
      MouseOff(&mouse);//��ʾ��ҳ��������¼��Ӧ·��
      rline=3;
      if(route.npassenger>(rpage-1)*4+rline-1) {
      	RPTrace(&route,rpage,rline);
      	PuOne();
      	Relevant(&route,rpage,user);
      	DrawPage(rpage);
	  }
      MouseOn(mouse);
    } else if(MousePress(760,512,858,546)) {
      MouseOff(&mouse);//��ʾ��ҳ��������¼��Ӧ·��
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
  puthz(918,716,"����",48,48,BLACK24);
  returnbut();
  for(i=0; i<4; i++) {
    Bar1(218,96+i*170,806,174+i*170,DARKGRAY24);
    Bar1(222,100+i*170,802,170+i*170,LIGHTGRAY24);
  }
  puthz(223,113,"һ·",48,48,BLACK24);
  puthz(222,112,"һ·",48,48,BLACK24);
  puthz(431,126,"���Ҵ���",24,24,BLACK24);
  puthz(430,125,"���Ҵ���",24,24,BLACK24);
  put_asc16_size(520,115,3,3,"(   )",BLACK24);
  puthz(543,126,"�⻷��",24,24,BLACK24);
  puthz(542,125,"�⻷��",24,24,BLACK24);

  /*	puthz(223,113+130,"��·��",48,48,BLACK24);
  	puthz(222,112+130,"��·��",48,48,BLACK24);
  	puthz(431,126+130,"���Ҵ���",24,24,BLACK24);
  	puthz(430,125+130,"���Ҵ���",24,24,BLACK24);
  	put_asc16_size(520,115+130,3,3,"(   )",BLACK24);
  	puthz(543,126+130,"�ڻ���",24,24,BLACK24);
  	puthz(542,125+130,"�ڻ���",24,24,BLACK24);*/

  puthz(223,113+170,"��·",48,48,BLACK24);
  puthz(222,112+170,"��·",48,48,BLACK24);
  puthz(431,126+170,"ͭ��ɽׯ",24,24,BLACK24);
  puthz(430,125+170,"ͭ��ɽׯ",24,24,BLACK24);
  put_asc16_size(535,115+170,3,3,"-->",BLACK24);
  puthz(603,126+170,"���Ҵ���",24,24,BLACK24);
  puthz(602,125+170,"���Ҵ���",24,24,BLACK24);
  put_asc16_size(695,115+170,3,3,"( )",BLACK24);
  puthz(719,126+170,"��",24,24,BLACK24);
  puthz(718,125+170,"��",24,24,BLACK24);

  puthz(223,113+340,"��·",48,48,BLACK24);
  puthz(222,112+340,"��·",48,48,BLACK24);
  puthz(431,126+340,"ͭ��ɽׯ",24,24,BLACK24);
  puthz(430,125+340,"ͭ��ɽׯ",24,24,BLACK24);
  put_asc16_size(535,115+340,3,3,"-->",BLACK24);
  puthz(603,126+340,"���Ҵ���",24,24,BLACK24);
  puthz(602,125+340,"���Ҵ���",24,24,BLACK24);
  put_asc16_size(695,115+340,3,3,"( )",BLACK24);
  puthz(719,126+340,"ȫ",24,24,BLACK24);
  puthz(718,125+340,"ȫ",24,24,BLACK24);

  puthz(223,113+510,"��·",48,48,BLACK24);
  puthz(222,112+510,"��·",48,48,BLACK24);
  puthz(431,126+510,"ͭ��ɽׯ",24,24,BLACK24);
  puthz(430,125+510,"ͭ��ɽׯ",24,24,BLACK24);
  put_asc16_size(535,115+510,3,3,"-->",BLACK24);
  puthz(603,126+510,"���Ҵ���",24,24,BLACK24);
  puthz(602,125+510,"���Ҵ���",24,24,BLACK24);
  put_asc16_size(695,115+170*3,3,3,"( )",BLACK24);
  puthz(719,126+170*3,"��",24,24,BLACK24);
  puthz(718,125+170*3,"��",24,24,BLACK24);
  Bar1(435,708,589,768,DARKGRAY24);
  Bar1(437,710,587,766,LIGHTGRAY24);
  puthz(441,716,"��һҳ",48,48,BLACK24);
  puthz(440,715,"��һҳ",48,48,BLACK24);
}


void AddBox1()
{
  Bar1(0,560,1024,705,LIGHTGRAY24);
  Bar1(782,708,902,768,LIGHTGRAY24);
  Bar1(0,560,1024,705,LIGHTGRAY24);
  Bar1(208,598,462,662,BLACK24);
  Bar1(212,602,458,658,LIGHTGRAY24);
  puthz(215,605,"������վ",48,48,BLACK24);
  put_asc16_size(478,610,3,3,"-->",BLACK24);
  Bar1(562,598,816,662,BLACK24);
  Bar1(566,602,812,658,LIGHTGRAY24);
  puthz(569,605,"����յ�վ",48,48,BLACK24);
  Bar1(904,708,1024,768,DARKGRAY24);
  Bar1(906,710,1022,766,LIGHTGRAY24);
  puthz(918,716,"����",48,48,BLACK24);
  returnbut();
}


void StationName(int Sflag,int Station)
{
  staname station[28]= {
    {1,"���Ҵ���"},
    {2,"������"},
    {3,"����һƷ"},
    {4,"�����"},
    {5,"���㳡"},
    {6,"����ҽԺ"},
    {7,"�����"},
    {8,"����"},
    {9,"�ź���"},
    {10,"���԰"},
    {11,"���Ļ�԰"},
    {12,"���ױ���Ժ"},
    {13,"����ɽׯ"},
    {14,"����ɽׯ"},
    {15,"������԰"},
    {16,"Ф��"},
    {17,"���ݹ���"},
    {18,"����С��"},
    {19,"����ɽ"},
    {20,"����"},
    {21,"������"},
    {22,"��ά�Ƕ�"},
    {23,"ͭ��ɽׯ"},
    {24,"�����"},
    {25,"�����"},
    {26,"������԰"},
    {27,"�����"},
    {28,"Ԭ��"}
  };
  
  if(Sflag==1) { //���վ
    Bar1(208,598,462,662,BLACK24);
    Bar1(212,602,458,658,LIGHTGRAY24);
    puthz(217,606,station[Station-1].stationname,48,48,BLACK24);
  } else if(Sflag==2) { //�յ�վ
    Bar1(562,598,816,662,BLACK24);
    Bar1(566,602,812,658,LIGHTGRAY24);
    puthz(571,606,station[Station-1].stationname,48,48,BLACK24);
  }
}

void AddBox2()
{
  Bar1(0,560,1024,705,LIGHTGRAY24);
  Bar1(782,708,902,768,LIGHTGRAY24);
  puthz(369,566,"¼���ϳ�ʱ��",48,48,BLACK24);
  puthz(368,565,"¼���ϳ�ʱ��",48,48,NAVY24);
  Bar1(145,642,275,692,WHITE24);
  bar3(145,642,275,692,BLACK24);
  puthz(280,643,"��",48,48,BLACK24);
  Bar1(333,642,433,692,WHITE24);
  bar3(333,642,433,692,BLACK24);
  puthz(438,643,"��",48,48,BLACK24);
  Bar1(491,642,591,692,WHITE24);
  bar3(491,642,591,692,BLACK24);
  puthz(596,643,"��",48,48,BLACK24);
  Bar1(649,642,810,692,WHITE24);
  bar3(649,642,810,692,BLACK24);
  puthz(815,643,"����",48,48,BLACK24);
}
void YNbut(int cho)
{
  if(cho==1) {
  	Bar1(639,589,689,639,LIGHTGRAY24);
    bar3(639,589,689,639,WHITE24);
    puthz(640,590,"��",48,48,BLACK24);
    Bar1(692,589,742,639,LIGHTGRAY24);
    bar3(692,589,742,639,WHITE24);
    puthz(693,590,"��",48,48,BLACK24);
  } else if(cho==2) {
    Bar(639,589,689,639,DARKGRAY24);
    puthz(640,590,"��",48,48,RED24);
    Bar1(692,589,742,639,LIGHTGRAY24);
    bar3(692,589,742,639,WHITE24);
    puthz(693,590,"��",48,48,BLACK24);
  } else if(cho==3) {
  	Bar1(639,589,689,639,LIGHTGRAY24);
  	bar3(639,589,689,639,WHITE24);
    puthz(640,590,"��",48,48,BLACK24);
    Bar(692,589,742,639,DARKGRAY24);
    puthz(693,590,"��",48,48,GREEN24);
  } else if(cho==4) {
  	Bar1(739,649,789,699,LIGHTGRAY24);
    bar3(739,649,789,699,WHITE24);
    puthz(740,650,"��",48,48,BLACK24);
  } else if(cho==5) {
    Bar(739,649,789,699,DARKGRAY24);
    puthz(740,650,"��",48,48,RED24);
  }  
}
void AddBox3()
{
  Bar1(0,560,1024,705,LIGHTGRAY24);
  puthz(100,590,"��ʮ�����Ƿ��з���֢״",48,48,BLACK24);
  YNbut(1);
  puthz(100,650,"�˳������Ƿ�ȷ��Ϊ�¹ڻ���",48,48,BLACK24);
  YNbut(4); 
  Bar1(782,708,902,768,DARKGRAY24);
  Bar1(784,710,900,766,LIGHTGRAY24);
  puthz(795,716,"ȷ��",48,48,BLACK24);
  puthz(794,715,"ȷ��",48,48,BLACK24);
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
	if(c==1) {//���Ӹ����û���¼��ʱ�� 
		strcpy(time,year);
        strcat(time,".");
        strcat(time,month);
        strcat(time,".");
        strcat(time,day);
	} else if(c==2) {//�γɳ��ζ�λ 
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
	}
}
void AddHis(char *account, int line, UserInfo *user,int page)   //page==1����page==2����
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
  puthz(364,721,"��һҳ",32,32,BLACK24);
  puthz(564,721,"��һҳ",32,32,BLACK24);
  Mouse_Init();
  while(1) {
    MouseShow(&mouse);
    if(MousePress(532,716,692,758)) {
      if(Dflag==1) {
        MouseOff(&mouse);
        AddBox2();//���ʱ��
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
		  Connect(year,month,day,time,route_name,bnum,1,btime,page,line);//����ʱ�� 
		  Connect(year,month,day,time,route_name,bnum,2,btime,page,line);//���ɳ��� ����+���� 
          AddBox3();//���ע��
          if(temp.note==1){
          	YNbut(2);
		  } else if(temp.note==0){
		  	YNbut(3);
		  }
          Dflag++;
          delay(100);
        } else if(JudgeTime(year,month,day,yi,mi,di)==ERROR_CODE) {
          InputError(line,start,end,1); 
        }
        MouseOn(mouse);
      }
    } else if(MousePress(332,716,492,758)) {
      if(Dflag==3) {
        AddBox2();
        put_asc16_size(149,641,2,2,year,BLACK24);
        put_asc16_size(337,641,2,2,month,BLACK24);
        put_asc16_size(494,641,2,2,day,BLACK24);
        put_asc16_size(653,64,2,2,bnum,BLACK24);
        Dflag--;
        delay(100);
      } else if(Dflag==2) {
        AddBox1();
        Dflag--;
        delay(100);
      }
    } else if(MousePress(212,602,458,658) && Dflag==1 && start==0) {
      MouseOff(&mouse);
      start=ClickStation(335,658);
      Bar1(212,663,458,713,LIGHTGRAY24);

      if(start!=0) {
      	StationName(1,start);
	  }

      if(start!=0&&end!=0) {
        DisplayTraces(line,start,end);
      }
      MouseOn(mouse);
    } else if(MousePress(566,602,812,658) && Dflag==1 && end==0) {
      MouseOff(&mouse);
      end=ClickStation(689,658);
      Bar1(566,663,812,713,LIGHTGRAY24);
      
      if(end!=0) {
      	StationName(2,end);
	  }

      if(start!=0&&end!=0) {
        DisplayTraces(line,start,end);
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
      //�������
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
void InputError(int line,int start,int end,int k)
{
  Bar1(362,400,662,550,LIGHTGRAY24);
  bar3(362,400,662,550,BLACK24);
  puthz(367,430,"��������",48,54,RED24);
  Bar1(462,495,562,545,CYAN24);
  bar3(462,495,562,545,BLACK24);
  puthz(464,496,"ȷ��",48,48,BLACK24);
  Mouse_Init();
  while(1) {
    MouseShow(&mouse);
    if(MousePress(462,495,562,545)) {
      MouseOff(&mouse);
      if(k==1) {
        DisplayLine(line);
        if(start!=0&&end!=0) {
          DisplayTraces(line,start,end);
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
  int line=0;//page=1���� page=2����
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
      //·�߲�ѯ����
      MouseOff(&mouse);
      SelectMap();
      MouseOn(mouse);
    } else if(MousePress(322,328,704,402)) {
      //�����ʷ��¼
      MouseOff(&mouse);
      AddFunc(&user);
      //AdFunc();
      MouseOn(mouse);
    } else if(MousePress(322,458,704,532)) {
      //��ʷ�г̼�¼��ѯ
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
