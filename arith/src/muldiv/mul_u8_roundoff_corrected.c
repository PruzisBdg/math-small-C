#include "common.h"
#include "arith.h"

/* ----------------------------- MulU8R --------------------------------------- 

   Byte multiplication, corrected for roundoff errors.
*/

PUBLIC S16 MulU8R(U8 a, U8 b) 
{ 
   return (a >> 1) + (a * (S16)b) + (b >> 1);
}
  
