#include "bldcfg.h"
#include "common.h"
#include "mathfunc.h"
#include <stdio.h>

S16 f1(S16 x) { return x; }

int main(void)
{
   printf("f1 = %ld\r\n", SimpsonS16(f1, 0, 1, 4) );

   while(1);
}


// -------------------------------- eof -----------------------------------------

