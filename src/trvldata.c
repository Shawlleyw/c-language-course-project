#include "headers/calcpath.h"
#include "headers/info.h"
#include "headers/status.h"
#include <stdio.h>
#include <string.h>

STATUS_CODE FetchRoute(Route *route, char *path, char *route_name,
                       int route_line)
{
  FILE *fp;
  fp = fopen(path, "rb");
  if (fp == NULL)
  {
    memset(route, 0, sizeof(Route));
    route->line = route_line;
    route->npassenger = 0;
    strcpy(route->route_name, route_name);
  }
  else
  {
    fread(route, sizeof(Route), 1, fp);
    fclose(fp);
    fp = NULL;
  }
  return SUCCESS_CODE;
}

STATUS_CODE FetchNewpass(Passenger *newpass, HisLi *passenger_info,
                         char *passenger_name)
{
  newpass->start = passenger_info->start;
  newpass->end = passenger_info->end;
  newpass->note = passenger_info->note;
  strcpy(newpass->name, passenger_name);
  strcpy(newpass->time, passenger_info->time);
  return SUCCESS_CODE;
}

STATUS_CODE BusPassengerNote(int newnote, char *busname, char *username){
	char path[32];
	int i;
	Route bus;
	FILE *fp;
	CalcBusPath(path, busname);
	fp = fopen(path, "wb");
	fread(&bus, sizeof(Route), 1, fp);
	fclose(fp);
	fp = NULL;
	for(i = 0; i < bus.npassenger; i++){
		if(!strcmp(bus.ps[i].name, username))
			bus.ps[i].note = newnote;
	}
	fp = fopen(path, "wb");
	fwrite(&bus, sizeof(Route), 1, fp);
	fclose(fp);
	fp = NULL;
	return SUCCESS_CODE;
}

STATUS_CODE RouteNewPassenger(int route_line, char *route_name,
                              HisLi *passenger_info, char *passenger_name)
{
  STATUS_CODE flag;
  char path[32];
  int i;
  FILE *fp;
  Route route;
  Passenger newpass;
  CalcBusPath(path, route_name);
  FetchNewpass(&newpass, passenger_info, passenger_name);
  FetchRoute(&route, path, route_name, route_line);
  if(route.npassenger < 16) {
  	route.ps[route.npassenger] = newpass;
  	route.npassenger++;
	}
	else{
		for(i = 0; i < 15; i++)
			route.ps[i] = route.ps[i+1];
		route.ps[15] = newpass;
	}
  fp = fopen(path, "wb");
  fwrite(&route, sizeof(Route), 1, fp);
  fclose(fp);
  fp = NULL;
  return SUCCESS_CODE;
}

STATUS_CODE ReadRoute(Route *route, char *route_name)
{
  char path[32];
  FILE *fp;
  CalcBusPath(path, route_name);
  fp = fopen(path, "rb");
  fread(route, sizeof(Route), 1, fp);
  fclose(fp);
  fp = NULL;
  return SUCCESS_CODE;
}
