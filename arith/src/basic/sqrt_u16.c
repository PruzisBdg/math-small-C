#include "common.h"
#include "arith.h"

/* ----------------------------- SqrtU16 ---------------------------------------

   Returns the square root of the ABSOLUTE value of 'n'. Uses successive aproximation. 
   Will terminate in 8 loops or less. Much faster than any method conventionally used with
   real numbers.

   Taking the sqrt of the absolute enables this function to be used in 2-quadrant
   compression and linearisation schemes.
*/
PUBLIC U8 SqrtU16(U16 n) 
{
   U16   u;
   U8  root, step;

   if( n == 0 ) 
      { return 0; }
   else
   {
      for( root = 128U, step = 64U; step > 0; step >>= 1 ) {
         u = SqU8(root);
   
         if( u == n ) break;           /* Be nice and terminate on exact root if it is an integer */
         if( u >  n ) root -= step;
         if( u <  n ) root += step;
         }
      return root;
   }
}

  
