//========================================//
// Projeto APC - Number Sum               //
// Daniel Florencio Hollenbach - 241020859//
//========================================//

#include <stdio.h>
#include <string.h> // to use the strcmp function
#include <stdlib.h> // to use the qsort function

#ifdef _WIN32 // a if def to the clear function to work either in windows or linux
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef enum Difficulty // a enum to define the difficulty
{
    easy = 4,
    mid = 6,
    dif
} Difficulty;
typedef struct Players // a struct to define the players
{
    char nick[21];
    int score;
} Players;

Difficulty diff; // a variable to define the difficulty
Players player;  // a variable to define the player

// my global variables
int level, life;
char lineSum[7], columnSum[7];
char matrix[7][7], mirror[7][7];

void clearScreen() // a function to clear the screen
{
    system(CLEAR);
}
int compare(Players *p1, Players *p2) // a function to compare two scores
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
void welcome() // a welcome screen
{
    clearScreen();
    printf("Welcome to AddNums!!\n");
    printf("Enter your nickname: ");
    fflush(stdin);
    scanf("%s", player.nick);
    fflush(stdin);
    int lenght = strlen(player.nick);
    if (lenght > 20) // check if nickname is valid, less than 20 characters
    {
        printf("Invalid nickname, try again\n");
        waitInput();
        welcome();
    }

    for (int i = 0; i < lenght; i++) // check if nickname is valid, only letters, numbers, underscore and space
    {
        if (!isalpha(player.nick[i]) && !isdigit(player.nick[i]) && player.nick[i] != ' ' && player.nick[i] != '_')
        {
            printf("Invalid nickname, try again\n");
            waitInput();
            welcome();
        }
    }
    clearScreen();
}

