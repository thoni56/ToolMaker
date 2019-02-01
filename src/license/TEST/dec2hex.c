/* Read an integer from stdin and writes it hexadecimal 
   representation to standard output. Free from error
   handling.
   */

#include <stdio.h>

void main()
{
  int x;
  scanf("%d", &x);
  printf("%x\n", x);
}
