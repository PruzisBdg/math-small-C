 /*-----------------------------------------------------------------------------------------
|
|  VecU8_Mean()
|
------------------------------------------------------------------------------------------*/

#include "arith.h"

PUBLIC S16 VecU8_Sum(U8 const *v, U8 cnt)
{
   U8  c;
   S16 sum;
   
   for( c = 0, sum = 0; c < cnt; c++ )
   {
      sum += v[c];
   }
   return sum;
}

  
