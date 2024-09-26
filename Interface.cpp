#include <iostream>
#include "Interface.hpp"
#include "Board.hpp"


using namespace std;

void createSpace(short n){ 

    for (short k=0; k<n; k++){
        std:cout<<endl;
    }
}

void ShowBoard(Board *boardElement){

    char gameBoard[N][N];

     for (int i = 0; i < N; i++){ 
        for (int j = 0; j < N; j++){
            switch (boardElement->boardMatrix[i][j]){
                case 1:
                gameBoard[i][j]='X';
                break;
                case 2:
                gameBoard[i][j]='O';
                break;
                case 0:
                gameBoard[i][j]='-';
                break;
            }
            cout << "| " <<gameBoard[i][j]<< " ";  
        }
        cout << endl; 
    }  
}

void startGame(short *treeDepth, string *playerName, short *starter){

    *treeDepth=-1;
    *starter=-1;
    bool validInput=false;

    createSpace(500);
    cout << "Quem é o pichuco a DERROTAR?" << endl;
    while(!(cin >> *playerName)){
     cin.clear();
     cin.ignore(10000,'\n');
    }




    cout << "       _                    _           _   _                _              _          _             _       _    _  " << endl;        
    cout << "   _  /\\ \\                 /\\ \\        /\\_\\/\\_\\ _           _\\ \\           /\\ \\       /\\ \\     _    / /\\    / /\\ / /\\ " << endl;          
    cout << "  /\\_\\  \\ \\               /  \\ \\      / / / / //\\_\\        /\\__ \\          \\ \\ \\     /  \\ \\   /\\_\\ / / /   / / // /  \\ " << endl;          
    cout << " / / / \\ \\ \\             / /\\ \\ \\    /\\ \\/ \\ \\/ / /       / /_ \\_\\         /\\ \\_\\   / /\\ \\ \\_/ / // /_/   / / // / /\\ \\ " << endl;      
    cout << "/ / /   \\ \\ \\           / / /\\ \\_\\  /  \\____\\__/ /       / / /\\/_/        / /\\/_/  / / /\\ \\___/ // /\\ \\__/ / // / /\\ \\ \\ " << endl;     
    cout << "\\ \\ \\____\\ \\ \\         / /_/_ \\/_/ / /\\/________/       / / /            / / /    / / /  \\/____// /\\ \\___\\/ // / /  \\ \\ \\ " << endl;    
    cout << " \\ \\________\\ \\       / /____/\\   / / /\\/_// / /       / / /            / / /    / / /    / / // / /\\/___/ // / /___/ /\\ \\ " << endl;   
    cout << "  \\/________/\\ \\     / /\\____\\/  / / /    / / /       / / / ____       / / /    / / /    / / // / /   / / // / /_____/ /\\ \\ " << endl;  
    cout << "            \\ \\ \\   / / /______ / / /    / / /       / /_/_/ ___/\\ ___/ / /__  / / /    / / // / /   / / // /_________/\\ \\ \\ " << endl; 
    cout << "             \\ \\_\\ / / /_______\\/_/    / / /        /_______/\\__\\//\\__\\/_/___\\/ / /    / / // / /   / / // / /_       __\\ \\_\\ " << endl;
    cout << "              \\/_/ \\/__________/        \\/_/        \\_______\\/    \\/_________/\\/_/     \\/_/ \\/_/    \\/_/ \\_\\___\\     /____/_/ " << endl;

    cout << endl;
    cout << " Escolhe o teu nivel de dificuldade 1...6"<<endl;
    while ((*treeDepth>6) || (*treeDepth<1) || !validInput){
        cin >> *treeDepth;
        validInput=true;
        if (cin.fail()){
            cin.clear();
            cin.ignore(10000,'\n');
            validInput=false;
            cout << "Apenas numeros...tenta outra vez dissu"<<endl;
      }
        if (validInput){
            if ((*treeDepth>6) || (*treeDepth<1)){
                cout << "Nivel de Dificuldade entre 1 e 6!...Repete didi"<<endl;

            }
        }

    }

    cout << "Quem começa Richichi? " << *playerName  << "=1, COMPUTADOR=2" << endl;
    while (((*starter!=1) && (*starter!=2)) || !validInput){

        cin >> *starter;

        validInput=true;
        if (cin.fail()){
            cin.clear();
            cin.ignore(10000,'\n');
            validInput=false;
            cout << "Apenas numeros...tenta outra vez dissu"<<endl;
      }
        if (validInput){
            if ((*starter!=1) && (*starter!=2)){
                cout << "1 ou 2...tenta outra vez dissu"<<endl;

            }
        }
    }

}



short collectInput(Board *boardElement, string playerName){

    short columnNumber=-1;
    bool validColumn=false, validInput=false;

    createSpace(20);
    cout << "É a tua vez róró "<< playerName <<endl;
    createSpace(2);
    ShowBoard(boardElement);
    createSpace(2);
    cout << playerName<<" escolhe uma coluna rituxu "<<" 1..."<<N  <<endl;
    while (!(validColumn) || !(validInput)){
        cin >> columnNumber;

    
        validInput=true;
        if (cin.fail()){
            cin.clear();
            cin.ignore(10000,'\n');
            validInput=false;
            cout << "Apenas numeros...tenta outra vez dissu"<<endl;
            

        }
          
        validColumn=true;
        if (validInput){
            if (((columnNumber>N) || (columnNumber<1)) && validInput){
                validColumn=false;
                cout << "O minimo é 1 e o máximo é "<<N<<", tenta outra vez tussitussi"<<endl;
             }
        }
        if(validColumn && validInput){
            if (((boardElement->boardMatrix[0][columnNumber-1])!=0)){
            validColumn=false;
            cout << "A coluna " << columnNumber << " está cheia ...tenta outra vez tussitussi"<<endl;

            }

        } 

       
    }

    return (columnNumber-1);
}

/*mostra o tabuleiro APOS a jogada do utilizador */
void showUserMove(Board *boardElement){


    createSpace(20);
    ShowBoard(boardElement);

}

void wait(){

char c;

cout << "Press any key to continue"<< endl;
cin >> c;
}


