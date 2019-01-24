#include "common.h"
#include "arith.h"

/* ----------------------------- AbsS16 --------------------------------------- */

PUBLIC S8 AbsS8(S8 n) 
{ 
   return 
   (n == MIN_S8)        // -128? ...
   ? 
   MAX_S8               // has no negative in S8, so map to +127
   : 
   ((n > 0) ? n : -n);  // else return ABS(n)
}


