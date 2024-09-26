#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include "Board.hpp"

typedef struct stack{
struct stack *next;
Board *board;

}Stack;

void stackInit(Board **fatherBoard, Stack **stackTop);

Board *stackPop(Stack **stackTop);

Board *stackPopDelete(Stack **stackTop);

void stackPush(Stack **stackTop, Board *newBoard);

void stackPrint(Stack *stackTop);

void stackFlush(Stack **stackTop);

short stackEmpty(Stack *stackTop);

#endif