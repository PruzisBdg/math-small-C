/* -------------------------------------------------------------------------
|
|  Integer FIR Filter 
|   
|
|
|
|
|
|   
|      Rev 1.0   May 19 2009 12:56:24   spruzina
|   Initial revision.
|  
----------------------------------------------------------------------------- */

#ifndef FIRFILT_H
#define FIRFILT_H

#include "math_common.h"

/* '_cdecl' is required when included in C++ files */
#ifdef _DECL_EXTERN_C
   #define _DECL(ret)   extern "C" ret _cdecl
#else
   #define _DECL(ret)   PUBLIC ret
#endif

#ifndef _TOOL_IS
   #error "_TOOL_IS not defined for _USE_ARRAY_INDICES in firfilt.h"
#else
   #if _TOOL_IS == TOOL_RIDE_8051 || _TOOL_IS == TOOL_CC430
      #define _USE_ARRAY_INDICES
   #endif
#endif

// To tune speed vs size & safety
typedef struct {
   U8       checkOverrange :1,   // Check (32bit) for overrange (slower)
            noOutClip      :1;   // Do not clip output to S16 (faster)
} S_FIRFlags;

// Buffer may be S16[] to accumulate input samples, or S32[], to accumulate products
typedef union {S16 *_s16; S32 *_s32; } U_pS16pS32;

typedef struct    // Used by FIR_MakeB(); may tune operation with flags
{
   U_pS16pS32  buf;
   S16 CONST   *coffs;
   U8          taps,
               rShift;
   S_FIRFlags  flags;
} S_FIRCfg;

#ifdef _USE_ARRAY_INDICES   

// 'put' and 'end' are array indices, most efficient with 8 bit MCU's

typedef struct 
{
   U8          put,        /* next put                                     */
               end;        /* data buffer end                              */
   S_FIRCfg    cfg;
} S_FIR;

#else

// 'put' and 'end' are pointer, most efficient with 16/32 bit , register-file MCU's

typedef struct 
{
   S16       *put,       /* next put                                     */
             *end;       /* data buffer end                              */
   S_FIRCfg   cfg;
} S_FIR;

#endif


#define _FIR_Coff(n) ((S16)(CLIP( (32768.0F * (n)), MIN_INT, MAX_INT )))

_DECL(void) FIR_Make    ( S_FIR *f,  S16 *buf, S16 CONST *coffs, U8 taps, U8 rShift );
_DECL(void) FIR_MakeB   ( S_FIR *f,  S_FIRCfg CONST *cfg );
#define     FIR_Destroy(f)                /* no malloc() so nothing to do */
_DECL(void) FIR_Reset   ( S_FIR *f,  S16 initValue           );
_DECL(S16)  FIR_Run     ( S_FIR *f,  S16 i                   );
_DECL(void) FIR_Fill    ( S_FIR *f,  S16 const *fillVec      );
_DECL(void) FIR_Flush   ( S_FIR *f,  S16 fillValue           );
_DECL(void) FIR_SetCoffs( S_FIR *f,  S16 CONST *coffs        );

#endif

/* ------------------------------------------------------------------------------
|
|                 Floating-point FIR Filter
|
--------------------------------------------------------------------------------*/

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
   float *put,          /* next put                                     */
         *buf,          /* data buffer start                            */
         *end;          /* data buffer end                              */
   float CONST *coffs;  /* FIR coffs                                    */
   U8    taps;          /* number of taps, should equal number of coffs */
} S_FIRFP;

#endif

PUBLIC void FIRFP_Make( S_FIRFP *f, float *buf, float CONST *coffs, U8 taps );
PUBLIC void FIRFP_Reset( S_FIRFP *f, float initValue );
PUBLIC void FIRFP_Flush( S_FIRFP *f, float fillValue );
PUBLIC float FIRFP_Run( S_FIRFP * f, float i );


/* ------------------------------------------------------------------------------
|
|                 Integer FIR Filter with pre-decimator
|
--------------------------------------------------------------------------------*/

typedef struct
{
   S_FIRCfg  fir;    // FIR filter, post-decimation.
   U8        dec;    // Decimation ratio.
} S_DecFIRCfg;

typedef union
{
   S16 asS16;
   S32 asS32;
} U_S16_S32;

typedef struct
{
   U_S16_S32   acc;           // decimator accumulator, may be 16 or 32bit
   S_FIR       fir;           // the FIR filter
   U8          cnt,           // the current decimator count
               dec,           // decimation ratio, copied from 'S_DecFIRCfg' 
               rShift;        // if 'dec' is an exact power of 2, equals 'dec' as power of 2 , else = 0
} S_DecFIR;


PUBLIC void DecFIR_Make( S_DecFIR *f, S_DecFIRCfg CONST *cfg);
PUBLIC void DecFIR_Flush( S_DecFIR *f );
PUBLIC BIT DecFIR_Run( S_DecFIR *f, S16 *out, S16 in);
PUBLIC BIT DecFIR_RunS( S_DecFIR *f, S16 *out, S16 in);

/* ------------------------------------------------------------------------------
|
|                 Floating-point FIR Filter with pre-decimator
|
--------------------------------------------------------------------------------*/

typedef struct
{
   float       *firBuf;    // FIR filter buffer       
   float CONST *firCoffs;  // FIR filter coefficients
   float       coffSum;    // Sum of coffs.
   U8          taps,       // FIR filter taps (number of coffs)
               dec;        // decimation ratio
} S_DecFIRFP_Cfg;

typedef struct
{
   float       acc,        // decimator accumulator
               z1, z2;     // previous FIR filter outputs, for interpolation.
   float CONST *coffSum;   // Sum of coffs, for flushing the decimator
   S_FIRFP     fir;        // the FIR filter
   U8          cnt,        // the current decimator count
               dec;        // decimation ratio, copied from 'S_DecFIRFP_Cfg' 
} S_DecFIRFP;


PUBLIC void DecFIRFP_Make( S_DecFIRFP *f, S_DecFIRFP_Cfg CONST *cfg);
PUBLIC void DecFIRFP_Flush( S_DecFIRFP *f, float initVal );
PUBLIC float DecFIRFP_Run( S_DecFIRFP *f, float in);

// --------------------------------------- eof ---------------------------------------
 
