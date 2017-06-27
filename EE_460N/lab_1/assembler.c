
/*
    Name : alan tan	
    LRC acount: atan
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>




int toNum(char* pStr);
int readAndParse( FILE* pInfile, char* pLine, char** pLabel, char** pOpcode, char** pArg1, char** pArg2, char** pArg3, char** pArg4);

#define MAX_LINE_LENGTH 255

enum
{
   DONE, OK, EMPTY_LINE
};


int isOpcode(char* opcode);



FILE* in_file;
FILE* out_file;

char line_buffer[MAX_LINE_LENGTH +1];
char* label;
char* opcode;
char* arg1;
char* arg2;
char* arg3;
char* arg4;

int start_address = 0;
int current_address = 0;

char* symbol_table[80];					
int symbol_table_addresses[80];			
int symbol_table_size = 0;


int first_parse();
int second_parse();
void printSymbolTable();
void write(int vector);
int getLabelAddress(char* label);
int isValidLabel(char* label);





int main(int argc, char* argv[]) {

	
	if( argc != 3) {
		printf("requires syntax \"assemble input output\"\n");
		return -1;
	}

	
	in_file = fopen(argv[1] , "r");
	out_file = fopen(argv[2], "w");

	
	if( in_file == NULL || out_file == NULL){
		printf("Could not open file(s)\n");
		return -1;
	}

	
	first_parse();

	
	printf("start address: %i\n", start_address);
	printSymbolTable();

	
	printf("start 2nd scan\n");
	second_parse();

	
	fclose(in_file);
	fclose(out_file);

	
}




int first_parse() {
	
	int parse_status = OK;

	printf(" addr\t| label\t| op\t| arg1\t| arg2\t| arg3\t| arg4\n");

	while(1) {
		
		
		parse_status = readAndParse(in_file, line_buffer, &label, &opcode, &arg1, &arg2, &arg3, &arg4);
		printf("%i\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\n", current_address, label, opcode, arg1, arg2,arg3, arg4);

		if(strcmp(opcode, ".orig") == 0) {
			start_address = toNum(arg1);
			current_address = start_address-2;
			break;
		}

		
		if(parse_status == DONE){
			printf("could not find .ORIG\n");
			break;
		}

		
	}

	while(1) {
		
		parse_status = readAndParse(in_file, line_buffer, &label, &opcode, &arg1, &arg2, &arg3, &arg4);
		

		if(parse_status != EMPTY_LINE || strcmp(opcode, ".orig") == 0 || strcmp(opcode, ".end") == 0) {
			current_address+=2;
		}

		printf("%i\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\n", current_address, label, opcode, arg1, arg2,arg3, arg4);


		if( label[0] != '\0' ) {
			if(isValidLabel(label) == -1){
				exit(1);
			}
			
			symbol_table[symbol_table_size] = (char*) malloc(strlen(label)*sizeof(char) +1*sizeof(char));
			strcpy( symbol_table[symbol_table_size], label);
			symbol_table_addresses[symbol_table_size] = current_address;

			symbol_table_size++;
		}



		if(strcmp(opcode, ".end") == 0) {
			return;
		}
		if (parse_status == DONE) {
			exit(4);
		}

		

	}

}

int second_parse() {
	rewind(in_file);
	

	current_address = start_address -2;

	write(start_address & 0xFFFF);

	while(1){
		int parse_status = readAndParse(in_file, line_buffer, &label, &opcode, &arg1, &arg2, &arg3, &arg4);
		current_address += 2;

		if(parse_status == EMPTY_LINE || strcmp(opcode, ".orig") == 0) {
			current_address -= 2;
			continue;
		}

		if(strcmp(opcode, ".end") == 0) {
			break;
		}

		int bit_vector = 0;

		printf("%s: ",opcode );
		
		if( strcmp(opcode, "add") == 0){
			bit_vector = bit_vector | 0x1000; 
			int dest_register = atoi(arg1+1);
			bit_vector = bit_vector |  (dest_register << 9);
			int sr1 = atoi(arg2+1);
			bit_vector = bit_vector | (sr1 << 6);

			if (dest_register >7 || sr1 > 7) {
				exit(4);
			}

			if(arg3[0] == 'r') {
				int sr2 = atoi(arg3+1);
				bit_vector = bit_vector | (sr2 );

				if(sr2 > 7){
					exit(4);
				}
			}
			else {
				bit_vector = bit_vector | (1 << 5);
				int immediate = toNum(arg3);
				if(immediate > 15 || immediate < -16) {
					exit(3); 
				}
				bit_vector = bit_vector | (immediate & 0x1F); 
			}


		}
		else if( strcmp(opcode, "and") == 0){
			bit_vector = bit_vector | 0x5000; 
			int dest_register = atoi(arg1+1);
			bit_vector = bit_vector | (dest_register<< 9);
			int sr1 = atoi(arg2+1);
			bit_vector = bit_vector | (sr1 << 6);
			if (dest_register >7 || sr1 > 7) {
				exit(4);
			}

			if(arg3[0] == 'r') {
				int sr2 = atoi(arg3+1);
				bit_vector = bit_vector | (sr2 );
				if(sr2 > 7){
					exit(4);
				}
			
			}
			else {
				int immediate = toNum(arg3);

				bit_vector = bit_vector | (1 << 5);
				if(immediate > 15 || immediate < -16) {
					exit(3); 
				}
				bit_vector = bit_vector | (immediate & 0x1F); 
			}


		}
		else if( strcmp(opcode, "br") == 0){
			bit_vector = bit_vector | 0xE00 ;
			if(getLabelAddress(arg1) == -1) {
				exit(1);
			}
			if(isValidLabel(arg1) == -1){
				exit(4);
			}
			int offset = current_address +2 - getLabelAddress(arg1);
			offset*=-1;
			offset = offset/2;
			if (offset > 255 || offset < -256){
				exit(4); 
			}
			bit_vector = bit_vector | (offset & 0x1FF); 
 		}
		else if( strcmp(opcode, "brn") == 0){
			bit_vector = bit_vector | 0x800; 
			if(getLabelAddress(arg1) == -1) {
				exit(1);
			}
			if(isValidLabel(arg1) == -1){
				exit(4);
			}
			int offset = current_address +2 - getLabelAddress(arg1);
			offset*=-1;
			offset = offset/2;
			if (offset > 255 || offset < -256){
				exit(4); 
			}
			bit_vector = bit_vector | (offset & 0x1FF );
		}
		else if( strcmp(opcode, "brz") == 0){
			bit_vector = bit_vector | 0x400;
			if(getLabelAddress(arg1) == -1) {
				exit(1);
			}
			if(isValidLabel(arg1) == -1){
				exit(4);
			}
			int offset = current_address +2 - getLabelAddress(arg1);
			offset*=-1;
			offset = offset/2;
			if (offset > 255 || offset < -256){
				exit(4); 
			}
			bit_vector = bit_vector | (offset & 0x1FF); 
		}
		else if( strcmp(opcode, "brp") == 0){
			bit_vector = bit_vector | 0x200; 
			if(getLabelAddress(arg1) == -1) {
				exit(1);
			}
			if(isValidLabel(arg1) == -1){
				exit(4);
			}
			int offset = current_address +2 - getLabelAddress(arg1);
			offset*=-1;
			offset = offset/2;
			if (offset > 255 || offset < -256){
				exit(4); 
			}
			bit_vector = bit_vector | (offset & 0x1FF);
		}
		else if( strcmp(opcode, "brzp") == 0){
			bit_vector = bit_vector | 0x600; 
			if(getLabelAddress(arg1) == -1) {
				exit(1);
			}
			if(isValidLabel(arg1) == -1){
				exit(4);
			}
			int offset = current_address +2 - getLabelAddress(arg1);
			offset*=-1;
			offset = offset/2;
			if (offset > 255 || offset < -256){
				exit(4); 
			}
			bit_vector = bit_vector | (offset & 0x1FF); 
		}
		else if( strcmp(opcode, "brnp") == 0){
			bit_vector = bit_vector | 0xA00; 
			if(getLabelAddress(arg1) == -1) {
				exit(1);
			}
			if(isValidLabel(arg1) == -1){
				exit(4);
			}
			int offset = current_address +2 - getLabelAddress(arg1);
			offset*=-1;
			offset = offset/2;
			if (offset > 255 || offset < -256){
				exit(4); 
			}
			bit_vector = bit_vector | (offset & 0x1FF); 
		}
		else if( strcmp(opcode, "brnz") == 0){
			bit_vector = bit_vector | 0xC00; 
			if(getLabelAddress(arg1) == -1) {
				exit(1);
			}
			if(isValidLabel(arg1) == -1){
				exit(4);
			}
			int offset = current_address +2 - getLabelAddress(arg1);
			offset*=-1;
			offset = offset/2;
			if (offset > 255 || offset < -256){
				exit(4); 
			}
			bit_vector = bit_vector | (offset & 0x1FF); 

		}
		else if( strcmp(opcode, "brnzp") == 0){
			bit_vector = bit_vector | 0xE00; 
			if(getLabelAddress(arg1) == -1) {
				exit(1);
			}
			if(isValidLabel(arg1) == -1){
				exit(4);
			}
			int offset = current_address +2 - getLabelAddress(arg1);
			offset*=-1;
			offset = offset/2;
			if (offset > 255 || offset < -256){
				exit(4); 
			}
			bit_vector = bit_vector | (offset & 0x1FF); 

		}
		else if( strcmp(opcode, "halt") == 0){
			bit_vector = 0xF025; 

		}
		else if( strcmp(opcode, "jmp") == 0){
			bit_vector = bit_vector | 0xC000; 
			int baser = atoi(arg1+1);
			bit_vector = bit_vector | (baser << 6);

			if(baser > 7){
				exit(4);
			}
		}
		else if( strcmp(opcode, "jsr") == 0){
			bit_vector = bit_vector | 0x4800; 
			if(getLabelAddress(arg1) == -1) {
				exit(1);
			}
			if(isValidLabel(arg1) == -1){
				exit(4);
			}
			int offset = current_address +2 - getLabelAddress(arg1);
			offset*=-1;
			offset = offset/2;
			if (offset > 1023 || offset < -1024){
				exit(4); 
			}
			bit_vector = bit_vector | (offset & 0x7FF); 
		}
		else if( strcmp(opcode, "jsrr") == 0){
			bit_vector = bit_vector | 0x4000; 
			int baser = atoi(arg1+1);
			bit_vector = bit_vector | (baser << 6);

			if(baser > 7){
				exit(4);
			}
		}
		else if( strcmp(opcode, "ldb") == 0){
			bit_vector = bit_vector | 0x2000; 
			int dr = atoi(arg1+1);
			int br = atoi(arg2+1);
			int offset = toNum(arg3);

			if(dr> 7 || br>7){
				exit(4);
			}

			if (offset > 31 || offset < -32){
				exit(3); 
			}

			bit_vector = bit_vector | (dr << 9);
			bit_vector = bit_vector | (br << 6);

			bit_vector = bit_vector | (offset & 0x3F); 
		}
		else if( strcmp(opcode, "ldw") == 0){
			bit_vector = bit_vector | 0x6000; 
			int dr = atoi(arg1+1);
			int br = atoi(arg2+1);
			int offset = toNum(arg3);

			if(dr> 7 || br>7){
				exit(4);
			}

			if (offset > 31 || offset < -32){
				exit(3);
			}

			bit_vector = bit_vector | (dr << 9);
			bit_vector = bit_vector | (br << 6);

			bit_vector = bit_vector | (offset & 0x3F); 
		}
		else if( strcmp(opcode, "lea") == 0){
			bit_vector = bit_vector | 0xE000; 
			int dr = atoi(arg1+1);
			bit_vector = bit_vector | (dr << 9);

			printf("%s\n", arg2);
			if(getLabelAddress(arg2) == -1) {
				exit(1);
			}
			if(dr> 7 ){
				exit(4);
			}

			int offset = current_address +2 - getLabelAddress(arg2);
			
			offset*=-1;
			offset = offset/2;

			if (offset > 255 || offset < -256){
				exit(4); 
			}
			bit_vector = bit_vector | (offset & 0x1FF); 

		}
		else if( strcmp(opcode, "nop") == 0){
			bit_vector = 0x0000; 
		}
		else if( strcmp(opcode, "not") == 0){
			bit_vector = bit_vector | 0x903F; 
			int dr = atoi(arg1+1);
			int sr = atoi(arg2+1);

			if(dr> 7 || sr>7){
				exit(4);
			}
			bit_vector = bit_vector | (dr << 9);
			bit_vector = bit_vector | (sr << 6);

		}
		else if( strcmp(opcode, "ret") == 0){
			bit_vector = 0xC1C0; 

		}
		else if( strcmp(opcode, "lshf") == 0){
			bit_vector = bit_vector | 0xD000; 
			int dr = atoi(arg1+1);
			int sr = atoi(arg2+1);
			if(dr> 7 || sr>7){
				exit(4);
			}

			int amount = toNum(arg3);
			if( amount > 15 || amount <0) {
				exit(3);
			}
			bit_vector = bit_vector | (dr << 9);
			bit_vector = bit_vector | (sr << 6);
			bit_vector = bit_vector | (amount & 0xF ); 
		}
		else if( strcmp(opcode, "rshfl") == 0){
			bit_vector = bit_vector | 0xD010; 
			int dr = atoi(arg1+1);
			int sr = atoi(arg2+1);

			if(dr> 7 || sr>7){
				exit(4);
			}
			int amount = toNum(arg3);
			if( amount > 15 || amount <0) {
				exit(3);
			}
			bit_vector = bit_vector | (dr << 9);
			bit_vector = bit_vector | (sr << 6);
			bit_vector = bit_vector | (amount & 0xF); 

		}
		else if( strcmp(opcode, "rshfa") == 0){
			bit_vector = bit_vector | 0xD030; 
			int dr = atoi(arg1+1);
			int sr = atoi(arg2+1);
			if(dr> 7 || sr>7){
				exit(4);
			}
			int amount = toNum(arg3);
			if( amount > 15 || amount <0) {
				exit(3);
			}
			bit_vector = bit_vector | (dr << 9);
			bit_vector = bit_vector | (sr << 6);
			bit_vector = bit_vector | (amount & 0xF ); 
		}
		else if( strcmp(opcode, "rti") == 0){
			bit_vector = 0x8000; 
		}
		else if( strcmp(opcode, "stb") == 0){
			bit_vector = bit_vector | 0x3000; 
			int sr = atoi(arg1+1);
			int br = atoi(arg2+1);
			if(br> 7 || sr>7){
				exit(4);
			}
			int offset = toNum(arg3);

			if (offset > 31 || offset < -32){
				exit(3); 
			}

			bit_vector = bit_vector | (sr << 9);
			bit_vector = bit_vector | (br << 6);

			bit_vector = bit_vector | (offset & 0x3F); 
		}
		else if( strcmp(opcode, "stw") == 0){
			bit_vector = bit_vector | 0x7000; 
			int sr = atoi(arg1+1);
			int br = atoi(arg2+1);
			if(br> 7 || sr>7){
				exit(4);
			}
			int offset = toNum(arg3);

			if (offset > 31 || offset < -32){
				exit(3); 
			}

			bit_vector = bit_vector | (sr << 9);
			bit_vector = bit_vector | (br << 6);

			bit_vector = bit_vector | (offset & 0x3F); 

		}
		else if( strcmp(opcode, "trap") == 0){
			bit_vector = bit_vector | 0xF000; 
			int trap = toNum(arg1);
			if(trap > 255 || trap < 0) {
				exit(3);
			}
			bit_vector = bit_vector | (trap & 0xFF);

		}
		else if( strcmp(opcode, "xor") == 0){
			bit_vector = bit_vector | 0x9000; 
			int dr = atoi(arg1+1);
			int sr1 = atoi(arg2+1);
			if(dr> 7 || sr1>7){
				exit(4);
			}

			if(arg3[0] = 'r') {
				bit_vector = bit_vector | (0 <<5);
				int sr2 = atoi(arg3+1);
				bit_vector = bit_vector | (sr2 & 0x7); 
				if(sr2>7){
					exit(4);
				}
			} 
			else {
				bit_vector = bit_vector | (1 << 5);
				int immediate = toNum(arg3);
				if(immediate > 15 || immediate < -16) {
					exit(3);
				}
				bit_vector = bit_vector | (immediate & 0x1F); 
			}
			bit_vector = bit_vector | (dr << 9);
			bit_vector = bit_vector | (sr1 <<6);

		}
		else if( strcmp(opcode, ".fill") == 0){
			int num = toNum(arg1);
			if ( num > 32767 || num < -32768) {
				exit(3);
			}
			bit_vector = num & 0xFFFF;
		}
		else {
			
			exit(2);
		}

		write(bit_vector);
	
	}

}	


void printSymbolTable() {
	printf("# of labels = %i\n", symbol_table_size);

	int i = 0;
	for (i = 0; i<symbol_table_size; i++) {
		printf(" %i\t| %s\n", symbol_table_addresses[i], symbol_table[i]);
	}
}

void write(int vector) {
	int num = vector;
	char buffer[5];

	int i = 0;
	for ( i= 0; i<4 ; i++) {
		int remainder = num%16;
		num = num/16;
		if(remainder <10) {
			buffer[i] = (char)(remainder+48);
		}
		else {
			buffer[i] = (char)(remainder + 55);
		}
	}
	buffer[4] = '\0';

	fprintf(out_file, "0x" );
	printf("0x");
	int j = 3;
	for (j = 3; j>=0; j--) {
		fprintf(out_file, "%c", buffer[j]);
		printf("%c", buffer[j]);
	}
	fprintf(out_file, "\n" );
	printf("\n");
}

int getLabelAddress(char* label) {
	int i = 0;
	for( i = 0; i< symbol_table_size; i++) {
		if (strcmp(label, symbol_table[i]) == 0) {
			return symbol_table_addresses[i];
		}
	}

	return -1;
}

int isValidLabel(char* label) {
	int len = strlen(label);
	int i = 0;
	if(label[0] == 'x'){
		return -1;
	}
	for (i = 0; i<len; i++) {
		if(!isalnum(label[i])){
			return -1;
		}
	}
	return 0;

}


int isOpcode(char* opcode) {
	if (strcmp(opcode, "add") == 0 || 
		strcmp(opcode, "and") == 0 || 
		strcmp(opcode, "br") == 0 || 
		strcmp(opcode, "brn") == 0 || 
		strcmp(opcode, "brz") == 0 || 
		strcmp(opcode, "brp") == 0 || 
		strcmp(opcode, "brnz") == 0 || 
		strcmp(opcode, "brnp") == 0 || 
		strcmp(opcode, "brzp") == 0 || 
		strcmp(opcode, "brnzp") == 0 || 
		strcmp(opcode, "halt") == 0 || 
		strcmp(opcode, "jmp") == 0 || 
		strcmp(opcode, "jsr") == 0 || 
		strcmp(opcode, "jsrr") == 0 || 
		strcmp(opcode, "ldb") == 0 || 
		strcmp(opcode, "ldw") == 0 || 
		strcmp(opcode, "lea") == 0 || 
		strcmp(opcode, "nop") == 0 || 
		strcmp(opcode, "not") == 0 || 
		strcmp(opcode, "ret") == 0 || 
		strcmp(opcode, "lshf") == 0 || 
		strcmp(opcode, "rshfl") == 0 || 
		strcmp(opcode, "rshfa") == 0 || 
		strcmp(opcode, "rti") == 0 || 
		strcmp(opcode, "stb") == 0 || 
		strcmp(opcode, "stw") == 0 || 
		strcmp(opcode, "trap") == 0 || 
		strcmp(opcode, "xor") == 0 || 
		strcmp(opcode, "add") == 0  
											) {
		return 0;
	}
	else {
		return -1;
	}
}




int toNum( char * pStr )
{
   char * t_ptr;
   char * orig_pStr;
   int t_length,k;
   int lNum, lNeg = 0;
   long int lNumLong;

   orig_pStr = pStr;
   if( *pStr == '#' )                /* decimal */
   { 
     pStr++;
     if( *pStr == '-' )            /* dec is negative */
     {
       lNeg = 1;
       pStr++;
     }
     t_ptr = pStr;
     t_length = strlen(t_ptr);
     for(k=0;k < t_length;k++)
     {
       if (!isdigit(*t_ptr))
       {
     printf("Error: invalid decimal operand, %s\n",orig_pStr);
     exit(4);
       }
       t_ptr++;
     }
     lNum = atoi(pStr);
     if (lNeg)
       lNum = -lNum;
 
     return lNum;
   }
   else if( *pStr == 'x' )    /* hex */
   {
     pStr++;
     if( *pStr == '-' )            /* hex is negative */
     {
       lNeg = 1;
       pStr++;
     }
     t_ptr = pStr;
     t_length = strlen(t_ptr);
     for(k=0;k < t_length;k++)
     {
       if (!isxdigit(*t_ptr))
       {
     printf("Error: invalid hex operand, %s\n",orig_pStr);
     exit(4);
       }
       t_ptr++;
     }
     lNumLong = strtol(pStr, NULL, 16);    /* convert hex string into integer */
     lNum = (lNumLong > INT_MAX)? INT_MAX : lNumLong;
     if( lNeg )
       lNum = -lNum;
     return lNum;
   }
   else
   {
    printf( "Error: invalid operand, %s\n", orig_pStr);
    exit(4); 
    /*This has been changed from error code 3 to error code 4, see clarification 12 */
   }
}


