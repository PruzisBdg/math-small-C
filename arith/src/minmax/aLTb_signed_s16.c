
#include "common.h"
#include "arith.h"

/* Return 1 (TRUE) the mag of 'a' and 'b' have the same sign AND the magnitude of
  'a' is less than than magnitude of 'b'
  
   If b == 0 then always return 1.
  
  Note: This is not the same as comparing magnitudes i.e abs(a) >= abs(b)?
*/

PUBLIC BIT aLTb_Signed_S16(S16 a, S16 b) {
   return
      b == 0 ||
      (a > 0 && b > 0 && a < b) ||
      (a < 0 && b < 0 && a > b );
}

// -------------------------------- eof ---------------------------------------
