/*-----------------------------------------------------------------------------------------
|
|  AbsDiffU8()
|
------------------------------------------------------------------------------------------*/

#include "arith.h"

PUBLIC U8 AbsDiffU8(U8 a, U8 b)
{
   return (a > b) ? a - b : b - a;
}
 
