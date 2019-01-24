#include "common.h"
#include "arith.h"

/* ----------------------------- SignS8 --------------------------------------- 

   Return 1 if 'n' is postive or zero, else -1.
*/

PUBLIC S8 SignS8(S8 n) 
{ 
   return (n < 0) ? -1 : 1;
}


