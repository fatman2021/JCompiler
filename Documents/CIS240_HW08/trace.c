#include "ObjectFiles.h"
#include "LC4.h"
#include <stdlib.h>


int main(int argc, char *argv[]) {
	FILE *outputFile;
	MachineState *theMachineState;
	ControlSignals *theControlSignals;
	DatapathSignals *theDatapath;
	int i;

	outputFile = fopen(argv[1], "w");
	theMachineState = malloc(sizeof(*theMachineState));
	Reset(theMachineState);
	// check piazza for how to handle errors produced by ReadObjectFile
	for(i = 2; i < argc; i++) {
		ReadObjectFile(argv[i], theMachineState));
	}

	theControlSignals = malloc(sizeof(*theControlSignals));
	theDatapath = malloc(sizeof(*theDatapath));
	while(theMachineState->PC != 0x80FF) {
		unsigned short int INSN = theMachineState->memory[theMachineState->PC];
		if(!DecodeCurrentInstruction(INSN, theControlSignals)) {
			
		}
		SimulateDatapath(theControlSignals, theMachineState, theDatapath);
		UpdateMachineState(theControlSignals, theMachineState, theDatapath);
	}
}