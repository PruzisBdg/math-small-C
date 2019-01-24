#include "math_common.h"
#include "util.h"
#include "arith.h"
#include "firfilt.h"

#if _TOOL_IS == TOOL_RIDE_8051
   #define _USE_ARRAY_INDICES
#else
   #error "Tool not defined"   
#endif

#ifdef _USE_ARRAY_INDICES   

// 'put' and 'end' are array indices, most efficient with 8 bit MCU's

typedef struct 
{
   U8          put,        /* next put                                     */
               end,        /* data buffer end                              */
               taps;       /* number of taps, should equal number of coffs */
   float       *buf;       /* data buffer start                            */
   float CONST *coffs;     /* FIR coffs, are in ROM                        */
} S_FIRFP;

#else

// 'put' and 'end' are pointer, most efficient with 16/32 bit , register-file MCU's

typedef struct 
{
   float *put,       /* next put                                     */
         *buf,       /* data buffer start                            */
         *end,       /* data buffer end                              */
         *coffs;     /* FIR coffs                                    */
   U8    taps;       /* number of taps, should equal number of coffs */
} S_FIRFP;

#endif


/*-------------------------------------------------------------------------------------------------
|
|  FIRFP_Flush
|
|  Fill entire buffer of 'f' with 'fillValue'
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void FIRFP_Flush( S_FIRFP *f, float fillValue )
{
   FillFloatsU8( f->buf, fillValue, f->taps );
}



/*-------------------------------------------------------------------------------------------------
|
|  FIRFP_Reset
|
|  Reset point FIR filter 'f'. Fill with 'initValue'
|
-------------------------------------------------------------------------------------------------*/

#include "firfilt.h"

PUBLIC void FIRFP_Reset( S_FIRFP *f, float initValue ) 
{
   #ifdef _USE_ARRAY_INDICES
   f->put = 0;
   #else
   f->put = f->buf;
   #endif
   
   FIRFP_Flush(f, initValue);
}

/*-------------------------------------------------------------------------------------------------
|
|  FIRFP_Make
|
|  Make floating point FIR filter 'f'.
|
|  PARAMETERS:   'f'     - the filter
|                'buf'   - buffer
|                'coffs' - filter coefficients
|                'taps'  - number of filter taps
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void FIRFP_Make( S_FIRFP *f, float *buf, float CONST *coffs, U8 taps )
{
   f->coffs = coffs;
   f->taps = taps;
   f->buf = buf;
   
   #ifdef _USE_ARRAY_INDICES
   f->end = taps - 1;
   #else
   f->end = f->buf + taps - 1;
   #endif

   FIRFP_Reset(f, 0);
}


/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  FIRFP_Run
|
|  Crunches new sample 'i' through FIR 'f' and return one new filtered result.
|
-------------------------------------------------------------------------------------------------*/

#ifdef _USE_ARRAY_INDICES
PUBLIC float FIRFP_Run( S_FIRFP * f, float i )
{

   U8    c;
   float acc;
   U8    p, coffs;

   f->buf[f->put] = i;  /* Add new 'i' */

   /* Get sum of products of coffs[] and buffer, starting from the most recent sample. 
      Note that the filter runs BACK through the samples from the youngest. This allows 
      the buffer to be longer than the filter, adding a delay if required.
   */
   for( c = f->taps,                   /* for each tap                  */
        coffs = 0,                     /* forward from start of coffs   */
        p = f->put,                    /* backward from youngest sample */
        acc = 0;                       /* init accumulator              */
        c; 
        c--, coffs++ ) 
   {
      acc += f->buf[p] * (S32)f->coffs[coffs];         /* Accumulate coff * sample.     */
      
      /* The put ptr is at the last sample in the buffer. Go back from there. */
      if( p == 0 ) p = f->end; else p--;  /* wrap? */
   }

   /* Now advance 'put' ptr to next empty slot */
   if( f->put >= f->end ) f->put = 0; else f->put++;     /* wrap? */

   /* Return result */
   return acc;
}


