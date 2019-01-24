/* --------------------------------------------------------------------------
|
|              Tiny 1 Library - Tool / Type Mappings
|
|  This file handles non-standard, tool-specific 'C' language extensions for
|  all Tiny1 libraries and optionally, for projects that use them.  The
|  Tool (compiler) must be #defed to the compiler.
|
----------------------------------------------------------------------------- */

#ifndef BLDCFG_H
#define BLDCFG_H

/* ---------------------- Tools and Targets --------------------------- */

/* --------------- The Tools */

#define TOOL_RIDE_8051   1     /* Raisoance 8051                     */
#define TOOL_Z8_ENCORE   2     /* Zilog Z8 Encore, under ZDSII IDE   */
#define TOOL_ICC08       3     /* Imagecraft ICC08 for HC08          */
#define TOOL_COSMIC_HC08 4     /* Cosmic IdeaHC08 for HC08           */
#define TOOL_CW08        5     /* CodeWarrior for HC08               */
#define TOOL_CBUILDER_5  6     /* Borland C++ Builder 5              */
#define T00L_CC430       7     /* Code Composer for MSP430           */
#define TOOL_RIDE_STM32  8     /* Ride7 with ARM gcc                 */
#define TOOL_SPLINT      9     /* Splint syntax checker              */
#define TOOL_XC16        10    /* Microchip XC16                     */
#define TOOL_X86_GCC     11

/* Legacy RIDE projects, needed in assert.h. But don't redef it, if the legacy
   project already provides it.
*/
#ifndef _TOOL_RIDE_8051
   #define _TOOL_RIDE_8051  20
#endif

/* Note that the tools list above must include all tools used anywhere. This is
   because, for CC430 compiler at least, the expression

      #if _TOOL_IS == THIS_DEF_DOESNT_EXIST   evaluates to TRUE

   and thus the compiler parses text which should be invisible to it.
*/
#ifdef __TOOL_IS_X86_GCC__
    #define _TOOL_IS TOOL_X86_GCC
#endif

#ifdef TOOL_IS_RIDE_8051
   // Don't redef this if it's already provided in a legacy project.
   #ifndef _TOOL_IS
      #define _TOOL_IS TOOL_RIDE_8051
   #endif
#endif

#ifdef TOOL_IS_Z8ENCORE
   #define _TOOL_IS TOOL_Z8_ENCORE
#endif

#ifdef TOOL_IS_ICC08
   #define _TOOL_IS TOOL_ICC08
#endif

#ifdef TOOL_IS_COSMIC_HC08
   #define _TOOL_IS TOOL_COSMIC_HC08
#endif

#ifdef TOOL_IS_CW08
   #define _TOOL_IS TOOL_CW08
#endif

#ifdef TOOL_IS_CC430
   #define _TOOL_IS TOOL_CC430
#endif

#ifdef TOOL_IS_RIDE_STM32
   #define _TOOL_IS TOOL_RIDE_STM32
#endif

// If we have defined a TOOL yet assume that the code is generic.
// Then if we're running Splint, then make it the TOOL.
#ifndef _TOOL_IS
   #ifdef TOOL_IS_SPLINT
      #define _TOOL_IS TOOL_SPLINT
   #endif
#endif

#ifdef TOOL_IS_MCHIP_XC16
   #define _TOOL_IS TOOL_XC16
#endif

/* The compiler must have identified itself  */

#ifndef _TOOL_IS
   #error "Toolchain not defined"
#endif


/* ---------------- Tool-specifc 'C' Language extensions ----------------------- */

