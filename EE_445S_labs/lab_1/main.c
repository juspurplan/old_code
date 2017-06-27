// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2011
 
///////////////////////////////////////////////////////////////////////
// Filename: main.c
//
// Synopsis: Main program file for demonstration code
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h"   
#include "stdio.h"
#include"stdlib.h"

int state = 5;
int sequence [100];
int MAX_ITERATIONS = 100;
int index = 1;

int generatePN(int state);


int scramble_state = 5;
int descramble_state = 5;
int scramble(int input);
int descramble(int input);

int in_seq[10] = {1,1,0,0,1,0,1,1,1,0};
int out_seq[10];

int main()
{    
	
	// initialize DSP board
  	//DSP_Init();

	// call StartUp for application specific code
	// defined in each application directory
	//StartUp();
	
	//psuedo-random generation
	sequence[0] = state;

	for(index = 1; index < MAX_ITERATIONS; index++) {
		int next_state = generatePN(state);

		// save state, and write to our sequence array
		state = next_state;
		sequence[index] = state;
	}


	// print sequence of states
	for(index = 0; index < MAX_ITERATIONS; index++) {
		int current_state = sequence[index];
		printf("%i\n", current_state);
	}

	printf("\n");
	// print only the current bit
	for(index = 1; index < MAX_ITERATIONS; index++) {
		int current_state = sequence[index];
		current_state = (current_state >> 5) & 0x01;
		printf("%i\n", current_state);
	}


	printf("\n");
	//do scrabmler descrambler
	for (index = 0; index < 10; index ++) {
		int temp = scramble(in_seq[index]);
		int result = descramble(temp);
		out_seq[index] = result;
	}
	//print output of descrambler
	for(index = 0; index<10; index++) {
		printf("%i\n", out_seq[index]);
	}


	// main stalls here, interrupts drive operation 
  	while(1) { 
		;
  	}   
}

int generatePN(int state) {
	int result = state;

	int y_5 = state & 0x01;
	int y_2 = (state >> 3) & 0x01;

	result = result |  ((y_5 ^ y_2) << 6);
	result = result >> 1;

	return result;
}

int scramble (int input) {
	int in = input & 0x01;
	int result = scramble_state;

	int y_5 = scramble_state & 0x01;
	int y_2 = (scramble_state >> 3) & 0x01;

	result = result |  ((y_5 ^ y_2 ^ in) << 6);
	result = result >> 1;

	scramble_state = result;

	return (result >> 5) & 0x01;
}
int descramble(int input) {
		int in = input & 0x01;

		int y_5 = descramble_state & 0x01;
		int y_2 = (descramble_state >> 3) & 0x01;

		int result = descramble_state;
		result = result | (in << 6);

		result = result >> 1;
		descramble_state = result;

		return (y_5 ^ y_2 ^ in);

}

