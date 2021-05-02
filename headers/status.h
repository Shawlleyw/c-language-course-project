#ifndef TRAFFIC_HEADERS_STATUS_H_
#define TRAFFIC_HEADERS_STATUS_H_

#define BLACK24 0x0000
#define NAVY24 0x000f
#define DARKGREEN24 0x03e0
#define DARKCYAN24 0x03ef
#define RED24 0x7800
#define PURPLE24 0x780f
#define LIGHTGRAY24 0xc618
#define DARKGRAY24 0x7bef
#define BLUE24 0x001f
#define GREEN24 0x07e0
#define CYAN24 0x07ff
#define LIGHTRED24 0xf800
#define MAGENTA24 0xf81f
#define YELLOW24 0xffe0
#define WHITE24 0xffff

/*
STATUS_CODE{
  EXIT_CODE = 0: 退出信号
  SUCCESS_CODE = 1: 成功信号
  ERROR_CODE = -1: 错误信号
}
*/
typedef enum {
  EXIT_CODE = 0,
  SUCCESS_CODE = 1,
  ERROR_CODE = -1,
} STATUS_CODE;

#endif // TRAFFIC_HEADERS_STATUS_H_
