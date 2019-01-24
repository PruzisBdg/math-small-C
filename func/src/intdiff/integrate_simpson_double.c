#include "bldcfg.h"
#include "common.h"
#include "mathfunc.h"

typedef double T_Integral;

/* ----------------------------------------------------------------------------

	SimpsonDouble()
	
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

PUBLIC T_Integral SimpsonDouble( T_Integral(*f)(T_Integral), T_Integral start, T_Integral intvl, S16 steps)
{
	T_Integral x,
              sum;
	S16        i;
	
	steps &= 0xFFFE; 					// Truncate 'steps' to even number.
	
	sum = f(start);					// f[0]
	
	for(x = start+intvl, 			// Onto f[1]
	    i = 1; 							// For f[1]...
	    i < steps; 					// thru f[steps-1]
	    i++, 
	    x += intvl )
	{
		// If i is odd then add 4*f[i], else 2*f[1]
		sum += f(x) * (i & 0x0001 ? 4.0 : 2.0);		
	}
	sum += f(x);						// Add f[steps]
	
	// Multiply by intvl/3 -> done
	return intvl * sum / 3.0;
} 


// --------------------------------------- eof -----------------------------------------------------   
