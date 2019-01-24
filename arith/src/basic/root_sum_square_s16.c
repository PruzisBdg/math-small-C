/*-----------------------------------------------------------------------------------------
|
|  RootSumSq_S16()
|
|  The hypotenuse of 'a' and 'b'
|
------------------------------------------------------------------------------------------*/

#include "arith.h"

PUBLIC S16 RootSumSq_S16(S16 a, S16 b)
{
   return SqrtLong( AddTwoS32(SqS16(b),SqS16(a)) );
}

   
