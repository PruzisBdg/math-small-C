#include "arith.h"

/* ----------------------------- SpinUpU8 --------------------------------------- 

   Increment 'in' thru 'maxCnt' and back to zero.  Note that the modulus
   of the count is 'maxCnt'.  If 'maxCnt' is 1 then iterations of the 
   function will give 0,1,0,1,0.....
*/

PUBLIC U8 SpinUpU8(U8 in, U8 maxCnt) 
{ 
   return in >= maxCnt ? 0 : in+1;   
}
  