#if _TOOL_IS == TOOL_RIDE_8051

      #ifdef TOOL_IS_SPLINT   // Running a Splint check on Raisonance RC51 code?

   /* For a Splint check, all the RIDE-specific 'C' language extensions must be
      nullified or made sensible.
   */
   #define CONST const
   #define CODE
   #define CONST_FP const
   #define CODE_FP

   /* 8051 memory space qualifiers */
   #define IDATA
   #define rIDATA
   #define XDATA
   #define rXDATA
   #define DATA
   #define BIT    BOOLEAN     // For Splint, BIT can actually be boolean

   // 8051 generic (3 byte) pointer
   #define GENERIC

   #define _U8Ptr

   #define sfr   int
   #define sfr16 int
   #define sbit  int
   #define at

      #else                   // else actually compiling with Raisonance RC51

   /* 8051 has Harvard architecture and limited RAM. Ensure that consts are not
      copied to external RAM - and so use it all up.
   */
   #define CONST const code
   #define CODE code
   #define CONST_FP const
   #define CODE_FP code

   /* 8051 memory space qualifiers */
   #define IDATA     idata
   #define rIDATA    idata    // use for locals vars (r = register)
   #define XDATA     xdata
   #define rXDATA    xdata    // use for local vars  (r = register)
   #define DATA      data
   #define BIT       bit

   // 8051 generic (3 byte) pointer
   #define GENERIC generic

   #define _U8Ptr

      #endif                  // TOOL_IS_SPLINT

#elif _TOOL_IS == TOOL_Z8_ENCORE

   /* Z8 Encore is Harvard (separate code/data) */
   #define HARVARD_CPU

   /* Z8 Encore has Harvard architecture and limited RAM. Ensure that consts are not
      copied to external RAM - and so use it all up.
   */
   #define CONST rom
   #define CODE rom
   #define CONST_FP
   #define CODE_FP

   /* Z8 Encore memory space qualifiers */
   #define IDATA     near
   #define rIDATA                // In ZDS local vars don't have a memory qualifier
   #define XDATA     far
   #define rXDATA                // in ZDS local vars don't have a memory qualifier
   #define DATA      near
   #define BIT       U8          // no Bit variables in Z8

   // No generic pointer support
   #define GENERIC

   // Strings type = C8*, must be cast to U8* to avoid pointer mismatch warnings
   #define _U8Ptr (U8*)

#elif _TOOL_IS == TOOL_ICC08

   /* HC08 has limited RAM. Ensure that consts are not copied to external RAM - and so use it all up.
   */
   #define CONST const
   #define CODE const
   #define CONST_FP

   /* HC08 memory space qualifiers */
   #define IDATA
   #define rIDATA                // In ZDS local vars don't have a memory qualifier
   #define XDATA
   #define rXDATA                // in ZDS local vars don't have a memory qualifier
   #define DATA
   #define BIT       U8          // no Bit variables in HC08

   // No generic pointer support
   #define GENERIC

#elif _TOOL_IS == TOOL_COSMIC_HC08 || _TOOL_IS == TOOL_CW08 || _TOOL_IS == TOOL_CC430

   /* With limited RAM. Ensure that consts are not copied to external RAM - and so use it all up.
   */
   #define CONST const
   #define CODE const
   #define CONST_FP const

   /* HC08 memory space qualifiers */
   #define IDATA
   #define rIDATA
   #define XDATA
   #define rXDATA
   #define DATA
   #define BIT       U8          // no Bit variables in HC08

   // No generic pointer support
   #define GENERIC

#elif _TOOL_IS == TOOL_CBUILDER_5

   // No code space qualifiers
   #define CONST const
   #define CODE  const
   #define CONST_FP const

   /* no memory space qualifiers */
   #define IDATA
   #define rIDATA
   #define XDATA
   #define rXDATA                // in ZDS local vars don't have a memory qualifier
   #define DATA

   #define BIT       bool        // is the C++ bool type

   // No generic pointer support
   #define GENERIC

   #define _TARGET_IS_PC    // will build large vectors

#elif _TOOL_IS == TOOL_RIDE_STM32

   // For a generic target
   #define CONST const
   #define IDATA
   #define XDATA
   #define DATA
   #define BIT  U8
   #define GENERIC

   #define NEAR

#elif _TOOL_IS == TOOL_SPLINT

   // Generic code checked by Splint. Standard C only
   #define CONST const
   #define IDATA
   #define XDATA
   #define DATA
   #define BIT  BOOLEAN    // For Splint BIT can be a true boolean type
   #define GENERIC

   #define NEAR

#else

   // For a generic target
   #define CONST const
   #define IDATA
   #define XDATA
   #define BIT  U8
   #define NEAR

#endif

/* ------------------------ End of tools and targets ---------------------------  */

#endif // BLDCFG_H

// ------------------------------- eof ------------------------------------------
