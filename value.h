#pragma once

#ifndef clox_value_h
#define clox_value_h

#include "common.h"

/*
* This typedef abstracts how Lox values are concretely represented in C. That way,
we can change that representation without needing to go back and fix existing code that passes around values.
*/
typedef double Value;

// dynamic array data structure for the value
typedef struct {
	int capacity;
	int count;
	Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif
