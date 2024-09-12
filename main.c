// Projeto APC - Number Sum
// Daniel Florencio Hollenbach - 241020859

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef enum Difficulty
{
    easy = 4,
    mid = 6,
    dif
} Difficulty;
typedef struct players
{
    char nick[21];
    int score;
} players;

Difficulty diff;
players player;

int level, life;
char lineSum[7], columnSum[7]; // lines and column deletes?
char matrix[7][7], mirror[7][7];

void clearScreen() // a function to clear the screen
{
    system(CLEAR);
}

int compare(players *p1, players *p2) // a function to compare two strings
{
    return p2->score - p1->score;
}

void whichLevel(FILE *fp, int level) // a function to check the level
{
    int count = 0;
    while (count != level)
    {
        char c = fgetc(fp);
        if (c == '*')
        {
            count++;
            fgetc(fp); // skip the space (\n)
        }
    }
}

void checkFile(FILE *fp) // a function to check if the file is openning
{
    if (fp == NULL) //
    {
        printf("Error opening file\n");
        exit(1);
    }
}

void readFile(int level) // a function to read the file
{
    FILE *fp;
    switch (diff) // check which file to open
    {
    case easy:
        fp = fopen("iniciante.txt", "r");
        break;
    case mid:
        fp = fopen("intermediario.txt", "r");
        break;
    case dif:
        fp = fopen("avancadi.txt", "r");
        break;
    }
    checkFile(fp);
    whichLevel(fp, level);
    for (int i = 0; i < diff; i++) // fill the first easy mode matrix
    {
        for (int j = 0; j < diff; j++)
        {
            matrix[i][j] = fgetc(fp) - '0'; // convert char to int
        }
        fgetc(fp); // skip the space (\n)
    }
    for (int i = 0; i < diff; i++) // fill the first easy mode columns sums
    {
        columnSum[i] = (fgetc(fp) - '0') * 10 + (fgetc(fp) - '0'); // turns the first number into a ten and convert char to int
    }
    fgetc(fp);                     // skip the space (\n)
    for (int i = 0; i < diff; i++) // fill the first easy mode lines sums
    {
        lineSum[i] = (fgetc(fp) - '0') * 10 + (fgetc(fp) - '0'); // turns the first number into a ten and convert char to int
    }
    fgetc(fp);                     // skip the space (\n)
    for (int i = 0; i < diff; i++) // fill the first easy mode mirror matrix
    {
        for (int j = 0; j < diff; j++)
        {
            mirror[i][j] = fgetc(fp) - '0'; // convert char to int
        }
        fgetc(fp); // skip the space (\n)
    }
    fclose(fp);
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
    // life 5
    readFile(level);
    for (int i = 0; i < diff; i++)
    {
        printf(" %d ", columnSum[i]);
    }
    printf("\n");
    for (int i = 0; i < diff; i++)
    {
        for (int j = 0; j < diff; j++)
        {
            printf(" %d ", matrix[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < diff; i++)
    {
        printf("%d ", lineSum[i]);
    }
    for (int i = 0; i < diff; i++)
    {
        for (int j = 0; j < diff; j++)
        {
            printf(" %d ", mirror[i][j]);
        }
        printf("\n");
    }
}

void resetRanking() // a function to reset the ranking
{
    char choice;
    printf("Are you sure you want to reset the ranking? (y/n): ");
    choice = getchar();
    if (choice == 'y')
    {
        FILE *fp_ranking = fopen("ranking.bin", "wb");
        checkFile(fp_ranking);
        fclose(fp_ranking);
        printf("Ranking reseted\n");
    }
    else if (choice == 'n')
    {
        printf("Ranking not reseted\n");
    }
    else
    {
        printf("Invalid choice\n");
        resetRanking();
    }
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
    clearScreen();
    FILE *fp_ranking = fopen("ranking.bin", "rb");
    checkFile(fp_ranking);
    printf("ranking :\n");
    while (1)
    {
        players others;
        int read = fread(&others, sizeof(player), 1, fp_ranking);
        if (read == 0) break;   // end of file
        printf("%s %d\n", others.nick, others.score);
    } 
    printf("\n\npress <Enter> to get back to the menu");
    getchar();
   
}
void updateRanking()  // a function to update the ranking
{
    FILE *fp_ranking = fopen("ranking.bin", "rb+");
    if (fp_ranking == NULL)
    {
        fp_ranking = fopen("ranking.bin", "wb");
        checkFile(fp_ranking);
        fwrite(&player, sizeof(player), 1, fp_ranking);
        fclose(fp_ranking);
        return;
    }
    fseek(fp_ranking, 0, SEEK_END);     //go to the end of the file
    int size = ftell(fp_ranking) / sizeof(player);
    size++;
    fseek(fp_ranking, 0, SEEK_SET);     // back to the beginning
    players ranking[size];
    fread(ranking, sizeof(player), size, fp_ranking);
    int found = 0;
    for(int i = 0; i < size - 1; i++){
        if(strcmp(player.nick, ranking[i].nick) == 0){
            ranking[i].score += player.score;
            player.score = 0;
            found = 1;
            break;
        }
    }
    if (!found)
    {
        ranking[size - 1] = player;
    }else{
        size--;
        

    }
    qsort(ranking, size, sizeof(player), compare);
    fseek(fp_ranking, 0, SEEK_SET);
    fwrite(ranking, sizeof(player), size, fp_ranking);
    fclose(fp_ranking);
}
void menu()
{
    clearScreen();
    char choice;
    printf("1. Play\n");
    printf("2. Configs\n");
    printf("3. Instructions\n");
    printf("4. Ranking\n");
    printf("5. Exit ;<\n");
    printf("Enter your choice: ");
    fflush(stdin);
    choice = getchar();
    fflush(stdin);
    switch (choice)
    {
    case '1':
        game();
        break;
    case '2':
        configurations();
        break;
    case '3':
        instructions();
        break;
    case '4':
        ranking();
        break;
    case '5':
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
    diff = mid;
    level = 3;
    char *str = "player1";
    strcpy(player.nick, str);
    player.score = 500;
    updateRanking();
    player.score = 600;
    updateRanking();
    ranking();
    return 0;
    // fp=fopen("ranking.txt","r");
    welcome();
    while(1){
        menu();
    }

    return 0;
}