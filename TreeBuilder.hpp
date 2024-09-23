#ifndef TREE_H
#define TREE_H
#include <stdlib.h>
#include "Stack.hpp"
#include "Board.hpp"


void basicContructor(Board **fatherBoard, long *nChilds);
void treeConstructor(Board **fatherBoard, Stack **stackTop, short treeDepth);
void treePrinter(Board **fatherBoard, Stack **stackTop, short treeDepth);
short isLeafe(Board *element);
void levelPrinter(Board **fatherBoard, Stack **stackTop, short treeDepth);
void deleteTree(Board **fatherBoard, Stack **stackTop);



#endif