#else
PUBLIC float FIRFP_Run( S_FIRFP * f, float i )
{

   U8       c;
   float    acc, prev, term;
   float    *p;
   float    CONST *coffs;

   *f->put = i;  /* Add new 'i' */

   /* Get sum of products of coffs[] and buffer, starting from the most recent sample. 
      Note that the filter runs BACK through the samples from the youngest. This allows 
      the buffer to be longer than the filter, adding a delay if required.
   */
   for( c = f->taps,                   /* for each tap                  */
        coffs = &f->coffs[0],          /* forward from start of coffs   */
        p = f->put,                    /* backward from youngest sample */
        acc = 0;                       /* init accumulator              */
        c; 
        c--, coffs++ ) 
   {
      prev = acc; 
      term = *p * (S32)*coffs;         /* Accumulate coff * sample.     */
      acc += term;

      /* The put ptr is at the last sample in the buffer. Go back from there. */
      if( p == f->buf ) p = f->end; else p--;  /* wrap? */
   }

   /* Now advance 'put' ptr to next empty slot */
   if( f->put >= f->end ) f->put = f->buf; else f->put++;     /* wrap? */

   /* Return result */
   return acc;
}

#endif // _USE_ARRAY_INDICES


typedef struct
{
   float       *firBuf;    // FIR filter buffer       
   float CONST *firCoffs;  // FIR filter coefficients
   U8          taps,       // FIR filter taps (number of coffs)
               dec;        // decimation ratio
} S_DecFIRFP_Cfg;

typedef struct
{
   float       acc,        // decimator accumulator
               z1, z2;     // previous FIR filter outputs, for interpolation.
   S_FIRFP     fir;        // the FIR filter
   U8          cnt,        // the current decimator count
               dec;        // decimation ratio, copied from 'S_DecFIRFP_Cfg' 
} S_DecFIRFP;


/* ------------------------------------------------------------------------------
|
|  DecFIRFP_Flush
|
--------------------------------------------------------------------------------*/

PUBLIC void DecFIRFP_Flush( S_DecFIRFP *f, float initVal )
{
   FIRFP_Flush(&f->fir, initVal);
   f->cnt = 0;
   f->acc = 0;;
   f->z1 = initVal;
   f->z2 = initVal;
}


/*-------------------------------------------------------------------------------------------------
|
|  DecFIRFP_Make
|
|  Make decimated floating point FIR filter 'f' from 'cfg'.
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void DecFIRFP_Make( S_DecFIRFP *f, S_DecFIRFP_Cfg CONST *cfg)
{
   FIRFP_Make(&f->fir, cfg->firBuf, cfg->firCoffs, cfg->taps);
   f->dec = cfg->dec;
   DecFIRFP_Flush(f, 0);
}


/* ------------------------------------------------------------------------------
|
|  DecFIRFP_Run
|
|  Run 'in' thru 'f', returnng the result. The 'in' stream is decimated before
|  the FIR and (linearly) interpolated to give the output.
|
--------------------------------------------------------------------------------*/

PUBLIC float DecFIRFP_Run( S_DecFIRFP *f, float in)
{
   f->acc += in;                          // Update accumulator
   f->cnt++;                              // and decimator count
   
   if(f->cnt < f->dec)                    // Continue to accumulate?
   {                                      // Return interpolation from z2 -> z1.
      return f->z2 + ((f->z1 - f->z2) * f->cnt / f->dec);
   }
   else                                   // else decimate now
   {
      f->z2 = f->z1;                      // Shift history
      f->z1 = FIRFP_Run(&f->fir, f->acc / f->dec);    // Get new output from FIR
      f->acc = 0;                         // Zero accumulator and count for next decimation cycle.
      f->cnt = 0;
      return f->z2;                       // Return oldest; will interpolate forward from there.
   }
}


