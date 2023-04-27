#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    start();
    playAgain();

    return 0;
}

void playAgain()
{

    for(int i=0 ; ; i++)
    {
        char YorN[10]="";
        printf("\nDO YOU WANT TO PLAY AGAIN(Y/N): ");
        scanf("%s",&YorN);

        if(strcmp(YorN,"Y")==0 || strcmp(YorN,"y")==0)
        {
            clear();
            printf("RESTARTING...");
            delay(1);
            clear();
            start();
        }
        if(strcmp(YorN,"N")==0 || strcmp(YorN,"n")==0)
        {
            printf("\nGAME OVER.\n");
            exit(0);
        }
        if(strcmp(YorN,"Y")!=0 && strcmp(YorN,"y")!=0 && strcmp(YorN,"N")!=0 || strcmp(YorN,"n")!=0) //fsgDFAFDA
        {
            error("INVALID KEY FOR Y/N");
            playAgain();
        }
    }

}

void clear()
{
    //for clear all screen
    system("@cls||clear");
}

void delay(int seconds)
{
    //for seconds delay
    int mseconds = 1000 * seconds;

    clock_t starttime = clock();

    while (clock() < starttime + mseconds);
}

void error(char errorName[])
{
    //for show and hide error message with red text
    setTextColor(4);
    printf("ERROR: %s.",errorName);
    delay(1);
    clear();
    setTextColor(15);
}

void playWithComputer()
{
    char matrix[10][10];
    int playerscore=0;
    int computerscore=0;
    int movenumber;
    int prow,pcolumn;
    int crow,ccolumn;

    //CREATING BOARD
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            matrix[i][j]='-';
            matrix[0][0]='0';
            matrix[1][0]='1';
            matrix[2][0]='2';
            matrix[3][0]='3';
            matrix[4][0]='4';
            matrix[5][0]='5';
            matrix[6][0]='6';
            matrix[7][0]='7';
            matrix[8][0]='8';
            matrix[9][0]='9';
            matrix[0][1]='1';
            matrix[0][2]='2';
            matrix[0][3]='3';
            matrix[0][4]='4';
            matrix[0][5]='5';
            matrix[0][6]='6';
            matrix[0][7]='7';
            matrix[0][8]='8';
            matrix[0][9]='9';
        }
    }

    //STARTING
    printMatrix(matrix);

    printf("\nHOW MANY MOVES DO YOU WANT TO PLAY WITH COMPUTER(MIN 1 MAX 40): ");
    scanf("%d",&movenumber);

    if(movenumber<=0 || movenumber>40)
    {
        do
        {
            error("MIN 1 MAX 40 MOVES");
            printMatrix(matrix);
            printf("\nHOW MANY MOVES DO YOU WANT TO PLAY WITH COMPUTER(MIN 1 MAX 40): ");
            scanf("%d",&movenumber);
        }
        while(movenumber<=0 || movenumber>40);
    }

    clear();
    printMatrix(matrix);

    for(int i=0; i<movenumber; i++)
    {
        //PLAYER MOVES
        printf("\n%d MOVES LEFT\n",movenumber-i);
        printf("SELECT ROW AND COLUMN(MIN 1 MAX 9)(MIN 1 MAX 9): ");
        scanf("%d %d",&prow,&pcolumn);
        if(prow<=0 || prow>9 || pcolumn<=0 || pcolumn>9)
        {
            do
            {
                error("INVALID AREA");
                printMatrix(matrix);
                printf("\n%d MOVES LEFT",movenumber-i);
                printf("\nSELECT ROW AND COLUMN(MIN 1 MAX 9)(MIN 1 MAX 9): ");
                scanf("%d %d",&prow,&pcolumn);
            }
            while(prow<=0 || prow>9 || pcolumn<=0 || pcolumn>9);
        }
        if(matrix[prow][pcolumn] != 'X' && matrix[prow][pcolumn] != 'O')
        {
            char *p;
            p = &matrix[prow][pcolumn];
            *p = 'X';
        }
        else
        {
            do
            {
                error("INVALID AREA");
                printMatrix(matrix);
                printf("\n%d MOVES LEFT",movenumber-i);
                printf("\nSELECT ROW AND COLUMN(MIN 1 MAX 9)(MIN 1 MAX 9): ");
                scanf("%d %d",&prow,&pcolumn);
            }
            while(matrix[prow][pcolumn] == 'X' || matrix[prow][pcolumn] == 'O' || (prow<=0 || prow>9) || ((pcolumn<=0 || pcolumn>9)));

            char *p;
            p = &matrix[prow][pcolumn];
            *p = 'X';
        }

        //COMPUTER RANDOM MOVES
        srand(time(NULL));
        int crow = rand() % 9 + 1;
        int ccolumn = rand() % 9 + 1;

        if(matrix[crow][ccolumn] != 'X' && matrix[crow][ccolumn] != 'O')
        {
            char *c;
            c = &matrix[crow][ccolumn];
            *c = 'O';
        }
        else
        {
            do
            {
                crow = rand() % 9 + 1;
                ccolumn = rand() % 9 + 1;
            }
            while(matrix[crow][ccolumn] == 'X' || matrix[crow][ccolumn] == 'O');

            char *c;
            c = &matrix[crow][ccolumn];
            *c = 'O';
        }


        clear();
        printMatrix(matrix);
    }

    //FOR SCORES
    for(int i=1; i<10; i++)
    {
        for(int j=1; j<10; j++)
        {
            if(matrix[i][j]=='X' && matrix[i+1][j]=='X' && matrix[i+2][j]=='X')
                playerscore++;
            if(matrix[i][j]=='X' && matrix[i][j+1]=='X' && matrix[i][j+2]=='X')
                playerscore++;
            if(matrix[i][j]=='X' && matrix[i+1][j+1]=='X' && matrix[i+2][j+2]=='X')
                playerscore++;
            if(matrix[i][j]=='X' && matrix[i+1][j-1]=='X' && matrix[i+2][j-2]=='X')
                playerscore++;
        }
    }

    for(int i=1; i<10; i++)
    {
        for(int j=1; j<10; j++)
        {
            if(matrix[i][j]=='O' && matrix[i+1][j]=='O' && matrix[i+2][j]=='O')
                computerscore++;
            if(matrix[i][j]=='O' && matrix[i][j+1]=='O' && matrix[i][j+2]=='O')
                computerscore++;
            if(matrix[i][j]=='O' && matrix[i+1][j+1]=='O' && matrix[i+2][j+2]=='O')
                computerscore++;
            if(matrix[i][j]=='O' && matrix[i+1][j-1]=='O' && matrix[i+2][j-2]=='O')
                computerscore++;
        }
    }

    //SCORES AND WINNER
    printf("\nYOUR SCORE IS %d POINTS\nCOMPUTER SCORE IS %d POINTS.\n",playerscore,computerscore);

    if(playerscore>computerscore)
        printf("\nWINNER: PLAYER 1.\n");
    if(playerscore<computerscore)
        printf("\nWINNER: COMPUTER\n");
    if(playerscore==computerscore)
        printf("\nDRAW.\n");

}

