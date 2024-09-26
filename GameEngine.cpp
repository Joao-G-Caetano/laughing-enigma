#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "GameEngine.hpp"
#include "Stack.hpp"
#include "TreeBuilder.hpp"
#include "Interface.hpp"

using namespace std;

void treeScorer (Board **fatherBoard, Stack *stackTop){

    int score1=0, score2=0;
    

  while(stackTop!=NULL){
       *fatherBoard=stackTop->board;

          if (isLeafe((*fatherBoard))){
            score1=(-1)*scoreBuilder((*fatherBoard),1,2);
            score2=scoreBuilder((*fatherBoard),2,1);
            (*fatherBoard)->boardScore=score1+score2;  
        }   
        stackTop=stackTop->next;
    } 
   
}

void SearchMinMax (Board **fatherBoard, Stack *stackTop){


    int minScore=0;
    int maxScore=0;
    Board *treeNode=*fatherBoard;
  
    while(stackTop!=NULL){
        treeNode=stackTop->board;
        minScore=treeNode->boardScore+1;
        maxScore=(-1)*(treeNode->boardScore+1);
       
       
        for (short k=0; k<N;k++){  
            if ((treeNode->childs[k]!=NULL)){
                if ((treeNode->childs[k]->boardScore!=pow(2,16))){
                    if((treeNode->level%2) && (treeNode->childs[k]->boardScore < minScore)){
                        minScore=treeNode->childs[k]->boardScore; 
                        treeNode->boardScore=minScore;     
                }   
                    if(!(treeNode->level%2) && (treeNode->childs[k]->boardScore > maxScore)){
                        maxScore=treeNode->childs[k]->boardScore; 
                        treeNode->boardScore=maxScore;           
                }   
             }   
                
            }
        }            
    stackTop=stackTop->next;
    }
}

void updateBoard(Board **fatherBoard,  short column){
    (*fatherBoard)->level=0;
    (*fatherBoard)->playerID=1;
    for (short k=(N-1); k>=0; k--){
        if (((*fatherBoard)->boardMatrix[k][column])==0){
            (*fatherBoard)->boardMatrix[k][column]=1;
            break;
        }
    }
}

bool verifyWinner(Board *boardElement, short playerID, string player){

    char c;
    short antiPlayer=2;
    string winnerName=player;

    if(playerID==2){
        antiPlayer=1;
        winnerName="COMPUTADOR";
    }
    if (abs(scoreBuilder(boardElement, playerID, antiPlayer))>=N*1000){
        createSpace(90);
        ShowBoard(boardElement);
        cout << "This is the END!"<<endl;
        cout << winnerName <<" esmagou o seu inimigo de morte "<< endl;
        cout << "Press any key to continue..." << endl;
        cin >> c;
        return true;      
    }
    return false;
}

Board *selectPlay(Stack *stackTop){

    int maxScore=(-1)*pow(2,16);
    Board *selectedBoard;
    Board *rootBoard=stackTop->board;

    for (short k=0; k<N; k++){
        if ((rootBoard)->childs[k]!=NULL){
            if (rootBoard->childs[k]->boardScore > maxScore){
                maxScore=(rootBoard)->childs[k]->boardScore;
                selectedBoard=(rootBoard)->childs[k];
            } 
        }
    }
    return selectedBoard;
}



