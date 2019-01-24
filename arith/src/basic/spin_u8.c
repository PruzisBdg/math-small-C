#include "common.h"
#include "arith.h"

/*---------------------------------------------------------------------
|
|  RotateU8()
|
|  Increment or decrement 'n' over the range 0...last, wrapping round at
|  either end. 
|
|  If 'n' is outside the range 0...last then it will be folded into that
|  range.
|
|----------------------------------------------------------------------*/


PUBLIC U8 SpinU8(U8 n, U8 incr, U8 last)
{
   return
   (
      (incr)                        // Up?
      ?
         (n >= last) ? 0 : n+1      // then increment/wrap at top
      :
         (n == 0) ? last : n-1      // else decrement/wrap at bottom
   );
} 
