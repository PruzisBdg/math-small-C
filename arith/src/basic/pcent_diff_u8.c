#include "arith.h"

PUBLIC U8 PcentDiffU8(U8 a, U8 b)
{
   // The larger of 'a', 'b' is the numerator (2nd parm), the smaller is the denominator (parm3)
   return AmulBdivC_U8(100, (a>b)?a:b, (a>b)?b:a) - 100;
}


  
