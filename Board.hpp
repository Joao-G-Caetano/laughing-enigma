#ifndef BOARD_H
#define BOARD_H


#include <iostream>
#include <string>

static short const N=5;

typedef struct board{
    short playerID;
    short level;
    short boardMatrix[N][N];
    int  boardScore;
    struct board *childs[N];
}Board;


int scoreBuilder(Board *boardElement1, short target, short antiTarget);

Board *childGenerator(Board *fatherBoar, short **usedPositions);

void displayBoard(Board *boardElement);

short compareBoard(Board *boardElement1, Board *boardElement2);

int *scoreLines(Board *boardElement1, short target, short antiTarget);

int *scoreColumns(Board *boardElement1, short target, short antiTarget);

int *scoreSecDiag(Board *boardElement1, short target, short antiTarget);

int *scoreMainDiag(Board *boardElement1, short target, short antiTarget);

short childsSize(Board *fatherBoard);

#endif