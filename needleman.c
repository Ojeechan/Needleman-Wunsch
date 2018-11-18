#include <stdio.h>
#include <string.h>


#define MAX(x, y) (((x) > (y)) ? (x) : (y))

void initialize(char[],char[]);
void ScoreTable(char[],char[]);
void TraceBack(char[],char[]);

int M[20][20];
int GAP = -2;
int MATCH = 5;
int MISSMATCH = -1;

int main(){

    char seq1[10]="TCCTA";
    char seq2[10]="TCATA";


    printf("%s\t%s",seq1,seq2);

    initialize(seq1,seq2);
    ScoreTable(seq1,seq2);
    TraceBack(seq1,seq2);
    return 0;
}

void initialize(char seq1[],char seq2 []){

    int seq1len = strlen(seq1);
    int seq2len = strlen(seq2);
    M[0][0] = 0;
    for (int i = 0; i < seq1len; i++){

        M[i][0] = i == 0 ? 0 : M[i-1][0] + (GAP); 
    }

    for (int j = 0; j < seq2len; j++){

        M[0][j] = j == 0 ? 0 : M[0][j-1] + (GAP);
    }

}

void ScoreTable(char seq1[],char seq2 []){
    int seq1len = strlen(seq1);
    int seq2len = strlen(seq2);
    for (int i = 1; i < seq1len; i++)
    {
        for (int j = 1; j < seq2len; j++)
        {
            int scroeDiag = 0;

            if (seq1[j - 1] == seq2[i - 1])
                scroeDiag = M[i - 1][j - 1] + MATCH;
            else
                scroeDiag = M[i - 1][j - 1] + MISSMATCH;

            int scroeLeft = M[i][j - 1] - GAP;
            int scroeUp = M[i - 1][j] - GAP;

            int maxScore = MAX(MAX(scroeDiag, scroeLeft), scroeUp);
            M[i][j] = maxScore;
        }
    }
}


void TraceBack(char seq1[],char seq2 []){

    char AlignA,AlignB;
    int m = strlen(seq1) - 1;
    int n = strlen(seq2) - 1;

    while (m > 0 && n > 0){
        int score = 0;

        if(seq1[m-1] == seq2[n-1]){
            score = MATCH;
        }
        else{
            score = MISSMATCH;
        }
        if (m > 0 && n > 0 && M[m, n] == M[m - 1, n - 1] + score)
        {
            AlignA = seq1[n - 1] + AlignA;
            AlignB = seq2[m - 1] + AlignB;
            m = m - 1;
            n = n - 1;
        }
        else if (n > 0 && M[m, n] == M[m, n - 1] - 2)
        {
            AlignA = seq1[n - 1] + AlignA;
            AlignB = "-" + AlignB;
            n = n - 1;
        }
        else 
        {
            AlignA = "-" + AlignA;
            AlignB = seq2[m - 1] + AlignB;
            m = m - 1;
        }
    }
    int seq1len = strlen(seq1);
    int seq2len = strlen(seq2);
    for (int i = 0; i < seq1len; i++){
        printf("\n");
        for (int j = 0; j < seq2len; j++){
            printf("%d\t",M[i][j]);
        }

    }

}
