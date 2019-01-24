#include "common.h"
#include "arith.h"

/* ----------------------------------------------------------------
|
|  Increment 'a', but not above MAX_U8 (0xFF). Return 1 if 'a' == 0xFF afterwards.
|
-------------------------------------------------------------------*/

PUBLIC BIT IncrU8(U8 * a)
{
   return (*a == MAX_U8) ? 1 : (BIT)(++(*a) == MAX_U8);
}

     
