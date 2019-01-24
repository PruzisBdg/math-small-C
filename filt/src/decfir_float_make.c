/*-------------------------------------------------------------------------------------------------
|
|  DecFIRFP_Make
|
|  Make decimated floating point FIR filter 'f' from 'cfg'.
|
-------------------------------------------------------------------------------------------------*/

#include "firfilt.h"

PUBLIC void DecFIRFP_Make( S_DecFIRFP *f, S_DecFIRFP_Cfg CONST *cfg)
{
   FIRFP_Make(&f->fir, cfg->firBuf, cfg->firCoffs, cfg->taps);
   f->dec = cfg->dec;
   f->coffSum = &cfg->coffSum;
   DecFIRFP_Flush(f, 0);
}

// ------------------------------ eof --------------------------------------- 
