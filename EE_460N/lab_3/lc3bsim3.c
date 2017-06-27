/*
    Name 1: Your full name
    UTEID 1: Your UT EID

    Alan Tan
    ajt 2459
*/

/***************************************************************/
/*                                                             */
/*   LC-3b Simulator                                           */
/*                                                             */
/*   EE 460N                                                   */
/*   The University of Texas at Austin                         */
/*                                                             */
/***************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/***************************************************************/
/*                                                             */
/* Files:  ucode        Microprogram file                      */
/*         isaprogram   LC-3b machine language program file    */
/*                                                             */
/***************************************************************/

/***************************************************************/
/* These are the functions you'll have to write.               */
/***************************************************************/

void eval_micro_sequencer();
void cycle_memory();
void eval_bus_drivers();
void drive_bus();
void latch_datapath_values();

/***************************************************************/
/* A couple of useful definitions.                             */
/***************************************************************/
#define FALSE 0
#define TRUE  1

/***************************************************************/
/* Use this to avoid overflowing 16 bits on the bus.           */
/***************************************************************/
#define Low16bits(x) ((x) & 0xFFFF)

/***************************************************************/
/* Definition of the control store layout.                     */
/***************************************************************/
#define CONTROL_STORE_ROWS 64
#define INITIAL_STATE_NUMBER 18

/***************************************************************/
/* Definition of bit order in control store word.              */
/***************************************************************/
enum CS_BITS {                                                  
    IRD,
    COND1, COND0,
    J5, J4, J3, J2, J1, J0,
    LD_MAR,
    LD_MDR,
    LD_IR,
    LD_BEN,
    LD_REG,
    LD_CC,
    LD_PC,
    GATE_PC,
    GATE_MDR,
    GATE_ALU,
    GATE_MARMUX,
    GATE_SHF,
    PCMUX1, PCMUX0,
    DRMUX,
    SR1MUX,
    ADDR1MUX,
    ADDR2MUX1, ADDR2MUX0,
    MARMUX,
    ALUK1, ALUK0,
    MIO_EN,
    R_W,
    DATA_SIZE,
    LSHF1,
    CONTROL_STORE_BITS
} CS_BITS;

/***************************************************************/
/* Functions to get at the control bits.                       */
/***************************************************************/
int GetIRD(int *x)           { return(x[IRD]); }
int GetCOND(int *x)          { return((x[COND1] << 1) + x[COND0]); }
int GetJ(int *x)             { return((x[J5] << 5) + (x[J4] << 4) +
				      (x[J3] << 3) + (x[J2] << 2) +
				      (x[J1] << 1) + x[J0]); }
int GetLD_MAR(int *x)        { return(x[LD_MAR]); }
int GetLD_MDR(int *x)        { return(x[LD_MDR]); }
int GetLD_IR(int *x)         { return(x[LD_IR]); }
int GetLD_BEN(int *x)        { return(x[LD_BEN]); }
int GetLD_REG(int *x)        { return(x[LD_REG]); }
int GetLD_CC(int *x)         { return(x[LD_CC]); }
int GetLD_PC(int *x)         { return(x[LD_PC]); }
int GetGATE_PC(int *x)       { return(x[GATE_PC]); }
int GetGATE_MDR(int *x)      { return(x[GATE_MDR]); }
int GetGATE_ALU(int *x)      { return(x[GATE_ALU]); }
int GetGATE_MARMUX(int *x)   { return(x[GATE_MARMUX]); }
int GetGATE_SHF(int *x)      { return(x[GATE_SHF]); }
int GetPCMUX(int *x)         { return((x[PCMUX1] << 1) + x[PCMUX0]); }
int GetDRMUX(int *x)         { return(x[DRMUX]); }
int GetSR1MUX(int *x)        { return(x[SR1MUX]); }
int GetADDR1MUX(int *x)      { return(x[ADDR1MUX]); }
int GetADDR2MUX(int *x)      { return((x[ADDR2MUX1] << 1) + x[ADDR2MUX0]); }
int GetMARMUX(int *x)        { return(x[MARMUX]); }
int GetALUK(int *x)          { return((x[ALUK1] << 1) + x[ALUK0]); }
int GetMIO_EN(int *x)        { return(x[MIO_EN]); }
int GetR_W(int *x)           { return(x[R_W]); }
int GetDATA_SIZE(int *x)     { return(x[DATA_SIZE]); } 
int GetLSHF1(int *x)         { return(x[LSHF1]); }