void engineMain1(string player, short treeDepth){

    Board gameBoard;
    Board *boardPtr1;
    Board *boardPtr2=(Board *)malloc(sizeof(Board));
    Stack *nodeStack=NULL;
    bool winner=false;
    short selectedColumn;

    for (int i = 0; i < N; i++){ 
        boardPtr2->childs[i]=NULL;
        for (int j = 0; j < N; j++) {
            boardPtr2->boardMatrix[i][j]=0;
        }
    }
    boardPtr2->playerID=1;
    boardPtr2->level=0;

    while (!winner){
        selectedColumn=collectInput(boardPtr2, player);
        updateBoard(&boardPtr2,selectedColumn);
        ShowBoard(boardPtr2);
        if (verifyWinner(boardPtr2, boardPtr2->playerID, player)){
            break;
        }
        treeConstructor( &boardPtr2,&nodeStack, treeDepth);
        treeScorer(&boardPtr2, nodeStack);
        for (short h=0; h<(treeDepth-1); h++){
            SearchMinMax(&boardPtr2, nodeStack);
        }
        boardPtr1=selectPlay(nodeStack);
        ShowBoard(boardPtr1);
        if (verifyWinner(boardPtr1, boardPtr1->playerID, player)){
            deleteAll(&boardPtr2, &nodeStack);
            break;
        }
        gameBoard.boardScore=pow(2,16);
        gameBoard.level=0;
        gameBoard.playerID=1;
        for (short l=0; l<N; l++){
            gameBoard.childs[l]=NULL;
            for (short c=0; c<N; c++){
                gameBoard.boardMatrix[l][c]=boardPtr1->boardMatrix[l][c];
            }
        } 
        deleteAll(&boardPtr2, &nodeStack);
        boardPtr2=(Board *)malloc(sizeof(Board));
        boardPtr2->level=gameBoard.level;
        boardPtr2->playerID=gameBoard.playerID;
        boardPtr2->boardScore=gameBoard.boardScore;
        for (short l=0; l<N; l++){
            boardPtr2->childs[l]=NULL;
            for (short c=0; c<N; c++){
                boardPtr2->boardMatrix[l][c]=gameBoard.boardMatrix[l][c];
            }
        } 
    }
}


void engineMain2(string player, short treeDepth){

    Board gameBoard;
    Board *boardPtr1;
    Board *boardPtr2=(Board *)malloc(sizeof(Board));
    Stack *nodeStack=NULL;
    bool winner=false;
    short selectedColumn;

    for (int i = 0; i < N; i++) { 
        boardPtr2->childs[i]=NULL;
        for (int j = 0; j < N; j++) {
            boardPtr2->boardMatrix[i][j]=0;
        }
    }
    boardPtr2->playerID=1;
    boardPtr2->level=0;

    while (!winner){
        treeConstructor( &boardPtr2,&nodeStack, treeDepth);
        treeScorer(&boardPtr2, nodeStack);
        for (short h=0; h<(treeDepth-1); h++){
            SearchMinMax(&boardPtr2, nodeStack);
        }
        boardPtr1=selectPlay(nodeStack);
        ShowBoard(boardPtr1);
        if (verifyWinner(boardPtr1, boardPtr1->playerID, player)){
            deleteAll(&boardPtr2,&nodeStack);
            break;
            
        }
        gameBoard.boardScore=pow(2,16);
        gameBoard.level=0;
        gameBoard.playerID=1;
        for (short l=0; l<N; l++){
            gameBoard.childs[l]=NULL;
            for (short c=0; c<N; c++){
                gameBoard.boardMatrix[l][c]=boardPtr1->boardMatrix[l][c];
            }
        }
        deleteAll(&boardPtr2, &nodeStack);
        boardPtr2=(Board *)malloc(sizeof(Board));
        boardPtr2->level=gameBoard.level;
        boardPtr2->playerID=gameBoard.playerID;
        boardPtr2->boardScore=gameBoard.boardScore;
        for (short l=0; l<N; l++){
            boardPtr2->childs[l]=NULL;
            for (short c=0; c<N; c++){
                boardPtr2->boardMatrix[l][c]=gameBoard.boardMatrix[l][c];
            }
        }
        selectedColumn=collectInput(boardPtr2, player);
        updateBoard(&boardPtr2,selectedColumn);
        ShowBoard(boardPtr2);
        if (verifyWinner(boardPtr2, boardPtr2->playerID, player)){
            break;
        }    
    }
}

