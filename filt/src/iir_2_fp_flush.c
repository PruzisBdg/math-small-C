/*-------------------------------------------------------------------------------------------------
|
|  Flush 2nd-order floating point IIR filter 'f' with 'n'
|
-------------------------------------------------------------------------------------------------*/

#include "iirfilt_fp.h"

PUBLIC void IIRF2_Flush( S_IIRF2  *f, S16 n ) 
{
	f->buf[0] = n;
	f->buf[1] = n;
   f->tapIdx = 0;
}

// ------------------------------------- eof ----------------------------------------- 
