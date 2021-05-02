#include "headers/info.h"
#include "headers/register.h"
#include "headers/run.h"
#include "headers/status.h"
#include "headers/mouse.h"
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "headers/svga.h"

int main()
{
  STATUS_CODE flag;
  char user_account[16];
  SetSVGA64k();
  while (1)
  {
    flag = RegisterFunc(user_account);
    if (flag == EXIT_CODE)
    {
      CloseSVGA();
      break;
    }
    else
    {
      flag = RunFunc(user_account);
      if (flag != SUCCESS_CODE)
      {
        CloseSVGA();
        fprintf(stderr, "Run Error\n");
        break;
      }
    }
  }

  return 0;
}
