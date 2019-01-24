/*-----------------------------------------------------------------------------------------
|
|  VecU8_DevSum()
|
------------------------------------------------------------------------------------------*/

#include "arith.h"

PUBLIC S16 VecU8_DevSum(U8 *v, U8 cnt)
{
   U8 c, mean;
   S16 sum;
   
   mean = VecU8_Mean(v, cnt);
   
   for( c = 0, sum = 0; c < cnt; c++ )
   {
      sum += AbsDiffU8(v[c], mean);
   }
   return sum;
}

  