/* -------------------- IIRF2_:  2nd-order IIR Filter ---------------------

   Has 2 numerators, 2 denominators
*/
typedef float T_IIRFAcc;
typedef float T_IIRFCoffs;

typedef struct
{
   T_IIRFAcc         buf[2];     /* accumulators                              */
   T_IIRFCoffs CONST *coffs;     /* coffs                                     */
   U8                tapIdx;     /* indexes most recent sample in the buffer  */
} S_IIRF2;

/* 2 denominators (A1, A2) + 3 numerators (B0.. B2). A0 always equals '1' 
   so doesn't have to be in the coffs list.
*/
#define IIRF2_CoffsPerSection 5

typedef struct 
{
   T_IIRFCoffs  coffs[IIRF2_CoffsPerSection];
} S_IIRF2_Coffs;


/* ------------- iirNx2_: multiple 2nd order sections - parallel ----------------------- */

typedef struct
{
   S_IIRF2   *iir2;          /* the 2nd order sections  */
   U8       numSections;    /* how many  */
} S_IIRFNx2;



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

PUBLIC void IIRF2_Init( S_IIRF2  *f, T_IIRFCoffs CONST *coffs ) 
{
	f->buf[0] = 0;
	f->buf[1] = 0;
   f->coffs  = coffs;
   f->tapIdx = 0;
}


/*-------------------------------------------------------------------------------------------------
|
|  IIRFF2_Flush
|
|  Flush 'f' with 'n'
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void IIRFF2_Flush( S_IIRF2 *f, float n ) 
{
	f->buf[0] = n;
	f->buf[1] = n;
   f->tapIdx = 0;
}



/*-------------------------------------------------------------------------------------------------
|
|  IIRFF2_Run
|
|  Runs 2nd-order IIR 'f' on 'in'. Returns result. 
|
|  A 2nd order IIR, canonical form (Direct 2) has a 2-element buffer. 
|  (2 poles, 2 zeros) 'tapIdx' indexes the buffer; it is 0 or !0.
|
|  Order of coffs in S_IIRF2.coffs is:
|
|  D1, D2, N0, N1, N2   (D = demonimator, N = numerator)
|
|  A0 always equals (1 << _CoffFSBits) so doesn't have to be in the coffs list
|
|  PARAMETERS:    - 'f'    the filter
|                 - 'in'   input value
|
|  RETURNS:       - the filtered result
|     
-------------------------------------------------------------------------------------------------*/

#define LPROD(a,b)  ((a) * (b))

PUBLIC float IIRFF2_Run( S_IIRF2  *f, float in ) 
{
   T_IIRFAcc   z1, z2,     /* temp storage for buffer data  */
               m;          /* m = den(in)  */

   T_IIRFAcc   *p;

   T_IIRFCoffs CONST *cp;  /* to read filter coffs          */
   U8          tapIdx;     /* either the 1st or 2nd tap     */

   /* Get buffer contents into z1, z2. z1 has the youngest sample.  */
   p = f->buf;

   if( f->tapIdx )
      { z1 = *(p++); z2 = *p; }
   else
      { z2 = *(p++); z1 = *p; }

   /* Denominator: m = (A0 * in) + (A1 * z1) + (A2 + z2)  */
   cp = f->coffs;

   /* Denominator: m = (A0 * in) + (A1 * z1) + (A2 + z2)  */
   m = (T_IIRFAcc)in + LPROD(*cp,  z1) + LPROD(*(cp+1),  z2);

   /* Update buffer, replacing the oldest sample  */
   tapIdx = f->tapIdx;
   if( tapIdx ) { *(f->buf+1) = m; } else { *f->buf = m; }

   /* Flip tap idx 1 <-> 0  */
   f->tapIdx = tapIdx ^ 0x01;
 
   /* Numerator: y = (B0 * m) + (B1 * z1) + (B2 * z2)  */
   return LPROD(*(cp+2),  m ) + LPROD(*(cp+3),  z1) + LPROD(*(cp+4),  z2);
}


