/*-------------------------------------------------------------------------------------------------
|
|  IIRFFNx2_Flush
|
|  Flush multiple 2nd-order parallel filter 'f' with 'initVal'. 
|
|  This version takes a float as a parameter; see IIRFNx2_Flush for a version which
|  takes an integer for 'initVal'.
|
-------------------------------------------------------------------------------------------------*/

#include "iirfilt_fp.h"

PUBLIC void IIRFFNx2_Flush( S_IIRFNx2  *f, float initVal ) 
{
   U8 c;

   for( c = 0; c < f->numSections; c++ ) 
      { IIRFF2_Flush(&f->iir2[c], initVal); }
}

// ----------------------------- eof ---------------------------------------- 
