/*-----------------------------------------------------------------------------------------
|
|  VecB_Sum()
|
------------------------------------------------------------------------------------------*/

#include "arith.h"

PUBLIC S16 VecB_SumToS16(S16 *v, U8 cnt)
{
   S16 sum;
   
   sum = 0;
   
   while( cnt > 0)
   {
      cnt--;
      sum = AddTwoS16(v[cnt], sum);    
   }
   return sum;
}

  