void playWithPlayer2()
{
    char matrix[10][10];
    int player1score=0;
    int player2score=0;
    int movenumber;
    int prow,pcolumn;
    int crow,ccolumn;

    //CREATING BOARD
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            matrix[i][j]='-';
            matrix[0][0]='0';
            matrix[1][0]='1';
            matrix[2][0]='2';
            matrix[3][0]='3';
            matrix[4][0]='4';
            matrix[5][0]='5';
            matrix[6][0]='6';
            matrix[7][0]='7';
            matrix[8][0]='8';
            matrix[9][0]='9';
            matrix[0][1]='1';
            matrix[0][2]='2';
            matrix[0][3]='3';
            matrix[0][4]='4';
            matrix[0][5]='5';
            matrix[0][6]='6';
            matrix[0][7]='7';
            matrix[0][8]='8';
            matrix[0][9]='9';
        }
    }

    //STARTING
    printMatrix(matrix);

    printf("\nHOW MANY MOVES DO YOU WANT TO PLAY WITH PLAYER 2(MIN 1 MAX 40): ");
    scanf("%d",&movenumber);

    if(movenumber<=0 || movenumber>40)
    {
        do
        {
            error("MIN 1 MAX 40 MOVES");
            printMatrix(matrix);
            printf("\nHOW MANY MOVES DO YOU WANT TO PLAY WITH PLAYER 2(MIN 1 MAX 40): ");
            scanf("%d",&movenumber);
        }
        while(movenumber<=0 || movenumber>40);
    }

    clear();
    printMatrix(matrix);

    for(int i=0; i<movenumber; i++)
    {

        //PLAYER 1 MOVES
        printf("\n%d MOVES LEFT\n",movenumber-i);
        setTextColor(1);
        printf("PLAYER 1");
        setTextColor(15);
        printf(" SELECT ROW AND COLUMN(MIN 1 MAX 9)(MIN 1 MAX 9): ");
        scanf("%d %d",&prow,&pcolumn);

        if(matrix[prow][pcolumn] != 'X' && matrix[prow][pcolumn] != 'O')
        {
            char *p;
            p = &matrix[prow][pcolumn];
            *p = 'X';
        }
        else
        {
            do
            {
                error("FILLED AREA");
                printMatrix(matrix);
                printf("\n%d MOVES LEFT",movenumber-i);
                setTextColor(1);
                printf("\nPLAYER 1");
                setTextColor(15);
                printf(" SELECT ROW AND COLUMN(MIN 1 MAX 9)(MIN 1 MAX 9): ");
                scanf("%d %d",&prow,&pcolumn);
            }
            while(matrix[prow][pcolumn] == 'X' || matrix[prow][pcolumn] == 'O');

            char *p;
            p = &matrix[prow][pcolumn];
            *p = 'X';
        }
        clear();
        printMatrix(matrix);

        //PLAYER 2 MOVES
        printf("\n%d MOVES LEFT\n",movenumber-i);
        setTextColor(14);
        printf("PLAYER 2");
        setTextColor(15);
        printf(" SELECT ROW AND COLUMN(MIN 1 MAX 9)(MIN 1 MAX 9): ");
        scanf("%d %d",&prow,&pcolumn);

        if(matrix[prow][pcolumn] != 'X' && matrix[prow][pcolumn] != 'O')
        {
            char *p;
            p = &matrix[prow][pcolumn];
            *p = 'O';
        }
        else
        {
            do
            {
                error("FILLED AREA");
                printMatrix(matrix);
                printf("\n%d MOVES LEFT",movenumber-i);
                setTextColor(14);
                printf("\nPLAYER 2");
                setTextColor(15);
                printf(" SELECT ROW AND COLUMN(MIN 1 MAX 9)(MIN 1 MAX 9): ");
                scanf("%d %d",&prow,&pcolumn);
            }
            while(matrix[prow][pcolumn] == 'X' || matrix[prow][pcolumn] == 'O');

            char *p;
            p = &matrix[prow][pcolumn];
            *p = 'O';
        }
        clear();
        printMatrix(matrix);

    }

    //FOR SCORES
    for(int i=1; i<10; i++)
    {
        for(int j=1; j<10; j++)
        {
            if(matrix[i][j]=='X' && matrix[i+1][j]=='X' && matrix[i+2][j]=='X')
                player1score++;
            if(matrix[i][j]=='X' && matrix[i][j+1]=='X' && matrix[i][j+2]=='X')
                player1score++;
            if(matrix[i][j]=='X' && matrix[i+1][j+1]=='X' && matrix[i+2][j+2]=='X')
                player1score++;
            if(matrix[i][j]=='X' && matrix[i+1][j-1]=='X' && matrix[i+2][j-2]=='X')
                player1score++;
        }
    }

    for(int i=1; i<10; i++)
    {
        for(int j=1; j<10; j++)
        {
            if(matrix[i][j]=='O' && matrix[i+1][j]=='O' && matrix[i+2][j]=='O')
                player2score++;
            if(matrix[i][j]=='O' && matrix[i][j+1]=='O' && matrix[i][j+2]=='O')
                player2score++;
            if(matrix[i][j]=='O' && matrix[i+1][j+1]=='O' && matrix[i+2][j+2]=='O')
                player2score++;
            if(matrix[i][j]=='O' && matrix[i+1][j-1]=='O' && matrix[i+2][j-2]=='O')
                player2score++;
        }
    }

    //SCORES AND WINNER
    setTextColor(1);
    printf("\nPLAYER 1 ");
    setTextColor(15);
    printf("SCORE IS %d POINTS.\n",player1score);
    setTextColor(14);
    printf("\nPLAYER 2 ");
    setTextColor(15);
    printf("SCORE IS %d POINTS.\n",player2score);

    if(player1score>player2score)
    {
        printf("\nWINNER: ");
        setTextColor(1);
        printf("PLAYER 1\n");
        setTextColor(15);
    }
    if(player1score<player2score)
    {
        printf("\nWINNER: ");
        setTextColor(14);
        printf("PLAYER 2\n");
        setTextColor(15);
    }
    if(player1score==player2score)
        printf("\nDRAW.\n");

}

void printMatrix(char tempMatrix[10][10])
{
    //for print matrix
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            printf("%c ",tempMatrix[i][j]);
        }
        printf("\n");
    }
}

void removeSpaces(char* str)
{
    char* d = str;
    do
    {
        while (*d == ' ')
        {
            ++d;
        }
    }
    while (*str++ = *d++);
}

void setTextColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }

    return;
}

void start()
{

    char CorP[100];
    printf("DO YOU WANT TO PLAY WITH COMPUTER OR PLAYER 2(C/P): ");
    gets(CorP);

    removeSpaces(CorP);

    if(strcmp(CorP,"C")==0 || strcmp(CorP,"c")==0 || strcmp(CorP,"P")==0 || strcmp(CorP,"p")==0)
    {
        if(strcmp(CorP,"C")==0 || strcmp(CorP,"c")==0)
        {
            clear();
            playWithComputer();
        }

        if(strcmp(CorP,"P")==0 || strcmp(CorP,"p")==0)
        {
            clear();
            playWithPlayer2();
        }
    }

    else
    {
        error("INVALID KEY FOR C/P");
        start();
    }

}