/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIRFNx2_Init
|
|     Make / initialise filter block 'f' using buffer RAM 'iir2Blocks' and filter coefficients
|     'coffs'
|
|  DESCRIPTION:
|
|  PARAMETERS:    - 'f'             the (resulting) filter
|                 - 'iir2Blocks'    allocated for filter buffers
|                 - 'coffs'         coffs for each section
|                 - 'numSections'   number of 2nd order sections
|
|  RETURNS:
|     
|
|	DATE		AUTHOR		DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void IIRFNx2_Init( S_IIRFNx2        *f,				   /* make this filter 					   */
                       S_IIRF2             *iir2Blocks,     /* using this RAM						   */
                       S_IIRF2_Coffs CONST *coffs, 		   /* set these as the filter coffs	   */
                       U8                  numSections )    /* number 2nd-order sections		   */
{
   S_IIRF2  *s;

   f->numSections = numSections;
   f->iir2 = iir2Blocks;

	/* Init each 2nd-order section */
   for( s = f->iir2 ;numSections; numSections--, coffs++, s++ ) 
   { 
      IIRF2_Init( s, coffs->coffs ); 
   }
}



/*-------------------------------------------------------------------------------------------------
|
|  IIRFFNx2_Flush
|
|  Flush multiple 2nd-order parallel filter 'f' with 'initVal'. 
|
|  This version takes a float as a parameter
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void IIRFFNx2_Flush( S_IIRFNx2  *f, float initVal ) 
{
   U8       c;

	/* Parallel: apply 'in' to each 2nd-order section, sum outputs */
   for( c = 0; c < f->numSections; c++ ) 
      { IIRFF2_Flush(&f->iir2[c], initVal); }
}

/*-------------------------------------------------------------------------------------------------
|
|  IIRFFNx2_Run
|
|  Run multiple 2nd-order parallel filter 'f' on 'in', returning result. 
|
|  This version takes a float as a parameter and return the result as a float.
|
|  PARAMETERS:    - 'f'     the filter
|                 - 'in'    input sample
|
|  RETURNS:       filter output (as a float)
|     
-------------------------------------------------------------------------------------------------*/

PUBLIC float IIRFFNx2_Run( S_IIRFNx2  *f, float in ) 
{
   U8       c;
   float    n;

	/* Parallel: apply 'in' to each 2nd-order section, sum outputs */
   for( c = 0, n = 0; c < f->numSections; c++ ) 
      { n += IIRFF2_Run( &f->iir2[c], in ); }
      
   return n;
}

/* ------------------------Pulse Filter ---------------------------------------

   This filter removes the baseline pressure from the raw pressure signal to
   leave the BP pulse. It is a 1Hz high-pass IIR; runs at 100/sec.
*/

/* ------------------------- 1Hz High Pass --------------------------------------

   2x2 cascade, fs = 100/sec, f0 = 1Hz, 4th-order Butterworth.
*/

PRIVATE CONST S_IIRF2_Coffs pulseHPCoffs[] =
{
   //    D1             D2          N0,          N1            N2
   {+1.911196288, -0.914975054, +0.9565428,  -1.913085671, +0.9565428355},    // sec 0
   {+1.9111962,   -0.91497505,  +0.95654283, -1.913085671, +0.95654283  }     // sec 1
};

#define _PulseHPSections RECORDS_IN(pulseHPCoffs)

// High pass filter to get pulse has...
typedef struct
{
   S_IIRF2     iir2s[_PulseHPSections];   // (2) 2nd order IIRs 
   S_IIRFNx2   theFilt;                   // in parallel to make a 4th order high-pass
} S_PulseHPFilt;



// The combined filter has.....
typedef struct
{
   S_PulseHPFilt pulseHP;     // ... a high-pass section to extract the pulse and
   S_DecFIRFP    baseLPass;   // ... a low-pass section to get the baseline
} S_PresFilt;

PRIVATE S_PresFilt presFilt;  // One instance of the-above.



