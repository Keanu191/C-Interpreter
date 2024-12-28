#pragma once

#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

#include "value.h"

typedef enum {
	OP_CONSTANT,
	// OP_RETURN essentially means "return from the current function
	OP_RETURN,
} OpCode;

typedef struct {
	int count;
	int capacity;
	uint8_t* code;
	int* lines;
	ValueArray constants;
} Chunk;

// because C does not have constructors we will declare a function to initalise a new chunk
void initChunk(Chunk* chunk);
// We have to free the memory ourselves because we are in C don't forget that.
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);


#endif