/***************************************************************/
/* The control store rom.                                      */
/***************************************************************/
int CONTROL_STORE[CONTROL_STORE_ROWS][CONTROL_STORE_BITS];

/***************************************************************/
/* Main memory.                                                */
/***************************************************************/
/* MEMORY[A][0] stores the least significant byte of word at word address A
   MEMORY[A][1] stores the most significant byte of word at word address A 
   There are two write enable signals, one for each byte. WE0 is used for 
   the least significant byte of a word. WE1 is used for the most significant 
   byte of a word. */

#define WORDS_IN_MEM    0x08000 
#define MEM_CYCLES      5
int MEMORY[WORDS_IN_MEM][2];

/***************************************************************/

/***************************************************************/

/***************************************************************/
/* LC-3b State info.                                           */
/***************************************************************/
#define LC_3b_REGS 8

int RUN_BIT;	/* run bit */
int BUS;	/* value of the bus */

typedef struct System_Latches_Struct{

int PC,		/* program counter */
    MDR,	/* memory data register */
    MAR,	/* memory address register */
    IR,		/* instruction register */
    N,		/* n condition bit */
    Z,		/* z condition bit */
    P,		/* p condition bit */
    BEN;        /* ben register */

int READY;	/* ready bit */
  /* The ready bit is also latched as you dont want the memory system to assert it 
     at a bad point in the cycle*/

int REGS[LC_3b_REGS]; /* register file. */

int MICROINSTRUCTION[CONTROL_STORE_BITS]; /* The microintruction */

int STATE_NUMBER; /* Current State Number - Provided for debugging */ 
} System_Latches;

/* Data Structure for Latch */

System_Latches CURRENT_LATCHES, NEXT_LATCHES;

/***************************************************************/
/* A cycle counter.                                            */
/***************************************************************/
int CYCLE_COUNT;

/***************************************************************/
/*                                                             */
/* Procedure : help                                            */
/*                                                             */
/* Purpose   : Print out a list of commands.                   */
/*                                                             */
/***************************************************************/
void help() {                                                    
    printf("----------------LC-3bSIM Help-------------------------\n");
    printf("go               -  run program to completion       \n");
    printf("run n            -  execute program for n cycles    \n");
    printf("mdump low high   -  dump memory from low to high    \n");
    printf("rdump            -  dump the register & bus values  \n");
    printf("?                -  display this help menu          \n");
    printf("quit             -  exit the program                \n\n");
}

/***************************************************************/
/*                                                             */
/* Procedure : cycle                                           */
/*                                                             */
/* Purpose   : Execute a cycle                                 */
/*                                                             */
/***************************************************************/
void cycle() {                                                

  eval_micro_sequencer();   
  cycle_memory();
  eval_bus_drivers();
  drive_bus();
  latch_datapath_values();

  printf("cycle = %i, bus = %x, MDR = %x\n", CYCLE_COUNT, BUS, CURRENT_LATCHES.MDR);

  CURRENT_LATCHES = NEXT_LATCHES;

  CYCLE_COUNT++;
}

/***************************************************************/
/*                                                             */
/* Procedure : run n                                           */
/*                                                             */
/* Purpose   : Simulate the LC-3b for n cycles.                 */
/*                                                             */
/***************************************************************/
void run(int num_cycles) {                                      
    int i;

    if (RUN_BIT == FALSE) {
	printf("Can't simulate, Simulator is halted\n\n");
	return;
    }

    printf("Simulating for %d cycles...\n\n", num_cycles);
    for (i = 0; i < num_cycles; i++) {
	if (CURRENT_LATCHES.PC == 0x0000) {
	    RUN_BIT = FALSE;
	    printf("Simulator halted\n\n");
	    break;
	}
	cycle();
    }
}

/***************************************************************/
/*                                                             */
/* Procedure : go                                              */
/*                                                             */
/* Purpose   : Simulate the LC-3b until HALTed.                 */
/*                                                             */
/***************************************************************/
void go() {                                                     
    if (RUN_BIT == FALSE) {
	printf("Can't simulate, Simulator is halted\n\n");
	return;
    }

    printf("Simulating...\n\n");
    while (CURRENT_LATCHES.PC != 0x0000)
	cycle();
    RUN_BIT = FALSE;
    printf("Simulator halted\n\n");
}

