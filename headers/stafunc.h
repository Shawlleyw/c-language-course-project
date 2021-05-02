#ifndef _STAFUNC_H
#define _STAFUNC_H

int ClickStation(int x, int y);

void StakInfo(int x, int y, char *name);

int Stak(int line, int x, int y, int func, int note, int Sflag, int lim);

void StationName(int Sflag, int Station, char *name);

void ShowSta(int line);

void StakInput(int func, char *name, int station, int x, int y, int Sflag);
#endif
