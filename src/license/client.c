/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-08-20/tony@wolf
 * CREATED: 1993-08-20
 *
 * SoftLab ab (c) 1993
 */

#include <stdio.h>
#include "common.h"
#include "license.h"

int main(int argc,char **argv)
{
  switch(license()) {
  case LICENSE_OK:
    printf("Got license.\n");
    exit(0);
  case LICENSE_EXPIRED:
    printf("%s: Fatal! license server: date expired\n",*argv);
    exit(1);
  case LICENSE_DENIED:
    printf("%s: Fatal! license server: no license available\n",*argv);
    exit(1);
  case LICENSE_FORMAT_ERROR:
    printf("%s: Fatal! license server: format error\n",*argv);
    exit(1);
  case LICENSE_NO_SERVER:
    printf("%s: Fatal! license server: no contact\n",*argv);
    exit(1);
  case LICENSE_NO_FILE:
    printf("%s: Fatal! license server: license file missing\n",*argv);
    exit(1);
  case LICENSE_ILLEGAL_PASSWORD:
    printf("%s: Fatal! license server: illegal license key\n",*argv);
    exit(1);
  case LICENSE_INITIALIZATION_FAILURE:
    printf("%s: Fatal! license server: initialization failure\n",*argv);
    exit(1);
  default:
    printf("%s: Fatal! unkown license error\n",*argv);
    exit(1);
  }
}
