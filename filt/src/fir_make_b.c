/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  FIR_Make
|
|  DESCRIPTION:
|
|  Make FIR 'f'.
|
|  PARAMETERS:   'f'     - the filter
|                'cfg'   - full configuration for 'f'
|
|  RETURNS:
|     
|
|	DATE		AUTHOR		DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "firfilt.h"

PUBLIC void FIR_MakeB( S_FIR *f,  S_FIRCfg CONST *cfg )
{
   f->cfg = *cfg;    // Configuration is copied into 'f'. faster to use form RAM.
   
   #ifdef _USE_ARRAY_INDICES
   f->end = f->cfg.taps - 1;
   #else
   f->end = f->cfg.buf._s16 + f->cfg.taps - 1;
   #endif

   FIR_Reset(f, 0);
}



// ---------------------------------- eof ------------------------------------------ 