/***************************************************************/ 
/*                                                             */
/* Procedure : mdump                                           */
/*                                                             */
/* Purpose   : Dump a word-aligned region of memory to the     */
/*             output file.                                    */
/*                                                             */
/***************************************************************/
void mdump(FILE * dumpsim_file, int start, int stop) {          
    int address; /* this is a byte address */

    printf("\nMemory content [0x%.4x..0x%.4x] :\n", start, stop);
    printf("-------------------------------------\n");
    for (address = (start >> 1); address <= (stop >> 1); address++)
	printf("  0x%.4x (%d) : 0x%.2x%.2x\n", address << 1, address << 1, MEMORY[address][1], MEMORY[address][0]);
    printf("\n");

    /* dump the memory contents into the dumpsim file */
    fprintf(dumpsim_file, "\nMemory content [0x%.4x..0x%.4x] :\n", start, stop);
    fprintf(dumpsim_file, "-------------------------------------\n");
    for (address = (start >> 1); address <= (stop >> 1); address++)
	fprintf(dumpsim_file, " 0x%.4x (%d) : 0x%.2x%.2x\n", address << 1, address << 1, MEMORY[address][1], MEMORY[address][0]);
    fprintf(dumpsim_file, "\n");
    fflush(dumpsim_file);
}

/***************************************************************/
/*                                                             */
/* Procedure : rdump                                           */
/*                                                             */
/* Purpose   : Dump current register and bus values to the     */   
/*             output file.                                    */
/*                                                             */
/***************************************************************/
void rdump(FILE * dumpsim_file) {                               
    int k; 

    printf("\nCurrent register/bus values :\n");
    printf("-------------------------------------\n");
    printf("Cycle Count  : %d\n", CYCLE_COUNT);
    printf("PC           : 0x%.4x\n", CURRENT_LATCHES.PC);
    printf("IR           : 0x%.4x\n", CURRENT_LATCHES.IR);
    printf("STATE_NUMBER : 0x%.4x\n\n", CURRENT_LATCHES.STATE_NUMBER);
    printf("BUS          : 0x%.4x\n", BUS);
    printf("MDR          : 0x%.4x\n", CURRENT_LATCHES.MDR);
    printf("MAR          : 0x%.4x\n", CURRENT_LATCHES.MAR);
    printf("CCs: N = %d  Z = %d  P = %d\n", CURRENT_LATCHES.N, CURRENT_LATCHES.Z, CURRENT_LATCHES.P);
    printf("Registers:\n");
    for (k = 0; k < LC_3b_REGS; k++)
	printf("%d: 0x%.4x\n", k, CURRENT_LATCHES.REGS[k]);
    printf("\n");

    /* dump the state information into the dumpsim file */
    fprintf(dumpsim_file, "\nCurrent register/bus values :\n");
    fprintf(dumpsim_file, "-------------------------------------\n");
    fprintf(dumpsim_file, "Cycle Count  : %d\n", CYCLE_COUNT);
    fprintf(dumpsim_file, "PC           : 0x%.4x\n", CURRENT_LATCHES.PC);
    fprintf(dumpsim_file, "IR           : 0x%.4x\n", CURRENT_LATCHES.IR);
    fprintf(dumpsim_file, "STATE_NUMBER : 0x%.4x\n\n", CURRENT_LATCHES.STATE_NUMBER);
    fprintf(dumpsim_file, "BUS          : 0x%.4x\n", BUS);
    fprintf(dumpsim_file, "MDR          : 0x%.4x\n", CURRENT_LATCHES.MDR);
    fprintf(dumpsim_file, "MAR          : 0x%.4x\n", CURRENT_LATCHES.MAR);
    fprintf(dumpsim_file, "CCs: N = %d  Z = %d  P = %d\n", CURRENT_LATCHES.N, CURRENT_LATCHES.Z, CURRENT_LATCHES.P);
    fprintf(dumpsim_file, "Registers:\n");
    for (k = 0; k < LC_3b_REGS; k++)
	fprintf(dumpsim_file, "%d: 0x%.4x\n", k, CURRENT_LATCHES.REGS[k]);
    fprintf(dumpsim_file, "\n");
    fflush(dumpsim_file);
}

/***************************************************************/
/*                                                             */
/* Procedure : get_command                                     */
/*                                                             */
/* Purpose   : Read a command from standard input.             */  
/*                                                             */
/***************************************************************/
void get_command(FILE * dumpsim_file) {                         
    char buffer[20];
    int start, stop, cycles;

    printf("LC-3b-SIM> ");

    scanf("%s", buffer);
    printf("\n");

    switch(buffer[0]) {
    case 'G':
    case 'g':
	go();
	break;

    case 'M':
    case 'm':
	scanf("%i %i", &start, &stop);
	mdump(dumpsim_file, start, stop);
	break;

    case '?':
	help();
	break;
    case 'Q':
    case 'q':
	printf("Bye.\n");
	exit(0);

    case 'R':
    case 'r':
	if (buffer[1] == 'd' || buffer[1] == 'D')
	    rdump(dumpsim_file);
	else {
	    scanf("%d", &cycles);
	    run(cycles);
	}
	break;

    default:
	printf("Invalid Command\n");
	break;
    }
}

