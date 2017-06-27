// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2011
 
///////////////////////////////////////////////////////////////////////
// Filename: main.c
//
// Synopsis: Main program file for frame-based processing using EDMA
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h" 
#include "frames.h" 

int main()
{    
	float x =0;
	x = sinf(1.7);

	float y = x;
	// initialize EDMA controller 

	
	// initialize DSP for EDMA operation
  	DSP_Init_EDMA();

    // call to StartUp not needed here

	// main loop here, process buffer when ready 
  	while(1) { 

  	}   
}


