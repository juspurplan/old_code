// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2011

///////////////////////////////////////////////////////////////////////
// Filename: ISRs.c
//
// Synopsis: Interrupt service routine for codec data transmit/receive
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h" 
  
// Data is received as 2 16-bit words (left/right) packed into one
// 32-bit word.  The union allows the data to be accessed as a single 
// entity when transferring to and from the serial port, but still be 
// able to manipulate the left and right channels independently.

#define LEFT  0
#define RIGHT 1

volatile union {
	Uint32 UINT;
	Int16 Channel[2];
} CodecDataIn, CodecDataOut;


/* add any global variables here */
#define N 6		// IIR filter order

float B[N+1] = {.1085, 0, -.3255, 0, .3255, 0, -.1085};  // numerator coefficients
float A[N+1] = {1, -1.1355, .9443, -.6378, .5444, -.1737, .0459};  // denominator coefficients
float x[N+1] = {0, 0, 0, 0, 0, 0, 0};   // input value (buffered)
float y[N+1] = {0, 0, 0, 0, 0, 0, 0};   // output values (buffered)

void iir_df_one();

interrupt void Codec_ISR()
///////////////////////////////////////////////////////////////////////
// Purpose:   Codec interface interrupt service routine  
//
// Input:     None
//
// Returns:   Nothing
//
// Calls:     CheckForOverrun, ReadCodecData, WriteCodecData
//
// Notes:     None
///////////////////////////////////////////////////////////////////////
{                    
	/* add any local variables here */


 	if(CheckForOverrun())					// overrun error occurred (i.e. halted DSP)
		return;								// so serial port is reset to recover

  	CodecDataIn.UINT = ReadCodecData();		// get input data samples
	
	/* I added my IIR filter routine here */
  	x[0] = CodecDataIn.Channel[0];
  	iir_df_one();
  	CodecDataOut.Channel[0] = (y[0]);


	/* end of my IIR filter routine	*/

	WriteCodecData(CodecDataOut.UINT);		// send output data to  port
}


float result = 0;
void iir_df_one() {
	result = 0;
	int i = 0;

	// calculat result from x values
	for (i =0; i <= N; i++) {
		result += x[i] * B[i];
	}

	// calculate result form y values
	for (i = 1; i <= N; i++) {
		result += y[i] * -1 * A[i];
	}

	y[0] = result;

	// shift old values
	for (i = N; i>=0; i--) {
		x[i+1] = x[i];
		y[i+1] = y[i];
	}

}

