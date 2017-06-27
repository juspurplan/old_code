#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

 /* A couple of nice tricks to help reverse engineer this project
 *
 * 1) make Source.s will create the assembly listing
 * 2) after running gdb you can 
 *   a) get a disassembly listing by executing the disassemble &main
 *   b) look at a register (like ebp) using "print $ebp"
 *   c) display the current instruction with "display /i $pc"
 */

void doit1(void) {
}

void die(void) {
    abort();
}

void getName(char* name) {
    printf("enter your name: ");
    scanf("%s", name);
}

int getData(int data[]) {
    int k = 0;
    char buff[16];
    int val;
    while(1) {
        printf("enter value %d (press enter to keep default, ctrl-D<ret> to end) [%d]",
                k, data[k]);
        gets(buff);
        if (feof(stdin)) { break; }
        if (buff[0]) {
            sscanf(buff, "%d", &data[k]);
        } else {
            printf("OK, not changing the data\n");
        }
        k += 1;
    }
    return k;
}


void doit2(void) {
    int data[12];
    printf("name is at 0x%x\n", data);

    char resp = 'n';
    getData(data);
    printf("\n");
}

void doit3(){
    char buff[8];
    printf("data is 0x%x 0x%x\n", *(int*)&buff[8], *(int*)&buff[4]);
    gets(buff);
    printf("now data is 0x%x 0x%x\n", *(int*)&buff[8], *(int*)&buff[4]);
}

void test1(void) {
    /* test1: don't die and win */
    doit1();
    die();
    printf("You Win (test1)!\n");
}

void test2(void) {
    /* test2: don't die and win */
    doit2();
    die();
    printf("You win!\n");
}

    /* test3 must be run using "setarch `uname -m` -R ./prog < input.txt" so that
     * Linux will assign the same addresses each time the program
     * is run -- if you know what addresses are used, then you know
     * what values need to be overflowed into the array
     * To do test3, you will need to create input.txt. You may need to
     * write a program to fill input.txt with the right character data
     * (some of the right characters may not be printable) 
     * comment out the invocations of test1 and test2 and uncomment test3
     */
void test3(void) {
    /* test3: don't die and win */
    doit3();
    die();
    printf("You win\n");
}


int main(void) {
    test1();
    //test2();
    //test3();
}
