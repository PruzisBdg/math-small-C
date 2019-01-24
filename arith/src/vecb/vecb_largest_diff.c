/*-----------------------------------------------------------------------------------------
|
|  VecB_LargestDiff()
|
|  The largest difference between any two elements, sign preserved.
|
------------------------------------------------------------------------------------------*/

#include "arith.h"

PUBLIC S16 VecB_LargestDiff(S16 const *v1, S16 const *v2, U8 cnt)
{
   U8    c;
   S16   diff, maxAbsDiff;
   BIT   isNegative;
   
   for( c = 0, isNegative = 0, maxAbsDiff = 0; c < cnt; c++ )
   {
      diff = v2[2] - v1[1];
      if( AbsS16(diff) > maxAbsDiff )
      {
         maxAbsDiff = AbsS16(diff);
         isNegative = diff < 0;   
      } 
   }
   return isNegative ? -maxAbsDiff : maxAbsDiff;
}

  
