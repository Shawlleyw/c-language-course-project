#include "headers/draw.h"
#include "headers/add.h"
#include "headers/admini.h"
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
#include "headers/userdata.h"
#include <bios.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void JRight(int x, int y)
{
  Circlefill(x, y, 25, GREEN24);
  Circle(x, y, 25, BLACK24);
  Line_Thick(x - 12, y - 10, x, y + 14, 3, BLACK24);
  Line_Thick(x + 15, y - 16, x, y + 14, 3, BLACK24);
}

void JWrong(int x, int y)
{
  Circlefill(x, y, 25, RED24);
  Circle(x, y, 25, BLACK24);
  Line_Thick(x - 15, y - 15, x + 15, y + 15, 3, BLACK24);
  Line_Thick(x + 15, y - 15, x - 15, y + 15, 3, BLACK24);
}

void DrawBus()
{
  int i;

  Bar1(162, 70, 862, 320, 0x8b45);

  Bar1(172, 120, 302, 180, 0x07ff);
  Bar1(422, 120, 552, 180, 0x07ff);
  Bar1(672, 120, 802, 180, 0x07ff);

  bar3(162, 70, 862, 320, 0xffe0);
  bar3(160, 68, 864, 322, 0xffe0);
  Bar1(152, 260, 175, 285, 0x7800);
  Bar1(849, 260, 871, 285, 0x7800);
  Bar1(850, 115, 875, 135, 0x8b45);
  Bar1(875, 115, 900, 175, 0x8b45);
  Bar1(835, 72, 860, 200, 0x07ff);
  Line1(835, 72, 835, 200, 0xffff);
  Line1(835, 200, 860, 200, 0xffff);
  Line1(834, 72, 834, 201, 0xffff);
  Line1(834, 201, 860, 201, 0xffff);
  Line1(836, 73, 836, 199, 0xffff);
  Line1(836, 199, 860, 199, 0xffff);
  Circlefill(250, 320, 50, 0x0000);
  Circlefill(774, 320, 50, 0x0000);
  Circlefill(250, 320, 40, 0xc618);
  Circlefill(774, 320, 40, 0xc618);
  Circlefill(250, 320, 20, 0x7bef);
  Circlefill(774, 320, 20, 0x7bef);

  for (i = 0; i < 2; i++) {
    bar3(322 + i * 250, 110, 402 + i * 250, 290, 0xffe0);
    Circlefill(362 + i * 250, 150, 20, 0x07ff);
    Circle(362 + i * 250, 150, 20, 0xfde0);
    Circle(362 + i * 250, 150, 21, 0xfde0);
    Circle(362 + i * 250, 150, 19, 0xfde0);
  }
  for (i = 0; i < 3; i++) {
    bar3(172 + i * 250, 120, 302 + i * 250, 180, 0xffff);
    Line1(235 + i * 250, 120, 235 + i * 250, 180, 0xffff);
    Line1(234 + i * 250, 120, 234 + i * 250, 180, 0xffff);
    Line1(236 + i * 250, 120, 236 + i * 250, 180, 0xffff);
  }
}

void DrawEntryWindow()
{

  Bar1(0,0,1024,768,0x03ef);
  DrawBus();
  puthz(418,402,"欢迎使用",48,48,0x7bef);
  puthz(276,492,"公共交通乘客行程系统",48,48,0x7bef);
  puthz(416,400,"欢迎使用",48,48,0xffe0);
  puthz(274,490,"公共交通乘客行程系统",48,48,0xffe0);
  Bar1(98,638,352,722,0x7bef);
  Bar1(1024-352,638,1024-98,722,0x7bef);
  Bar1(102,642,348,718,0xc618);
  Bar1(676,642,922,718,0xc618);
  puthz(107,658,"管理员登录",48,48,0x0000);
  puthz(705,658,"用户登录",48,48,0x0000);
  puthz(105,656,"管理员登录",48,48,0xffff);
  puthz(703,656,"用户登录",48,48,0xffff);
  Bar1(971,3,1021,53,RED24);
  bar3(971,3,1021,53,WHITE24);
  bar3(970,2,1022,54,WHITE24);
  Line_Thick(971,3,1021,53,2,WHITE24);
  Line_Thick(971,53,1021,3,2,WHITE24);
}

void Sign_in()
{
  Bar1(0,0,1024,768,0x03ef);
  DrawBus();
  Bar1(0,400,1024,740,0x03ef);
  Bar1(200,420,824,480,0xffff);
  bar3(200,420,824,480,0x0000);
  Line1(330,420,330,480,0x0000);
  Line1(331,420,331,480,0x0000);
  Line1(329,420,329,480,0x0000);
  Bar1(200,520,824,580,0xffff);
  bar3(200,520,824,580,0x0000);
  Line1(330,520,330,580,0x0000);
  Line1(331,520,331,580,0x0000);
  Line1(329,520,329,580,0x0000);
  puthz(230,436,"账号",32,48,0x7bef);
  puthz(229,435,"账号",32,48,0x0000);
  puthz(230,536,"密码",32,48,0x7bef);
  puthz(229,535,"密码",32,48,0x0000);
  Bar1(212,642,362,702,0x7bef);
  Bar1(210,640,360,700,0x001f);
  Bar1(662,642,812,702,0x7bef);
  Bar1(660,640,810,700,0xc618);
  Bar1(437,642,582,702,0x7bef);
  Bar1(435,640,580,700,0xf800);
  puthz(238,647,"注册",48,48,0x0000);
  puthz(237,646,"注册",48,48,0xffff);
  puthz(688,647,"退出",48,48,0x0000);
  puthz(687,646,"退出",48,48,0x7800);
  puthz(463,647,"登录",48,48,0x0000);
  puthz(462,646,"登录",48,48,0xffff);
}

