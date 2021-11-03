/*-----------------------------------------------
 Submitted By: Dillon Mead, Benjamin Ranew, Michael Hall
 Homework Number: Project 1
 Credit to: Aaron Van De Brook for memory file reader.
 

 Submitted On: 11 November 2021

 By submitting this program with my name,
 I affirm that the creation and modification
 of this program is primarily my own work.
------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#define HALT_OPCODE 0x19

// Registers simulated as global variables

// 16 bit Program Counter. Address of next instruction
uint16_t pc = 0;

// 8 bit Instruction Register. Contains current instruction
uint8_t ir = 0;

// 16 bit Memory Address Register. Holds pointer to address in memory.
uint16_t mar = 0;

// 8 bit Accumulator. Used to operate on data.
uint8_t acc = 0;

// memory array
unsigned char memory[65536];

/**
 * @param No input.
 * @return No return.
 * Uses program counter as index of memory array. Stores instruction from memory into instruction register.
 * Increases program counter to point at the next instruction.
 */
void fetchNextInstruction(void){
    ir = memory[pc++]; 
 //Michael Hall wrote an outline for this currently.
    //Right, made an initial format.  I've got this loaded into my text editor, just pushing changes.
 //I swear if this breaks something.  IT SHOULDN'T, although it's untested. 
 //Im still kinda wondering about where PC will increment?  Maybe ill figure it out.  
 if(ir & 0x80 == 0x80){ //Checks for math/ logic operations  && is going to be stupidly useful, since I can check individual bits.  
	
    switch(ir & 0x0c){ //Looks at the last two bits of the first 4 and checks where it goes: && with ir since those are the only bits its' looking for.  
    // This checks the first half of the first hex bit
    //All the statements inside will check the last two.  
      case 0x00: // Sets the destination as indirect, mar. since its 0000
      //Putting another switch here to look at the first 2 of the first 4, so it's something like ir && 03? 
       break;

      case 0x04: // Sets the destination as an acc  since 0100
      //Putting another switch here to look at the first 2, so it's something like ir && 03? 

       break;
      case 0x08: // Sets the destination to Address register mar since it's 1000
      //Putting another switch here to look at the first 2, so it's something like ir && 03? 

       break;
      case 0x0c: // Sets the destination to Memory, since it's 1100

       //Putting another switch here to look at the first 2, so it's something like ir && 03? 

       break;

      default:
        //This state shouldn't happen
       break;
		} //Going from verilog to C makes me want to put 'begin' and 'end' everywhere smh.  
	}//All of the functions above are generally the same, since it's branching into different statments considering what ever the first 4 bits are. 
else if((ir & 0xf0) == 0){
 
} //Grabbing this from her QnA document.  Basically it checks if ir && with all ones, it's a mem op
 
 //Putting code designating a NOP stamtent
 /*else if(ir && 0x18){ Commented since I don't know if it's correct?
     pc++;
} *\



//The memory functions is going to be below this, and will be structered similary, probably.  
//Gonna compare 0f, since documents show that's memory ops
//Ill think about memory later.  
    /*
    // if instruction register is blank operation
    if(ir == NOP_CODE){
        ir = memory[pc++];
    }
    */
}

/**
 * @param No input.
 * @return No return.
 * Examines ir and determines execution opertion. Performs operation on registers and memory.
 */
void executeInstruction(void){

}

int main(int argc, char* argv[]){
    // File reader transfers info from memory file to memory array.
    if(argc != 3) {
        fprintf(stderr, "Please provide an input file, such as: .\%s [mem_in] [mem_out]\n", argv[0]);
        return -1;
    }

    FILE *mem_out, *mem_in = fopen(argv[1], "r");
    uint8_t *mem_ptr = memory;

    while(!feof(mem_in)){
        fscanf(mem_in, "%x", mem_ptr++);
    }
    fclose(mem_in);

    // Execution loop. Continue fetching and executing until program counter
    // points to a HALT instruction.
    while(memory[pc] != HALT_OPCODE){
        fetchNextInstruction();
        executeInstruction();
    }
    return 0;
}