/***************************************************************/
/*                                                             */
/* Procedure : init_control_store                              */
/*                                                             */
/* Purpose   : Load microprogram into control store ROM        */ 
/*                                                             */
/***************************************************************/
void init_control_store(char *ucode_filename) {                 
    FILE *ucode;
    int i, j, index;
    char line[200];

    printf("Loading Control Store from file: %s\n", ucode_filename);

    /* Open the micro-code file. */
    if ((ucode = fopen(ucode_filename, "r")) == NULL) {
	printf("Error: Can't open micro-code file %s\n", ucode_filename);
	exit(-1);
    }

    /* Read a line for each row in the control store. */
    for(i = 0; i < CONTROL_STORE_ROWS; i++) {
	if (fscanf(ucode, "%[^\n]\n", line) == EOF) {
	    printf("Error: Too few lines (%d) in micro-code file: %s\n",
		   i, ucode_filename);
	    exit(-1);
	}

	/* Put in bits one at a time. */
	index = 0;

	for (j = 0; j < CONTROL_STORE_BITS; j++) {
	    /* Needs to find enough bits in line. */
	    if (line[index] == '\0') {
		printf("Error: Too few control bits in micro-code file: %s\nLine: %d\n",
		       ucode_filename, i);
		exit(-1);
	    }
	    if (line[index] != '0' && line[index] != '1') {
		printf("Error: Unknown value in micro-code file: %s\nLine: %d, Bit: %d\n",
		       ucode_filename, i, j);
		exit(-1);
	    }

	    /* Set the bit in the Control Store. */
	    CONTROL_STORE[i][j] = (line[index] == '0') ? 0:1;
	    index++;
	}

	/* Warn about extra bits in line. */
	if (line[index] != '\0')
	    printf("Warning: Extra bit(s) in control store file %s. Line: %d\n",
		   ucode_filename, i);
    }
    printf("\n");
}

/************************************************************/
/*                                                          */
/* Procedure : init_memory                                  */
/*                                                          */
/* Purpose   : Zero out the memory array                    */
/*                                                          */
/************************************************************/
void init_memory() {                                           
    int i;

    for (i=0; i < WORDS_IN_MEM; i++) {
	MEMORY[i][0] = 0;
	MEMORY[i][1] = 0;
    }
}

/**************************************************************/
/*                                                            */
/* Procedure : load_program                                   */
/*                                                            */
/* Purpose   : Load program and service routines into mem.    */
/*                                                            */
/**************************************************************/
void load_program(char *program_filename) {                   
    FILE * prog;
    int ii, word, program_base;

    /* Open program file. */
    prog = fopen(program_filename, "r");
    if (prog == NULL) {
	printf("Error: Can't open program file %s\n", program_filename);
	exit(-1);
    }

    /* Read in the program. */
    if (fscanf(prog, "%x\n", &word) != EOF)
	program_base = word >> 1;
    else {
	printf("Error: Program file is empty\n");
	exit(-1);
    }

    ii = 0;
    while (fscanf(prog, "%x\n", &word) != EOF) {
	/* Make sure it fits. */
	if (program_base + ii >= WORDS_IN_MEM) {
	    printf("Error: Program file %s is too long to fit in memory. %x\n",
		   program_filename, ii);
	    exit(-1);
	}

	/* Write the word to memory array. */
	MEMORY[program_base + ii][0] = word & 0x00FF;
	MEMORY[program_base + ii][1] = (word >> 8) & 0x00FF;
	ii++;
    }

    if (CURRENT_LATCHES.PC == 0) CURRENT_LATCHES.PC = (program_base << 1);

    printf("Read %d words from program into memory.\n\n", ii);
}

