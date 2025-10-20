/* --------------------------------------------------------------------------------

   Given 'a' and 'b' and a ranked list 'ranks' which contains both 'a' & 'b', return
   either the higher-ranked or lower-ranked number.

   If 'a' is not in the list return 'b' and vice versa. If neither 'a' or 'b' are on
   the list or the list is empty return the mean of 'a' and 'b'.

   'ranks' are in reverse index order; ranks.ns[0] = highest. ranks.ns[ranks.cnt-1]
   is lowest.
*/

#include "common.h"
#include "arith.h"

/* ------------------------------- MaxRank_U16 ----------------------------------------- */

PUBLIC U16 MaxRank_U16(S_BufU16 const *ranks, U16 a, U16 b) {

   if(ranks->ns != NULL && ranks->cnt > 0) {       // 'ranks' is non-empty?
      for(U16 i = 0; i < ranks->cnt; i++)          // From ranks.ns[0] (the highest) downward...
      {
         if(ranks->ns[i] == a ) {                  // Matched 'a'?
            return a; }                            // then 'a' is higher than 'b'
         else if(ranks->ns[i] == b) {              // else matched 'b'? ...
            return b; }                            // then'b' is higher.
      }
   }
   return ((U32)a + b + 1) / 2;                    // Empty list OR No 'a' or 'b'? <- mean(a,b)
}

/* ------------------------------- MinRank_U16 ----------------------------------------- */

PUBLIC U16 MinRank_U16(S_BufU16 const *ranks, U16 a, U16 b) {
   // Same as MaxRank_U16() above but from lowest-ranked upwards.

   if(ranks->ns != NULL && ranks->cnt > 0) {       // 'ranks' is non-empty?
      for(U16 i = ranks->cnt; i > 0; i--)          // Note! Unsigned countdown from 'cnt' -> 1...
      {
         if(ranks->ns[i-1] == a ) {                // ...so ns[i-1]
            return a; }
         else if(ranks->ns[i-1] == b) {
            return b; }
      }
   }
   return ((U32)a + b + 1) / 2;
}

// -------------------------------------------- EOF ---------------------------------------------
