#ifndef GAME_H
#define GAME_H
#include <stdlib.h>
#include "Board.hpp"
#include "Stack.hpp"

using namespace std;

void treeScorer (Board **fatherBoard, Stack *stackTop);
void SearchMinMax (Board **fatherBoard, Stack *stackTop);
void updateBoard(Board **fatherBoard,  short column);
bool verifyWinner(Board *boardElement, short playerID, std::string player);
Board *selectPlay(Stack *stackTop);
void engineMain2(string player, short treeDepth);
void engineMain1(string player, short treeDepth);







#endif