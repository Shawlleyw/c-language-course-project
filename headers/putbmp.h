#ifndef TRAFFIC_HEADERS_PUTBMP_H_
#define TRAFFIC_HEADERS_PUTBMP_H_
#include "headers/status.h"
/*
function PutBmp:
    传入参数: (图片左上角相对像素位置， 图片路径)
    功能: 贴图
    返回值：成功返回SUCCESS_CODE,失败返回ERROR_CODE
*/
STATUS_CODE PutBmp(int x, int y, char *s);

#endif
