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
#define N 2		// IIR filter order
#define M 3

float B[M][N+1] = {{1, 0, -1}, {1, 2, 1}, {1, -2, 1}};  // numerator coefficients
float A[M][N+1] = {{1, -.3692, .1317}, {1, .5139, .5305}, {1, -1.2803, .6573}};  // denominator coefficients
float x[M][N+1] = {{0,0,0}, {0,0,0}, {0,0,0}};   // input value (buffered)
float y[M][N+1] = {{0,0,0}, {0,0,0}, {0,0,0}};   // output values (buffered)
float G[M+1] = {.1085, 1, 1, 1};

void biquad(int i);

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
  	x[0][0] = CodecDataIn.Channel[0];

	int m = 0;
	for (m = 0; m<M; m++){
		biquad(m);
	}

	CodecDataOut.Channel[0] = y[M-1][0] * G[M];
	/* end of my IIR filter routine	*/

	WriteCodecData(CodecDataOut.UINT);		// send output data to  port
}


float result;
void biquad(int m) {
	result = 0;
	int i = 0;

	// calculat result from x values
	for (i =0; i <= N; i++) {
		result += x[m][i] * B[m][i];
	}

	// calculate result form y values
	for (i = 1; i <= N; i++) {
		result += y[m][i] * -1 * A[m][i];
	}

	y[m][0] = G[m]*result;

	// shift old values, in current biquad
	for (i = N; i>=0; i--) {
		x[m][i+1] = x[m][i];
		y[m][i+1] = y[m][i];
	}

	// copy y[m][0] to x[m+1][0]
	// current biquad output is next biquad input
	if(m < M-1) {
		x[m+1][0] = y[m][0];
	}
	else {
		//do nothing we are in last biquad
	}
}

