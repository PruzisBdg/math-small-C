/* --------------------------- MapToSCurve ---------------------------------- 

   Returns a one-sided 'S' curve on 'n', parameterised by 'halfPoint' and 'max'

                                 n^2
   Returns    out =  max *  ----------------
                            halfPoint + n^2

   This is an 'S' curve:
         
         out =  0;      n = 0;
         out -> max     n -> large
         out =  max/2;  n = halfPoint

   The curve is used to provide smooth and limited increase of gain in servos
   which require a fast recovery to baseline.


   Note: The math will overrange if:
   
            max * n * n > largest unsigned long (0xFFFFFFFF)
            
   This limit isn't checked for in code.
*/
#include "common.h"
#include "arith.h"

PUBLIC U8 MapToSCurve( S16 n, U16 halfPoint, U8 max ) {

   U32 l, u;

   u = halfPoint * (U32)halfPoint;
   l = n * (U32)n;
   return (U8) (( max * l ) / (u + l));
}

// ---------------------------------- eof --------------------------------------- 
