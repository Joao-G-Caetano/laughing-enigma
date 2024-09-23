#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Board.hpp"

using namespace std;


Board *childGenerator(Board *fatherBoard, short **usedPositions){

    
    
    short i,l,c,j,nextChild;
  
    



    Board *newChild=(Board *)malloc(sizeof(Board));

    /*NOK -> esta matrix é relevante para todos os filhos gerados a partir de um pai, tem que ser passada por referencia*/
    
     newChild->level=fatherBoard->level+1; /*ok -> atribui o level (pai+1)*/

        for (l=0; l<N; l++){
            for (c=0; c<N; c++){
                newChild->boardMatrix[l][c]=fatherBoard->boardMatrix[l][c];
            }
        } /*ok->filho herda a posições do pai*/
        for (j=0; j<N;j++){
            newChild->childs[j]=NULL;
            newChild->boardScore=pow(2,16);   
        }/*ok-> coloca o vector de filhos a NULL, atribui um boardScore*/
        if (fatherBoard->playerID==1){
            newChild->playerID=2;
        }/*ok estabelece o player ID*/
        if (fatherBoard->playerID==2){
            newChild->playerID=1;
        }/*ok estabelece o player ID*/

        for (c=0;c<N;c++){
            nextChild=0;
            if(fatherBoard->boardMatrix[0][c]!=0){
                continue;
            }/*ok se a coluna estiver cheia passa à proxima*/
            if((fatherBoard->boardMatrix[N-1][c]==0) && (usedPositions[N-1][c]==0)){ 
                usedPositions[N-1] [c]=1;
                if (fatherBoard->playerID==1){
                    newChild->boardMatrix[N-1][c]=2;          
                }
                if (fatherBoard->playerID==2){
                    newChild->boardMatrix[N-1][c]=1;
                }
            break; /*ok se a coluna estiver livre preenche e actualiza o used positions, sai do ciclo colunas*/         
           }
           
            for (l=0;l<N-1;l++){
                if ((fatherBoard->boardMatrix[l][c]==0) && (newChild->boardMatrix[l+1][c]!=0)){
                       if (usedPositions[l][c]==0){
                            usedPositions[l][c]=1;
                            nextChild=1; 
                            if (fatherBoard->playerID==1){
                                newChild->boardMatrix[l][c]=2;

                            }
                            if (fatherBoard->playerID==2){
                                 newChild->boardMatrix[l][c]=1;     
                            }
                        break;
                       }
                    }   
                }/*ok se a coluna estiver semi-preenchida, preenche e actualiza o used positions, sai do ciclo linhas, cria condiçoes atraves do next child para sair do ciclo colunas*/   
            if (nextChild){
            break;    
            }    
        }  
      
return newChild;
}


void displayBoard(Board *boardElement){
    
    cout << "Level -> " << boardElement->level<< endl;
    cout << "Player ID -> " << boardElement->playerID<< endl;
    cout << "BoardScore -> " << boardElement->boardScore<< endl;
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) { 
            cout << boardElement->boardMatrix[i][j] << " "; 
        } 
        cout << endl; 
    } 
}

short compareBoard(Board *boardElement1, Board *boardElement2){

    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) { 
            if (boardElement1->boardMatrix[i][j] != boardElement2->boardMatrix[i][j]){
                return 0;
            }
            
        } 
    }
    return 1;
}

