/* ---------------------------- ClippedLinSquare -----------------------------------

   For fast recovery in servo loops; symmetrical, linear in the middle, squared outside 
   with limited output.

   Returns:   -linBand < x < +linBand:       in

              +linBand < x < SQRT(maxOut),
              -linBand > x > -SQRT(maxOut):  in^2 / linBand

              SQRT(maxOut * linBand) < x:      maxOut
              -SQRT(maxOut * linBand) < x:     -maxOut
*/

#include "common.h"
#include "arith.h"

PUBLIC S16 ClippedLinSquare(S16 x, S16 linBand, S16 maxOut) {

   S32 n;

   if( ABS(x) < linBand ) {
      return x;
      }
   else {
      n = (x * (S32)x)/(S32)linBand;
      n = MIN(n, (S32)maxOut);

      if( x > 0 ) 
         {return n;} 
      else 
         {return -n;}
      }

}

// ---------------------------------- eof ----------------------------------

 
