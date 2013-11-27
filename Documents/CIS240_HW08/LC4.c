#include "LC4.h"
#include <stdio.h>

// macros to access different bits
#define INSN_OP(I)((I) >> 12)
#define INSN_5_3(I)(((I) >> 3) & 0x7)
#define INSN_8_7(I)(((I) >> 7) & 0x3)
#define INSN_11(I)((I >> 11) & 0x1)
#define INSN_5_4(I)((I >> 4) & 0x3)
#define INSN_11_9(I)((I >> 9) & 0x7)
#define INSN_8_6(I)((I >> 6) & 0x7)
#define INSN_2_0(I)(I & 0x7)
#define INSN_3_0(I)(I & 0xF)
#define SEXT5(I)(((I & 0x1F) > 0xF) ? I | 0xFFE0 : I)
#define SEXT6(I)(((I & 0x3F) > 0x1F) ? I | 0xFFC0 : I)
#define SEXT7(I)(((I & 0x7F) > 0x3F) ? I | 0xFF80 : I)
#define SEXT9(I)(((I & 0x1FF) > 0xFF) ? I | 0xFE00 : I)
#define SEXT11(I)(((I & 0x7FF) > 0x3FF) ? I | 0xF800 : I)





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
			theControls->Privilege_CTL = 2;
			break;
		case 0x1 :							// arithmetic
			switch (INSN_5_3(INSN)) {
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
					theControls->Privilege_CTL = 2;
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
					theControls->Privilege_CTL = 2;
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
					theControls->Privilege_CTL = 2;
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
					theControls->Privilege_CTL = 2;
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
					theControls->Privilege_CTL = 2;
					break;
			}
			break;
		case 0x2 :							// compare
			switch (INSN_8_7(INSN)){
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
					theControls->Privilege_CTL = 2;
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
					theControls->Privilege_CTL = 2;
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
					theControls->Privilege_CTL = 2;
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
					theControls->Privilege_CTL = 2;
			}
			break;
		case 0x4 :							// jump sub-routine
			// jsr
			if (INSN_11(INSN)) { 	
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
				theControls->Privilege_CTL = 2;
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
				theControls->Privilege_CTL = 2;
			}
			break;
		case 0x5 :							// logic
			switch (INSN_5_3(INSN)) {
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
					theControls->Privilege_CTL = 2;
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
					theControls->Privilege_CTL = 2;
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
					theControls->Privilege_CTL = 2;
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
					theControls->Privilege_CTL = 2;
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
					theControls->Privilege_CTL = 2;
			}
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
			theControls->Privilege_CTL = 2;
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
			theControls->Privilege_CTL = 2;
			break;
		case 0x8 : 							// RTI
			theControls->PCMux_CTL = 3;
			theControls->rsMux_CTL = 1;
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
		case 0x9 : 							// constant
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
			theControls->ALUMux_CTL = 3;
			theControls->NZP_WE = 1;
			theControls->DATA_WE = 0;
			theControls->Privilege_CTL = 2;
			break; 
		case 0xA :							// shift and mod
			switch (INSN_5_4(INSN)) {
				case 0x0 :	// SLL
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
					theControls->ALUMux_CTL = 2;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 2;
					break;
				case 0x1 :	// SRA
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
					theControls->SHIFT_CTL = 1;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 0;
					theControls->ALUMux_CTL = 2;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 2;
					break;
				case 0x2 :	// SRL
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
					theControls->SHIFT_CTL = 2;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 0;
					theControls->ALUMux_CTL = 2;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 2;
					break;
				case 0x3 :	// MOD
					theControls->PCMux_CTL = 1;
					theControls->rsMux_CTL = 0;
					theControls->rtMux_CTL = 0;
					theControls->rdMux_CTL = 0;
					theControls->regFile_WE = 1;
					theControls->regInputMux_CTL = 0;
					theControls->Arith_CTL = 4;
					theControls->ArithMux_CTL = 0;
					theControls->LOGIC_CTL = 0;
					theControls->LogicMux_CTL = 0;
					theControls->SHIFT_CTL = 0;
					theControls->CONST_CTL = 0;
					theControls->CMP_CTL = 0;
					theControls->ALUMux_CTL = 0;
					theControls->NZP_WE = 1;
					theControls->DATA_WE = 0;
					theControls->Privilege_CTL = 2;
			}
			break;
		case 0xC :							// jump
			// jmp
			if (INSN_11(INSN)) {
				theControls->PCMux_CTL = 2;
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
				theControls->Privilege_CTL = 2;
			}
			// jmpr
			else {
				theControls->PCMux_CTL = 3;
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
				theControls->Privilege_CTL = 2;
			}
			break;
		case 0xD : 							// hi-constant
			if((INSN_8_7(INSN) != 0x2) && (INSN_8_7(INSN) != 0x3)) {
				puts("Invalid hi-const instruction.");
				break;
			}
			theControls->PCMux_CTL = 1;
			theControls->rsMux_CTL = 2;
			theControls->rtMux_CTL = 0;
			theControls->rdMux_CTL = 0;
			theControls->regFile_WE = 1;
			theControls->regInputMux_CTL = 0;
			theControls->Arith_CTL = 0;
			theControls->ArithMux_CTL = 0;
			theControls->LOGIC_CTL = 0;
			theControls->LogicMux_CTL = 0;
			theControls->SHIFT_CTL = 0;
			theControls->CONST_CTL = 1;
			theControls->CMP_CTL = 0;
			theControls->ALUMux_CTL = 3;
			theControls->NZP_WE = 1;
			theControls->DATA_WE = 0;
			theControls->Privilege_CTL = 2;
			break;
		case 0xF :							// trap
			theControls->PCMux_CTL = 4;
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
			theControls->Privilege_CTL = 1;
			break;
		default :
			printf("Invalid instruction: %d", INSN);
			return 1;
	}
	return 0;
}

