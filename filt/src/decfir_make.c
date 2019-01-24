/* ------------------------------------------------------------------------------
|
|                 FIR Filter with pre-decimator
|
--------------------------------------------------------------------------------*/

#include "firfilt.h"

PRIVATE U8 getExactPowerOfTwo(U8 n)
{
   switch(n)
   {
      case 2: return 1;
      case 4: return 2;
      case 8: return 3;
      case 16: return 4;
      case 32: return 5;
      case 64: return 6;
      case 128: return 7;
      default: return 0;
   }
}

PUBLIC void DecFIR_Make( S_DecFIR *f, S_DecFIRCfg CONST *cfg)
{
   FIR_Make(&f->fir, cfg->firBuf, cfg->firCoffs, cfg->taps, cfg->rShift);
   f->dec = cfg->dec;
   f->rShift = getExactPowerOfTwo(f->dec);
   DecFIR_Flush(f);
}

// ------------------------------ eof -----------------------------------------
