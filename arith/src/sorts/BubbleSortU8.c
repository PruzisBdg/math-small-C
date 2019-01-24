/* ---------------------------- Bubble Sort ------------------------------------------ 

   Sort 'cnt' items in 'n' in place.
*/

#include "common.h"
#include "arith.h"

PUBLIC void BubbleSortU8( U8 *v, U8 cnt, U8 ascending ) 
{

   U8    b, c;
   BIT   swap, didSwap;
   U8    n; 
   U8    *p, *q;

   for( c = cnt-1,               /* 1st pass compares 'cnt - 1' pairs            */
        didSwap = TRUE;          /* so we do at least one pass                   */
        c && didSwap;            /* Make passes until get one with no swaps.     */
                                 /* check 'c' to ensure we terminate             */
        c-- )                    /* On each pass the last pair compared are in   */
   {                             /* correct order so next pass is one shorter.   */

      for( b = c,                /* Compare this many pairs this pass.           */
           p = v,                /* From the start                               */
           q = v + 1,
           didSwap = FALSE;      /* until we do a swap on this pass              */
           b; 
           b--, p++, q++ ) 
      {
         swap = FALSE;
         if(ascending) { if( *p > *q ) swap = TRUE; }             /* check swap                     */
         else          { if( *p < *q ) swap = TRUE; }
         if(swap) { n = *p; *p = *q; *q = n; didSwap = TRUE; }    /* swap reqd? do it and mark done */
      }
   }
}


// -------------------------------- eof -------------------------------------------- 
