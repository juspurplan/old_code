/*
    REFER TO THE SUBMISSION INSTRUCTION FOR DETAILS

    Name 1: alan tan 
    Name 2: Full name of the second partner
    UTEID 1: ajt2459
    UTEID 2: UT EID of the second partner
*/

/***************************************************************/
/*                                                             */
/*   LC-3b Instruction Level Simulator                         */
/*                                                             */
/*   EE 460N                                                   */
/*   The University of Texas at Austin                         */
/*                                                             */
/***************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************/
/*                                                             */
/* Files: isaprogram   LC-3b machine language program file     */
/*                                                             */
/***************************************************************/

/***************************************************************/
/* These are the functions you'll have to write.               */
/***************************************************************/

void process_instruction();

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
/* Main memory.                                                */
/***************************************************************/
/* MEMORY[A][0] stores the least significant byte of word at word address A
   MEMORY[A][1] stores the most significant byte of word at word address A 
*/

#define WORDS_IN_MEM    0x08000 
int MEMORY[WORDS_IN_MEM][2];

/***************************************************************/

/***************************************************************/

/***************************************************************/
/* LC-3b State info.                                           */
/***************************************************************/
#define LC_3b_REGS 8

int RUN_BIT;	/* run bit */


typedef struct System_Latches_Struct{

  int PC,		/* program counter */
    N,		/* n condition bit */
    Z,		/* z condition bit */
    P;		/* p condition bit */
  int REGS[LC_3b_REGS]; /* register file. */
} System_Latches;

/* Data Structure for Latch */

System_Latches CURRENT_LATCHES, NEXT_LATCHES;

/***************************************************************/
/* A cycle counter.                                            */
/***************************************************************/
int INSTRUCTION_COUNT;

/***************************************************************/
/*                                                             */
/* Procedure : help                                            */
/*                                                             */
/* Purpose   : Print out a list of commands                    */
/*                                                             */
/***************************************************************/
void help() {                                                    
  printf("----------------LC-3b ISIM Help-----------------------\n");
  printf("go               -  run program to completion         \n");
  printf("run n            -  execute program for n instructions\n");
  printf("mdump low high   -  dump memory from low to high      \n");
  printf("rdump            -  dump the register & bus values    \n");
  printf("?                -  display this help menu            \n");
  printf("quit             -  exit the program                  \n\n");
}

/***************************************************************/
/*                                                             */
/* Procedure : cycle                                           */
/*                                                             */
/* Purpose   : Execute a cycle                                 */
/*                                                             */
/***************************************************************/
void cycle() {                                                

  process_instruction();
  CURRENT_LATCHES = NEXT_LATCHES;
  INSTRUCTION_COUNT++;
}

/***************************************************************/
/*                                                             */
/* Procedure : run n                                           */
/*                                                             */
/* Purpose   : Simulate the LC-3b for n cycles                 */
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
/* Purpose   : Simulate the LC-3b until HALTed                 */
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
  printf("Instruction Count : %d\n", INSTRUCTION_COUNT);
  printf("PC                : 0x%.4x\n", CURRENT_LATCHES.PC);
  printf("CCs: N = %d  Z = %d  P = %d\n", CURRENT_LATCHES.N, CURRENT_LATCHES.Z, CURRENT_LATCHES.P);
  printf("Registers:\n");
  for (k = 0; k < LC_3b_REGS; k++)
    printf("%d: 0x%.4x\n", k, CURRENT_LATCHES.REGS[k]);
  printf("\n");

  /* dump the state information into the dumpsim file */
  fprintf(dumpsim_file, "\nCurrent register/bus values :\n");
  fprintf(dumpsim_file, "-------------------------------------\n");
  fprintf(dumpsim_file, "Instruction Count : %d\n", INSTRUCTION_COUNT);
  fprintf(dumpsim_file, "PC                : 0x%.4x\n", CURRENT_LATCHES.PC);
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
/* Procedure : init_memory                                     */
/*                                                             */
/* Purpose   : Zero out the memory array                       */
/*                                                             */
/***************************************************************/
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

