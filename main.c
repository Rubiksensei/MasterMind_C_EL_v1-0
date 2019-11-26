#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initHist(int tabHistAns[12][4], char tabHistHint[12][4], char waiting);
void printHist(int tabHistAns[12][4], char tabHistHint[12][4]);
void rules(char wrong, char almost, char good);
void insertAnswer(int tabHistAns[12][4], char sTry[5], int round);
void checking(int tabHistAns[12][4], char tabHistHint[12][4], char wrong, char almost, char good, int value1, int value12, int value13, int value14, int round);

int main()
{
    const int MIN = 0, MAX = 9;
    char cWrong = '_', cAlmost = '-', cGood = '=',  cWaiting = '.', sTry[5], histHint[12][4];
    int histAns[12][4], gameEnd=0, round;

    //Init secret code
    srand(time(NULL));
    int n1 = (rand()%(MAX-MIN+1))+MIN;
    int n2 = (rand()%(MAX-MIN+1))+MIN;
    int n3 = (rand()%(MAX-MIN+1))+MIN;
    int n4 = (rand()%(MAX-MIN+1))+MIN;

    //Init historics of inputs and of feedbacks
    initHist(histAns, histHint, cWaiting);

    //Prints rules and indications
    rules(cWrong, cAlmost, cGood);

    //Prints both historics
    printHist(histAns, histHint);

    //Instructions just for debug
    //printf("code pour debug : %d %d %d %d \n", n1, n2, n3, n4);

    //Reads and inserts input into inputs historic
    for (round = 0; round < 12; round++)
    {
        scanf("%s", sTry);
        //Inserts the input into histAns
        insertAnswer(histAns, sTry, round);

        system("cls" );
        rules(cWrong, cAlmost, cGood);

        //Checks the current input and fills the feedback historic tab
        checking(histAns, histHint, cWrong, cAlmost, cGood, n1, n2, n3, n4, round);

        if (histHint[round][0]==cGood && histHint[round][1]==cGood && histHint[round][2]==cGood && histHint[round][3]==cGood)
        {
            gameEnd=1;
            break;
        }

        printHist(histAns, histHint);
        //Instruction for debug
        //printf("code  debug : %d%d%d%d \n\n", n1, n2, n3, n4);
    }

    //Checks victory condition and indicates if the player won plus additional informations
    if (gameEnd==1)
    {
        printHist(histAns, histHint);
        printf("You find the code with %d try! It was %d%d%d%d \n", round+1, n1, n2, n3, n4);
    }
    else if (gameEnd!=1)
    {
        printf("You lose ! It was %d%d%d%d \n", n1, n2, n3, n4);
    }

    return 0;
}

void initHist(int tabHistAns[12][4], char tabHistHint[12][4], char waiting)
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //Init the Answers historic
            tabHistAns[i][j]=0;
            //Init the Hints historic
            tabHistHint[i][j]=waiting;
        }
    }
}

void printHist(int tabHistAns[12][4], char tabHistHint[12][4])
{
    int i, j;
    printf(" + ~ ~ ~ ~ + ~ ~ ~ ~ +\n");
    for (i = 0; i < 12; i++)
    {
        printf(" | ");
        //Prints the left part of the UI with answers and previous answers
        for (j = 0; j < 4; j++)
        {
            printf("%d ", tabHistAns[i][j]);
        }
        printf("| ");
        //Prints the right part of the UI with hints and previous hints
        for (j = 0; j < 4; j++)
        {
            printf("%c ", tabHistHint[i][j]);
        }
        printf("|\n");
    }
    printf(" + ~ ~ ~ ~ + ~ ~ ~ ~ +\n\n");
}

void rules(char wrong, char almost, char good)
{
    printf("Wanna try to crack the code ?\n");
    printf("Then give a 4 digits number and see if you can find the good one.\n\n");
    printf("%c : number not in the code\n%c : number in the code but not at the good position\n%c : good number at the right position\n\n", wrong, almost, good);
}

void insertAnswer(int tabHistAns[12][4], char sTry[5], int round)
{
    for (int j = 0; j < 4; j++)
    {
        switch (sTry[j])
        {
            case '0':
                tabHistAns[round][j] = 0;
                break;
            case '1':
                tabHistAns[round][j] = 1;
                break;
            case '2':
                tabHistAns[round][j] = 2;
                break;
            case '3':
                tabHistAns[round][j] = 3;
                break;
            case '4':
                tabHistAns[round][j] = 4;
                break;
            case '5':
                tabHistAns[round][j] = 5;
                break;
            case '6':
                tabHistAns[round][j] = 6;
                break;
            case '7':
                tabHistAns[round][j] = 7;
                break;
            case '8':
                tabHistAns[round][j] = 8;
                break;
            case '9':
                tabHistAns[round][j] = 9;
                break;
            default:
                tabHistAns[round][j] = 0;
                break;
        }
    }
}

void checking(int tabHistAns[12][4], char tabHistHint[12][4], char wrong, char almost, char good, int value1, int value2, int value3, int value4, int round)
{
    for (int j = 0; j < 4; j++)
    {
        //initiate the case where all numbers are wrong
        if (tabHistAns[round][j]!=value1 && tabHistAns[round][j]!=value2 && tabHistAns[round][j]!=value3 && tabHistAns[round][j]!=value4)
        {
            tabHistHint[round][j]=wrong;
        }
        //check if the number is in the secret code
        if (tabHistAns[round][j]==value1 || tabHistAns[round][j]==value2 || tabHistAns[round][j]==value3 || tabHistAns[round][j]==value4)
        {
            tabHistHint[round][j]=almost;
        }
        //check if the number is rightly place
        if (tabHistAns[round][0]==value1)
        {
            tabHistHint[round][0]=good;
        }
        if (tabHistAns[round][1]==value2)
        {
            tabHistHint[round][1]=good;
        }
        if (tabHistAns[round][2]==value3)
        {
            tabHistHint[round][2]=good;
        }
        if (tabHistAns[round][3]==value4)
        {
            tabHistHint[round][3]=good;
        }
    }
}
