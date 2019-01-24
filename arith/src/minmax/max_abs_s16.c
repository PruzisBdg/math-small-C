#include "common.h"
#include "arith.h"

/* ----------------------------- AbsMaxS16 --------------------------------------- */

PUBLIC S16 MaxAbsS16(S16 a, S16 b) 
{ 
   return MaxS16(AbsS16(b), AbsS16(a)); 
} 
