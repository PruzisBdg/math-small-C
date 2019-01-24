#include "arith.h"

/* ----------------------------- SpinDownU8 --------------------------------------- 

   Decrement 'in' thru zero and back to 'maxCnt'. Note that the modulus
   of the count is 'maxCnt' + 1.   E.g if maxcnt == 1 then the function
   iterated will count 0,1,0,1....
*/

PUBLIC U8 SpinDownU8(U8 in, U8 maxCnt) 
{ 
   return in == 0 ? maxCnt : in-1;   
}
 