/************************************************************/
/*                                                          */
/* Procedure : initialize                                   */
/*                                                          */
/* Purpose   : Load machine language program                */ 
/*             and set up initial state of the machine.     */
/*                                                          */
/************************************************************/
void initialize(char *program_filename, int num_prog_files) { 
  int i;

  init_memory();
  for ( i = 0; i < num_prog_files; i++ ) {
    load_program(program_filename);
    while(*program_filename++ != '\0');
  }
  CURRENT_LATCHES.Z = 1;  
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
  if (argc < 2) {
    printf("Error: usage: %s <program_file_1> <program_file_2> ...\n",
           argv[0]);
    exit(1);
  }

  printf("LC-3b Simulator\n\n");

  initialize(argv[1], argc - 1);

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

   MEMORY

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

void process_instruction(){
	/*  function: process_instruction
	*  
	*    Process one instruction at a time  
	*       -Fetch one instruction
	*       -Decode 
	*       -Execute
	*       -Update NEXT_LATCHES
	*/

	int instruction_lower = Low16bits( MEMORY[CURRENT_LATCHES.PC/2][0] );
	int instruction_upper = Low16bits( MEMORY[CURRENT_LATCHES.PC/2][1] ); 
	int instruction = 0;
	instruction = instruction | (instruction_upper << 8) | (instruction_lower);

	int next_pc = CURRENT_LATCHES.PC +2;
	NEXT_LATCHES.REGS[0] = CURRENT_LATCHES.REGS[0];
	NEXT_LATCHES.REGS[1] = CURRENT_LATCHES.REGS[1];
	NEXT_LATCHES.REGS[2] = CURRENT_LATCHES.REGS[2];
	NEXT_LATCHES.REGS[3] = CURRENT_LATCHES.REGS[3];
	NEXT_LATCHES.REGS[4] = CURRENT_LATCHES.REGS[4];
	NEXT_LATCHES.REGS[5] = CURRENT_LATCHES.REGS[5];
	NEXT_LATCHES.REGS[6] = CURRENT_LATCHES.REGS[6];
	NEXT_LATCHES.REGS[7] = CURRENT_LATCHES.REGS[7];
	NEXT_LATCHES.N = CURRENT_LATCHES.N;
	NEXT_LATCHES.Z = CURRENT_LATCHES.Z;
	NEXT_LATCHES.P = CURRENT_LATCHES.P;

	int opcode = instruction >> 12;
	switch (opcode) {
	case 0 : /* 0000 - Branch*/ {
		int pc_offset = instruction & 0x01FF;
		pc_offset = sext9to16(pc_offset);
		pc_offset = pc_offset*2;
		pc_offset = Low16bits(pc_offset);
		int test_n = (instruction >> 11) & 0x0001;
		int test_z = (instruction >> 10) & 0x0001;
		int test_p = (instruction >> 9 ) & 0x0001;
		if( (test_n && CURRENT_LATCHES.N) || (test_z && CURRENT_LATCHES.Z) || (test_p && CURRENT_LATCHES.P) ) {
			next_pc += pc_offset;
			next_pc = Low16bits(next_pc);
		}

		break;
	}
	case 1 : /* 0001 - ADD*/ {
		int has_immediate = (instruction >> 5) & 0x0001;
		int dr = (instruction >> 9) & 0x0007;
		int sr1 = (instruction >> 6) & 0x0007; /* 0b 0111 */
		int sum = 0;
		
		if(has_immediate){
			/* DR = SR1 + immediate */
			int immediate = instruction & 0x001F;
			immediate = sext5to16(immediate);
			sum = CURRENT_LATCHES.REGS[sr1] + immediate;
		}
		else {
			/* DR = SR1 + SR2 */
			int sr2 = instruction & 0x0007;
			sum = CURRENT_LATCHES.REGS[sr1] + CURRENT_LATCHES.REGS[sr2];
		}

		sum = Low16bits(sum);
		NEXT_LATCHES.REGS[dr] = sum;
		
		/* set condition codes */
		setConditionCodes(sum);

		break;
	}

	case 2 : /* 0010 - LDB load byte*/ {
		int dr = (instruction >> 9) & 0x0007;
		int baser = (instruction >> 6) & 0x0007;
		int base_offset = instruction & 0x003F;
		base_offset = sext6to16(base_offset);

		int address = CURRENT_LATCHES.REGS[baser] + base_offset;
		address = Low16bits(address);

		int result = MEMORY[address/2][address&0x0001];
		result = sext8to16(result);
		NEXT_LATCHES.REGS[dr] = result;

		/* set condition codes TODO */
		setConditionCodes(result);
		break;
	}

	case 3 : /* 0011 - STB store byte */ {
		int sr = (instruction >> 9) & 0x0007;
		int baser = (instruction >> 6) & 0x0007;
		int base_offset = instruction & 0x003F;
		base_offset = sext6to16(base_offset);

		int address = CURRENT_LATCHES.REGS[baser] + base_offset;
		int value = CURRENT_LATCHES.REGS[sr];
		value = value & 0x00FF; /* store lower byte only */
		MEMORY[address/2][address&0x0001] = value;
		break;
	}

	case 4 : /* 0100 - JSR or JSRR (jump subroutine) */ {
		int has_baser = !((instruction >> 11) & 0x0001);
		NEXT_LATCHES.REGS[7] = next_pc;

		if(has_baser) {
			int baser = (instruction >> 6) & 0x0007;
			next_pc = CURRENT_LATCHES.REGS[baser];
		}
		else {
			int pc_offset = instruction & 0x07FF;
			pc_offset = sext9to16(pc_offset);
			pc_offset = pc_offset*2;
			pc_offset = Low16bits(pc_offset);
			next_pc += pc_offset;
			next_pc = Low16bits(next_pc);
		}

		break;
	}

	case 5 : /* 0101 - AND*/ {
		int has_immediate = (instruction >> 5) & 0x0001;
		int dr = (instruction >> 9) & 0x0007;
		int sr1 = (instruction >> 6) & 0x0007; /* 0b 0111 */
		int and_result = 0;
		if(has_immediate){
			/* DR = SR1 & immediate */
			int immediate = instruction & 0x001F;
			immediate = sext5to16(immediate);
			and_result = CURRENT_LATCHES.REGS[sr1] & immediate;
		}
		else {
			/* DR = SR1 & SR2 */
			int sr2 = instruction & 0x0007;
			and_result = CURRENT_LATCHES.REGS[sr1] & CURRENT_LATCHES.REGS[sr2];
		}

		and_result = Low16bits(and_result);
		NEXT_LATCHES.REGS[dr] = and_result;

		/* set condition codes */
		setConditionCodes(and_result);

		break;
	}

	case 6 : /* 0110 - LDW load word*/ {
		int dr = (instruction >> 9) & 0x0007;
		int baser = (instruction >> 6) & 0x0007;
		int base_offset = instruction & 0x003F;
		base_offset = sext6to16(base_offset);
		base_offset = base_offset*2;
		base_offset = Low16bits(base_offset);

		int address = CURRENT_LATCHES.REGS[baser] + base_offset;
		address = Low16bits(address);

		int result_lower = MEMORY[address/2][0];
		int result_upper = MEMORY[address/2][1];
		int result = 0;
		result = result | result_lower | (result_upper << 8);
		result = Low16bits(result);
		NEXT_LATCHES.REGS[dr] = result;

		/* set condition codes TODO*/
		setConditionCodes(result);
		break;
	}

	case 7 : /* 0111 - STW store word*/ {
		int sr = (instruction >> 9) & 0x0007;
		int baser = (instruction >> 6) & 0x0007;
		int base_offset = instruction & 0x003F;
		base_offset = sext6to16(base_offset);

		int address = CURRENT_LATCHES.REGS[baser] + base_offset;
		int value = CURRENT_LATCHES.REGS[sr];
		MEMORY[address/2][0] = value & 0x00FF; /*store lower byte*/
		MEMORY[address/2][1] = (value >> 8) & 0x00FF; /* store upper byte */
		break;
	}

	case 8 : /* 1000 - RTI*/ {
		/* skip implementation */
		break;
	}

	case 9 : /* 1001 - XOR (there is a special case for NOT) */ {
		int has_immediate = (instruction >> 5) & 0x0001;
		int dr = (instruction >> 9) & 0x0007;
		int sr1 = (instruction >> 6) & 0x0007;
		int result = 0;

		if(has_immediate) {
			int immediate = instruction & 0x001F;
			immediate = sext5to16(immediate);
			result = CURRENT_LATCHES.REGS[sr1] ^ immediate;
			result = Low16bits(result);
		}
		else {
			int sr2 = instruction & 0x0007;
			result = CURRENT_LATCHES.REGS[sr1] ^ CURRENT_LATCHES.REGS[sr2];
			result = Low16bits(result);
		}

		NEXT_LATCHES.REGS[dr] = result;
		/* set condition codes TODO */
		setConditionCodes(result);
		break;
	}

	case 10 : /* 1010 - not used */ {
		break;
	}

	case 11 : /* 1011 - not used */ {
		break;
	}

	case 12 : /* 1100 - JMP or RET */ {
		int baser = (instruction >> 6) & 0x0007; /* 0b 0111 */
		next_pc = CURRENT_LATCHES.REGS[baser]; 

		break;
	}

	case 13 : /* 1101 - shift (includes LSHF, RSHFL, RSHFA) */ {
		int dr = (instruction >> 9) & 0x0007;
		int sr = (instruction >> 6) & 0x0007;
		int is_lsh = !((instruction >> 4) & 0x0001);
		int is_sha = (instruction >> 5) & 0x0001;
		int amount = instruction & 0x000F;
		int result = 0;

		if(is_lsh) {
			result = CURRENT_LATCHES.REGS[sr] << amount;
			result = Low16bits(result);
		}
		else if (is_sha)  {
			/*arithmetic right shift*/
			result = Low16bits(CURRENT_LATCHES.REGS[sr]);
			int is_neg = (result >> 15) & 0x0001;
			if(is_neg){
				int i = 0;
				for(i = 0; i < amount; i++){
					result = result >> 1;
					result = result | 0x8000; /* insert 1 at the left */
				}
			}
			else{
				/* arithemtic right shift on postive number is same as logical right shift */
				result = result >> amount;
			}
		}
		else  {
			/*logical right shift*/
			result = Low16bits(CURRENT_LATCHES.REGS[sr]) >> amount;
		}

		NEXT_LATCHES.REGS[dr] = result;

		/* set condition codes TODO */
		setConditionCodes(result);
		break;
	}

	case 14 : /* 1110 - LEA load effective address*/ {
		int dr = (instruction >> 9) & 0x0007;
		int pc_offset = instruction & 0x01FF;
		pc_offset = sext9to16(pc_offset);
		pc_offset = pc_offset*2;
		pc_offset = Low16bits(pc_offset);
		int result = next_pc + pc_offset;
		NEXT_LATCHES.REGS[dr] = result;
		/* does not set condition codes */
		break;
	}

	case 15 : /* 1111 - TRAP */ {
		NEXT_LATCHES.REGS[7] = next_pc;

		int trap_vector = instruction & 0x00FF;
		int address = trap_vector *2;
		address = Low16bits(address);
		int lower = MEMORY[address][0];
		int upper = MEMORY[address][1];
		next_pc = 0 | lower | (upper << 8);

		break;
	}
	}


	NEXT_LATCHES.PC = next_pc;

}
        

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


