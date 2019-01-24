#include "arith.h"

PUBLIC U8 PcentDiffS16(S16 a, S16 b)
{
   // The larger of 'a', 'b' is the numerator (2nd parm), the smaller is the denominator (parm3)
   return 
   ClipS16toU8
   (
      AmulBdivC_S16(100, MaxS16(a,b), MinS16(a,b))
   ) 
   - 100; 
}


   
