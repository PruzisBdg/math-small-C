#include "bldcfg.h"
#include "common.h"
#include "mathfunc.h"

/* ----------------------------------------------------------------------------

	SimpsonS16()
	
	Integrate 'f' from 'start' by 'intvl' thru 'steps' by Simpsons rule. 'steps' 
	must be even; if it's odd then it will be truncated to an even number.
	
	Simpson's is:
	                         intvl  steps-2
		Integral f(x)dx  =    ----  *  SUM  ( f[i] + 4f[i+1] + f[i+2]) + O(h^3) )
		                       3      i = 0
		                       
	Consolidated duplicate evaluations of 'f' gives:
	
	                       intvl
	   Integral f(x)dx =    ----  * ( f[0] + 4f[1] + 2f[2] + 4f[3] .... 2f[steps-1] + f[steps]
	                         3
	
			i.e  1,2,4,2,4.... 4,2,1
			
	Note that 'f' is evaluated at 'steps'+1 points.			                      
*/

PUBLIC S32 SimpsonS16( S16(*f)(S16), S16 start, S16 intvl, S16 steps)
{
   S32 sum;
	S16 i;
	S16 x;
	
	steps &= 0xFFFE; 					// Truncate 'steps' to even number.
	
	sum = f(start);					// f[0]
	
	for(x = start+intvl, 			// Onto f[1]
	    i = 1; 							// For f[1]...
	    i < steps; 					// thru f[steps-1]
	    i++, 
	    x += intvl )
	{
		// If i is odd then add 4*f[i], else 2*f[1]
		sum += (S32)f(x) << (i & 0x0001 ? 2 : 1);		
	}
	sum += f(x);						// Add f[steps]
	
	// Multiply by intvl/3 -> done
	// Do the arithmetic in an order which won't overrange.
	return (intvl * sum) / 3;
} 


// --------------------------------------- eof ----------------------------------------------------- 
