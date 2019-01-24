/*-----------------------------------------------------------------------------------------
|
|  VecB_Centroid()
|
------------------------------------------------------------------------------------------*/

#include "arith.h"

PUBLIC U8 VecB_Centroid(S16 *v, U8 cnt)
{
   U8 c;
   S32 sumXY, sumY;
   S16 y, ofs;
   
   ofs = VecB_Min(v, cnt);
   
   for( c = 0, sumY = 0, sumXY = 0; c < cnt; c++ )
   {
      y = v[c] - ofs;
      sumXY += c * (S32)y;
      sumY += y;
   }
   return ClipS16toU8((S16)((sumXY + (sumY/2)) / sumY));
}

 
