#include "headers/info.h"
#include "headers/userdata.h"
#include "headers/status.h"
#include "headers/hz.h"
#include "headers/mouse.h"
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <bios.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>

void JRight(int x,int y)
{
  Circlefill(x,y,25,GREEN24);
  Circle(x,y,25,BLACK24);
  Line_Thick(x-12,y-10,x,y+14,3,BLACK24);
  Line_Thick(x+15,y-16,x,y+14,3,BLACK24);
}
void JWrong(int x,int y)
{
  Circlefill(x,y,25,RED24);
  Circle(x,y,25,BLACK24);
  Line_Thick(x-15,y-15,x+15,y+15,3,BLACK24);
  Line_Thick(x+15,y-15,x-15,y+15,3,BLACK24);
}
STATUS_CODE CheckEntryPwd(int uid, char *passwd, FILE *passwd_fp)
{
  int user_cnt;
  int len;
  char s_passwd[32];
  char *s_ptr;
  user_cnt = 0;
  while ((s_ptr = fgets(s_passwd, 32, passwd_fp)) != NULL) {
    user_cnt++;
    if (user_cnt != uid)
      continue;
    len = strlen(s_passwd);
    s_passwd[len-1] = '\0';
    if (strcmp(s_ptr, passwd))
      return ERROR_CODE;
    else {
      JRight(880,550);
      return SUCCESS_CODE;
    }
  }
  return ERROR_CODE;
}

STATUS_CODE CheckEntryAccount(char *account, FILE *account_fp, int *uid)
{
  char s_account[32];
  char *s_ptr;
  int user_cnt;
  int len;
  user_cnt = 0;
  while ((s_ptr = fgets(s_account, 32, account_fp)) != NULL) {
    user_cnt++;
    len = strlen(s_account);
    s_account[len-1] = '\0';
    if (strcmp(account, s_ptr))
      continue;
    *uid = user_cnt;
    JRight(880,450);
    return SUCCESS_CODE;
  }
  return ERROR_CODE;
}

STATUS_CODE CheckEntryId(char *account, char *passwd)
{
  FILE *account_fp, *passwd_fp;
  UserInfo user;
  STATUS_CODE flag;
  int i, j, uid;
  account_fp = fopen("userinfo/account.txt", "r");
  if (account_fp == NULL) {
    closegraph();
    fprintf(stderr, "File Error: account.txt does not exist\n");
    exit(ERROR_CODE);
  }

  flag = CheckEntryAccount(account, account_fp, &uid);
  if (flag == ERROR_CODE) {
    JWrong(880,450);
    return ERROR_CODE;
  }
  fclose(account_fp);
  account_fp = NULL;

  passwd_fp = fopen("userinfo/password.txt", "r");
  if (passwd_fp == NULL) {
    closegraph();
    fprintf(stderr, "File Error: %s: file does not exist\n", "userinfo/passwd.txt");
    exit(ERROR_CODE);
  }
  flag = CheckEntryPwd(uid, passwd, passwd_fp); // how to quickly match?
  if (flag == ERROR_CODE) {
    JWrong(880,550);
    return ERROR_CODE;
  }
  fclose(passwd_fp);
  passwd_fp = NULL;
  return SUCCESS_CODE;
}



STATUS_CODE CheckRegAccount(char *account)
{
  FILE *fp;
  char path[64];
  strcpy(path, "userinfo/");
  strcat(path, account);
  fp = fopen(path, "r");
  if (fp == NULL) {
    JRight(880,500);
    return SUCCESS_CODE;
  } else {
    fclose(fp);
    fp = NULL;
    JWrong(880,200);
    return ERROR_CODE;
  }
}

