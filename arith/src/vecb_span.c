/*-----------------------------------------------------------------------------------------
|
|  VecB_Span()
|
------------------------------------------------------------------------------------------*/

#include "arith.h"

PUBLIC S16 VecB_Span(S16 *v, U8 cnt)
{
   return AddTwoS16(VecB_Max(v, cnt), -VecB_Min(v, cnt));
}


 
