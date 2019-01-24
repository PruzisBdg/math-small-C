/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_ByElementT
|
|  DESCRIPTION:
|
|  As for Vec_ByElement() but tranposing rows, cols
|  
|  RETURNS:
|     
|
|	DATE	      AUTHOR		      DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC void Vec_ByElementT( S_Vec *dest, S_Vec const *src, void(*op)(S16*, S16*, S16), S16 parm )
{
   T_VecRows LVAR rows, r;
   T_VecCols LVAR cols, c, srcCols;
   S16       * LVAR s, * LVAR d;

   /* Get number of source rows to operate on */

   if( src == 0 )                                     /* No 'src'? => unary operation                          */
      { rows = dest->cols; }                          /* then use dest                                         */
   else if( src->rows == 0 )                          /* 'src' size unspecified?                               */
      { rows = dest->cols; }                          /* then use 'dest'                                       */
   else if( dest->cols == 0 )                         /* 'dest' size unspecified                               */
      { rows = src->rows; dest->cols = src->rows; }   /* then use all of 'src'; also set 'dest' size to 'src'  */
   else                                               /* else both specified                                   */
      { rows = MIN(src->rows, dest->cols); }          /* so use lower of two                                   */

   /* Get number of source columns to operate */

   if( src == 0 )                                     /* as for rows. etc etc..... */
      { cols = dest->rows; }
   else if( src->cols == 0 )
      { cols = dest->rows; }
   else if( dest->cols == 0 )
      { cols = src->cols; dest->rows = src->cols; }
   else
      { cols = MIN(src->cols, dest->rows); }

   /* Setup source column skip distance. If not specified in source vector
      then must assume its same as 'dest'.
   */
   if( src->cols != 0 ) { srcCols = src->cols; } else { srcCols = dest->rows; }

   /* Do the operation.
      Note that if its a unary operation ('src' == 0 ) then 's' is garbage but has
      no effect since its not used by 'op()'.
   */
   for( r = 0,
        s = src->nums, 
        d = dest->nums; 
        r < rows; r++ ) 
   {
      for( c = 0,
           s = src->nums + (r * srcCols), 
           d = dest->nums + r; 
           c < cols; c++ ) 
      {
         (*op)(d, s, parm);
         s++; d += dest->cols;
      }
   }
}


 