STATUS_CODE CheckRegName(char *name)
{
  FILE *fp;
  char user_name[32];
  char *s_ptr;
  fp = fopen("userinfo/namelist.txt", "r");
  if (fp == NULL) {
    return SUCCESS_CODE;
  }
  while ((s_ptr = fgets(user_name, 32, fp)) != NULL) {
    if (!strcmp(name, s_ptr)) {
      fclose(fp);
      fp = NULL;
      JWrong(880,500);
      return ERROR_CODE;
    }
  }
  fclose(fp);
  fp = NULL;
  return SUCCESS_CODE;
}

STATUS_CODE CheckRegId(char *account, char *name)
{
  STATUS_CODE flag;
  flag = CheckRegAccount(account);
  if (flag == ERROR_CODE) {
    return ERROR_CODE;
  }
  flag = CheckRegName(name);
  if (flag == ERROR_CODE) {
    return ERROR_CODE;
  }
  return SUCCESS_CODE;
}


void RegFunc()
{
  int i,ai,p1i,p2i,ni;
  char account_1[32];
  char passwd_1[32];
  char name_1[32];
  char account[10];
  char password1[16];
  char password2[16];
  char name[20];
  int flag_passwd = -1;
  int flag_account = 0;
  FILE *fp;
  account[0] = '\0';
  password1[0] = '\0';
  password2[0] = '\0';
  name[0] = '\0';
  Bar1(0,0,1024,768,0x03ef);
  /*	setfillstyle(1,BLUE);
  	pieslice(320,60,0,360,35);
  	setcolor(BLUE);
  	line(320,60,354,60);
  	setfillstyle(1, WHITE);
  	sector(320, 60, 230, 310, 35, 35);
  	fillellipse(320, 60 - 5, 15, 15);
  	setcolor(WHITE);
  	circle(320, 60 - 5, 15);	//锟斤拷锟斤拷录小锟斤拷
  	setlinestyle(0,0,3);
  	circle(320,60,35);
  	setcolor(DARKGRAY);
  	setlinestyle(0,0,3);
  	setfillstyle(1,DARKGRAY);*/
  Bar1(202,172,826,232,0x7bef);
  Bar1(202,272,826,332,0x7bef);
  Bar1(202,372,826,432,0x7bef);
  Bar1(202,472,826,532,0x7bef);

  Bar1(232,612,382,672,0x7bef);
  Bar1(230,610,380,670,0x001f);
  Bar1(642,612,792,672,0x7bef);
  Bar1(640,610,790,670,0xc618);

  Bar1(200,170,824,230,0xffff);
  Bar1(200,270,824,330,0xffff);
  Bar1(200,370,824,430,0xffff);
  Bar1(200,470,824,530,0xffff);

  bar3(200,170,824,230,0x0000);
  bar3(200,270,824,330,0x0000);
  bar3(200,370,824,430,0x0000);
  bar3(200,470,824,530,0x0000);

  for(i=0; i<4; i++) {
    Line1(349,170+i*100,349,230+i*100,0x0000);
    Line1(350,170+i*100,350,230+i*100,0x0000);
    Line1(351,170+i*100,351,230+i*100,0x0000);
  }

  puthz(238,187,"账号",32,48,0x7bef);
  puthz(237,186,"账号",32,48,0x0000);
  puthz(238,287,"密码",32,48,0x7bef);
  puthz(237,286,"密码",32,48,0x0000);
  puthz(212,385,"确认密码",32,32,0x7bef);
  puthz(211,384,"确认密码",32,32,0x0000);
  puthz(214,487,"用户名",32,48,0x7bef);
  puthz(213,486,"用户名",32,48,0x0000);
  puthz(258,617,"注册",48,48,0x0000);
  puthz(257,616,"注册",48,48,0xffff);
  puthz(668,617,"退出",48,48,0x0000);
  puthz(667,616,"退出",48,48,0x7800);
  Mouse_Init();
  while(1) {
    MouseShow(&mouse);
    if(MousePress(350,170,824,230)) {
      delay(100);
      MouseOff(&mouse);
      ai=strlen(account);
      Getinfo(353,180,account,16,ai);
    } else if(MousePress(350,270,824,330)) {
      delay(100);
      MouseOff(&mouse);
      p1i=strlen(password1);
      Getcode(353,280,password1,16,p1i);
    } else if(MousePress(350,370,824,430)) {
      delay(100);
      MouseOff(&mouse);
      p2i=strlen(password2);
      Getcode(353,380,password2,16,p2i);
    } else if(MousePress(350,470,824,530)) {
      delay(100);
      MouseOff(&mouse);
      ni=strlen(name);
      Getinfo(353,480,name,16,ni);
    } else if(MousePress(230,610,380,670)) {
      MouseOff(&mouse);
      if(CheckRegId(account, name)==SUCCESS_CODE) {
        JRight(880,200);
        strcpy(account_1, account);
        strcpy(name_1, name);
        if(strcmp(password1,password2)==0) {
          JRight(880,300);
          JRight(880,400);
          passwd_1[0]='\0';
          strcpy(passwd_1, password1);
          AddNewUser(account_1, name_1);
          fp = fopen("userinfo/account.txt", "a+");
          fprintf(fp, "%s\n", account_1);
          fclose(fp);
          fp = NULL;
          fp = fopen("userinfo/password.txt", "a+");
          fprintf(fp, "%s\n", passwd_1);
          fclose(fp);
          fp = NULL;
          break;
        } else if(strcmp(password1,password2)!=0) {
          JWrong(880,400);
        }
        delay(200);
        //储存信息并返回登录界面
      }

    } else if(MousePress(640,610,790,670)) {
      MouseOff(&mouse);
      delay(100);
      //返回登录界面
      break;
    }
  }
}

