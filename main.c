#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stbool.h>

// suggest global variables
char nick[20];

// FILE* fp;
// ,arquivo[20];
// int pontuacao=0, modo=1,
// Int tam_matriz,perdeu=0;
// char matriz[10][10];
// char matrizEspelho[10][10];
// char SomaCol[20];
// char SomaLin[20];
// int VetContLin[10];
// int VetContCol[10];
// char matriz_orig[10][10];
// int VetContLin_orig[10];
// int VetContCol_orig[10];
// char SomaCol_orig[20];
// char SomaLin_orig[20];

// usar a fx system da stdlib pra limpar terminal

void welcome()
{
    char nick;
    printf("Welcome to AddNums!!\n");
    printf("Enter your nickname: ");
    scanf("%c", &nick);
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
        //  exit
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
}
void game()
{
    // fazer uma matriz de char e identacao top
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
    case 3
        //  voltar
        break;
        default: //?
        printf("Invalid choice\n");
        break;
    }
    printf("Choose a option: ");
    scanf("%d", &choice);
}
void instructions()
{
    //  game instructions
}
void ranking()
{
    printf("ranking :\n");
    //  ranking
    //  voltar
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

void main(void)
{
    welcome();
    menu();
}