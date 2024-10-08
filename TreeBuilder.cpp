#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "TreeBuilder.hpp"

using namespace std;

Stack *nodeStack=NULL;


short isLeafe(Board *element){

    for (int p=0; p<N; p++){
        if (element->childs[p]!=NULL){
            return 0;
        }
    }
    return 1;
}

void basicContructor(Board **fatherBoard, long *nChilds){

    Board *newBoard;
    short target=2;
    short antiTarget=1;
    short offSpringSize=childsSize(*fatherBoard);
    short **usedPositions;
 
    if ((*fatherBoard)->playerID == 1 ){
        target=1;
        antiTarget=2;
    }
    if (abs(scoreBuilder(*fatherBoard, target,antiTarget )) >= N*1000){
        return;
    }
    usedPositions=(short **)malloc(N*sizeof(usedPositions));
    for (short u=0; u<N; u++){
        usedPositions[u]=(short *)malloc(N*sizeof(usedPositions[u]));
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            usedPositions[i][j]=0;
        }
    } 
    if (isLeafe(*fatherBoard)){
        for (short k=0; k<offSpringSize; k++){
            newBoard=childGenerator((*fatherBoard), usedPositions);
            *nChilds=*nChilds-1;
            (*fatherBoard)->childs[k]=newBoard;
        }
    }
    for (short u=0; u<N; u++){
     free(usedPositions[u]);
    }
    free(usedPositions);
}

void treeConstructor(Board **fatherBoard, Stack **stackTop, short treeDepth){


    Board *popedBoard;
    long remainingChilds=0;
    Stack *stackHead=(Stack*) malloc(sizeof(Stack));
    Stack *newElement;
    Stack *stackTailHead;
    Stack *stackTailTop;
    Stack *auxStack;
    Stack **stackInit;
    char c;

    for (short k=1; k<=treeDepth; k++){
      remainingChilds+= pow(N,k);  
    }   
    
    /*queueInit*/
    stackHead->board=*fatherBoard;
    stackHead->next=NULL;

    (*stackTop)=stackHead;

    while(stackHead!=NULL){
        /*queuePop*/
        popedBoard=(stackHead)->board;
        stackHead=stackHead->next;


        /*child generation*/
        if ((remainingChilds > 0) && (isLeafe(popedBoard)) && (popedBoard->level < treeDepth)){
            basicContructor(&popedBoard, &remainingChilds);            
        }
        /*queuePush*/
        for (int k=0; k<N; k++){
            if ((popedBoard)->childs[k]!=NULL){
                Stack *newElement= (Stack*) malloc(sizeof(Stack));
                newElement->board=(popedBoard)->childs[k];
                newElement->next=NULL;
                stackTailHead=stackHead;
                stackTailTop=(*stackTop);
                 if (stackHead==NULL){
                    stackHead=newElement;
                    stackHead->next=NULL; 
                    (*stackTop)->next=newElement;
                    continue;
                 }
                 while(stackTailHead->next!=NULL){
                    stackTailHead=stackTailHead->next;
                 }
                 while(stackTailTop->next!=NULL){
                    stackTailTop=stackTailTop->next;
                 }
                 
                stackTailHead->next=newElement;
                stackTailTop->next=newElement;

            }

        }

    }
}
    
void treePrinter(Stack *stackTop, short treeDepth){
    Board *popedBoard;
    char c;
 

    while(stackTop!=NULL){
        popedBoard=stackTop->board;
        if ((popedBoard->level) > treeDepth){
            break;
        }
        displayBoard(popedBoard);
        cout << "Press any key to continue..." << endl;
        cin >> c;
        stackTop=stackTop->next;
    }      
}

void levelPrinter(Stack *stackTop, short treeDepth){
    
    Board *popedBoard;
    char c;
     
     while(stackTop!=NULL){
        popedBoard=stackTop->board;
        if ((popedBoard->level) == treeDepth){
            displayBoard(popedBoard);
            cout << "Press any key to continue..." << endl;
            cin >> c;  
        }
        stackTop=stackTop->next;
    } 
}

void deleteAll(Board **fatherBoard, Stack **stackTop){

    Stack *aux;
    
     while((*stackTop)!=NULL){
        (*fatherBoard)=(*stackTop)->board;
        free(*fatherBoard);
        aux=(*stackTop);
        *stackTop=(*stackTop)->next;
        free(aux);
    } 
}


   

   /*   
     Board *popedBoard;
    Stack *stackTop=NULL;
  
    Stack *stackHead=(Stack*) malloc(sizeof(Stack));
    Stack *newElement;
    Stack *stackTailHead;
    Stack *stackTailTop;
    Stack *auxStack;
    short jumpLenght;
    char c;

    stackHead->board=*fatherBoard;
    stackHead->next=NULL;
 
   stackTop=stackHead;
  
    while(stackHead!=NULL){
      
        
        popedBoard=(stackHead)->board;
        stackHead=stackHead->next;
    
        for (int k=0; k<N; k++){
            if ((popedBoard)->childs[k]!=NULL){
                Stack *newElement= (Stack*) malloc(sizeof(Stack));
                newElement->board=(popedBoard)->childs[k];
                newElement->next=NULL;
                stackTailHead=stackHead;
                stackTailTop=stackTop;
                 if (stackHead==NULL){
                    stackHead=newElement;
                    stackHead->next=NULL;
                    stackTop->next=newElement;
                    continue;
                 }
                 while(stackTailHead->next!=NULL){
                    stackTailHead=stackTailHead->next;
                 }
                 while(stackTailTop->next!=NULL){
                    stackTailTop=stackTailTop->next;
                 }
                 
                stackTailHead->next=newElement;
                stackTailTop->next=newElement;

            }

        }
    
    }
 */ 
      
    
     



