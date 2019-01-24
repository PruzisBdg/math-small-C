#include "arith.h"

PUBLIC S16 ClipPosS16(S16 n)
{
   return n > 0 ? n : 0;      // Return n if n is positove, else return 0
} 
