#include "math_common.h"
#include "iirFilt1.h"

PUBLIC S16 IIR1_Rescale( S_IIR1 RAM_IS *f, U8 newDiv )
{
   return IIR1_InitVal(f, newDiv, f->acc/f->div);
}

// -------------------------- eof --------------------------------------
 
