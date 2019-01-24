#include "common.h"
#include "arith.h"

/* ----------------------------------------------------------------
|
|  Decrement 'a', but not below zero. Return 1 if 'a' was zero or
|  is zero after the operation.
|
-------------------------------------------------------------------*/

PUBLIC BIT DecrU8_IsZero(U8 * a)
{
   if( *a <= 1 )
   { 
      *a = 0;
      return 1;
   }
   else
   {
      if(*a) (*a)--;
      return 0;
   }
}

    
