#ifndef _RECORD_H
#define _RECORD_H
#include "headers/info.h"
void RecordTrace(UserInfo *user, int page, int line, int c);

void RecordBox(int i);

void RecordFunc(UserInfo *user, int page, int line);

void HisBoxFunc(UserInfo *user);

void RelevantF(int page, int line, UserInfo *user);
#endif
