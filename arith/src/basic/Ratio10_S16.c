#include "arith.h"

/* --------------------------------------------------------------------------
|
|  Return a measure of the ratio a:b.  Range of the measure is 12.8:1 -> 1:12.8
|
------------------------------------------------------------------------------ */

PUBLIC S8 Ratio10_S16(S16 a, S16 b)
{
   return 
   ClipS16toS8
   (
      ClipLongToInt
      (
         (a > b)                 // a > b? 
         ? 
         MulS16(10, a)/b         // then return 10 * a / b
         : 
         MulS16(-10, b)/a        // else return -10 * b / a
      )
   );                            // but limit to +/-128
}


  
