#include <stdio.h>

#include "debug.h"
#include "value.h"

/*
* To disassemble a chunk, we print a little header (so we can tell which chunk we’re looking at) and then crank through the bytecode, disassembling each instruction.
The way we iterate through the code is a little odd.
Instead of incrementing offset in the loop, we let disassembleInstruction() do it for us. 
When we call that function, after disassembling the instruction at the given offset, it returns the offset of the next instruction.
This is because, as we’ll see later, instructions can have different sizes.
*/
void disassembleChunk(Chunk* chunk, const char* name) {
	printf("== %s ==\n", name);

	for (int offset = 0; offset < chunk->count;) {
	   offset = disassembleInstruction(chunk, offset);
	}
}

// This instruction has a different instruction format, so we write a new helper function to disassemble it.
static int constantInstruction(const char* name, Chunk* chunk, int offset) {
	uint8_t constant = chunk->code[offset + 1];
	printf("%-16s %4d '", name, constant);
	printValue(chunk->constants.values[constant]);
	printf("'\n");
	return offset + 2;
}

static int simpleInstruction(const char* name, int offset) {
	printf("%s\n", name);
	return offset + 1;
}

int disassembleInstruction(Chunk* chunk, int offset) {
	printf("%04d ", offset);
	if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
		printf("   |  ");
	}
	else {
		printf("%4d ", chunk->lines[offset]);
	}

	uint8_t instruction = chunk->code[offset];
	switch (instruction) {
	case OP_CONSTANT:
		return constantInstruction("OP_CONSTANT", chunk, offset);
	case OP_RETURN:
		return simpleInstruction("OP_RETURN", offset);
	default:
		printf("Unknown opcode %d\n", instruction);
		return offset + 1;
	}
}