int readAndParse( FILE * pInfile, char * pLine, char ** pLabel, char ** pOpcode, char ** pArg1, char ** pArg2, char ** pArg3, char ** pArg4 )
    {
       char * lRet, * lPtr;
       int i;
       if( !fgets( pLine, MAX_LINE_LENGTH, pInfile ) )
        return( DONE );
       for( i = 0; i < strlen( pLine ); i++ )
        pLine[i] = tolower( pLine[i] );
       
           /* convert entire line to lowercase */
       *pLabel = *pOpcode = *pArg1 = *pArg2 = *pArg3 = *pArg4 = pLine + strlen(pLine);

       /* ignore the comments */
       lPtr = pLine;

       while( *lPtr != ';' && *lPtr != '\0' &&
       *lPtr != '\n' ) 
        lPtr++;

       *lPtr = '\0';
       if( !(lPtr = strtok( pLine, "\t\n ," ) ) ) 
        return( EMPTY_LINE );

       if( isOpcode( lPtr ) == -1 && lPtr[0] != '.' ) /* found a label */
       {
        *pLabel = lPtr;
        if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
       }
       
           *pOpcode = lPtr;

       if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
       
           *pArg1 = lPtr;
       
           if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

       *pArg2 = lPtr;
       if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

       *pArg3 = lPtr;

       if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

       *pArg4 = lPtr;

       return( OK );
    }

    /* Note: MAX_LINE_LENGTH, OK, EMPTY_LINE, and DONE are defined values */
