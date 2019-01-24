/*-----------------------------------------------------------------------------------------
|
|  VecU8_Dev()
|
------------------------------------------------------------------------------------------*/

#include "arith.h"

PUBLIC U8 VecU8_Dev(U8 *v, U8 cnt)
{
   U8 c, mean;
   U16 sum;
   
   mean = VecU8_Mean(v, cnt);
   
   for( c = 0, sum = 0; c < cnt; c++ )
   {
      sum += AbsDiffU8(v[c], mean);
   }
   return (U8)(sum/cnt);
}

 