void DrawEntryWindow()
{
  int i;

  Bar1(0,0,1024,768,0x03ef);
  Bar1(162,70,862,320,0x8b45);

  Bar1(172,120,302,180,0x07ff);
  Bar1(422,120,552,180,0x07ff);
  Bar1(672,120,802,180,0x07ff);

  bar3(162,70,862,320,0xffe0);
  bar3(160,68,864,322,0xffe0);
  Bar1(152,260,175,285,0x7800);
  Bar1(849,260,871,285,0x7800);
  Bar1(850,115,875,135,0x8b45);
  Bar1(875,115,900,175,0x8b45);
  Bar1(835,72,860,200,0x07ff);
  Line1(835,72,835,200,0xffff);
  Line1(835,200,860,200,0xffff);
  Line1(834,72,834,201,0xffff);
  Line1(834,201,860,201,0xffff);
  Line1(836,73,836,199,0xffff);
  Line1(836,199,860,199,0xffff);
  Circlefill(250,320,50,0x0000);
  Circlefill(774,320,50,0x0000);
  Circlefill(250,320,40,0xc618);
  Circlefill(774,320,40,0xc618);
  Circlefill(250,320,20,0x7bef);
  Circlefill(774,320,20,0x7bef);

  for(i=0; i<2; i++) {
    bar3(322+i*250,110,402+i*250,290,0xffe0);
    Circlefill(362+i*250,150,20,0x07ff);
    Circle(362+i*250,150,20,0xfde0);
    Circle(362+i*250,150,21,0xfde0);
    Circle(362+i*250,150,19,0xfde0);
  }
  for(i=0; i<3; i++) {
    bar3(172+i*250,120,302+i*250,180,0xffff);
    Line1(235+i*250,120,235+i*250,180,0xffff);
    Line1(234+i*250,120,234+i*250,180,0xffff);
    Line1(236+i*250,120,236+i*250,180,0xffff);
  }
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

  char account[32],password[32],user_account[32];
  int i;

  Bar1(0,0,1024,768,0x03ef);
  Bar1(162,70,862,320,0x8b45);

  Bar1(172,120,302,180,0x07ff);
  Bar1(422,120,552,180,0x07ff);
  Bar1(672,120,802,180,0x07ff);

  bar3(162,70,862,320,0xffe0);
  bar3(160,68,864,322,0xffe0);
  Bar1(152,260,175,285,0x7800);
  Bar1(849,260,871,285,0x7800);
  Bar1(850,115,875,135,0x8b45);
  Bar1(875,115,900,175,0x8b45);
  Bar1(835,72,860,200,0x07ff);
  Line1(835,72,835,200,0xffff);
  Line1(835,200,860,200,0xffff);
  Line1(834,72,834,201,0xffff);
  Line1(834,201,860,201,0xffff);
  Line1(836,73,836,199,0xffff);
  Line1(836,199,860,199,0xffff);
  Circlefill(250,320,50,0x0000);
  Circlefill(774,320,50,0x0000);
  Circlefill(250,320,40,0xc618);
  Circlefill(774,320,40,0xc618);
  Circlefill(250,320,20,0x7bef);
  Circlefill(774,320,20,0x7bef);

  for(i=0; i<2; i++) {
    bar3(322+i*250,110,402+i*250,290,0xffe0);
    Circlefill(362+i*250,150,20,0x07ff);
    Circle(362+i*250,150,20,0xfde0);
    Circle(362+i*250,150,21,0xfde0);
    Circle(362+i*250,150,19,0xfde0);
  }
  for(i=0; i<3; i++) {
    bar3(172+i*250,120,302+i*250,180,0xffff);
    Line1(235+i*250,120,235+i*250,180,0xffff);
    Line1(234+i*250,120,234+i*250,180,0xffff);
    Line1(236+i*250,120,236+i*250,180,0xffff);
  }
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

STATUS_CODE RegisterFunc(char *user_account)
{
  int flagc=0,ai,pi;
  char account[32], password[32];
  account[0] = '\0';
  password[0] = '\0';
  DrawEntryWindow();
  // mouse operation
  Mouse_Init();
  while (1) {
    MouseShow(&mouse);
    if(MousePress(102,642,348,718)&&flagc==0) {
      MouseOff(&mouse);
      delay(50);
      Sign_in();//管理员
      flagc=1;
      delay(50);
      MouseOn(mouse);
    } else if(MousePress(676,642,922,718)&&flagc==0) {
      MouseOff(&mouse);
      delay(50);
      Sign_in();//乘客
      flagc=1;
      delay(50);
      MouseOn(mouse);
    } else if(MousePress(210,640,360,700)&&flagc==1) {
      MouseOff(&mouse);
      delay(50);
      RegFunc();
      account[0] = '\0';
      password[0] = '\0';
      delay(100);
      Sign_in();
      flagc=1;
      MouseOn(mouse);
    } else if(MousePress(435,640,580,700)&&flagc==1) {
      MouseOff(&mouse);
      delay(100);
      if (CheckEntryId(account, password) == SUCCESS_CODE) {
        strcpy(user_account, account);
        MouseOn(mouse);
        //ChoosePage();
        delay(100);
        break;
      }
    } else if(MousePress(660,640,810,700)&&flagc==1) {
      MouseOff(&mouse);
      delay(100);
      DrawEntryWindow();
      flagc=0;
      MouseOn(mouse);
    } else if(MousePress(350,520,824,580)&&flagc==1) {
      delay(100);
      MouseOff(&mouse);
      pi=strlen(password);
      Getcode(353,530,password,16,pi);
      MouseOn(mouse);
      //密码输入
    } else if(MousePress(350,420,824,480)&&flagc==1) {
      delay(100);
      MouseOff(&mouse);
      ai=strlen(account);
      Getinfo(353,430,account,16,ai);
      MouseOn(mouse);
      //账号输入
    } else if(MousePress(921,3,1021,103))
    {
       CloseSVGA();
       return EXIT_CODE;
	}
  }
  return SUCCESS_CODE;
}