int *scoreLines(Board *boardElement1, short target, short antiTarget){

short incLineGroup=0;
int groupScore=0;
int  lineScore=0;
int *sLines=(int *)malloc(N*sizeof(int));

    for (short i = 0; i < N; i++){
            lineScore=0;
            for (short j=0; j<N ; j++){ 
                groupScore=0; 
                if((j+4)<=N){
                    incLineGroup=0;   
                    for(short k=j+1; k<j+4;k++){
                        if (((boardElement1->boardMatrix[i][k]) == antiTarget) || ((boardElement1->boardMatrix[i][k-1]) == antiTarget)){
                            incLineGroup=0;
                            groupScore=0;
                            break;
                        } 
                        if(((boardElement1->boardMatrix[i][k-1]) == (boardElement1->boardMatrix[i][k])) && (boardElement1->boardMatrix[i][k-1] == target)){
                            incLineGroup++;
                       //     cout << "incLineGroup= " << incLineGroup << endl;
                        }                                           
                    
                    }
                    if (incLineGroup){
                        groupScore+=(incLineGroup+1)*25; 
                    }
                    if ((incLineGroup+1)==4){
                        groupScore+=N*1000;
                    }
                }
                else{
                    break;
                }
            lineScore+=groupScore;
            }           
        sLines[i]=lineScore;
//       cout << "Score line " << i << " =" << sLines[i] << endl;
    } 
    return sLines;
}         

int *scoreColumns(Board *boardElement1, short target, short antiTarget){

short incColumnGroup=0;
int groupScore=0;
int  columnScore=0;
int *sColumns=(int *)malloc(N*sizeof(int));

    for (short i = 0; i < N; i++){
            columnScore=0;
            for (short j=0; j<N ; j++){ 
                groupScore=0; 
                if((j+4)<=N){
                    incColumnGroup=0;   
                    for(short k=j+1; k<j+4;k++){
                        if (((boardElement1->boardMatrix[k][i]) == antiTarget) || ((boardElement1->boardMatrix[k-1][i]) == antiTarget)){
                            incColumnGroup=0;
                            groupScore=0;
                            break;
                        } 
                        if(((boardElement1->boardMatrix[k-1][i]) == (boardElement1->boardMatrix[k][i])) && (boardElement1->boardMatrix[k-1][i] == target)){
                            incColumnGroup++;
                       //     cout << "inColumnGroup= " << incColumnGroup << endl;
                        }                                           
                    
                    }
                    if (incColumnGroup){
                        groupScore+=(incColumnGroup+1)*25; 
                    }
                    if ((incColumnGroup+1)==4){
                        groupScore+=N*1000;
                    }
                }
                else{
                    break;
                }
            columnScore+=groupScore;
            }           
        sColumns[i]=columnScore;
//        cout << "Score column " << i << " =" << sColumns[i] << endl;
    } 
    return sColumns;
}

int scoreBuilder(Board *boardElement1, short target, short antiTarget){ 
   
    int *lines=scoreLines(boardElement1,target, antiTarget);
    int *columns=scoreColumns(boardElement1,target,antiTarget);
    int *secDiagonals=scoreSecDiag(boardElement1,target, antiTarget);
    int *mainDiagonals=scoreMainDiag(boardElement1,target, antiTarget);
    int linesTotal=0;
    int columnsTotal=0;
    int secDiagonalsTotal=0;
    int mainDiagonalsTotal=0;

   for (short k=0; k<N; k++){
        linesTotal+=lines[k];
        columnsTotal+=columns[k];
    }

   for (short k=0; k<2*N-7; k++){
      secDiagonalsTotal+=secDiagonals[k];
      mainDiagonalsTotal+=mainDiagonals[k];
    }
    free(lines);
    free(columns);
    free(secDiagonals);
    free(mainDiagonals);


     return (linesTotal+columnsTotal+secDiagonalsTotal+mainDiagonalsTotal);   
} 
   
