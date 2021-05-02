#ifndef TRAFFIC_HEADERS_RUN_H_
#define TRAFFIC_HEADERS_RUN_H_
#include "headers/status.h"
/*
function RunFunc:
    传入参数: 无
    功能: 登录后进入此函数，控制运行总框架
    返回值：成功返回SUCCESS_CODE,失败返回ERROR_CODE
*/
STATUS_CODE RunFunc();

/*
function GetUserInfo:
    传入参数：(用户信息结构地址, 用户账号)
    功能：从用户文件中取得用户信息并存入*user结构体中
    返回值：成功返回SUCCESS_CODE,失败返回ERROR_CODE
*/
STATUS_CODE GetUserInfo(UserInfo *user, char *user_account);

/*
function PrintUseName:
    传入参数：(用户名)
    功能：在DrawRunWindow函数中调用，在界面左上角显示出用户名
    返回值：成功返回SUCCESS_CODE,失败返回ERROR_CODE
*/
STATUS_CODE PrintUseName(char *user_name);

/*
function DrawRunWindow:
    传入参数: （用户信息结构体）
    功能：画出基本用户界面
    返回值：成功返回SUCCESS_CODE,失败返回ERROR_CODE
*/
STATUS_CODE DrawRunWindow(UserInfo *user);
STATUS_CODE DisplayLine(int line);

STATUS_CODE SelectMap();
/*
function AddFunc:
   
*/ 
void AddFunc(UserInfo *user);
void AddHis(char *account, int line, UserInfo *user,int page); 
void AddBox3(void);
void AddBox2(void);
int Stak(int line,int x,int y,int func,int note,int Sflag,int lim);
void ShowSta(int line);
void StationName(int Sflag,int Station,char *name);
void AddBox1(void);
void RSelectMaps(void);
void HisBoxFunc(UserInfo *user);
void Hisbox(int page,UserInfo *user);
void Relevant(Route *route,int rpage,UserInfo *user);
STATUS_CODE DrawMainPage();
STATUS_CODE DisplayLine(int line);
char *CalcMapName(char *path, int line);
int ClickStation(int x,int y);
void Comfirm(int x,int y);
void DisplayTraces(int line, int start, int end);
void ReadLineInfo(Lines *l, int line);
char* CalcStationPath(char *path, int station);
char* CalcRoutePath(char *path, int line);
STATUS_CODE GetUserInfo(UserInfo *user, char *user_account);
void Maps(void);
void NextPage(void);
void RelevantF(int page,int line,UserInfo *user);
STATUS_CODE JudgeTime(char *year,char *month,char *day,int yi,int mi,int di);
void InputError(int line,int start,int end,int k);
void RecordFunc(UserInfo *user,int page,int line);
void RecordTrace(UserInfo *user,int page,int line,int c);
void RPTrace(Route *route,int page,int line);
void RecordBox(int i); 
void YNbut(int cho);
void InfoName(int c,int i);
void InfoN(int c,int i);
void returnbut(void);
void Connect(char *year,char *month,char *day,char *time,char *route_name,char *bnum,int c,char *btime,int page,int line);
void StakInfo(int x,int y,char *name);
void StakInput(int func,char *name,int station,int x,int y,int Sflag);
#endif
