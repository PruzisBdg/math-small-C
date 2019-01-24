/* ---------------------------- Interpolate_NewtonFwd2 ----------------------------- 

   Interpolation of 3 equally-spaced points by Newton's forward differences. 
   
   For n = [0,1]
   
                      1               1
      fn = f0 + nD +  -- n(n-1)D^2  + - n(n-1)(n-2)D^3 .....
                      2!              3!
                      
   where D^n are forward differences to the nth power.
   
   Using just 3 points so, taking the 1st 3 terms gives
   
                            1
      fn = f0 + n(f1-f0) +  - n(n-1)(f2 - 2f1 + f0)
                            2
       
   Inputs:  y0, y1, y2  - the 3 points; y0 is the pivot
            n           - interpolation index, scaled 0..1.0 -> 0->256
            
   Returns: the result of the interpolation.
   
   Notes:   Mostly, but not completely numerically guarded. Extreme curves with
            large integers will overrange this routine. 
*/                      

#include "common.h"
#include "arith.h"

PUBLIC S16 Interpolate_NewtonFwd2(S16 y0, S16 y1, S16 y2, U8 n)
{
   return 
   (
      y0 +
      (
         (
            (n * (y1 - (S32)y0)) +
            (
               (
                  n * ((S16)n - 256) * (y0 - (2 * (S32)y1) + y2)
               )
               >> 9
            )
         )
         >> 8
      )
   );
}


// ---------------------------------- eof ------------------------------------------- 
