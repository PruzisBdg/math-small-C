 /*---------------------------------------------------------------------------
|
|                  1st-order IIR filters
|
|--------------------------------------------------------------------------*/

#include "math_common.h"
#include "iirFilt1.h"


PUBLIC void IIR1_Init( S_IIR1 RAM_IS *f, U8 div )
{
   f->acc = 0;
   f->div = MAX(div, 2);      // div can't be less than 2 for filter to function
}

PUBLIC S16 IIR1_LPass_Run( S_IIR1 RAM_IS *f, S16 in )
{
   f->acc = (((f->div - 1) * f->acc) / f->div) + in;
   return f->acc / f->div;
}

// -------------------------- eof --------------------------------------