void AdSign()
{
  Bar1(0,0,1024,768,0x03ef);
  DrawBus();
  Bar1(0,400,1024,740,0x03ef);
  Bar1(200,420,824,480,0xffff);
  bar3(200,420,824,480,0x0000);
  Line1(330,420,330,480,0x0000);
  Line1(331,420,331,480,0x0000);
  Line1(329,420,329,480,0x0000);
  Bar1(200,520,824,580,0xffff);
  bar3(200,520,824,580,0x0000);
  Line1(330,520,330,580,0x0000);
  Line1(331,520,331,580,0x0000);
  Line1(329,520,329,580,0x0000);
  puthz(230,436,"账号",32,48,0x7bef);
  puthz(229,435,"账号",32,48,0x0000);
  puthz(230,536,"密码",32,48,0x7bef);
  puthz(229,535,"密码",32,48,0x0000);
  Bar1(212,642,362,702,0x7bef);
  Bar1(210,640,360,700,0xf800);
  Bar1(662,642,812,702,0x7bef);
  Bar1(660,640,810,700,0xc618);
  puthz(238,647,"登录",48,48,0x0000);
  puthz(237,646,"登录",48,48,0xffff);
  puthz(688,647,"退出",48,48,0x0000);
  puthz(687,646,"退出",48,48,0x7800);
}

void NextPage()
{
  Bar1(375,708,649,768,DARKGRAY24);
  Bar1(377,710,647,766,LIGHTGRAY24);
  puthz(385,723,"点击录入反向路线",32,32,BLACK24);
  puthz(384,722,"点击录入反向路线",32,32,BLACK24);
}

