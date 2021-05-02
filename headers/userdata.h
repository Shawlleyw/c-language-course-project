#ifndef TRAFFIC_HEADERS_USERDATA_H_
#define TRAFFIC_HEADERS_USERDATA_H_
#include "headers/info.h"
#include "headers/status.h"
/*
function AddNewUser:
    传入参数: (用户账户, 用户名字)
    功能:
添加一个新用户，为其新建用户文件存于userinfo/目录下，并将此用户名字及账号汇总入userinfo/namelist文件中
    返回值：成功返回SUCCESS_CODE,失败返回ERROR_CODE
*/
STATUS_CODE AddNewUser(char *account, char *name);

/*
function UserNewTravel:
    传入参数: (用户账户, 一条历史记录, 用户信息结构体)
    功能:
为用户添加一条新的行程记录，记录存入cur中，用cur写入到pre_user结构体中并更新该用户信息文件
    返回值：成功返回SUCCESS_CODE,失败返回ERROR_CODE
*/
STATUS_CODE UserNewTravel(char *account, HisLi *cur, UserInfo *pre_user);

/*
function GetUserInfo:
    传入参数：(用户信息结构地址, 用户账号)
    功能：从用户文件中取得用户信息并存入*user结构体中
    返回值：成功返回SUCCESS_CODE,失败返回ERROR_CODE
*/
STATUS_CODE GetUserInfo(UserInfo *user, char *user_account);
#endif
