#include<stdio.h>
#include<string.h>
#include "headers/info.h"
#include "headers/status.h"


void CalcBusPath(char *path, char *route){
    strcpy(path, "data/bus/");
    strcat(path, route);
    return path;
}

STATUS_CODE FetchRoute(Route *route, char *path, char *route_name, int route_line){
    FILE *fp;
    fp = fopen(path, "rb");
    if(fp == NULL){
        memset(route, 0, sizeof(Route));
        route->line = route_line;
        route->npassenger = 0;
        strcpy(route->route_name, route_name);
    }
    else{
        fread(&route, sizeof(Route), 1, fp);
        fclose(fp);
        fp = NULL;
    }
    return SUCCESS_CODE;
}

STATUS_CODE FetchNewpass(Passenger *newpass, HisLi *passenger_info, char *passenger_name){
    newpass->start = passenger_info -> start;
    newpass->end = passenger_info -> end;
    newpass->note = passenger_info -> note;
    strcpy(newpass->name, passenger_name);
    strcpy(newpass->time, passenger_info -> time);
    return SUCCESS_CODE;
}

STATUS_CODE RouteNewPassenger(int route_line, char *route_name, HisLi *passenger_info, char *passenger_name){
    STATUS_CODE flag;
    char path[32];
    FILE *fp;
    Route route;
    Passenger newpass;
    CalcBusPath(path, route_name);
    flag = FetchNewpass(&newpass, passenger_info, passenger_name);
    flag = FetchRoute(&route, path, route_name, route_line);
    route.ps[route.npassenger] = newpass;
    route.npassenger++;
    fp = fopen(path, "wb");
    fwrite(&route, sizeof(Route), 1, fp);
    fclose(fp);
    fp = NULL;
    return SUCCESS_CODE;
}

STATUS_CODE ReadRoute(Route *route, char *route_name){
    char path[32];
    FILE *fp;
    CalcBusPath(path, route_name);
    fp = fopen(path, "rb");
    fread(route, sizeof(Route), 1, fp);
    fclose(fp);
    fp = NULL;
    return SUCCESS_CODE;
}
