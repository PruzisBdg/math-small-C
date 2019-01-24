/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Diff
|
|  DESCRIPTION:
|
|  Gets 1st difference of each row in 'src'.
|
|  For n = 0.. (src.cols - 1)
|
|     dest[row, n] = src[row, n+1] - src[row, n]
|
|  PARAMETERS: - 'dest'  'src' vectors.
                 Note that 'dest' will have one fewer columns than 'src'
|
|  RETURNS: 
|     
|
|	DATE        AUTHOR            DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PRIVATE void diffOne( S16 *dest, S16 *src, S16 parm ) { *dest = *(src+1) - *src; }

PUBLIC void Vec_Diff( S_Vec *dest, S_Vec const *src )
{
   S_Vec       d, s;
   T_VecRows   LVAR r;
   T_VecCols   LVAR c;

   /* Figure number of columns in output vector */

   if( dest->cols )                                /* 'dest' cols specified?                    */
      { c = dest->cols; }                          /* then its that                             */
   else if( src->cols )                            /* else 'src' cols specified?                */
      { c = src->cols - 1; }                       /* then its one less than 'src'              */
   else                                            /* else neither specified                    */
      { c = 0; }                                   /* so do nothing                             */

   /* Diff each row in source vector */

   for( r = 0; r < src->rows; r++ )                /* for each row in 'src'                     */
   {
      Vec_RefRow( &s, src, r );                    /* address that source row                   */
      _Vec_Make( &d, dest->nums + (r * c), 1, c);  /* Address row to be made in 'dest' buffer   */
      Vec_ByElement(&d, (S_Vec const *)&s, diffOne, 0);           /* and diff source row.                      */
   }

   /* done; update dest size */
   dest->rows = src->rows;
   dest->cols = c; 
}


 
