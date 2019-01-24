#include "common.h"
#include "arith.h"

/* ----------------------------- SignS16 --------------------------------------- */

PUBLIC S8 SignS16(S16 n) 
{ 
   return (n < 0) ? -1 : 1;
}


