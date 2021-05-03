#include "headers/register.h"
#include "headers/add.h"
#include "headers/admini.h"
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
#include "headers/userdata.h"
#include <bios.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STATUS_CODE CheckEntryPwd(int uid, char *passwd, FILE *passwd_fp)
{
  int user_cnt;
  int len;
  char s_passwd[32];
  char *s_ptr;
  user_cnt = 0;
  while ((s_ptr = fgets(s_passwd, 32, passwd_fp)) != NULL)
  {
    user_cnt++;
    if (user_cnt != uid)
      continue;
    len = strlen(s_passwd);
    s_passwd[len - 1] = '\0';
    if (strcmp(s_ptr, passwd))
      return ERROR_CODE;
    else
    {
      JRight(880, 550);
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
  while ((s_ptr = fgets(s_account, 32, account_fp)) != NULL)
  {
    user_cnt++;
    len = strlen(s_account);
    s_account[len - 1] = '\0';
    if (strcmp(account, s_ptr))
      continue;
    *uid = user_cnt;
    JRight(880, 450);
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
  if (account_fp == NULL)
  {
    closegraph();
    fprintf(stderr, "File Error: account.txt does not exist\n");
    exit(ERROR_CODE);
  }

  flag = CheckEntryAccount(account, account_fp, &uid);
  if (flag == ERROR_CODE)
  {
    JWrong(880, 450);
    return ERROR_CODE;
  }
  fclose(account_fp);
  account_fp = NULL;

  passwd_fp = fopen("userinfo/password.txt", "r");
  if (passwd_fp == NULL)
  {
    closegraph();
    fprintf(stderr, "File Error: %s: file does not exist\n",
            "userinfo/passwd.txt");
    exit(ERROR_CODE);
  }
  flag = CheckEntryPwd(uid, passwd, passwd_fp); // how to quickly match?
  if (flag == ERROR_CODE)
  {
    JWrong(880, 550);
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
  if (fp == NULL)
  {
    JRight(880, 500);
    return SUCCESS_CODE;
  }
  else
  {
    fclose(fp);
    fp = NULL;
    JWrong(880, 200);
    return ERROR_CODE;
  }
}

STATUS_CODE CheckRegName(char *name)
{
  FILE *fp;
  char user_name[32];
  char *s_ptr;
  fp = fopen("userinfo/namelist.txt", "r");
  if (fp == NULL)
  {
    return SUCCESS_CODE;
  }
  while ((s_ptr = fgets(user_name, 32, fp)) != NULL)
  {
    if (!strcmp(name, s_ptr))
    {
      fclose(fp);
      fp = NULL;
      JWrong(880, 500);
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
  if (flag == ERROR_CODE)
  {
    return ERROR_CODE;
  }
  flag = CheckRegName(name);
  if (flag == ERROR_CODE)
  {
    return ERROR_CODE;
  }
  return SUCCESS_CODE;
}

void RegFunc()
{
  int i, ai, p1i, p2i, ni;
  char account_1[32];
  char passwd_1[32];
  char name_1[32];
  char account[10];
  char password1[16];
  char password2[16];
  char name[20];
  FILE *fp;
  account[0] = '\0';
  password1[0] = '\0';
  password2[0] = '\0';
  name[0] = '\0';
  Bar1(0, 0, 1024, 768, 0x03ef);
  Bar1(202, 172, 826, 232, 0x7bef);
  Bar1(202, 272, 826, 332, 0x7bef);
  Bar1(202, 372, 826, 432, 0x7bef);
  Bar1(202, 472, 826, 532, 0x7bef);

  Bar1(232, 612, 382, 672, 0x7bef);
  Bar1(230, 610, 380, 670, 0x001f);
  Bar1(642, 612, 792, 672, 0x7bef);
  Bar1(640, 610, 790, 670, 0xc618);

  Bar1(200, 170, 824, 230, 0xffff);
  Bar1(200, 270, 824, 330, 0xffff);
  Bar1(200, 370, 824, 430, 0xffff);
  Bar1(200, 470, 824, 530, 0xffff);

  bar3(200, 170, 824, 230, 0x0000);
  bar3(200, 270, 824, 330, 0x0000);
  bar3(200, 370, 824, 430, 0x0000);
  bar3(200, 470, 824, 530, 0x0000);

  for (i = 0; i < 4; i++)
  {
    Line1(349, 170 + i * 100, 349, 230 + i * 100, 0x0000);
    Line1(350, 170 + i * 100, 350, 230 + i * 100, 0x0000);
    Line1(351, 170 + i * 100, 351, 230 + i * 100, 0x0000);
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
  while (1)
  {
    MouseShow(&mouse);
    if (MousePress(350, 170, 824, 230))
    {
      delay(100);
      MouseOff(&mouse);
      ai = strlen(account);
      Getinfo(353, 180, account, 16, ai);
    }
    else if (MousePress(350, 270, 824, 330))
    {
      delay(100);
      MouseOff(&mouse);
      p1i = strlen(password1);
      Getcode(353, 280, password1, 16, p1i);
    }
    else if (MousePress(350, 370, 824, 430))
    {
      delay(100);
      MouseOff(&mouse);
      p2i = strlen(password2);
      Getcode(353, 380, password2, 16, p2i);
    }
    else if (MousePress(350, 470, 824, 530))
    {
      delay(100);
      MouseOff(&mouse);
      ni = strlen(name);
      Getinfo(353, 480, name, 4, ni);
    }
    else if (MousePress(230, 610, 380, 670))
    {
      MouseOff(&mouse);
      if (CheckRegId(account, name) == SUCCESS_CODE)
      {
        JRight(880, 200);
        strcpy(account_1, account);
        strcpy(name_1, name);
        if (strcmp(password1, password2) == 0)
        {
          JRight(880, 300);
          JRight(880, 400);
          passwd_1[0] = '\0';
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
        }
        else if (strcmp(password1, password2) != 0)
        {
          JWrong(880, 400);
        }
        delay(200);
      }
    }
    else if (MousePress(640, 610, 790, 670))
    {
      MouseOff(&mouse);
      delay(100);
      break;
    }
  }
}

void Nopermis()
{
  Bar1(362,400,662,550,LIGHTGRAY24);
  bar3(362,400,662,550,BLACK24);
  puthz(422,430,"无权限",48,60,RED24);
  Bar1(462,495,562,545,CYAN24);
  bar3(462,495,562,545,BLACK24);
  puthz(464,496,"确认",48,48,BLACK24);
  Mouse_Init();
  while (1)
  {
    MouseShow(&mouse);
    if (MousePress(462, 495, 562, 545))
    {
      MouseOff(&mouse);
      break;
    }
  }
}

void RSign_in()
{
  char ai, pi;
  char account[32], password[32];
  account[0] = '\0';
  password[0] = '\0';
  AdSign();
  Mouse_Init();
  while (1)
  {
    MouseShow(&mouse);
    if (MousePress(350, 520, 824, 580))
    {
      delay(100);
      MouseOff(&mouse);
      pi = strlen(password);
      Getcode(353, 530, password, 16, pi);
      MouseOn(mouse);
    }
    else if (MousePress(350, 420, 824, 480))
    {
      delay(100);
      MouseOff(&mouse);
      ai = strlen(account);
      Getinfo(353, 430, account, 16, ai);
      MouseOn(mouse);
    }
    else if (MousePress(660, 640, 810, 700))
    {
      MouseOff(&mouse);
      break;
    }
    else if (MousePress(210, 640, 360, 700))
    {
      MouseOff(&mouse);
      if (strcmp(account, "shhwsy") == 0 && strcmp(password, "shhwsy") == 0)
      {
        AdminiFunc();
        MouseOff(&mouse);
        AdSign();
        MouseOn(mouse);
        account[0] = '\0';
        password[0] = '\0';
      }
      else if (strcpy(account, "shhwsy") != 0 && (password, "shhwsy") != 0)
      {
        Nopermis();
        MouseOff(&mouse);
        AdSign();
        MouseOn(mouse);
        account[0] = '\0';
        password[0] = '\0';
      }
    }
  }
}

STATUS_CODE RegisterFunc(char *user_account)
{
  int flagc = 0, ai, pi;
  char account[32], password[32];
  account[0] = '\0';
  password[0] = '\0';
  DrawEntryWindow();
  // mouse operation
  Mouse_Init();
  while (1)
  {
    MouseShow(&mouse);
    if (MousePress(102, 642, 348, 718) && flagc == 0)
    {
      MouseOff(&mouse);
      delay(100);
      RSign_in(); 
      MouseOff(&mouse);
      DrawEntryWindow();
      flagc = 0; /////////////////////////////////////////
      delay(100);
      MouseOn(mouse);
    }
    else if (MousePress(676, 642, 922, 718) && flagc == 0)
    {
      MouseOff(&mouse);
      delay(100);
      Sign_in();
      flagc = 1;
      delay(100);
      MouseOn(mouse);
    }
    else if (MousePress(210, 640, 360, 700) && flagc == 1)
    {
      MouseOff(&mouse);
      delay(100);
      RegFunc();
      account[0] = '\0';
      password[0] = '\0';
      delay(100);
      Sign_in();
      flagc = 1;
      MouseOn(mouse);
    }
    else if (MousePress(435, 640, 580, 700) && flagc == 1)
    {
      MouseOff(&mouse);
      delay(100);
      if (CheckEntryId(account, password) == SUCCESS_CODE)
      {
        strcpy(user_account, account);
        MouseOn(mouse);
        delay(100);
        break;
      }
    }
    else if (MousePress(660, 640, 810, 700) && flagc == 1)
    {
      MouseOff(&mouse);
      delay(100);
      DrawEntryWindow();
      flagc = 0;
      MouseOn(mouse);
    }
    else if (MousePress(350, 520, 824, 580) && flagc == 1)
    {
      delay(100);
      MouseOff(&mouse);
      pi = strlen(password);
      Getcode(353, 530, password, 16, pi);
      MouseOn(mouse);
    }
    else if (MousePress(350, 420, 824, 480) && flagc == 1)
    {
      delay(100);
      MouseOff(&mouse);
      ai = strlen(account);
      Getinfo(353, 430, account, 16, ai);
      MouseOn(mouse);
    }
    else if (MousePress(921, 3, 1021, 103))
    {
      CloseSVGA();
      return EXIT_CODE;
    }
  }
  return SUCCESS_CODE;
}