/***************************************************************/
/*                                                             */
/* Procedure : initialize                                      */
/*                                                             */
/* Purpose   : Load microprogram and machine language program  */ 
/*             and set up initial state of the machine.        */
/*                                                             */
/***************************************************************/
void initialize(char *ucode_filename, char *program_filename, int num_prog_files) { 
    int i;
    init_control_store(ucode_filename);

    init_memory();
    for ( i = 0; i < num_prog_files; i++ ) {
	load_program(program_filename);
	while(*program_filename++ != '\0');
    }
    CURRENT_LATCHES.Z = 1;
    CURRENT_LATCHES.STATE_NUMBER = INITIAL_STATE_NUMBER;
    memcpy(CURRENT_LATCHES.MICROINSTRUCTION, CONTROL_STORE[INITIAL_STATE_NUMBER], sizeof(int)*CONTROL_STORE_BITS);

    NEXT_LATCHES = CURRENT_LATCHES;

    RUN_BIT = TRUE;
}

/***************************************************************/
/*                                                             */
/* Procedure : main                                            */
/*                                                             */
/***************************************************************/
int main(int argc, char *argv[]) {                              
    FILE * dumpsim_file;

    /* Error Checking */
    if (argc < 3) {
	printf("Error: usage: %s <micro_code_file> <program_file_1> <program_file_2> ...\n",
	       argv[0]);
	exit(1);
    }

    printf("LC-3b Simulator\n\n");

    initialize(argv[1], argv[2], argc - 2);

    if ( (dumpsim_file = fopen( "dumpsim", "w" )) == NULL ) {
	printf("Error: Can't open dumpsim file\n");
	exit(-1);
    }

    while (1)
	get_command(dumpsim_file);

}

/***************************************************************/
/* Do not modify the above code.
   You are allowed to use the following global variables in your
   code. These are defined above.

   CONTROL_STORE
   MEMORY
   BUS

   CURRENT_LATCHES
   NEXT_LATCHES

   You may define your own local/global variables and functions.
   You may use the functions to get at the control bits defined
   above.

   Begin your code here 	  			       */
/***************************************************************/

int sext5to16(int num);
int sext9to16(int num);
int sext11to16(int num);
int sext6to16(int num);
int sext4to16(int num);
int sext8to16(int num);

void setConditionCodes(int value);

void eval_micro_sequencer() {

  /* 
   * Evaluate the address of the next state according to the 
   * micro sequencer logic. Latch the next microinstruction.
   */

   	

   	/* get J */
   	int J = GetJ(CURRENT_LATCHES.MICROINSTRUCTION);
   	int J_mask = 0;
   	int condition = GetCOND(CURRENT_LATCHES.MICROINSTRUCTION);
   	/* if condition == 0, do nothign to J_mask */
   	if (condition == 1 && CURRENT_LATCHES.READY) { 
   		/* check if MEM is done with access */
   		/* set J[1] */
   		J_mask = J_mask | 0x0002;
   	}
   	else if (condition == 2 && CURRENT_LATCHES.BEN) {
   		/* check if we execute a branch */
   		/* set J[2] */
   		J_mask = J_mask | 0x0004;
   	}
   	else if (condition == 3 && ((CURRENT_LATCHES.IR >> 11) &0x0001) ) {
   		/* check addressing mode */
   		/* set J[0] */
   		J_mask = J_mask | 0x0001;
   	}

   	/* mask J */
   	J = J | J_mask;

   	int IRD = GetIRD(CURRENT_LATCHES.MICROINSTRUCTION);
   	int next_control_store_address = (IRD) ? ((CURRENT_LATCHES.IR>>12) &0x000F) : (J);

   	/* NEXT_LATCHES.MICROINSTRUCTION = CONTROL_STORE[next_control_store_address]; */
   	int i = 0;
   	for (i = 0; i < CONTROL_STORE_BITS; i++) {
   		NEXT_LATCHES.MICROINSTRUCTION[i] = CONTROL_STORE[next_control_store_address][i];
   	}
   	NEXT_LATCHES.STATE_NUMBER = next_control_store_address;
}

int MEM_result;
int memory_on = 0;
int memory_cycle_count = 0;
#define MEMORY_LATENCY 5

