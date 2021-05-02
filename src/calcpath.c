#include "headers/calcpath.h"
#include <stdio.h>
#include <string.h>

char *CalcBusPath(char *path, char *route)
{
  strcpy(path, "data/bus/");
  strcat(path, route);
  return path;
}

char *CalcRoutePath(char *path, int line)
{
  int len;
  strcpy(path, "data/routes/route");
  len = strlen(path);
  path[len] = line + '0';
  path[len + 1] = '\0';
  strcat(path, ".out");
  return path;
}

char *CalcUserPath(char *path, char *account)
{
  strcpy(path, "userinfo/");
  strcat(path, account);
  return path;
}

char *CalcStationPath(char *path, int station)
{
  int len;
  strcpy(path, "data/stations/_");
  len = strlen(path);
  path[len] = station / 100 + '0';
  path[len + 1] = (station / 10) % 10 + '0';
  path[len + 2] = station % 10 + '0';
  path[len + 3] = '\0';
  return path;
}
