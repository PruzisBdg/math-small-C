  /*---------------------------------------------------------------------------
|
|                  1st-order IIR filters
|
|--------------------------------------------------------------------------*/

#include "math_common.h"
#include "iirFilt1.h"

// Just read the filter without cranking it.
PUBLIC S16  IIR1_Read( S_IIR1 RAM_IS *f )
{
   return f->acc / f->div;
}

// -------------------------- eof --------------------------------------

