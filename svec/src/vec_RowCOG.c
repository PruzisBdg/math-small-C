/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_RowCOG
|
|  DESCRIPTION:
|
|  Return centre of gravity of the elements in the 1st/only row of 'v'.
|
|            SUM(n * v[n])
|     COG =  -------------
|              SUM(v[n])
|
|  There's no S32 overrange protection. So you must watch vector sizes.
|
|  Return 16 x COG of 'v'. The x16 gives some racitonal resolution.
|     
-------------------------------------------------------------------------------------------------*/

#include "vec.h"
#include "arith.h"

PUBLIC S16 Vec_RowCOG( S_Vec const *v )
{
   T_VecCols LVAR c;
   S32       LVAR sum;
   S32       LVAR sumProd;

   for( c = 0, sum = 0, sumProd = 0; c < v->cols; c++ )     // For the 1st row
   { 
      sum += v->nums[c];                                    // Sum v[n]
      sumProd += c * (S32)v->nums[c];                       // Sum  n * v[n]
   }
   
   if( sum == 0 )                                           // Row sum is zero
   {
      return 8 * (S16)(v->cols);                            // then return the middle of the row
   }
   else                                                     // else row sum is non-zero
   {                                                        // so calc COG
      return ClipFloatToInt(16.0 * (float)sumProd / (float)sum);
   }
}



  
