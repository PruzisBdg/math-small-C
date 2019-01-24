#include "common.h"
#include "arith.h"

/* ----------------------------- SqrtLong ---------------------------------------

   Returns the square root of the absolute value of 'n'. Uses successive aproximation. 
   Will terminate in 16 loops or less.

   Taking the sqrt of the absolute enables this function to be used in 2-quadrant
   compression and linearisation schemes.
*/
PUBLIC S32 SqrtLong(S32 n) {

   U32   u;
   U16   root, step;

   if( n == 0 ) return 0;

   if( n < 1 ) n = -n;

   for( root = 32768, step = 16384; step > 0; step >>= 1 ) {
      u = (U32)root * (U32)root;

      if( u == (U32)n ) break;           /* Be nice and terminate on exact root if it is an integer */
      if( u >  (U32)n ) root -= step;
      if( u <  (U32)n ) root += step;
      }
   return (S32)root;
}

 
