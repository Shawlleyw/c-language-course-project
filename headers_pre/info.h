#ifndef TRAFFIC_HEADERS_USERINFO_H_
#define TRAFFIC_HEADERS_USERINFO_H_

// struct for maps
/*
像素点结构体{
  (x, y): 像素点坐标
}
*/
typedef struct Locations {
  int x, y;
} Dots;

/*
车站信息结构体{
  (x, y): 车站坐标点
  R == 9
  number: 车站号码
  name: 车站名
}
*/
typedef struct Station {
  int number, x, y;
  char name[32];
} Sta;
// station: a circle on (x,y) with certain R

/*
公交路线结构体{
  station_numbers: 公交路线途经站点
}
*/
typedef struct LinesStations {
  int n, station_numbers[30];
} Lines;

/*
乘车记录信息结构体{
  line_no: 公交车号码
  start: 起点站
  end: 终点站
}
*/
typedef struct HistoryLinesInfomation {
  int line_no;
  int start;
  int end;
  int note;
  char time[16];
  char busnum[16];
} HisLi;

/*
用户信息结构体{
  nhistory: 用户历史乘车记录数
  name: 用户名
  history_lines: 用户历史乘车信息
}
*/
typedef struct UserInfomation { 
  int nhistory;
  char name[16];
  char account[16];
  HisLi history_lines[16];
} UserInfo;


/*
struct BusPassenger{ //用户在车次中的信息条目
  start: 起点站
  end: 终点站
  note: 14天内是否发热
  name: 用户名称
  time: 乘车时间
}
*/
typedef struct BusPassenger{
  int start, end, note;
  char name[16];
  char time[16];
}Passenger;

/*
struct BusRoute{ //某车次内乘客信息
  line: 车次线路
  npassenger: 当前储存乘客个数
  route_name: 车次名
  ps: 用户信息条目数组
}
*/
typedef struct BusRoute{
  int line, npassenger;
  char route_name[16];
  Passenger ps[16];
}Route;

#endif