void cycle_memory() {
 
  /* 
   * This function emulates memory and the WE logic. 
   * Keep track of which cycle of MEMEN we are dealing with.  
   * If fourth, we need to latch Ready bit at the end of 
   * cycle to prepare microsequencer for the fifth cycle.  
   */


	if(memory_on && memory_cycle_count >= MEMORY_LATENCY -2 ){
		/* finished memory access */
		int word_number = (CURRENT_LATCHES.MAR >> 1) & 0x7FFF;
		int is_write = GetR_W(CURRENT_LATCHES.MICROINSTRUCTION);
		if(is_write) {
			MEMORY[word_number][0] = CURRENT_LATCHES.MDR & 0x00FF;
			MEMORY[word_number][1] = (CURRENT_LATCHES.MDR >> 8) & 0x00FF;
		}
		else {
			MEM_result = (MEMORY[word_number][1] << 8) | MEMORY[word_number][0];
		}

		CURRENT_LATCHES.READY = 1;
		memory_on = 0;
    }
    else if (memory_on) {
    	/* memory is currently doing an access */
    	memory_cycle_count += 1;
    }
    else if (GetMIO_EN(CURRENT_LATCHES.MICROINSTRUCTION) && !CURRENT_LATCHES.READY) {
    	/* memory is idling and an access request comes in */
    	memory_on = 1;
    	memory_cycle_count = 1;
    }
    else {
    	/* memory is idle, no access request */
    	/* do nothing */
    }

    /* NOTE TO THE TAs
    	1 problem is that with the way the simulator is designed, the next state is already determined before memory cycles.
    	In real life, all this is done using combinational logic, so when the memory is "ready" it automatically changes the J bits.
    	The problem is the simulator already commited to a particular next state/ next J bits. As a result
    	the simulator recieves the reads the ready bit 1 cycle late. 

    	The current implementation right now with the (5 cycle -2), is technically a 4 cycle MEMORY latency.
    	as the MDR is loaded with the correct data after 4 cycles. but the SIMULATor doesnt read it on cycle 5, it reads it on cycle 6. which
    	makes it seem like there is 5 cycle MEM latency. 

		To fix, we need to alter that particular J bit in the cycle memory function. This is why i believed that the simulator code is wrong
		since cycle memory should happen first, then all the evaluation of bits, then calculating the next state when all the "combinatinoal" is done. 
		However, we can't change that code above.

		One hack-y solution is to just retroactively change the J-bits in thsi function as well. But that's not as pretty. 

	*/

}


int MARMUX_result;
int PC_result;
int ALU_result;
int SHF_result;
int MDR_result;

int added_result; /* input to MARMUX and PCMUX */

void eval_bus_drivers() {

  /* 
   * Datapath routine emulating operations before driving the bus.
   * Evaluate the input of tristate drivers 
   *             Gate_MARMUX,
   *		 Gate_PC,
   *		 Gate_ALU,
   *		 Gate_SHF,
   *		 Gate_MDR.
   */    

   	/* SOURCSE */
    int has_immediate = (CURRENT_LATCHES.IR >> 5) & 0x0001;
   	int SR1 = CURRENT_LATCHES.REGS[ (GetSR1MUX(CURRENT_LATCHES.MICROINSTRUCTION)) ? ((CURRENT_LATCHES.IR>>6) &0x0007) : ((CURRENT_LATCHES.IR>>9) &0x0007) ];
   	int SR2 = CURRENT_LATCHES.REGS[ (CURRENT_LATCHES.IR & 0x0007) ];
   	int ADDR2_result;
   	switch(GetADDR2MUX(CURRENT_LATCHES.MICROINSTRUCTION)) {
   	case 0: /* ZERO */
   		ADDR2_result = 0;
   		break;
   	case 1: /* offset6 */
   		ADDR2_result = sext6to16(CURRENT_LATCHES.IR & 0x003F);
   		break;
   	case 2: /* PC offset 9 */
   		ADDR2_result = sext9to16(CURRENT_LATCHES.IR & 0x01FF);
   		break;
   	case 3: /* PC offset 11 */
   		ADDR2_result = sext11to16(CURRENT_LATCHES.IR & 0x07FF);
   		break;
   	}
   	int LSHF1_result = (GetLSHF1(CURRENT_LATCHES.MICROINSTRUCTION)) ? (ADDR2_result << 1) : (ADDR2_result);
   	LSHF1_result = Low16bits(LSHF1_result);
   	int ADDR1_result = GetADDR1MUX(CURRENT_LATCHES.MICROINSTRUCTION) ? (SR1) : (CURRENT_LATCHES.PC);
   	added_result = Low16bits(LSHF1_result + ADDR1_result);


   	/* DRIVERS */
   	/* MARMUX */
	MARMUX_result = (GetMARMUX(CURRENT_LATCHES.MICROINSTRUCTION)) ? (added_result) : (CURRENT_LATCHES.IR & 0x00FF);

	/* PC */
	PC_result = CURRENT_LATCHES.PC;	

	/* ALU */
	int ALUK = GetALUK(CURRENT_LATCHES.MICROINSTRUCTION); 
	int A = SR1;
	int B = (has_immediate) ? (sext5to16(CURRENT_LATCHES.IR & 0x001F)) : (SR2);
	switch(ALUK) {
	case 0: /* ADD */
		ALU_result = A + B;
		break;
	case 1: /* AND */
		ALU_result = A & B;
		break;
	case 2: /* XOR */
		ALU_result = A ^ B;
		break;
	case 3: /* PASS A */
		ALU_result = A;
		break;
	}


	/* SHF */
	int amount = (CURRENT_LATCHES.IR & 0x000F);
	int shift_type = (CURRENT_LATCHES.IR >> 4) & 0x0003;
	int is_neg = (Low16bits(SR1) >> 15) & 0x0001;
	switch(shift_type) {
	case 0: /* left shift */
		SHF_result = SR1 << amount;
		break;
	case 1: /* logical right shift */
		SHF_result = (Low16bits(SR1)) >> amount;
		break;
	case 2: /* invalid */
		SHF_result = 0x0000;
		break;
	case 3: /* arith right shift */
		SHF_result = Low16bits(SR1);
		if(is_neg){
			int i = 0;
			for(i = 0; i < amount; i++){
				SHF_result = SHF_result >> 1;
				SHF_result = SHF_result | 0x8000; /* insert 1 at the left */
			}
		}
		else{
			/* arithemtic right shift on postive number is same as logical right shift */
			SHF_result = SR1 >> amount;
		}
		break;
	}

	SHF_result = Low16bits(SHF_result);
	

	/* MDR */
	MDR_result = CURRENT_LATCHES.MDR;

}


