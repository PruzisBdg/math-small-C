/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_BubbleSort
|
|  DESCRIPTION:    Sort 'v' in place.
|
|        **** 'v' must have just one row *****
|
|  PARAMETERS:  'v'         - vector to be sorted
|               'ascending' - TRUE => lowest values in lowest index
|
|  RETURNS:
|
|	DATE		   AUTHOR             DESCRIPTION OF CHANGE
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC void Vec_BubbleSort( S_Vec *v, BOOL ascending )
{
   U8       LVAR b, c;
   BOOL     LVAR swap, didSwap;
   S16      LVAR n;
   S16    * LVAR p, * LVAR q;

   for( c = v->cols - 1,                        /* 1st pass compares 'cols - 1' pairs            */
        didSwap = TRUE;                         /* so we do at least one pass                   */
        c && didSwap;                           /* Make passes until get one with no swaps.     */
                                                /* check 'c' to ensure we terminate             */
        c-- )                                   /* On each pass the last pair compared are in   */
   {                                            /* correct order so next pass is one shorter.   */
      for( b = c,                               /* Compare this many pairs this pass.           */
           p = v->nums,                         /* From the start                               */
           q = v->nums + 1,
           didSwap = FALSE;                     /* until we do a swap on this pass              */
           b; 
           b--, p++, q++ ) 
      {
         swap = FALSE;

         if(ascending)                          /* Check for swap */ 
            { if( *p > *q ) swap = TRUE; }
         else
            { if( *p < *q ) swap = TRUE; }

         if(swap)                               /* swap reqd?     */
         { 
            n = *p; *p = *q; *q = n;            /* then do it     */
            didSwap = TRUE;                     /* and mark done  */
         } 
      }
   }
}


 