void Maps()
{
  int i;
  Bar1(0, 0, 1024, 768, DARKCYAN24);
  returnbut();
  for (i = 0; i < 4; i++) {
    Bar1(218, 96 + i * 170, 806, 174 + i * 170, DARKGRAY24);
    Bar1(222, 100 + i * 170, 802, 170 + i * 170, LIGHTGRAY24);
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
}

void Comfirm(int x, int y)
{
  Circlefill(x - 40, y + 30, 20, GREEN24);
  Circlefill(x + 40, y + 30, 20, RED24);
  Circle(x - 40, y + 30, 20, BLACK24);
  Circle(x + 40, y + 30, 20, BLACK24);
  Line_Thick(x - 52, y + 34, x - 40, y + 45, 2, WHITE24);
  Line_Thick(x - 40, y + 45, x - 30, y + 22, 2, WHITE24);
  Line_Thick(x + 32, y + 22, x + 48, y + 38, 2, WHITE24);
  Line_Thick(x + 32, y + 38, x + 48, y + 22, 2, WHITE24);
}

STATUS_CODE DrawMainPage()
{
  int i;
  Bar1(0, 0, 1024, 768, DARKCYAN24);
  for (i = 0; i < 3; i++) {
    Bar1(320, 198 + i * 130, 704, 272 + i * 130, DARKGRAY24);
    Bar1(322, 200 + i * 130, 702, 270 + i * 130, LIGHTGRAY24);
  }
  puthz(391,212,"路线查询",48,64,BLACK24);
  puthz(390,211,"路线查询",48,64,BLACK24);
  puthz(371,212+130,"添加行程记录",48,50,BLACK24);
  puthz(370,211+130,"添加行程记录",48,50,BLACK24);
  puthz(371,212+260,"查看历史记录",48,50,BLACK24);
  puthz(370,211+260,"查看历史记录",48,50,BLACK24);
  returnbut();
  return SUCCESS_CODE;
}

void InfoN(int c, int i)
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

void InfoName(int c, int i)
{
  if (c == 0) {
    InfoN(1, i);
  } else if (c == 1) {
    Bar1(130, 140 + i * 120, 894, 250 + i * 120, LIGHTRED24);
    bar3(130, 140 + i * 120, 894, 250 + i * 120, BLACK24);
    InfoN(1, i);
  } else if (c == 2) {
    InfoN(2, i);
  } else if (c == 3) {
    Bar1(130, 140 + i * 120, 894, 250 + i * 120, LIGHTRED24);
    bar3(130, 140 + i * 120, 894, 250 + i * 120, BLACK24);
    InfoN(2, i);
  } else if (c == 4) {
    Bar1(130, 140 + i * 120, 894, 250 + i * 120, RED24);
    bar3(130, 140 + i * 120, 894, 250 + i * 120, BLACK24);
    InfoN(2, i);
  } else if (c == 5) {
    Bar1(130, 140 + i * 120, 894, 250 + i * 120, RED24);
    bar3(130, 140 + i * 120, 894, 250 + i * 120, BLACK24);
    InfoN(1, i);
  }
}

void returnbut()
{
  Bar1(904,708,1024,768,DARKGRAY24);
  Bar1(906,710,1022,766,LIGHTGRAY24);
  puthz(918,716,"返回",48,48,BLACK24);
  puthz(917,715,"返回",48,48,BLACK24);
}

void RSelectMaps()
{
  int i;
  Bar1(0, 0, 1024, 768, DARKCYAN24);
  returnbut();
  for (i = 0; i < 4; i++) {
    Bar1(218, 96 + i * 170, 806, 174 + i * 170, DARKGRAY24);
    Bar1(222, 100 + i * 170, 802, 170 + i * 170, LIGHTGRAY24);
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
  Bar1(375,708,649,768,DARKGRAY24);
  Bar1(377,710,647,766,LIGHTGRAY24);
  puthz(385,723,"点击录入正向路线",32,32,BLACK24);
  puthz(384,722,"点击录入正向路线",32,32,BLACK24);
}

void AddBox1()
{
  Bar1(135,560,1024,705,LIGHTGRAY24);
  //Bar1(782,708,902,768,LIGHTGRAY24);
  //Bar1(0,560,1024,705,LIGHTGRAY24);
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

void AddBox2()
{
  Bar1(135,560,1024,705,LIGHTGRAY24);
  Bar1(782,708,902,768,LIGHTGRAY24);
  Bar1(135,705,150,768,LIGHTGRAY24);
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

void AddBox3()
{
  Bar1(135,560,1024,705,LIGHTGRAY24);
  puthz(120,590,"近十四天是否有发热症状",48,48,BLACK24);
  YNbut(1);
  puthz(120,650,"乘车至今是否确诊为新冠患者",48,48,BLACK24);
  YNbut(4);
  Bar1(782,708,902,768,DARKGRAY24);
  Bar1(784,710,900,766,LIGHTGRAY24);
  puthz(795,716,"确认",48,48,BLACK24);
  puthz(794,715,"确认",48,48,BLACK24);
}

void YNbut(int cho)
{
  if(cho==1) {
    Bar1(659,589,709,639,LIGHTGRAY24);
    bar3(659,589,709,639,WHITE24);
    puthz(660,590,"是",48,48,BLACK24);
    Bar1(712,589,762,639,LIGHTGRAY24);
    bar3(712,589,762,639,WHITE24);
    puthz(713,590,"否",48,48,BLACK24);
  } else if(cho==2) {
    Bar1(659,589,709,639,DARKGRAY24);
    puthz(660,590,"是",48,48,RED24);
    Bar1(712,589,762,639,LIGHTGRAY24);
    bar3(712,589,762,639,WHITE24);
    puthz(713,590,"否",48,48,BLACK24);
  } else if(cho==3) {
    Bar1(659,589,709,639,LIGHTGRAY24);
    bar3(659,589,709,639,WHITE24);
    puthz(660,590,"是",48,48,BLACK24);
    Bar1(712,589,762,639,DARKGRAY24);
    puthz(713,590,"否",48,48,GREEN24);
  } else if(cho==4) {
    Bar1(759,649,809,699,LIGHTGRAY24);
    bar3(759,649,809,699,WHITE24);
    puthz(760,650,"是",48,48,BLACK24);
  } else if(cho==5) {
    Bar1(759,649,809,699,DARKGRAY24);
    puthz(760,650,"是",48,48,RED24);
  }
}

void DrawPage(int page)
{
  Bar1(484, 620, 570, 670, DARKCYAN24);
  if (page == 1) {
    put_asc16_size(485, 115 + 510, 2, 2, "1/4", BLACK24);
  } else if (page == 2) {
    put_asc16_size(485, 115 + 510, 2, 2, "2/4", BLACK24);
  } else if (page == 3) {
    put_asc16_size(485, 115 + 510, 2, 2, "3/4", BLACK24);
  } else if (page == 4) {
    put_asc16_size(485, 115 + 510, 2, 2, "4/4", BLACK24);
  }
}

void PuOne()
{
  Bar1(0, 0, 1024, 768, CYAN24);
  Bar1(110, 120, 914, 670, DARKCYAN24);
  Bar1(352, 621, 452, 661, DARKGRAY24);
  Bar1(574, 621, 674, 661, DARKGRAY24);
  Bar1(350, 619, 450, 659, LIGHTGRAY24);
  Bar1(572, 619, 674, 659, LIGHTGRAY24);
  puthz(352, 623, "上一页", 32, 32, WHITE24);
  puthz(574, 623, "下一页", 32, 32, WHITE24);
  Bar1(904, 708, 1024, 768, DARKGRAY24);
  Bar1(906, 710, 1022, 766, LIGHTGRAY24);
  puthz(918, 716, "返回", 48, 48, BLACK24);
  puthz(917, 715, "返回", 48, 48, BLACK24);
}
