#ifndef TRAFFIC_HEADERS_TRAVELDATA_H_
#define TRAFFIC_HEADERS_TRAVELDATA_H_
#include "headers/status.h"

/*
function ReadRoute:
    功能: 读取某车次信息 目录为 `data/bus/route_name`
    传参: route struct Route目标地址
         route_name 车次名
    返回值: SUCCESS_CODE
*/
STATUS_CODE ReadRoute(Route *route, char *route_name);

/*
function RouteNewPassenger:
    功能: 在某车次中添加一条用户信息  目录为 `data/bus/route_name`
    传参: route_line 公交车线路号码
         route_name 公交车车次名
         passenger_info 某用户的一条历史乘车信息
         passenger_name 某用户名字
    返回值: SUCCESS_CODE
*/

STATUS_CODE RouteNewPassenger(int route_line, char *route_name, HisLi *passenger_info, char *passenger_name);
#endif