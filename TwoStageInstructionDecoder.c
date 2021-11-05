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
//Ranew Start
    int address;

	if ((ir & 0x80) == 0x80){ // Mathematical or Logical Operation
		// Destination and source values
		int destination;
		int source;

		switch(ir & 0x0c){ // Destination
			case 0x0:
				destination = memory[mar]; // Indirect (mar used as a pointer)
				break;
			case 0x4:
				destination = acc; // Accumulator acc
				break;
			case 0x8:
				destination = mar; // Address register mar
				break;
			case 0xc:
				destination = memory[((memory[old_pc + 1] << 8) + memory[old_pc + 2])]; // Memory
				break;
		}

		switch(ir & 0x03){ // Source
			case 0x0:
				source = memory[mar]; // Indirect (mar used as a pointer)
				break;
			case 0x1:
				source = acc; // Accumulator acc
				break;
			case 0x2:
				if((ir & 0x0c) == 0x8) // Constant
					source = (memory[pc - 2] << 8) + memory[pc -1];
				else
					source = memory[pc - 1];
				break;
			case 0x3:
				if((ir & 0x0c) == 0x8){ // Memory
					address = ((memory[old_pc + 1] << 8) + memory[old_pc + 2]);
					source = (memory[address] << 8) + memory[address + 1];
				}
				else
					source = memory[((memory[old_pc + 1] << 8) + memory[old_pc + 2])];
				break;
		}

		switch (ir & 0x70){ // Checking the function
			case 0x00: // AND
				destination &= source;
				break;
			case 0x10: // OR
				destination |= source;
				break;
			case 0x20: // XOR
				destination ^= source;
				break;
			case 0x30: // ADD
				destination += source;
				break;
			case 0x40: // SUB
				destination -= source;
				break;
			case 0x50: // INC
				destination++;
				break;
			case 0x60: // DEC
				destination--;
				break;
			case 0x70: // NOT
				destination = !destination;
			break;
			default:
				break;
		}
		// Store destination
		switch(ir & 0x0c){ // Isolate destination id
			case 0x0:
				memory[mar] = destination & 0xff; // Indirect (mar used as a pointer)
				break;
			case 0x4:
				acc = destination & 0xff; // Accumulator acc
				break;
			case 0x8:
				mar = destination & 0xffff; // Address register mar
				break;
			case 0xc:
				memory[((memory[old_pc + 1] << 8) + memory[old_pc + 2])] = destination & 0xff; // Memory
				break;
		}
	}

	else if ((ir & 0xf0) == 0){ // Store/Load function
		if ((ir & 0x08) == 0){ // Store
			if ((ir & 0x04) == 0){ // Storing from Register = Accumulator acc
				switch(ir & 0x03){
					case 0:
						memory[((memory[old_pc + 1] << 8) + memory[old_pc + 2])] = acc; // Storing with Method = Operand is used as address
						break;
					case 1: // Operand is used as a Constant
						break;
					case 2:
						memory[mar] = acc; // Storing with Method = Indirect (mar used as a pointer)
						break;
					default:
						break;
				}
			}
			else{ // Storing from Register = Index register mar
				switch(ir & 0x03){
					case 0:
						memory[((memory[old_pc + 1] << 8) + memory[old_pc + 2])] = (mar >> 8) & 0xff; // Storing with Method = Operand is used as address
						memory[((memory[old_pc + 1] << 8) + memory[old_pc + 2]) + 1] = mar & 0xff;
						break;
					case 1: // Operand is used as a Constant
						break;
					case 2:
						memory[mar] = (mar >> 8) & 0xff; // Storing with Method = Indirect (mar used as a pointer)
						memory[mar + 1] = mar & 0xff;
						break;
					default:
						break;
				}
			}
		}
		else{ // Load
			if ((ir & 0x04) == 0){ // Loading into register Accumulator acc
				switch(ir & 0x03){
					case 0:
						acc = memory[((memory[old_pc + 1] << 8) + memory[old_pc + 2])]; // Method = Operand is used as address
						break;
					case 1:
						acc = memory[old_pc + 1]; // Method = Operand is used as a constant
						break;
					case 2:
						acc = memory[mar]; // Method = Indirect (mar used as a pointer)
						break;
					default:
						break;
				}
			}
			else{ // Loading into mar
				int oldMAR = mar;

				switch(ir & 0x03){
					case 0: // Method = Operand is used as address
						mar = memory[((memory[old_pc + 1] << 8) + memory[old_pc + 2])];
						mar <<=8;
						mar += memory[((memory[old_pc + 1] << 8) + memory[old_pc + 2]) + 1];
						break;
					case 1: // Method = Operand is used as a constant
						mar = memory[old_pc + 1];
						mar <<= 8;
						mar += memory[old_pc + 2];
						break;
					case 2: // Method = Indirect (mar used as pointer)
						mar = memory[oldMAR];
						mar <<= 8;
						mar += memory[oldMAR + 1];
						break;
					default:
						break;
				}
			}
		}
	}

	else if ((ir & 0xF8) == 0x10){ // Branches
		address = (memory[old_pc + 1] << 8) + memory[old_pc + 2];

		switch (ir & 0x07){
			case 0: // BRA (Unconditional branch/branch always)
				pc = address;
				break;
			case 1: // BRZ (Branch if acc = 0)
				if (acc == 0)
					pc = address;
				break;
			case 2: // BNE (Branch if acc != 0)
				if (acc != 0)
					pc = address;
				break;
			case 3: // BLT (Branch if acc < 0)
				if ((acc & 0x80) != 0)
					pc = address;
				break;
			case 4: // BLE (Branch if acc <= 0)
				if (((acc & 0x80) != 0) || (acc == 0))
					pc = address;
				break;
			case 5: // BGT (Branch if acc > 0)
				if (((acc & 0x80) == 0) && (acc != 0))
					pc = address;
				break;
			case 6: // BGE (Branch if acc >= 0)
				if ((acc & 0x80) == 0)
					pc = address;
				break;
			default:
				break;
		}
	}

	else{ // All else is either a "No Operation", "Halt" or and illegal opcode.
		if(ir == 0x18) // NOP "No Operation"
		{

		}

		else if(ir == 0x19) // Halt
		{

		}

		else // Illegal Operation
		{

		}
	}
} // Ranew End

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
