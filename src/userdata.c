#define _CRT_SECURE_NO_WARNINGS
#include "headers/info.h"
#include "headers/status.h"
#include "headers/svga.h"
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STATUS_CODE NewUser(char *name)  // USELESS!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
    UserInfo user;
    char path[64];
    FILE *fp = NULL;
    user.nhistory = 0;
    strcpy(path, "userinfo/");
    strcat(path, name);
    strcpy(user.name, name);
    memset(user.history_lines, 0, sizeof(user.history_lines));
    fp = fopen(path, "w");
    if (fp == NULL)
    {
        CloseSVGA();
        fprintf(stderr, "File Error: %s: %s\n", path, strerror(errno));
        exit(ERROR_CODE);
    }
    fwrite(&user, sizeof(UserInfo), 1, fp);
    return SUCCESS_CODE;
}

STATUS_CODE AddNewUser(char *account, char *name)
{
	UserInfo new_user;
	FILE *fp;
	char path[32];
	memset(&new_user, 0, sizeof(UserInfo));
	new_user.nhistory = 0;
	strcpy(path, "userinfo/");
	strcat(path, account);
	strcpy(new_user.name, name);
	strcpy(new_user.account, account);
	fp = fopen(path, "w+");
	if (fp == NULL)
	{
		CloseSVGA();
		fprintf(stderr, "File Error: %s: file does not exist\n", account);
		exit(ERROR_CODE);
	}
	fwrite(&new_user, sizeof(UserInfo), 1, fp);
	fclose(fp);
    fp = NULL;

	fp = fopen("userinfo/namelist.txt", "a+");
	if (fp == NULL)
	{
		CloseSVGA();
		fprintf(stderr, "File Error: %s: file does not exist\n", account);
		exit(ERROR_CODE);
	}
	fprintf(fp, "%s\n", name);
	fclose(fp);
    fp = NULL;
	return SUCCESS_CODE;
}

STATUS_CODE NewTravel(HisLi *cur, int line, int start, int end, char *time, int note){
    cur->line_no = line;
    cur->start = start;
    cur->end = end;
    cur->note = note;
    strcpy(cur->time, time);
}

STATUS_CODE UserNewTravel(char *account, HisLi *cur, UserInfo *pre_user)
{
    FILE *fp;
    UserInfo user;
    char path[32];
    int i;
    strcpy(path, "userinfo/");
	strcat(path, pre_user->account);
    fp = fopen(path, "rb");
    if (fp == NULL)
    {
        CloseSVGA();
        fprintf(stderr, "File Error: %s: %s\n", path, strerror(errno));
        getchar();
		exit(ERROR_CODE);
    }
    fread(&user, sizeof(UserInfo), 1, fp);
    if (user.nhistory == 16)
    {
        for (i = 0; i < 15; i++)
            user.history_lines[i] = user.history_lines[i + 1];
        user.history_lines[15] = *cur;
    }
    else
    {
        user.history_lines[user.nhistory] = *cur;
        user.nhistory++;
    }
    fclose(fp);
    fp = NULL;
    fp = fopen(path, "wb");
    fwrite(&user, sizeof(UserInfo), 1, fp);
    fclose(fp);
    fp = NULL;
    *pre_user = user;
    return SUCCESS_CODE;
}