void drive_bus() {

  /* 
   * Datapath routine for driving the bus from one of the 5 possible 
   * tristate drivers. 
   */       

   	/*drive bus */
   	if(GetGATE_MARMUX(CURRENT_LATCHES.MICROINSTRUCTION)) {
   		BUS = Low16bits(MARMUX_result);
   	}
   	else if (GetGATE_PC(CURRENT_LATCHES.MICROINSTRUCTION)) {
   		BUS = Low16bits(PC_result);
   	}
   	else if (GetGATE_ALU(CURRENT_LATCHES.MICROINSTRUCTION)) {
   		BUS = Low16bits(ALU_result);
   	}
   	else if (GetGATE_SHF(CURRENT_LATCHES.MICROINSTRUCTION)) {
   		BUS = Low16bits(SHF_result);
   	}
   	else if (GetGATE_MDR(CURRENT_LATCHES.MICROINSTRUCTION)) {
   		BUS = Low16bits(MDR_result);
   	}
   	else {
   		BUS = 0;
   	}

}


void latch_datapath_values() {

  /* 
   * Datapath routine for computing all functions that need to latch
   * values in the data path at the end of this cycle.  Some values
   * require sourcing the bus; therefore, this routine has to come 
   * after drive_bus.
   */       


   	/*  Registerse we need to update
	PC,		
	MDR,	
	MAR,	
	IR,		
	N,	
	Z,		
	P,		
	BEN;        
	READY;	
	REGS[LC_3b_REGS]; 

   */

	int load_pc = GetLD_PC(CURRENT_LATCHES.MICROINSTRUCTION);
	switch(GetPCMUX(CURRENT_LATCHES.MICROINSTRUCTION)) {
	case 0: /* PC + 2 */
		NEXT_LATCHES.PC = (load_pc) ? (CURRENT_LATCHES.PC + 2) : (CURRENT_LATCHES.PC);
		break;
	case 1: /* BUS */
		NEXT_LATCHES.PC = (load_pc) ? (BUS) : (CURRENT_LATCHES.PC);
		break;
	case 2: /* added result */
		NEXT_LATCHES.PC = (load_pc) ? (added_result) : (CURRENT_LATCHES.PC);
		break;
	case 3: /* unused */
		NEXT_LATCHES.PC = 0;
		break;
	}
	NEXT_LATCHES.MAR = (GetLD_MAR(CURRENT_LATCHES.MICROINSTRUCTION)) ? (BUS) : (CURRENT_LATCHES.MAR);
	NEXT_LATCHES.IR = (GetLD_IR(CURRENT_LATCHES.MICROINSTRUCTION)) ? (BUS) : (CURRENT_LATCHES.IR);

	int ir_11 = (CURRENT_LATCHES.IR >> 11) & 0x0001;
	int ir_10 = (CURRENT_LATCHES.IR >> 10) & 0x0001;
	int ir_9 = (CURRENT_LATCHES.IR >> 9) & 0x0001;
	NEXT_LATCHES.BEN = (GetLD_BEN(CURRENT_LATCHES.MICROINSTRUCTION)) ? ((ir_11&CURRENT_LATCHES.N) | (ir_10&CURRENT_LATCHES.Z) | (ir_9&CURRENT_LATCHES.P)) : (CURRENT_LATCHES.BEN);

	/* update NZP if necessary */
	if(GetLD_CC(CURRENT_LATCHES.MICROINSTRUCTION)) {
		setConditionCodes(Low16bits(BUS));
	}
	else {
		NEXT_LATCHES.N = CURRENT_LATCHES.N;
		NEXT_LATCHES.Z = CURRENT_LATCHES.Z;
		NEXT_LATCHES.P = CURRENT_LATCHES.P;
	}

	/* update registers. Copy first, then update specific ones */
	int i = 0;
	for(i = 0; i < 8; i++) {
		NEXT_LATCHES.REGS[i] = CURRENT_LATCHES.REGS[i];
	}
	int DR_location = (GetDRMUX(CURRENT_LATCHES.MICROINSTRUCTION)) ? (7) : ((CURRENT_LATCHES.IR >> 9) &0x0007);
	NEXT_LATCHES.REGS[DR_location] = (GetLD_REG(CURRENT_LATCHES.MICROINSTRUCTION)) ? (BUS) : (CURRENT_LATCHES.REGS[DR_location]);

	/* MDR updates is a bit special*/
	int new_MDR_value = (GetMIO_EN(CURRENT_LATCHES.MICROINSTRUCTION)) ? (MEM_result) : (BUS);
	NEXT_LATCHES.MDR = (GetLD_MDR(CURRENT_LATCHES.MICROINSTRUCTION)) ? (new_MDR_value) : (CURRENT_LATCHES.MDR);

	/* alter ready bit - special case */
	/* we only ready =0, when we are about to send a request to memory. the 1st state of LDB, LDW, STB, STW, TRAP */
	/* then during the waiting state, the memory controller will set read = 1; */
	/* we let ready ==1, until the next time we access memory */
	int current_state = CURRENT_LATCHES.STATE_NUMBER;
	if(current_state == 15 || current_state == 2 || current_state == 6 || current_state == 23 || current_state == 24 || current_state == 18 || current_state == 19) {
		NEXT_LATCHES.READY = 0;
	}
	else {
		NEXT_LATCHES.READY = CURRENT_LATCHES.READY;
	}
}


