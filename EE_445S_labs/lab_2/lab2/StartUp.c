// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2011

///////////////////////////////////////////////////////////////////////
// Filename: StartUp.c
//
// Synopsis: Placeholder for code run after DSP_Init()
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h"


extern float y1,y2,x,y,x1;
extern float v1,v2,v,u,u1;
extern int count;

void StartUp()
{
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
