#ifndef TRAFFIC_HEADERS_RUN_H_
#define TRAFFIC_HEADERS_RUN_H_
#include "headers/status.h"
#include "headers/info.h"
/*
function RunFunc:
    传入参数: 无
    功能: 登录后进入此函数，控制运行总框架
    返回值：成功返回SUCCESS_CODE,失败返回ERROR_CODE
*/
STATUS_CODE RunFunc(char *user_account);

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

int CheckRound(char *name);

int CheckRev(char *name);

char *CalcRoutePath(char *path, int line);

char *CalcStationPath(char *path, int station);

void ReadLineInfo(Lines *l, int line);

void DrawStart(int start);

void DrawEnd(int end);

void ReverseRoute(Lines *l);

STATUS_CODE DrawTraces(Lines *l, int ids, int ide);

STATUS_CODE PaintStations(Lines *l, int ids, int ide);

STATUS_CODE DisplayTraces(int line, int start, int end, int rev, int round);

char *CalcMapName(char *path, int line);

#endif
