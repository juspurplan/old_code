// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2011

///////////////////////////////////////////////////////////////////////
// Filename: ISRs.c
//
// Synopsis: Interrupt service routine for codec data transmit/receive
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h" 
#include <math.h>   
  
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
float A = 16000;		/* signal's amplitude */

float phase = 0;        /* signal's initial phase */

float pi = 3.1415927;	/* value of pi */




Int32 fs = 8000;       /* sample frequency */

float f0 = 2000;
float w0;
float y_coef;
float x_coef;
float y1,y2,x,y,x1;

float f1 = 6000;
float w1;
float v_coef;
float u_coef;
float v1,v2,v,u,u1;

int count;


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
	
	/* algorithm begins here */

  	//channel 0
  	w0 = 2*pi*f0/fs;
  	y_coef = cosf(w0);
  	x_coef = cosf(w0);

  	y = 2*y_coef*y1 - y2 + x - x_coef*x1;

  	y2 = y1;
  	y1 = y;
  	x1 = x;

  	if(x != 0) {
  		x = 0;
  	}


  	//channel 1
  	w1 = 2*pi*f1/fs;
  	v_coef = cosf(w1);
  	u_coef = cosf(w1);

  	v = 2*v_coef*v1 - v2 + u - u_coef*u1;

  	v2 = v1;
  	v1 = v;
  	u1 = u;
  	if(u != 0) {
  		u = 0;
  	}

  	if (count < 0) {
		count = 0;

		y1 = 0;
		y2 = 0;
		x = 1;
		y = 0;
		x1 = 0;

		v1 = 0;
		v2 =0;
		v = 0;
		u =1;
		u1 = 0;
  	}
  	else {
  		count++;
  	}

	CodecDataOut.Channel[ LEFT] = (int) (A*y); /* scaled L output */
	CodecDataOut.Channel[RIGHT] = (int) (A*v); /* scaled R output */


	/* algorithm ends here */

	WriteCodecData(CodecDataOut.UINT);		// send output data to  port
}

