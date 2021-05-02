#ifndef __ADMINI_H_
#define __ADMINI_H_
#include "headers/status.h"
#include "headers/info.h"

typedef struct inputstations {
  int name;
  char stationname[50];
} staname;/*  */

void DrawPage(int page);
void PuOne(void);
void SPeople(int x, int y);
void ShUsers(char user[][16]);
void UserHis(UserInfo *user, int page);
void ByBusOne(void);
void AChoose(void);
void ShowTime(char *time, int x, int y);
void StaName(int num, int x, int y);
void ByBusTwo(Route *route, int page);
void ByBuxF(Route *route, int line);
void ByBusNum(void);
void UseHisF(UserInfo *user);
void ByUser(void);
void AdminiFunc(void);
void ByBusF(Route *route, int line);
#endif
