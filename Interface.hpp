#ifndef INTERFACE_H
#define INTERFACE_H
#include "Board.hpp"

using namespace std;



void startGame(short *treeDepth, string *playerName, short *starter);
short collectInput(Board *boardElement, string playerName);
void createSpace(short n);
void ShowBoard(Board *boardElement);
void showOutput(Board *boardElement);
void wait();





#endif