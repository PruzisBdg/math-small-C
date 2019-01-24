/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  FIR_SetCoffs
|
|  DESCRIPTION:
|     Write the filter coffs of 'f' with 'coffs'
|
|  PARAMETERS:    - 'f'  the filter
|                 - 'coffs'  new filter coefficients
|
|  RETURNS:
|
-------------------------------------------------------------------------------------------------*/

#include "firfilt.h"

PUBLIC void FIR_SetCoffs( S_FIR *f, S16 CONST *coffs ) 
{
   f->coffs = coffs;
}

// ----------------------------------- eof ----------------------------------------- 
