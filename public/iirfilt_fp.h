/* -------------------------------------------------------------------------
|
|  Floating point IIR Filter - Multiple 2nd order sections - parallel
|
|  Pruzina 8/9/04
|
|  This is the IIR_ package with floating point accumulators and coefficients
|  in place of 16bit coffs and 32bit accumulators. In an IIR filter when the
|  transistion frequency is small compared to the sample rate the coffs are
|  small and the accumulator values large. The coffs are therefore not precise
|  and the 32 bit accumulators can overrange. This version of the IIR filter avoids
|  these issues at the expense of speed
|
|  Set T_IIRFAcc to float or double depending on the precision required.
|
|  Public functions:
|
|	   single 2nd order IIR, canonical (direct II)
|
|	      IIRF2_Init()		- initialise coffs etc
|	      IIRF2_Run()		- run, return result
|
|	   2xn order IIR, multiple 2nd-order, parallel
|
|	      IIRFNx2_Init()
|	      IIRFNx2_Run()
|
|
|
|
|
|
|   
|      Rev 1.1   Jan 10 2011 07:58:38   spruzina
|   Add structs for multi-section filters.
|   
|      Rev 1.0   May 19 2009 12:56:26   spruzina
|   Initial revision.
|  
----------------------------------------------------------------------------- */

#ifndef IIRFILT_FP_H
#define IIRFILT_FP_H

/* If basic types are supplied by the Host project instead \public\common.h then don't 
   resupply them from common.h.
*/ 
#ifndef _BASIC_TYPES_FROM_HOST_PROJECT
   #include "math_common.h"
#endif


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

typedef struct
{
   S_IIRF2_Coffs CONST *coffsOneSection;  // To an array of coefficient sets, one for each section
   U8                   numSections;      // The number of sections
} S_IIRF2_Coffs_Multi;

PUBLIC void IIRF2_Init( S_IIRF2  *f, T_IIRFCoffs CONST *coffs );

// Integer arguments, floating-point internal
PUBLIC void IIRF2_Flush( S_IIRF2  *f, S16 n );
PUBLIC S16 IIRF2_Run(  S_IIRF2  *f, S16 in );

// Floating-point arguments, floating-point internal
PUBLIC void IIRFF2_Flush( S_IIRF2 *f, float n ); 
PUBLIC float IIRFF2_Run( S_IIRF2  *f, float in ); 


/* ------------------------ end: IIRF2_ ---------------------------------------- */






/* ------------- iirNx2_: multiple 2nd order sections - parallel ----------------------- */

typedef struct
{
   S_IIRF2   *iir2;          /* the 2nd order sections  */
   U8       numSections;    /* how many  */
} S_IIRFNx2;


/* Wrappers for 4th, 6th and 8th order filters - the commonest for us. */
typedef struct
{
   S_IIRFNx2  filt;
   S_IIRF2    sections[2];
} S_IIRF2x2ndPar;

typedef struct
{
   S_IIRFNx2  filt;
   S_IIRF2    sections[3];
} S_IIRF3x2ndPar;

typedef struct
{
   S_IIRFNx2  filt;
   S_IIRF2    sections[4];
} S_IIRF4x2ndPar;


PUBLIC void IIRFNx2_Init( S_IIRFNx2  *f, S_IIRF2  *iir2Blocks, S_IIRF2_Coffs CONST *coffs, U8 numSections );

// Integer IO, Parallel
PUBLIC S16  IIRFNx2P_Run(  S_IIRFNx2  *f, S16 in );

// Floating-point IO
PUBLIC void IIRFFNx2_Flush( S_IIRFNx2  *f, float initVal );
PUBLIC float IIRFFNx2P_Run( S_IIRFNx2  *f, float in );         // Parallel 2nd-order sections
PUBLIC float IIRFFNx2C_Run( S_IIRFNx2  *f, float in );         // Cascade 2nd-order sections

/* --------------------------- end: iirNx2_ --------------------------------------- */


/* ------------------ Vector IIR; each section multiple-2nd-order -------------------- */

/* --------- 2-section Init/Run */
void IIRF2x2ndVec_Init( S_IIRF2x2ndPar       *f,               /* Init this vector-filter          */
                        S_IIRF2_Coffs  CONST *coffs,           /* each channel has the same coffs  */
                        U8                   vecSize );

PUBLIC void IIRF2x2ndVec_Init_MultiCoffs( 
                        S_IIRF2x2ndPar               * f,         /* Init this vector-filter  */
                        S_IIRF2_Coffs  CONST * CONST * coffs,     /* each channel has different coffs */
                        U8                             vecSize );
                        
void IIRF2x2ndVec_Run( S_IIRF2x2ndPar *f,                /* Run this vector-filter           */
                       S16            *in,               /* from here                        */
                       S16            *out,              /* to here                          */
                       U8             vecSize );
                       
/* ------ 3-section Init / Run */
void IIRF3x2ndVec_Init( S_IIRF3x2ndPar       *f,               /* Init this vector-filter                */
                        S_IIRF2_Coffs  CONST *coffs,           /* each channel has the same coffs        */
                        U8                   vecSize );

PUBLIC void IIRF3x2ndVec_Init_MultiCoffs( 
                        S_IIRF3x2ndPar               * f,            /* Init this vector-filter             */
                        S_IIRF2_Coffs  CONST * CONST * coffs,        /* each channel has different coffs    */
                        U8                             vecSize );
                        
void IIRF3x2ndVec_Run( S_IIRF3x2ndPar *f,                /* Run this vector-filter           */
                       S16            *in,               /* from here                        */
                       S16            *out,              /* to here                          */
                       U8             vecSize );
                       
// ------- Arbitrary number of sections Init() / Run()

PUBLIC void IIRFNx2ndVec_Init( 
               S_IIRFNx2                 *filt,       /* Init this vector-filter                   */
               S_IIRF2           * const *sections,   /* with these sections for each filter       */
               S_IIRF2_Coffs_Multi CONST *coffs,      /* each channel has these coffs              */
               U8                         vecSize );  /* Vector is this wide                       */
               
PUBLIC void IIRFNx2ndVec_Init_MultiCoffs( 
               S_IIRFNx2                 *filt,       /* Init this vector-filter                   */
               S_IIRF2           * const *sections,   /* with these sections for each filter       */
               S_IIRF2_Coffs_Multi CONST *coffs,      /* each channel has different bank of coffs  */
               U8                         vecSize );  /* Vector is this wide                       */
               
PUBLIC void IIRFNx2ndVec_Run( S_IIRFNx2   *f,             /* Run this vector-filter  */
                             S16          *in,            /* from here */
                             S16          *out,           /* to here */
                             U8           vecSize );
               

#endif // IIRFILT_FP_H ---------------- eof --------------------------------------------