// Simulate the action of the datapath
int SimulateDatapath (ControlSignals *theControls, MachineState *theMachineState, DatapathSignals *theDatapath) {

	unsigned short int INSN = theMachineState->memory[theMachineState->PC];
	// RS output
	if(theControls->rsMux_CTL == 0) {
		theDatapath->RS = theMachineState->R[INSN_8_6(INSN)];
	}
	else if(theControls->rsMux_CTL == 1) {
		theDatapath->RS = theMachineState->R[7];
	}
	else if(theControls->rsMux_CTL == 2) {
		theDatapath->RS = theMachineState->R[INSN_11_9(INSN)];
	}
	// RT output
	if(theControls->rtMux_CTL == 0) {
		theDatapath->RT = theMachineState->R[INSN_2_0(INSN)];
	}
	else if(theControls->rtMux_CTL == 1) {
		theDatapath->RT = theMachineState->R[INSN_11_9(INSN)];
	}
	// Arithmetic ops -- CHECK unsigned vs. signed calcs
	switch (theControls->Arith_CTL) {
		case 0 :
			switch (theControls->ArithMux_CTL) {
				case 0 :
					theDatapath->ArithmeticOps = (theDatapath->RS) + (theDatapath->RT);
					break;
				case 1 : 
					theDatapath->ArithmeticOps = (theDatapath->RS) + SEXT5(INSN); 
					break;
				case 2 :
					theDatapath->ArithmeticOps = (theDatapath->RS) + SEXT6(INSN);
			}
			break;
		case 1 :
			theDatapath->ArithmeticOps = (theDatapath->RS)*(theDatapath->RT);
			break;
		case 2 :
			theDatapath->ArithmeticOps = (theDatapath->RS)-(theDatapath->RT);
			break;
		case 3 : 
			theDatapath->ArithmeticOps = (theDatapath->RS)/(theDatapath->RT);
			break;
		case 4 :
			theDatapath->ArithmeticOps = (theDatapath->RS)%(theDatapath->RT);
	}
	// LogicalOps
	switch (theControls->LOGIC_CTL) {
		case 0 :
			if(theControls->LogicMux_CTL == 0) {
				theDatapath->LogicalOps = (theDatapath->RS)&(theDatapath->RT);
			}
			else if(theControls->LogicMux_CTL == 1) {
				theDatapath->LogicalOps = (theDatapath->RS) & SEXT5(INSN);
			}
			break;
		case 1 :
			theDatapath->LogicalOps = ~(theDatapath->RS);
			break;
		case 2 : 
			theDatapath->LogicalOps = (theDatapath->RS)|(theDatapath->RT);
			break;
		case 3 :
			theDatapath->LogicalOps = (theDatapath->RS)^(theDatapath->RT);
	}
	// DEFINITELY GO OVER THIS
	// Shifter
	switch (theControls->SHIFT_CTL) {
		case 0 :
			theDatapath->Shifter = theDatapath->RS << ((unsigned short int)INSN_3_0(INSN));
			break;
		//CHECK THIS EXTENSIVELY  
		case 1 : 
			int i;
			for(i = 0; i < INSN_3_0(INSN); i++) {
				theDatapath->RS = (theDatapath->RS >> 1) & 0x8000;
			}
			break;
		// this one should be fine because the RS is unsigned so the operator just shifts in zeroes
		case 2 : 
			theDatapath->Shifter = theDatapath->RS >> INSN_3_0(INSN);
	}
	// Constants
	switch (theControls->CONST_CTL) {
		case 0 :
			theDatapath->Constants = SEXT9(INSN);
			break;
		case 1 : 
			theDatapath->Constants = (theDatapath->RS & 0xFF)|((INSN & 0xFF) << 8);
	}
	// NEED TO FIX : Comparator-- can we just do that subtraction and then cast the result? that seems like what we should do but then NZP would be updated based on sign regardless?
	switch (theControls->CMP_CTL) {
		case 0 :

	}
	// ALUMux
	switch (theControls->ALUMux_CTL) {
		case 0 : 
			theDatapath->ALUMux = theDatapath->ArithmeticOps;
			break;
		case 1 :
			theDatapath->ALUMux = theDatapath->LogicalOps;
			break;
		case 2 :
			theDatapath->ALUMux = theDatapath->Shifter;
			break;
		case 3 : 
			theDatapath->ALUMux = theDatapath->Constants;
			break;
		case 4 :
			theDatapath->ALUMux = theDatapath->Comparator;
	}
	// regInputMux
	switch (theControls->regInputMux_CTL) {
		case 0 :
			theDatapath->regInputMux = theDatapath->ALUMux;
			break;
		case 1 :
			theDatapath->regInputMux = theMachineState->memory[theDatapath->ALUMux];
			break;
		case 2 :
			theDatapath->regInputMux = (theMachineState->PC) + 1;
	}
	// PCMux
	switch (theControls->PCMux_CTL) {
		case 0 :
			if(INSN_11_9(INSN) & (theMachineState->PSR & 0x7)) { //if the two have any bits in common then the test is satisfied
				theDatapath->PCMux = theMachineState->PC + 1 + SEXT9(INSN);
			}
			else {
				theDatapath->PCMux = theMachineState->PC + 1;
			}
			break;
		case 1 :
			theDatapath->PCMux = theMachineState->PC + 1;
			break;
		case 2 :
			theDatapath->PCMux = theMachineState->PC + 1 + SEXT11(INSN);
			break;
		case 3 :
			theDatapath->PCMux = theDatapath->RS;
			break;
		case 4 :
			theDatapath->PCMux = 0x8000 | (INSN & 0xFF);
			break;
		case 5 :
			theDatapath->PCMux = (theMachineState->PC & 0x8000) | ((INSN & 0x7FF) << 4);
	}
	return 0;
}

