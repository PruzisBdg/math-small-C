/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Sub
|
|  DESCRIPTION:
|
|  Extracts a portion of 'src' into 'sub'. The portion extracted is given by 'ctl' and also
|  depends on the numner of rows and column available in 'sub'.
|
|     For each of rows and columns (rows given as example):
|
|        If sub.rows == 0 then ctl.startRow... (ctl.startRow + ctl.numRows - 1) copied from 'src'
|        If sub.rows != 0 then copy no more then sub.rows
|
|        If sub.rows == 0 AND ctl.numRows == 0 then copy all rows from 'src'
|        If sub.rows != 0 AND ctl.numRows == 0 then copy all 'src' rows up to capacity of 'sub' (sub.rows)
|
|
|  PARAMETERS:    'sub'  - the sub-vector extracted from source
|                 'in'   - the source vector
|                 'ctl'  - 
|
|  RETURNS:    - vector index to min / max
|     
|
|	DATE		AUTHOR		DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC void Vec_Sub( S_Vec *sub, S_Vec const *src, S_Vec_SubCtl const *ctl )
{
   T_VecRows LVAR sr, dr, numR;
   T_VecCols LVAR sc, dc, numC, subCtls;

   /* Figure rows to copy */

   if( ctl->startRow >= src->rows )             /* start row at or beyond source?                                             */
      { numR = 0; }                             /* then no copy                                                               */
   else
      { numR = src->rows - ctl->startRow; }     /* but don't read beyond end of source; so no more than this number of rows.  */

   if( sub->rows != 0 )                         /* rows speced in destination?                                                */
   {
      numR = MIN(sub->rows, numR );             /* so number to copy can't be more than what's available from source OR       */
   }                                            /* what will fit in dest                                                      */

   if( ctl->numRows != 0 )                      /* if 'ctl' specs a number to copy                                            */
   {
      numR = MIN(ctl->numRows, numR);           /* then copy that but not more than 'src' or destination limits (above)       */
   }

   /* Figure rows to copy... same as for rows */

   if( ctl->startCol >= src->cols )             /* start column at or beyond source?               */
      { numC = 0; }                             /* then no copy                                    */
   else
      { numC = src->cols - ctl->startCol; }     /* Can't read beyond end of source; etc etc...     */

   if( sub->cols != 0 )                         /* destination column width not specified?         */
   {
      numC = MIN(sub->cols, numC );             
   }
   if( ctl->numCols != 0 )                   
   {
      numC = MIN(ctl->numCols, numC);           
   }

   if( sub->cols == 0 )                         /* dest column size not specified/     */
      { subCtls = ctl->numCols; }               /* then set column skip from 'ctl'     */
   else
      { subCtls = sub->cols; }                  /* else its from 'sub' itself          */

   /* Done with rows/cols in 'sub' now can overwrite with final values. */
   sub->rows = numR;
   sub->cols = numC;

   /* And do copy! */

   for( sr = ctl->startRow, dr = 0; dr < numR; sr++, dr++ )
   {
      for( sc = ctl->startCol, dc = 0; dc < numC; sc++, dc++ )
      {
         sub->nums[(dr * subCtls) + dc] = src->nums[(sr * src->cols) + sc];
      }
   }
}



 
