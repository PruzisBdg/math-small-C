/* -----------------------------------------------------------------------------------
|
| Support for (Renesas) ARM Tiny2 static and linked libraries.
|
| This file is specific to a project and has the same name in every project. Here it provides
| compile-time parameterisation for the Tiny2 library. The library calls will be 'weak'. If
| an application needs a different parameterization for a library function the app. should compile
| the necessary C-code directly and override the library version.
|
 -------------------------------------------------------------------------------------*/

#ifndef LIBS_SUPPORT_H
#define LIBS_SUPPORT_H

#include "GenericTypeDefs.h"

// Global suspend/resume of interrupts.
#define _BlockAllInterrupts()
#define _UnblockEnabledInterrupts()

#define _SystemTick_msec 10.0      		// Renesas Synergy ThreadX default SysTick.

#define CODE_SPACE_20BIT 1
#define CODE_SPACE_IS CODE_SPACE_20BIT

#define DATA_SPACE_16BIT 1
#define DATA_SPACE_32BIT 2
#define DATA_SPACE_IS DATA_SPACE_32BIT

#define BOOLEAN BOOL

#define _TARGET_8051_LIB_LGE_NANO 1
#define _TARGET_LIB_ARM 2

#define _TARGET_IS _TARGET_LIB_ARM

#define _HAS_TEXT_UI 1

#define _U8Ptr (U8*)

#define TicksPerSec 100

#define ResetTimer(timer) { *(timer) = _Now(); }

#define RAM_IS

#endif // LIBS_SUPPORT_H

// ------------------------------- eof -----------------------------------------------

