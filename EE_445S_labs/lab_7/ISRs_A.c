// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2011

///////////////////////////////////////////////////////////////////////
// Filename: ISRs.c
//
// Synopsis: Interrupt service routine for codec data transmit/receive
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h" 
#include "Echo.h"  
#include "math.h"
  
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
float xLeft, xRight, yLeft, yRight;
Uint32 oldest = 0; // index for buffer value

#define BUFFER_LENGTH   96000 // buffer length in samples

#pragma DATA_SECTION (buffer, "CE0"); // put "buffer" in external SDRAM

volatile float buffer[2][BUFFER_LENGTH]; /* need space for left and right */
volatile float gain = 0.75; /* set gain value for echoed sample */

// sample index
float n = 0;
Int16 delay;
float cos_in= 0;



void ZeroBuffer()
///////////////////////////////////////////////////////////////////////
// Purpose:   Initial fill of all buffer locations with 0.0
//
// Input:     None
//
// Returns:   Nothing
//
// Calls:     Nothing
//
// Notes:     None
///////////////////////////////////////////////////////////////////////
{
    int i;

    for(i=0; i < BUFFER_LENGTH; i++)  {
        buffer[LEFT][i] = 0.0;
        buffer[RIGHT][i] = 0.0;  
        }
}

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
	Uint32 newest;  // only used for infinite echo

 	if(CheckForOverrun())					// overrun error occurred (i.e. halted DSP)
		return;								// so serial port is reset to recover

  	CodecDataIn.UINT = ReadCodecData();		// get input data samples
	
	/* add your code starting here */

	/****************************
	ECHO ROUTINE BEGINS HERE
	****************************/
	xLeft = CodecDataIn.Channel[LEFT];   // current LEFT input value to float
	xRight = CodecDataIn.Channel[RIGHT];   // current RIGHT input value to float

	buffer[LEFT][oldest] = xLeft;
	buffer[RIGHT][oldest] = xRight;
	newest = oldest;
	oldest = (++oldest)%BUFFER_LENGTH; // modulo for circular buffer

	// use either FIR or IIR lines below

	// for FIR comb filter effect, uncomment next two lines
	//yLeft = xLeft + (gain * buffer[LEFT][oldest]);
	//yRight = xRight + (gain * buffer[RIGHT][oldest]);
    
	// for IIR comb filter effect, uncomment four lines below
	//buffer[LEFT][newest] = xLeft + (gain * buffer[LEFT][oldest]);
	//buffer[RIGHT][newest] = xRight + (gain * buffer[RIGHT][oldest]);
	//yLeft = buffer[LEFT][oldest];  // or use newest
	//yRight = buffer[RIGHT][oldest];  // or use newest



	// My code
	// Flanging Effect
	//
	// delay = R/2 (1 - cos(2*pi*f0/fs *n))
	// for us R = 48, fs = 48 kHz
	float R = 48;
	float f0 = 1;
	float fs = 48000;
	float PI = 3.14159265359;

	cos_in = 2*PI*f0*newest;
	cos_in = cos_in / fs;
	delay =  (Int16)( (R/2) * (1.0 - cosf(cos_in)) );


	n = n + 1;
	if (n == 48000){
		n = 1;
	}

	int index = (newest >= delay) ? (newest - delay) : (BUFFER_LENGTH - (delay - newest));
	yLeft = xLeft + buffer[LEFT][ index ];
	yRight = xRight + buffer[RIGHT][ index ];


	CodecDataOut.Channel[LEFT] = yLeft;   // setup the LEFT value
	CodecDataOut.Channel[RIGHT] = yRight; // setup the RIGHT value
	/*****************************/
	/* end your code here */

	WriteCodecData(CodecDataOut.UINT);		// send output data to  port
}

