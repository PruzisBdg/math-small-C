/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_ByElement
|
|  DESCRIPTION:
|
|  Performs unary or binary operation 'f' on vectors 'src' and 'dest'; result in 
|  'dest'. This function is a shell for common element-by-element operations such 
|  as Add, Subtract, Abs.
|
|  The shell provides consistent resolution of conflicting row and column dimensions 
|  in the source and destination vectors.
|
|  For either rows and columns, 
|
|     If both 'src' and 'dest' dimensions are specified then:
|
|        If 'src' >= 'dest' than operation is done on all of 'dest'
|        If 'src' < 'dest' then all of 'src' is used, remain elements in 'dest' are 
|        not operated on.
|     
|     If 'dest' dimension == 0 then its assumed that its the same as source. Likewise
|     if 'src' dimension == 0 its assumed its the same as 'dest'
|
|  PARAMETERS:    'dest'  - vector
|                 'src'   - vector, may be 0 if operation is unary
|                 'op'    - the unary or binary operation
|                 'parm'  - is passed to 'op' each time it is executed
|
|  RETURNS:
|     
|
|	DATE	      AUTHOR		      DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC void Vec_ByElement( S_Vec *dest, S_Vec const *src, void(*op)(S16*, S16*, S16), S16 parm )
{
   T_VecRows LVAR rows, r;
   T_VecCols LVAR cols, c, srcCols;
   S16       * LVAR s, * LVAR d;

   /* Get number of rows to operate on */

   if( src == 0 )                                     /* No 'src'? => unary operation                          */
      { rows = dest->rows; }                          /* then use dest                                         */
   else if( src->rows == 0 )                          /* 'src' size unspecified?                               */
      { rows = dest->rows; }                          /* then use 'dest'                                       */
   else if( dest->rows == 0 )                         /* 'dest' size unspecified                               */
      { rows = src->rows; dest->rows = src->rows; }   /* then use all of 'src'; also set 'dest' size to 'src'  */
   else                                               /* else both specified                                   */
      { rows = MIN(src->rows, dest->rows); }          /* so use lower of two                                   */

   /* Get number of columns to operate */

   if( src == 0 )                                     /* as for rows. etc etc..... */
      { cols = dest->cols; }
   else if( src->cols == 0 )
      { cols = dest->cols; }
   else if( dest->cols == 0 )
      { cols = src->cols; dest->cols = src->cols; }
   else
      { cols = MIN(src->cols, dest->cols); }

   /* Setup source column skip distance. If not specified in source vector
      then must assume its same as 'dest'.
   */
   if( src->cols != 0 ) { srcCols = src->cols; } else { srcCols = dest->cols; }

   /* Do the operation.
      Note that if its a unary operation ('src' == 0 ) then 's' is garbage but has
      no effect since its not used by 'op()'.
   */
   for( r = 0,
        s = src->nums, 
        d = dest->nums; 
        r < rows; r++ ) 
   {
      for( c = cols,
           s = src->nums + (r * srcCols), 
           d = dest->nums + (r * dest->cols); 
           c; c-- ) 
      {
         (*op)(d, s, parm);
         s++; d++;
      }
   }
}


 
