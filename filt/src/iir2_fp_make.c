/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIRF2_Init
|
|  DESCRIPTION:
|
|     Make / initialise 2nd-order section 'f' with coffs 'coffs'. The filter buffer is zeroed
|
|  PARAMETERS:    - 'f'       the filter
|                 - 'coffs'   the coffs
|
|  RETURNS:
|     
|
|	DATE		AUTHOR		DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "iirfilt_fp.h"

PUBLIC void IIRF2_Init( S_IIRF2  *f, T_IIRFCoffs CONST *coffs ) 
{
	f->buf[0] = 0;
	f->buf[1] = 0;
   f->coffs  = coffs;
   f->tapIdx = 0;
}

// ------------------------------------ eof ----------------------------------------------------- 
