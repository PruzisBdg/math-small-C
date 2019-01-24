/*-----------------------------------------------------------------------------------------
|
|  VecB_MaxIdx()
|
|  Return index of the largest value in 'v', not the value itself.
|
------------------------------------------------------------------------------------------*/

#include "arith.h"

PUBLIC U8 VecB_MaxIdx(S16 *v, U8 cnt)
{
   U8 c;
   S16 maxVal;
   U8  maxIdx;
   
   for(c = 0, maxVal = MIN_S16, maxIdx = 0; c < cnt; c++ )
   {
      if( v[c] > maxVal )
      {
         maxVal = v[c];
         maxIdx = c;   
      }
   }
   return maxIdx;
}

  