/* sign extending functions */

int sext5to16(int num) {
	int is_neg = (num>>4) & 0x0001;
	int result = 0;
	if(is_neg) {
		result = 0xFFFFFFE0 | num;
		result = Low16bits(result);
	}
	else {
		result = Low16bits(num);
	}
	return result;
}

int sext9to16(int num) {
	int is_neg = (num>>8) & 0x0001;
	int result = 0;
	if(is_neg) {
		result = 0xFFFFFE00 | num;
		result = Low16bits(result);
	}
	else {
		result = Low16bits(num);
	}
	return result;
}

int sext11to16(int num){
	int is_neg = (num>>10) & 0x0001;
	int result = 0;
	if(is_neg) {
		result = 0xFFFFF800 | num;
		result = Low16bits(result);
	}
	else {
		result = Low16bits(num);
	}
	return result;
}

int sext6to16(int num){
	int is_neg = (num>>5) & 0x0001;
	int result = 0;
	if(is_neg) {
		result = 0xFFFFFFC0 | num;
		result = Low16bits(result);
	}
	else {
		result = Low16bits(num);
	}
	return result;
}

int sext4to16(int num) {
	int is_neg = (num>>3) & 0x0001;
	int result = 0;
	if(is_neg) {
		result = 0xFFFFFFF0 | num;
		result = Low16bits(result);
	}
	else {
		result = Low16bits(num);
	}
	return result;
}

int sext8to16(int num){
	int is_neg = (num>>7) & 0x0001;
	int result = 0;
	if(is_neg) {
		result = 0xFFFFFF00 | num;
		result = Low16bits(result);
	}
	else {
		result = Low16bits(num);
	}
	return result;
}

/* value needs to be a 16-bit number */
/* AKA call Low16bits() on the value before this function */
void setConditionCodes(int value) {
	int is_zero = (value == 0)?(1):(0);
	int is_neg = ( (value >> 15) == 1 )?(1):(0);
	NEXT_LATCHES.N = is_neg;
	NEXT_LATCHES.Z = is_zero;
	NEXT_LATCHES.P = (!is_neg && !is_zero)?(1):(0);
}

