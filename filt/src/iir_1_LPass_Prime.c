#include "math_common.h"
#include "iirFilt1.h"


PUBLIC S16 IIR1_LPass_Prime( S_IIR1 RAM_IS *f, S16 in )
{
   f->acc = (S32)in * f->div;
   return in;
}

// -------------------------- eof -------------------------------------- 
