#include <iostream>
#include <stdlib.h>
#include "Stack.hpp"


using namespace std;


short stackEmpty(Stack *stackTop){
    if (stackTop==NULL){
        return 1;
    }
    return 0;
}


Board *stackPop(Stack **stackTop){

    Stack *aux=*stackTop;
    Board *popedBoard;

    popedBoard=(aux)->board;
    *stackTop=(*stackTop)->next;
    free(aux);
    return popedBoard;
}

void stackPush(Stack **stackTop, Board *newBoard){

    Stack *newElement= (Stack*) malloc(sizeof(Stack));
    newElement->board=newBoard;
    newElement->next=NULL;
    Stack *stackTail=*stackTop;
    
    if(*stackTop==NULL){
        *stackTop=newElement;
        (*stackTop)->next=NULL;
        return;
    } 

    while(stackTail->next!=NULL){
        stackTail=stackTail->next;
    }
    
    stackTail->next=newElement; 
}

void stackPrint(Stack *stackTop){

    char c;
    cout << "Printing the full stack..." << endl;
 
    if (stackTop==NULL){
        cout << "Nothing to print, stack/queue is empty" << endl;
    }

    while(stackTop!=NULL){

        cout << "Level -> "<< stackTop->board->level<< endl;
        cout << "playerID -> "<< stackTop->board->playerID << endl;
        displayBoard(stackTop->board);
        stackTop=stackTop->next;

    }   
    cout << "Press any key to continue..." << endl;
    cin >> c;
}

void stackFlush(Stack **stackTop){
    
    Stack *current=*stackTop;
    Stack *next;

    while(current!=NULL){
        next=current->next;
        free(current);
        current=next;
    } 
    *stackTop=NULL;
}

void stackInit(Board **fatherBoard, Stack **stackTop){
    if (stackEmpty(*stackTop)){
        stackPush(stackTop, *fatherBoard);
    }
}

