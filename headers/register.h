#ifndef TRAFFIC_HEADERS_REGISTER_H_
#define TRAFFIC_HEADERS_REGISTER_H_

#include "headers/status.h"
/*
function CheckEntryId:
    传入参数:（用户名， 用户密码）
    功能：登录时检验用户名是否存在以及密码是否正确
    返回值：成功返回SUCCESS_CODE,失败返回ERROR_CODE
*/
STATUS_CODE CheckEntryId(char *account, char *passwd);

/*
function CheckRegId:
    传入参数：（用户账户，用户名）
    功能：注册时检查用户账户及用户名是否和已存在用户重复
    返回值：成功返回SUCCESS_CODE,失败返回ERROR_CODE
*/
STATUS_CODE CheckRegId(char *account, char *name);

/*
function RegisterFunc:
    传入参数：无
    函数功能：登录总控制框架，加载图形界面，画出登录界面，提供退出接口按钮和注册接口按钮
    返回值：成功返回SUCCESS_CODE,失败返回ERROR_CODE
*/
STATUS_CODE RegisterFunc(char *user_account);

void RSign_in(void);
void Nopermis(void);
void RegFunc(void);

#endif
