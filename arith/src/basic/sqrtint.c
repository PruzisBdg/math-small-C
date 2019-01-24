#include "common.h"
#include "arith.h"

/* ----------------------------- SqrtInt ---------------------------------------

   Returns the square root of the ABSOLUTE value of 'n'. Uses successive aproximation. 
   Will terminate in 8 loops or less. Much faster than any method conventionally used with
   real numbers.

   Taking the sqrt of the absolute enables this function to be used in 2-quadrant
   compression and linearisation schemes.
*/
PUBLIC U8 SqrtInt(S16 n) {

#if 0
   U16   u;
   U8  root, step;

   if( n == 0 ) return 0;

   if( n < 1 ) n = -n;
   for( root = 128U, step = 64U; step > 0; step >>= 1 ) {
      u = (S16)root * (S16)root;

      if( u == (U16)n ) break;           /* Be nice and terminate on exact root if it is an integer */
      if( u >  (U16)n ) root -= step;
      if( u <  (U16)n ) root += step;
      }
   return root;
#else
   return SqrtU16(AbsS16(n));   
#endif   
}

 