// Update Machine State based on the prevailing control and Datapath Signals
int UpdateMachineState (ControlSignals *theControls, MachineState *theMachineState, DatapathSignals *theDatapath){
	unsigned short int INSN = theMachineState->memory[theMachineState->PC];

	if(theDatapath->PCMux > 0x1FFF || theDatapath->PCMux < 0x8000)

	theMachineState->PC = theDatapath->PCMux;

	if(theControls->NZP_WE == 1) {
		// need to cast as signed so that nzp can be updated accurately 
		signed short int input = (signed short int)theDatapath->regInputMux;
		if(input > 0) {
			theMachineState->PSR = theMachineState->PSR | 0x1; 
		}
		else {
			theMachineState->PSR = theMachineState->PSR & 0xFFFE;
		}
		if(input == 0) {
			theMachineState->PSR = theMachineState->PSR | 0x2;
		}
		else {
			theMachineState->PSR = theMachineState->PSR & 0xFFFD;
		}
		if(input < 0) {
			theMachineState->PSR = theMachineState->PSR | 0x4;
		}
		else {
			theMachineState->PSR = theMachineState->PSR & 0xFFFB;
		}
	}
	//this is where we would catch errors I believe
	if(theControls->Privilege_CTL == 0) {
		theMachineState->PSR = theMachineState->PSR & 0x7FFF;
	}
	else if(theControls->Privilege_CTL == 1) {
		theMachineState->PSR = theMachineState->PSR | 0x8000;
	}
	// also here we could catch errors--might want to reverse order of computation
	if(theControls->regFile_WE == 1) {
		if(theControls->rdMux_CTL == 0) {
			theMachineState->R[INSN_11_9(INSN)] = theDatapath->regInputMux;
		}
		else if (theControls->rdMux_CTL == 1) { 
			theMachineState->R[7] = theDatapath->regInputMux;
		}
	}
	// and here obvi
	if(theControls->DATA_WE == 1) {
		theMachineState->memory[theDatapath->ALUMux] = theDatapath->RT;
	}
	return 0;
}

// Reset the machine state as Pennsim would do
void Reset (MachineState *theMachineState) {
	int i;
	theMachineState->PC = 0x8200;
	theMachineState->PSR = 0x8002;
	for(i = 0; i < 8; i++) {
		theMachineState->R[i] = 0;
	}
	for(i = 0; i < 65536; i++) {
		theMachineState->memory[i] = 0;
	}

}
