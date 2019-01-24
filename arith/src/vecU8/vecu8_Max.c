/*-----------------------------------------------------------------------------------------
|
|  VecU8_Max()
|
------------------------------------------------------------------------------------------*/

#include "arith.h"

#if _TOOL_IS == TOOL_RIDE_8051
#pragma AUTO         // For 8051, its smaller on-stack
#endif

PUBLIC U8 VecU8_Max(U8 *v, U8 cnt)
{
   U8 c;
   U8 maxVal;
   
   for(c = 0, maxVal = 0; c < cnt; c++ )
   {
      if( v[c] > maxVal ) maxVal = v[c];
   }
   return maxVal;
}

  
