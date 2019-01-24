 #include "common.h"
#include "arith.h"

/* ----------------------------- MulS16ToS16 --------------------------------------- */

PUBLIC S16 MulS16ToS16(S16 a, S16 b) 
{ 
   return ClipLongToInt(MulS16(a, b)); 
}
 
