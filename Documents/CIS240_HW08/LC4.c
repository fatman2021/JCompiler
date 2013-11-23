#include "LC4.h"
#define INSN_OP(I)((I) >> 12)
#define INSN_11_9(I)(((I) >> 9) & 0x7)
#define INSN_8_6(I)(((I) >> 6) & 0x7)
#define INSN_2_0(I)((I) & 0x7)






// Fill in control signals based on the current instruction
int DecodeCurrentInstruction (unsigned short int INSN, ControlSignals *theControls){
	switch (INSN_OP(INSN)) {
		case 0x0 :							// branch
			theControls->PCMux_CTL = 0;
			theControls->rsMux_CTL = 0;
			theControls->rtMux_CTL = 0;
			theControls->rdMux_CTL = 0;
			theControls->regFile_WE = 0;
			theControls->regInputMux_CTL = 0;
			theControls->Arith_CTL = 0;
			theControls->ArithMux_CTL = 0;
			theControls->LOGIC_CTL = 0;
			theControls->LogicMux_CTL = 0;
			theControls->SHIFT_CTL = 0;
			theControls->CONST_CTL = 0;
			theControls->CMP_CTL = 0;
			theControls->ALUMux_CTL = 0;
			theControls->NZP_WE = 0;
			theControls->DATA_WE = 0;
			theControls->Privilege_CTL = 0;
			break;
		case 0x1 :							// arithmetic
			switch ((INSN >> 3) & 0x7) {
				case 0x0 :	// add
					theControls->PCMux_CTL = 1;
					theControls->rsMux_CTL = 0;
					theControls->rtMux_CTL = 0;
					theControls->rdMux_CTL = 0;
					theControls->regFile_WE = 1;
					theControls->regInputMux_CTL = 0;
					theControls->Arith_CTL = 0;
					theControls->ArithMux_CTL = 0;
					theControls->LOGIC_CTL = 0;
					theControls->LogicMux_CTL = 0;
					theControls->SHIFT_CTL = 0;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 0;
					theControls->ALUMux_CTL = 0;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 0;
					break;
				case 0x1 :	// mul
					theControls->PCMux_CTL = 1;
					theControls->rsMux_CTL = 0;
					theControls->rtMux_CTL = 0;
					theControls->rdMux_CTL = 0;
					theControls->regFile_WE = 1;
					theControls->regInputMux_CTL = 0;
					theControls->Arith_CTL = 1;
					theControls->ArithMux_CTL = 0;
					theControls->LOGIC_CTL = 0;
					theControls->LogicMux_CTL = 0;
					theControls->SHIFT_CTL = 0;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 0;
					theControls->ALUMux_CTL = 0;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 0;
					break;
				case 0x2 : 	// sub
					theControls->PCMux_CTL = 1;
					theControls->rsMux_CTL = 0;
					theControls->rtMux_CTL = 0;
					theControls->rdMux_CTL = 0;
					theControls->regFile_WE = 1;
					theControls->regInputMux_CTL = 0;
					theControls->Arith_CTL = 2;
					theControls->ArithMux_CTL = 0;
					theControls->LOGIC_CTL = 0;
					theControls->LogicMux_CTL = 0;
					theControls->SHIFT_CTL = 0;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 0;
					theControls->ALUMux_CTL = 0;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 0;
					break;
				case 0x3 :	// div
					theControls->PCMux_CTL = 1;
					theControls->rsMux_CTL = 0;
					theControls->rtMux_CTL = 0;
					theControls->rdMux_CTL = 0;
					theControls->regFile_WE = 1;
					theControls->regInputMux_CTL = 0;
					theControls->Arith_CTL = 3;
					theControls->ArithMux_CTL = 0;
					theControls->LOGIC_CTL = 0;
					theControls->LogicMux_CTL = 0;
					theControls->SHIFT_CTL = 0;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 0;
					theControls->ALUMux_CTL = 0;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 0;
					break;
				default : 	// add imm
					theControls->PCMux_CTL = 1;
					theControls->rsMux_CTL = 0;
					theControls->rtMux_CTL = 0;
					theControls->rdMux_CTL = 0;
					theControls->regFile_WE = 1;
					theControls->regInputMux_CTL = 0;
					theControls->Arith_CTL = 0;
					theControls->ArithMux_CTL = 1;
					theControls->LOGIC_CTL = 0;
					theControls->LogicMux_CTL = 0;
					theControls->SHIFT_CTL = 0;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 0;
					theControls->ALUMux_CTL = 0;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 0;

			}
			break;
		case 0x2 :							// compare
			switch ((INST >> 7) & 0x3){
				case 0x0 :	// cmp
					theControls->PCMux_CTL = 1;
					theControls->rsMux_CTL = 2;
					theControls->rtMux_CTL = 0;
					theControls->rdMux_CTL = 0;
					theControls->regFile_WE = 0;
					theControls->regInputMux_CTL = 0;
					theControls->Arith_CTL = 0;
					theControls->ArithMux_CTL = 0;
					theControls->LOGIC_CTL = 0;
					theControls->LogicMux_CTL = 0;
					theControls->SHIFT_CTL = 0;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 0;
					theControls->ALUMux_CTL = 4;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 0;
					break;
				case 0x1 : 	// cmpu
					theControls->PCMux_CTL = 1;
					theControls->rsMux_CTL = 2;
					theControls->rtMux_CTL = 0;
					theControls->rdMux_CTL = 0;
					theControls->regFile_WE = 0;
					theControls->regInputMux_CTL = 0;
					theControls->Arith_CTL = 0;
					theControls->ArithMux_CTL = 0;
					theControls->LOGIC_CTL = 0;
					theControls->LogicMux_CTL = 0;
					theControls->SHIFT_CTL = 0;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 1;
					theControls->ALUMux_CTL = 4;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 0;
					break;
				case 0x2 :	// cmpi
					theControls->PCMux_CTL = 1;
					theControls->rsMux_CTL = 2;
					theControls->rtMux_CTL = 0;
					theControls->rdMux_CTL = 0;
					theControls->regFile_WE = 0;
					theControls->regInputMux_CTL = 0;
					theControls->Arith_CTL = 0;
					theControls->ArithMux_CTL = 0;
					theControls->LOGIC_CTL = 0;
					theControls->LogicMux_CTL = 0;
					theControls->SHIFT_CTL = 0;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 2;
					theControls->ALUMux_CTL = 4;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 0;
					break;
				case 0x3 :	// cmpiu
					theControls->PCMux_CTL = 1;
					theControls->rsMux_CTL = 2;
					theControls->rtMux_CTL = 0;
					theControls->rdMux_CTL = 0;
					theControls->regFile_WE = 0;
					theControls->regInputMux_CTL = 0;
					theControls->Arith_CTL = 0;
					theControls->ArithMux_CTL = 0;
					theControls->LOGIC_CTL = 0;
					theControls->LogicMux_CTL = 0;
					theControls->SHIFT_CTL = 0;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 3;
					theControls->ALUMux_CTL = 4;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 0;
			}
			break;
		case 0x4 :							// jump sub-routine
			// jsr
			if ((INST >> 11) & 0x1) { 	/
				theControls->PCMux_CTL = 5;
				theControls->rsMux_CTL = 0;
				theControls->rtMux_CTL = 0;
				theControls->rdMux_CTL = 1;
				theControls->regFile_WE = 1;
				theControls->regInputMux_CTL = 2;
				theControls->Arith_CTL = 0;
				theControls->ArithMux_CTL = 0;
				theControls->LOGIC_CTL = 0;
				theControls->LogicMux_CTL = 0;
				theControls->SHIFT_CTL = 0;
				theControls->CONST_CTL = 0;
				theControls->CMP_CTL = 0;
				theControls->ALUMux_CTL = 0;
				theControls->NZP_WE = 1;
				theControls->DATA_WE = 0;
				theControls->Privilege_CTL = 0;
			}
			//jsrr
			else { 
				theControls->PCMux_CTL = 3;
				theControls->rsMux_CTL = 0;
				theControls->rtMux_CTL = 0;
				theControls->rdMux_CTL = 1;
				theControls->regFile_WE = 1;
				theControls->regInputMux_CTL = 2;
				theControls->Arith_CTL = 0;
				theControls->ArithMux_CTL = 0;
				theControls->LOGIC_CTL = 0;
				theControls->LogicMux_CTL = 0;
				theControls->SHIFT_CTL = 0;
				theControls->CONST_CTL = 0;
				theControls->CMP_CTL = 0;
				theControls->ALUMux_CTL = 0;
				theControls->NZP_WE = 1;
				theControls->DATA_WE = 0;
				theControls->Privilege_CTL = 0;
			}
			break;
		case 0x5 :							// logic
			switch ((INSN >> 3) & 0x7) {
				case 0x0 :	// and
					theControls->PCMux_CTL = 1;
					theControls->rsMux_CTL = 0;
					theControls->rtMux_CTL = 0;
					theControls->rdMux_CTL = 0;
					theControls->regFile_WE = 1;
					theControls->regInputMux_CTL = 0;
					theControls->Arith_CTL = 0;
					theControls->ArithMux_CTL = 0;
					theControls->LOGIC_CTL = 0;
					theControls->LogicMux_CTL = 0;
					theControls->SHIFT_CTL = 0;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 0;
					theControls->ALUMux_CTL = 1;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 0;
					break;
				case 0x1 :	// not
					theControls->PCMux_CTL = 1;
					theControls->rsMux_CTL = 0;
					theControls->rtMux_CTL = 0;
					theControls->rdMux_CTL = 0;
					theControls->regFile_WE = 1;
					theControls->regInputMux_CTL = 0;
					theControls->Arith_CTL = 0;
					theControls->ArithMux_CTL = 0;
					theControls->LOGIC_CTL = 1;
					theControls->LogicMux_CTL = 0;
					theControls->SHIFT_CTL = 0;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 0;
					theControls->ALUMux_CTL = 1;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 0;
					break;
				case 0x2 : 	// or
					theControls->PCMux_CTL = 1;
					theControls->rsMux_CTL = 0;
					theControls->rtMux_CTL = 0;
					theControls->rdMux_CTL = 0;
					theControls->regFile_WE = 1;
					theControls->regInputMux_CTL = 0;
					theControls->Arith_CTL = 0;
					theControls->ArithMux_CTL = 0;
					theControls->LOGIC_CTL = 2;
					theControls->LogicMux_CTL = 0;
					theControls->SHIFT_CTL = 0;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 0;
					theControls->ALUMux_CTL = 1;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 0;
					break;
				case 0x3 :	// xor
					theControls->PCMux_CTL = 1;
					theControls->rsMux_CTL = 0;
					theControls->rtMux_CTL = 0;
					theControls->rdMux_CTL = 0;
					theControls->regFile_WE = 1;
					theControls->regInputMux_CTL = 0;
					theControls->Arith_CTL = 0;
					theControls->ArithMux_CTL = 0;
					theControls->LOGIC_CTL = 3;
					theControls->LogicMux_CTL = 0;
					theControls->SHIFT_CTL = 0;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 0;
					theControls->ALUMux_CTL = 1;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 0;
					break;
				default : 	// and imm
					theControls->PCMux_CTL = 1;
					theControls->rsMux_CTL = 0;
					theControls->rtMux_CTL = 0;
					theControls->rdMux_CTL = 0;
					theControls->regFile_WE = 1;
					theControls->regInputMux_CTL = 0;
					theControls->Arith_CTL = 0;
					theControls->ArithMux_CTL = 0;
					theControls->LOGIC_CTL = 0;
					theControls->LogicMux_CTL = 1;
					theControls->SHIFT_CTL = 0;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 0;
					theControls->ALUMux_CTL = 1;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 0;
			break;
		case 0x6 :							// load
			theControls->PCMux_CTL = 1;
			theControls->rsMux_CTL = 0;
			theControls->rtMux_CTL = 0;
			theControls->rdMux_CTL = 0;
			theControls->regFile_WE = 1;
			theControls->regInputMux_CTL = 1;
			theControls->Arith_CTL = 0;
			theControls->ArithMux_CTL = 2;
			theControls->LOGIC_CTL = 0;
			theControls->LogicMux_CTL = 0;
			theControls->SHIFT_CTL = 0;
			theControls->CONST_CTL = 0;
			theControls->CMP_CTL = 0;
			theControls->ALUMux_CTL = 0;
			theControls->NZP_WE = 1;
			theControls->DATA_WE = 0;
			theControls->Privilege_CTL = 0;
			break;
		case 0x7 :							// store
			theControls->PCMux_CTL = 1;
			theControls->rsMux_CTL = 0;
			theControls->rtMux_CTL = 1;
			theControls->rdMux_CTL = 0;
			theControls->regFile_WE = 0;
			theControls->regInputMux_CTL = 0;
			theControls->Arith_CTL = 0;
			theControls->ArithMux_CTL = 2;
			theControls->LOGIC_CTL = 0;
			theControls->LogicMux_CTL = 0;
			theControls->SHIFT_CTL = 0;
			theControls->CONST_CTL = 0;
			theControls->CMP_CTL = 0;
			theControls->ALUMux_CTL = 0;
			theControls->NZP_WE = 0;
			theControls->DATA_WE = 1;
			theControls->Privilege_CTL = 0;
			break;
		case 0x8 : 							// RTI
			break;
		case 0x9 : 							// constant
			break; 
		case 0xA :							// shift
			break;
		case 0xC :							// jump
			break;
		case 0xD : 							// hi-constant
			break;
		case 0xF :							// trap
			break;
		default :
		puts("Invalid instruction.");
		return 1;
	}
}

// Simulate the action of the datapath
int SimulateDatapath (ControlSignals *theControls, MachineState *theMachineState, DatapathSignals *theDatapath);

// Update Machine State based on the prevailing control and Datapath Signals
int UpdateMachineState (ControlSignals *theControls, MachineState *theMachineState, DatapathSignals *theDatapath);

// Reset the machine state as Pennsim would do
void Reset (MachineState *theMachineState);