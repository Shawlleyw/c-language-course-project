#ifndef _ADD_H
#define _ADD_H
#include "headers/info.h"
#include "headers/status.h"

void AddHis(char *account, int line, UserInfo *user, int page);

void AddFunc(UserInfo *user);

STATUS_CODE SelectMap(void);
#endif
/*  */