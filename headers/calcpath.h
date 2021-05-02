#ifndef TRAFFIC_HEADERS_CALCPATH_H_
#define TRAFFIC_HEADERS_CALCPATH_H_

char *CalcBusPath(char *path, char *route);

char *CalcRoutePath(char *path, int line);

char *CalcStationPath(char *path, int station);
/*  */
char *CalcUserPath(char *path, char *account);
#endif
