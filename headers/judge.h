#ifndef _JUDGE_H
#define _JUDGE_H
#include "headers/status.h"
STATUS_CODE JudgeTime(char *year, char *month, char *day, int yi, int mi,int di);
void Connect(char *year, char *month, char *day, char *time, char *route_name,char *bnum, int c, char *btime, int page, int line);
void InputError(int line, int start, int end, int rev, int round, int k);
void ErrorTrace(void);
int UserExistedOnBus(char *busname, char *username);
void Errortime(void); 
#endif
