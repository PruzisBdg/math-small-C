/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Ref
|
|  DESCRIPTION:
|
|  Setup vector 'sub' to access 'numCols' of 'row' of reference vector 'ref' starting at 'startCol'.
|  The data in 'ref' is  not duplicated.
|
|  The number of columns accessed is written in 'sub'. If the access extends beyond the end of the
|  source row then sub.cols is truncated to less than 'numCols'.
|
|  If 'ref' has 0 columns then set the number of columns in 'sub' to 'numCols'. This allows a
|  section of a vector to be written to and the dimensions fixed up later.
|
|  PARAMETERS:
|
|     'ref'       -  reference vector
|     'sub'       -  a vector accessing row 'row' of 'ref'
|     'row'       -  row number of 'ref' to be accessed
|     'startCol'  -  1st column to access
|     'numCols'   -  (max) number of columns accessed
|
|  RETURNS:
|
|
|	DATE		   AUTHOR		      DESCRIPTION OF CHANGE
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC void Vec_Ref( S_Vec *sub, S_Vec const *ref, T_VecRows row, T_VecCols startCol, T_VecCols numCols )
{
   T_VecRows LVAR r;
   T_VecCols LVAR colOfs;

   sub->rows = 1;                                  /* Accessing 1 row                              */
   colOfs = startCol;                              /* unless limited below by size of 'ref'        */

   if( ref->cols == 0 )                            /* reference vector empty?                      */
   {                                               /* then assume we can write all of sub into it  */
      sub->cols = numCols;                         /* and fix up dimensions afterwards             */
   }
   else if( startCol >= ref->cols )                /* 'start' beyond end of row?                   */
   { 
      sub->cols = 0;                               /* then reference zero elements                 */
      colOfs = ref->cols - 1;                      /* and for safety place pointer at last element */
   }                                               
   else if( numCols > (ref->cols - startCol) )     /* requested end is past end-of-row?            */
      { sub->cols = (ref->cols - startCol); }      /* then will get just to end-of-row             */
   else                                            /* else can reference all requested elements    */
      { sub->cols = numCols; }                     /* so get them                                  */

   r = ref->rows - 1;
   r = MIN(row, r);                                /* Limit row access to inside 'ref'             */

   sub->nums = ref->nums + ((U16)ref->cols * r) + colOfs;   /* Jump in correct data position       */
}

// -------------------------------------- eof ---------------------------------------------------


 