int *scoreSecDiag(Board *boardElement1, short target, short antiTarget){

short secDiagID[2*N-7];
int diagScore=0;
int *scoreSecDiagonals=(int *)malloc((2*N-7)*sizeof(int));
short incDiagGroup=0;
int groupScore=0;
short m=0;
char c;




/* Construção do vector de identificação das diagonais secundarias e.g. N=5 -> {N-1, N, N+1}*/
    for (short p=-(N-4); p<=N-4; p++){
        secDiagID[p+(N-4)]=N+p;
         }    


    for (short k=0;k<(2*N-7);k++){
        diagScore=0;
        for (short i = 0; i < N; i++){
            for (short j=0; j< N ; j++){
                if (((i+j)==(secDiagID[k]-1))){
                     groupScore=0;
                     incDiagGroup=0;
                     if (((i+3)<N) && ((j-3)>=0)){  
//                            std::cout << "Group Detection " << " i="  << i << " j=" << j <<  endl;
                            m=i;
                            for (short n=j;n>j-4;n--){
                                if (((boardElement1->boardMatrix[m][n]) == antiTarget) || ((boardElement1->boardMatrix[m+1][n-1]) == antiTarget)){
                                    incDiagGroup=0;
                                    groupScore=0;
//                                    std::cout << "Anti detection" << endl;
                                    break;
                                } 
                                if(((boardElement1->boardMatrix[m+1][n-1]) == (boardElement1->boardMatrix[m][n])) && (boardElement1->boardMatrix[m][n] == target)){
                                    incDiagGroup++;
//                                    std::cout << "Diagonal " << k <<  " inc="<< incDiagGroup << " m="<< m <<" n=" << n<< endl;
//                                   cin >> c; 

                                }  
                            m++;
                            }
                                            
                        if(incDiagGroup){
                            diagScore=(incDiagGroup+1)*25;
                        }        
                        if ((incDiagGroup+1)==4){
                            diagScore+=N*1000;
                        }                     
                    }   
                }        
            }    
        }         
       
        scoreSecDiagonals[k]=diagScore;
//      std::cout << "diagscore " << k << "= " << diagScore << endl; 
    }
    return scoreSecDiagonals;
}
      
int *scoreMainDiag(Board *boardElement1, short target, short antiTarget){
    
    short mainDiagID[2*N-7];
    int diagScore=0;
    int *scoreMainDiagonals=(int *)malloc((2*N-7)*sizeof(int));
    short incDiagGroup=0;
    int groupScore=0;
    short m=0;
    char c;

    for (short p=-(N-4); p<=N-4; p++){
        mainDiagID[p+(N-4)]=p;
    }    
    for (short k=0;k<(2*N-7);k++){
        diagScore=0;
        for (short i = 0; i < N; i++){
            for (short j=0; j< N ; j++){
                
                if (i==(mainDiagID[k]+j)){
                     groupScore=0;
                     incDiagGroup=0;
//                     cout << "Diagonal Identified " << mainDiagID[k] <<endl;
                    if (((i+3)<N) && ((j+3)<N)){  
//                         std::cout << "Group Detection " << " i="  << i << " j=" << j <<  endl;
                        m=i;
                        for (short n=j;n<j+4;n++){
                            if (((boardElement1->boardMatrix[m][n]) == antiTarget) || ((boardElement1->boardMatrix[m+1][n+1]) == antiTarget)){
                                incDiagGroup=0;
                                groupScore=0;
//                                   std::cout << "Anti detection" << endl;
                                break;
                            } 
                            if(((boardElement1->boardMatrix[m+1][n+1]) == (boardElement1->boardMatrix[m][n])) && (boardElement1->boardMatrix[m][n] == target)){
                                incDiagGroup++;
//                                   std::cout << "Diagonal " << k <<  " inc="<< incDiagGroup << " m="<< m <<" n=" << n<< endl;
//                                    cin >> c; 
                            }  
                        m++;
                        }                   
                        if(incDiagGroup){
                            diagScore=(incDiagGroup+1)*25;
                        }        
                        if ((incDiagGroup+1)==4){
                            diagScore+=N*1000;
                        }                     
                    }   
                }        
            }    
        }         
       
    scoreMainDiagonals[k]=diagScore;
//        std::cout << "diagscore " << k << "= " << diagScore << endl; 
    }
    return scoreMainDiagonals;
}

short childsSize(Board *fatherBoard){

    short nChilds=N;

    for (short n=0; n<N;n++){
        if (fatherBoard->boardMatrix[0][n]!=0){
            nChilds--;
            }
        }
    return nChilds;
}









           
                
                

           