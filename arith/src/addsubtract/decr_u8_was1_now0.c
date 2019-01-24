#include "common.h"
#include "arith.h"

/* ----------------------------------------------------------------
|
|  Decrement 'a', but not below zero. Return 1 if 'a' was '1' before
|  being decremented (and is now zero).
|
-------------------------------------------------------------------*/

PUBLIC BIT DecrU8_Was1_NowZero(U8 * a)
{
   if( *a == 0 )
   {
      return 0;
   }
   else if( *a == 1 )
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

     
