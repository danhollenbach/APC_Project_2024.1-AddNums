#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef struct players
{
    char nick[20];
    int score, level, life;
} players;

players player;
// int easyLine[4], easyColumn[4];
char easyLineSum[4], easyColumnSum[4], midLineSum[6], midColumnSum[6], diffLineSum[7], diffColumnSum[7]; // lines and column deletes?
char easyMatrix[4][4], easyMirror[4][4], midMatrix[6][6], midMirror[6][6], diffMatrix[7][7], diffMirror[7][7];

// suggest global variables
// FILE* fp;
// ,arquivo[20];
// int pontuacao=0, modo=1,
// Int tam_matriz,perdeu=0;
// char matriz_orig[10][10];
// int VetContLin_orig[10];
// int VetContCol_orig[10];
// char SomaCol_orig[20];
// char SomaLin_orig[20];

void clearScreen() // a function to clear the screen
{
    system(CLEAR);
}

void readFile(FILE *fp)
{
    for (int i = 0; i < 4; i++) // fill the first easy mode matrix
    {
        for (int j = 0; j < 4; j++)
        {
            easyMatrix[i][j] = fgetc(fp) - '0'; // convert char to int
        }
        fgetc(fp); // skip the space (\n)
    }

    for (int i = 0; i < 4; i++) // fill the first easy mode columns sums
    {
        easyColumnSum[i] = (fgetc(fp) - '0') * 10 + (fgetc(fp) - '0'); // turns the first number into a ten and convert char to int
    }
    fgetc(fp);                  // skip the space (\n)
    for (int i = 0; i < 4; i++) // fill the first easy mode lines sums
    {
        easyLineSum[i] = (fgetc(fp) - '0') * 10 + (fgetc(fp) - '0'); // turns the first number into a ten and convert char to int
    }
    fgetc(fp);                  // skip the space (\n)
    for (int i = 0; i < 4; i++) // fill the first easy mode mirror matrix
    {
        for (int j = 0; j < 4; j++)
        {
            easyMirror[i][j] = fgetc(fp) - '0'; // convert char to int
        }
        fgetc(fp); // skip the space (\n)
    }
}

void welcome()
{
    printf("Welcome to AddNums!!\n");
    printf("Enter your nickname: ");
    scanf("%s", player.nick);
    int lenght = strlen(player.nick);
    if (lenght > 20) // check if nickname is valid, less than 20 characters
    {
        printf("Invalid nickname, try again\n");
        welcome();
    }

    for (int i = 0; i < lenght; i++) // check if nickname is valid, only letters, numbers, underscore and space
    {
        if (!isalpha(player.nick[i]) && !isdigit(player.nick[i]) && player.nick[i] != ' ' && player.nick[i] != '_')
        {
            printf("Invalid nickname, try again\n");
            welcome();
        }
    }
    clearScreen();
}

void game()
{
    clearScreen();
    player.level = 1;
    // life 5
    switch (player.level)
    {
    case 1:
        printf("Level 1\n");
        FILE *fp;
        fp = fopen("iniciante.txt", "r");
        readFile(fp);
        for (int i = 0; i < 4; i++)
        {
            printf(" %d ", easyColumnSum[i]);
        }
        printf("\n");
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                printf(" %d ", easyMatrix[i][j]);
            }
            printf("\n");
        }
        for (int i = 0; i < 4; i++)
        {
            printf("%d ", easyLineSum[i]);
        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                printf(" %d ", easyMirror[i][j]);
            }
            printf("\n");
        }
        break;
    case 2:
        for (int i = 0; i < 4; i++)
        {
            printf("%d", easyColumnSum[i]);
        }
        break;
    case 3:
        for (int i = 0; i < 4; i++)
        {
            printf("%d", easyColumnSum[i]);
        }
        break;
    case 4:
        for (int i = 0; i < 4; i++)
        {
            printf("%d", easyColumnSum[i]);
        }
        break;
    }
}
void resetRanking()
{
    printf("Are you sure you want to reset the ranking? (y/n): ");
    //  reset ranking
}
void diffs()
{
    int choice;
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Advanced\n");
    printf("4. Back\n");
    printf("Choose a option: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("You chose easy\n");
        //  easy
        break;
    case 2:
        printf("You chose medium\n");
        //  medium
        break;
    case 3:
        printf("You chose advanced\n");
        //  advanced
        break;
    case 4:
        //  back
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
}
void configurations()
{
    int choice;
    switch (choice)
    {
    case 1:
        //  zerar ranking
        resetRanking();
        break;
    case 2:
        diffs();
        //  dif ini, mid advanced
        // back
        break;
    case 3:
        //  voltar
        printf("Choose a option: ");
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
    printf("Choose a option: ");
    scanf("%d", &choice);
}
void instructions()
{
    char anyKey[1];
    clearScreen();
    printf("Instructions:\n");
    printf("-> This game is a number sum like game.\n");
    printf("You have 5 lifes and will have to delete matrix elements to get to the lines and columns sums,\n");
    printf("but be careful, if you delete the wrong number you will lose a life.\n");
    printf("to delete a number just write it's 'adress'([m][n]).\n");
    printf("For example, to delete a element in the 1st line and the 3rd column, simply give the input 1 3\n");
    printf("\npress any key to get back to the menu");
    scanf("%s", anyKey);
    clearScreen();
    menu();
}
void ranking()
{
    printf("ranking :\n");
    //  ranking
    //  voltar
}

void menu()
{
    int choice;
    printf("1. Play\n");
    printf("2. Configs\n");
    printf("3. Instructions\n");
    printf("4. Ranking\n");
    printf("5. Exit ;<\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        game();
        break;
    case 2:
        configurations();
        break;
    case 3:
        instructions();
        break;
    case 4:
        ranking();
        break;
    case 5:
        exit(0);
        break;
    default:
        clearScreen();
        printf("Invalid choice, try again\n");
        menu();
        break;
    }
}

void main(void)
{
    // fp=fopen("ranking.txt","r");
    welcome();
    menu();
}