
#include "spj_stdint.h"
#include "arith.h"

/* Return the bit position (0-15) of the msb of 'n' .

   If n == 0 return 0 (the same answer as for n = 0x0001)
*/

PUBLIC U8 MSB_U16(U16 n) {
   U8 msb;

   if(n ==0) {
      return 0;
      }
   else {
      for(msb = 0; n; msb++ ) {
         n >>=1;
         }
      return msb-1;
      }
}

// ------------------------------------------------ eof --------------------------------------------


