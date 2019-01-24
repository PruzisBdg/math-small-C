/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_MinMax_Idx
|
|  DESCRIPTION:
|
|     Return index to minimum or maximum element in 'vec', depending on 'ctl'. All rows and
|     columns are scanned.
|
|  PARAMETERS: - 'vec'  vector
|              - 'ctl'  control byte selects min or max
|
|  RETURNS:    - vector index to min / max
|     
|
|	DATE		AUTHOR		DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC T_VecCols Vec_MinMax_Idx( S_Vec const *vec, U8 ctl ) 
{
   U16    LVAR vecSize, c, 
               idx;
   S16  * LVAR s;
   S16    LVAR minMax;

   vecSize = vec->rows * (U16)vec->cols;     /* scan every element */
   
   for( c = 0,
        s = vec->nums,
        minMax = *s, 
        idx = 0; 
        c < vecSize; 
        c++, s++ ) 
   {
      if( (BSET(ctl, _Vec_Ctl_GetMax) && *s > minMax) || 
          (BSET(ctl, _Vec_Ctl_GetMin) && *s < minMax) ) 
      {
         minMax = *s;
         idx = c;
      }
   }
   return idx;
}


 
