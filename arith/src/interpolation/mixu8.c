/*-----------------------------------------------------------------------------------------
|
|  MixU8()
|
------------------------------------------------------------------------------------------*/

#include "arith.h"

PUBLIC U8 MixU8(U8 a, U8 b, U8 ratio)
{
   return (((255 - ratio) * (U16)a) + (ratio * (U16)b) + 127) >> 8;
}

 
