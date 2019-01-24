#include "common.h"
#include "arith.h"

/* ----------------------------- AbsS16 --------------------------------------- */

PUBLIC S16 AbsS16(S16 n) 
{ 
   // -(-32768) does not exist as a 'signed short', so handle gracefully
   
   if(n == MIN_S16)           // -32768? 
      { return MAX_S16; }     // then return +32767
   else                       
      { return ABS(n); }      // else it's a number whose sign can be inverted
}


