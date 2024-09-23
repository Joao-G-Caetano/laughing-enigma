#include <iostream>
#include <stdlib.h>
#include <math.h>

#include "Board.hpp"
#include "Stack.hpp"
#include "TreeBuilder.hpp"
#include "GameEngine.hpp"
#include "Interface.hpp"



using namespace std;



int main(){

std::string player;
short treeDepth;
short startOrder;

startGame(&treeDepth, &player, &startOrder);

if (startOrder==1){
    engineMain1(player,treeDepth);
    return 0;
}

if (startOrder==2){
    engineMain2(player,treeDepth);
    return 0;
}


}