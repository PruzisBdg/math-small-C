#include "arith.h"

PUBLIC BIT WithinPcentU8(U8 a, U8 b, U8 maxPcentApart)
{
   // The larger of 'a', 'b' is the numerator (2nd parm), the smaller is the denominator (parm3)
   return PcentDiffU8(a, b) < maxPcentApart;
}


 
