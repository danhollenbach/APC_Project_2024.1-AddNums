#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

// suggest global variables
char nick[20];
int level;
// FILE* fp;
// ,arquivo[20];
// int pontuacao=0, modo=1,
// Int tam_matriz,perdeu=0;
char matrix[10][10], mirror[10][10];
char lineSum[20], columnSum[20];
int lineValues[10], columnValues[10];
// char matriz_orig[10][10];
// int VetContLin_orig[10];
// int VetContCol_orig[10];
// char SomaCol_orig[20];
// char SomaLin_orig[20];

// usar a fx system da stdlib pra limpar terminal
void welcome()//check
{
    printf("Welcome to AddNums!!\n");
    printf("Enter your nickname: ");
    scanf("%s", &nick);
    // printf("Hello, %s\n", nick);
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
        printf("Invalid choice\n");
        clearScreen();
        invalidChoice();
        break;
    }
}
void invalidChoice()//check
{
    printf("Invalid choice, try again\n");
    menu();
}
void game()
{
    // life 5 
    switch(level)
    {
        case 1:
            //  easy
            //  life 5
            for(int i = 0; i < 4; i++){
            printf("%d", columnSum[i]);
            }
            break;
        case 2:
            //  medium
            //  life 3
            for(int i = 0; i < 4; i++){
            printf("%d", columnSum[i]);
            }
            break;
        case 3:
            //  advanced
            //  life 1
            for(int i = 0; i < 4; i++){
            printf("%d", columnSum[i]);
            }
            break;
        case 4:
            //  back
            for(int i = 0; i < 4; i++){
            printf("%d", columnSum[i]);
            }
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
void clearScreen()// check
{
    system(CLEAR);
}
void main(void)
{
    // fp=fopen("ranking.txt","r");
    welcome();
    clearScreen();
    menu();
}