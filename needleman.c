#include <stdio.h>
#include <string.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))


void initialize(char seq1[],char seq2 []);
void ScoreTable(char seq1[],char seq2 []);
void PrintTable(char seq1[],char seq2 []);


int M[200][200];
int GAP; 
int MATCH;
int MISSMATCH;

int main(){

    char seq1[100]; //First Sequence
    char seq2[100]; //Second Sequence
    printf("Enter First sequence\n");
    scanf("%s",seq1);
    printf("Enter Second sequence\n");
    scanf("%s",seq2); 
    printf("Enter the GAP value\n");
    scanf("%d",&GAP);
    printf("Enter the MATCH value\n");
    scanf("%d",&MATCH);
    printf("Enter the MISSMATCH value\n");
    scanf("%d",&MISSMATCH);

    initialize(seq1,seq2);
    ScoreTable(seq1,seq2);
    PrintTable(seq1,seq2);
    return 0;
}

//Step 1: Initialize the table
void initialize(char seq1[],char seq2 []){

    int seq1len = strlen(seq1);
    int seq2len = strlen(seq2);
    M[0][0] = 0;
    for (int i = 0; i < seq1len +  1; i++){

        M[i][0] = i == 0 ? 0 : M[i-1][0] + (GAP); 
    }

    for (int j = 0; j < seq2len + 1; j++){

        M[0][j] = j == 0 ? 0 : M[0][j-1] + (GAP);
    }

}

//Step 2: ScoreTable creation
void ScoreTable(char seq1[],char seq2 []){
    int seq1len = strlen(seq1);
    int seq2len = strlen(seq2);
    int a = -2;
    for (int i = 1; i < seq1len + 1; i++)
    {
        for (int j = 1; j < seq2len + 1; j++)
        {
            int scoreDiag = 0;

            if (seq1[j - 1] == seq2[i - 1]){
                scoreDiag = M[i - 1][j - 1] + MATCH;
            }
            else{
                scoreDiag = M[i - 1][j - 1] + MISSMATCH;
            }

            int scoreLeft = M[i][j - 1] + GAP;
            int scoreUp =  M[i - 1][j] + GAP;

            int maxScore = MAX(MAX(scoreDiag, scoreLeft), scoreUp);
            M[i][j] = maxScore;
        }
    }
}

//Step 3: PrintTable function
void PrintTable(char seq1[],char seq2 []){
    int seq1len = strlen(seq1);
    int seq2len = strlen(seq2);
    for (int i = 0; i < seq1len + 1; i++){
        printf("\n");
        for (int j = 0; j < seq2len + 1; j++){
            printf("%d\t",M[i][j]);
        }

    }

}