void checkSums(int line, int column) // check if the line sum is correct
{
    int lineSumLeft = 0, columnSumLeft = 0;
    for (int i = 0; i < diff; i++) // check the line sum
    {
        lineSumLeft += matrix[line][i];
        columnSumLeft += matrix[i][columnSumLeft];
    }
    if (lineSumLeft == lineSum[line])
    {
        lineSum[line] = 0;
        printf("Right, you got a line !!!\n");
        waitInput();
    }
    if (columnSumLeft == columnSum[column])
    {
        columnSum[column] = 0;
        printf("Right, you got a column !!!\n");
        waitInput();
    }
}
void checkElements() // check if the element can be erased
{
    char line, column;
    printf("Choose a line and a column: ");
    scanf("%c %c", &line, &column);
    line -= '0';
    column -= '0';
    line--;
    column--;
    if (line >= diff || column >= diff || line < 0 || column < 0) // check if the element is within the matrix deepth
    {
        printf("Invalid element, try again\n");
        return;
    }
    if (mirror[line][column] == 0)
    {
        matrix[line][column] = 0;
        checkSums(line, column);
        printf("Right, you got it !!\n");
    }
    else
    {
        life--;
        printf("Wrong element, you have %d lifes\n", life);
        printf("\n");
    }
}
void game() // the game indeed
{
    clearScreen();
    readFile(level);
    while (1)
    {
        printMatrix(); // print the matrix
        printf("\n");
        checkElements();
        if (life == 0)
        {
            life = 5;
            printf("Game Over\n");
            updateRanking();
            waitInput();
            break;
        }
        waitInput();
    }
}
void printMatrix() // a function to print the matrix
{
    clearScreen();
    for (int i = 0; i < diff; i++) // print the columns sums
    {
        if (i == 0)
            printf("     %d ", columnSum[i]); // print the first column sum
        else if (columnSum[i] > 9)
            printf("%d ", columnSum[i]); // print the others columns sums
        else
            printf(" %d ", columnSum[i]);
    }
    printf("\n   -------------\n");

    for (int i = 0; i < diff; i++)
    {
        if (lineSum[i] == 0)
        {
            printf("  ", lineSum[i]);
        }
        else if (lineSum[i] > 9)
            printf("%d", lineSum[i]); // print the lines sums
        else
            printf(" %d", lineSum[i]);
        printf(" ");
        printf("|");

        for (int j = 0; j < diff; j++) // print matrix elements
        {
            if (matrix[i][j] == 0)
                printf("   "); // print a blank space of erased elements
            else
                printf(" %d ", matrix[i][j]); // print the others matrix elemnts
        }
        printf("\n");
    }
}
void waitInput() // a function to wait for the user to press some key
{
    printf("Press <Enter> to continue\n");
    fflush(stdin);
    getchar();
    fflush(stdin);
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
        waitInput();
    }
    else if (choice == 'n')
    {
        printf("Ranking not reseted\n");
        waitInput();
    }
    else
    {
        printf("Invalid choice\n");
        resetRanking();
    }
}
void diffs() // a function to show and set the difficulties
{
    clearScreen();
    char choice;
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Advanced\n");
    printf("4. Back\n");
    printf("Choose a option: ");
    choice = getchar();
    switch (choice)
    {
    case '1':
        diff = easy;
        printf("You chose easy\n");
        waitInput();
        break;
    case '2':
        diff = mid;
        printf("You chose medium\n");
        waitInput();
        break;
    case '3':
        diff = dif;
        printf("You chose advanced\n");
        waitInput();
        break;
    case '4':
        configurations();
        break;
    default:
        printf("Invalid choice\n");
        diffs();
        break;
    }
}
void configurations() // a function to show and set the configurations
{
    clearScreen();
    char choice;
    printf("Configurations:\n");
    printf("1. Reset ranking\n");
    printf("2. Difficulty\n");
    printf("3. Back\n");
    fflush(stdin);
    printf("Choose a option: ");
    choice = getchar();
    fflush(stdin);
    switch (choice)
    {
    case '1':
        resetRanking();
        configurations();
        break;
    case '2':
        diffs();
        configurations();
        break;
    case '3':
        menu();
        break;
    default:
        clearScreen();
        printf("Invalid choice\n");
        waitInput();
        configurations();
        break;
    }
}
void instructions() // a function to show the instructions
{
    clearScreen();
    printf("Instructions:\n");
    printf("-> This game is a number sum like game.\n");
    printf("You have 5 lifes and will have to delete matrix elements to get to the lines and columns sums,\n");
    printf("but be careful, if you delete the wrong number you will lose a life.\n");
    printf("To delete a number just write it's 'adress'([m][n]).\n");
    printf("For example, to delete a element in the 1st line and the 3rd column, simply give the input 1 3\n");
    printf("\npress <Enter> to get back to the menu");
    getchar();
    clearScreen();
    menu();
}
void ranking() // a function to show the ranking
{
    clearScreen();
    FILE *fp_ranking = fopen("ranking.bin", "rb");
    checkFile(fp_ranking);
    printf("ranking :\n");
    while (1)
    {
        Players others;
        int read = fread(&others, sizeof(player), 1, fp_ranking);
        if (read == 0)
            break; // end of file
        printf("%s %d\n", others.nick, others.score);
    }
    printf("\n\npress <Enter> to get back to the menu");
    getchar();
}
void updateRanking() // a function to update the ranking
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
    fseek(fp_ranking, 0, SEEK_END); // go to the end of the file
    int size = ftell(fp_ranking) / sizeof(player);
    size++;
    fseek(fp_ranking, 0, SEEK_SET); // back to the beginning
    Players ranking[size];
    fread(ranking, sizeof(player), size, fp_ranking);
    int found = 0;
    for (int i = 0; i < size - 1; i++)
    {
        if (strcmp(player.nick, ranking[i].nick) == 0)
        {
            ranking[i].score += player.score;
            player.score = 0;
            found = 1;
            break;
        }
    }
    if (!found)
    {
        ranking[size - 1] = player;
    }
    else
    {
        size--;
    }
    qsort(ranking, size, sizeof(player), compare);
    fseek(fp_ranking, 0, SEEK_SET);
    fwrite(ranking, sizeof(player), size, fp_ranking);
    fclose(fp_ranking);
}
void menu() // a function to show the main menu of the game
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
        waitInput();
        menu();
        break;
    }
}
void main(void) // main function with the game loop
{
    diff = easy;
    level = 0;
    life = 5;

    welcome();
    while (1)
    {
        menu();
    }
}