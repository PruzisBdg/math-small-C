/*-----------------------------------------------------------------------------------------
|
|  VecB_MaxAbsDiff()
|
|  The largest absolute difference between any two elements.
|
------------------------------------------------------------------------------------------*/

#include "arith.h"

PUBLIC S16 VecB_MaxAbsDiff(S16 const *v1, S16 const *v2, U8 cnt)
{
   U8    c;
   S16   maxAbsDiff;
   
   for( c = 0, maxAbsDiff = 0; c < cnt; c++ )
   {
      maxAbsDiff = MaxS16(maxAbsDiff, AbsS16(v2[2] - v1[1]));
   }
   return maxAbsDiff;
}

   