/*-------------------------------------------------------------------------------------------------
|
|  PresFilt_GetPulse
|
|  Run at 100/sec. Given 'raw' 24bit pressure reading, returns the same signal minus baseline
|  pressure. The result is scaled to fit the pulse inside 16 bits.
|
-------------------------------------------------------------------------------------------------*/

PUBLIC S16 PresFilt_GetPulse(S32 raw)
{
   #define _FullScale_cnts 1.67E7
   #define _FullScale_mmHg  350.0
   #define _PulseRange_mmHg 10.0
   
   #define M1 (_FullScale_mmHg * MAX_S16) / (_PulseRange_mmHg *_FullScale_cnts)

   return ClipFloatToInt( M1 * IIRFFNx2_Run(&presFilt.pulseHP.theFilt, raw) );
}

// ---------------------------- end: Pulse Filter ----------------------------------





/* ------------------------- Baseline Pressure Filter --------------------------------

   This filter removes the pulse from the raw pressure signal to leave the underlying
   baseline pressure signal.
   
   This is a FIR filter and so will recover from large pressure transients in a finite
   time (about 0.8sec).
   
   The filter runs at 100/sec but has a 0.4Hz cutoff. To keep the number of taps
   manageable, it has a /10 pre-decimator. So the FIR runs at 10/sec. The FIR
   output is interpolated (linear) to 100/sec.
*/

/* Filter coffs: 
      Low pass: fs = 10/sec, fo = 0.4Hz, fstop = 1Hz, Stopband = -30dB, t10-t90 = 0.8sec.
*/
PRIVATE float CONST lpCoffs[] = 
{ 0.042241, 0.046134, 0.065026, 0.083291, 0.098525, 0.108672, 0.112221, 
  0.108672, 0.098525, 0.083291, 0.065026, 0.046134, 0.042241 };

#define _LPTaps RECORDS_IN(lpCoffs)

PRIVATE float lpBuf[_LPTaps];          // Signal is filtered in this buffer

PRIVATE S_DecFIRFP_Cfg CONST lpCfg =   // Define the filter...
{
   lpBuf,                              // uses this buffer
   lpCoffs,                            // and these coffs
   _LPTaps,                            // is this long
   10                                  // pre-decimator, ahead of the FIR
};


/*-------------------------------------------------------------------------------------------------
|
|  PresFilt_GetBaseline
|
|  Run at 100/sec. Given 'raw' 24bit pressure reading, returns the same signal minus pulse
|  (i.e gain = 1.0)
|
-------------------------------------------------------------------------------------------------*/

PUBLIC S32 PresFilt_GetBaseline(S32 raw)
{
   return ClipFloatToLong( DecFIRFP_Run(&presFilt.baseLPass, (float)raw) );
}

// ---------------------------- end: Baseline Pressure Filter ----------------------------------




// ------------------------- Operations on the combined filter -------------------------------------

/*-------------------------------------------------------------------------------------------------
|
|  PresFilt_Make
|
|  Call once to make the BP baseline filter.
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void PresFilt_Make(void)
{
   IIRFNx2_Init( &presFilt.pulseHP.theFilt,     // Make pulse high-pass filter
                 presFilt.pulseHP.iir2s,        // by cascading these 2nd-order sections
                 pulseHPCoffs,                  // using these coffs
                 _PulseHPSections);             // (2) sections
                 
   DecFIRFP_Make(&presFilt.baseLPass, &lpCfg);  // Make baseline low-pass filter.
}


/*-------------------------------------------------------------------------------------------------
|
|  PresFilt_Flush
|
|  Fill the baseline (low pass) filter with 'initVal'. Zero the pulse (high pass) filter.
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void PresFilt_Flush(S32 initVal)
{
   DecFIRFP_Flush(&presFilt.baseLPass, (float)initVal);
   IIRFFNx2_Flush(&presFilt.pulseHP.theFilt, 0);
}


// -------------------------------------- eof -------------------------------------------
