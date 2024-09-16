//========================================//
// Projeto APC - Number Sum               //
// Daniel Florencio Hollenbach - 241020859//
//========================================//

#include <stdio.h>  // standard c input output library to use the printf and scanf functions
#include <string.h> // to use the strcmp function
#include <stdlib.h> // to use the qsort function

#ifdef _WIN32 // a if def to the clear function to work either in windows or linux
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
// to the monitors
// i did some comments to easy the understanding and therefor the correction of the code...i hope it helps you guys 👍
// please run the code with the updated files cause teacher Carla's files are not working properly
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
int completedLines, completedColumns;
char lineSum[7], columnSum[7];
char matrix[7][7], mirror[7][7];

// Colors
void black() { printf("\x1b[0;30m"); }
void red() { printf("\x1b[0;31m"); }
void green() { printf("\x1b[0;32m"); }
void yellow() { printf("\x1b[0;33m"); }
void blue() { printf("\x1b[0;34m"); }
void purple() { printf("\x1b[0;35m"); }
void cyan() { printf("\x1b[0;36m"); }
void white() { printf("\x1b[0;37m"); }
void resetColor() { printf("\x1b[0m"); }

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
    if (fp == NULL)
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
        fp = fopen("avancado.txt", "r");
        break;
    }
    checkFile(fp);
    whichLevel(fp, level);
    for (int i = 0; i < diff; i++) // fill the matrix
    {
        for (int j = 0; j < diff; j++)
        {
            matrix[i][j] = fgetc(fp) - '0'; // convert char to int
        }
        fgetc(fp); // skip the space (\n)
    }
    for (int i = 0; i < diff; i++) // fill the columns sums
    {
        columnSum[i] = (fgetc(fp) - '0') * 10 + (fgetc(fp) - '0'); // turns the first number into a ten and convert char to int
    }
    fgetc(fp);                     // skip the space (\n)
    for (int i = 0; i < diff; i++) // fill the lines sums
    {
        lineSum[i] = (fgetc(fp) - '0') * 10 + (fgetc(fp) - '0'); // turns the first number into a ten and convert char to int
    }
    fgetc(fp);                     // skip the space (\n)
    for (int i = 0; i < diff; i++) // fill the mirror matrix
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
    fflush(stdin); // clear the buffer
    scanf("%s", player.nick);
    fflush(stdin); // clear the buffer
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
void checkSums(int line, int column) // check if the line sum and the column sum is correct
{
    int lineSumLeft = 0, columnSumLeft = 0;
    for (int i = 0; i < diff; i++) // check the line sum left and the column sum left
    {
        lineSumLeft += matrix[line][i];
        columnSumLeft += matrix[i][column];
    }
    if (lineSumLeft == lineSum[line]) // check if the line sum is complete
    {
        completedLines++;
        lineSum[line] = 0;
        printf("Right, you got a line !!!\n");
        waitInput();
    }
    if (columnSumLeft == columnSum[column]) // check if the column sum is complete
    {
        completedColumns++;
        columnSum[column] = 0;
        printf("Right, you got a column !!!\n");
        waitInput();
    }
    if ((completedLines == diff) && (completedColumns == diff)) // when the level is complete
    {
        clearScreen();
        printf("Congratulations, you won !!!\n");
        switch (diff) // differents scores for different difficulties
        {
        case easy:
            player.score += 50;
            break;
        case mid:
            player.score += 100;
            break;
        case dif:
            player.score += 200;
            break;
        }
        updateRanking();
        waitInput();
        level++;        // go to the next level
        if (level == 4) // go to the next difficulty
        {
            if (diff == 4)
                diff = 6;
            else
                diff++;
            level = 0;
            if (diff > 7) // if the game is over
            {
                printf("You won the game!!\n");
                waitInput();
                diff = 4;
            }
        }
        menu();
    }
}
void checkElements() // check if the element can be erased
{
    char line, column;
    printf("Choose a line and a column: ");
    scanf("%c %c", &line, &column);
    line -= '0';                                                  // convert char to int
    column -= '0';                                                // convert char to int
    line--;                                                       // adjust the line
    column--;                                                     // adjust the column
    if (line >= diff || column >= diff || line < 0 || column < 0) // check if the element is within the matrix deepth
    {
        printf("Invalid element, try again\n");
        return;
    }
    if (matrix[line][column] == 0) // erased element
    {
        printf("Element erased, please try other\n");
    }
    else if (mirror[line][column] == 0) // compare the mirror matrix with the matrix
    {
        matrix[line][column] = 0; // condition to be erased
        checkSums(line, column);  // do the math
        green();
        printf("Right, you got it !!\n");
        resetColor();
    }
    else // lose a life
    {
        life--;
        red();
        printf("Wrong element, you have %d lifes\n", life);
        resetColor();
        printf("\n");
    }
}
void game() // the game indeed
{
    clearScreen();
    readFile(level);      // read the file for a especific level
    completedLines = 0;   // reset/initialize the completed lines
    completedColumns = 0; // reset/initialize the completed columns
    while (1)             // game loop
    {
        printMatrix(); // print the matrix
        printf("\n");
        checkElements(); // check the elements
        if (life == 0)   // loose condition
        {
            life = 5;
            printf("Game Over\n");
            updateRanking(); // update the ranking          obs. (i didn't know if it were meant to be this way due to the nonspecifics instructions, but i did it anyway...my bad)
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
        if (columnSum[i] == 0) // if the column sum is 0 print some blank spaces
        {
            printf("   ", columnSum[i]);
            if (i == 0) // if first column sum
                printf("    ", columnSum[i]);
        }
        else if (i == 0)
            printf("     %d ", columnSum[i]); // print the first column sum
        else if (columnSum[i] > 9)
            printf("%d ", columnSum[i]); // print the others columns sums if a ten
        else
            printf(" %d ", columnSum[i]); // print the others columns sums if not a ten
    }
    switch (diff) // differents indentations for different difficulties
    {
    case easy:
        printf("\n   -------------\n");
        break;
    case mid:
        printf("\n   -------------------\n");
        break;
    case dif:
        printf("\n   -----------------------\n");
        break;
    }
    for (int i = 0; i < diff; i++) // print the lines sums and the matrix elements
    {
        if (lineSum[i] == 0) // if the line sum is 0 print some blank spaces
        {
            printf("  ", lineSum[i]);
        }
        else if (lineSum[i] > 9)
            printf("%d", lineSum[i]); // print the others columns sums if a ten
        else
            printf(" %d", lineSum[i]); // print the others columns sums if not a ten
        printf(" ");
        printf("|");

        for (int j = 0; j < diff; j++) // print matrix elements
        {
            if (matrix[i][j] == 0)
                printf("   "); // print a blank space of erased elements
            else
                printf(" %d ", matrix[i][j]); // print the others matrix elements
        }
        printf("\n");
    }
}
void waitInput() // a function to wait for the user to press some key
{
    printf("Press <Enter> to continue\n");
    fflush(stdin); // clear the buffer
    getchar();     // get a random character just to work as a pause
    fflush(stdin); // clear the buffer
}
void resetRanking() // a function to reset the ranking
{
    char choice;
    printf("Are you sure you want to reset the ranking? (y/n): ");
    choice = getchar();
    if (choice == 'y') // opens the ranking.bin and write nothing in it, making the file empty
    {
        FILE *fp_ranking = fopen("ranking.bin", "wb");
        checkFile(fp_ranking);
        fclose(fp_ranking);
        printf("Ranking reseted\n");
        waitInput();
    }
    else if (choice == 'n') // if the player doesn't want to reset the ranking
    {
        printf("Ranking not reseted\n");
        waitInput();
    }
    else // if the player doesn't choose a valid option
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
    switch (choice) // set the difficulty
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
    fflush(stdin); // clear the buffer
    printf("Choose a option: ");
    choice = getchar();
    fflush(stdin); // clear the buffer
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
    printf("For example, to delete a element in the 1st line and the 3rd column, simply give the input 1 3.\n");
    printf("\n");
    waitInput();
    clearScreen();
    menu();
}
void ranking() // a function to show the ranking
{
    int count = 0;
    clearScreen();
    FILE *fp_ranking = fopen("ranking.bin", "rb"); // open the ranking file
    checkFile(fp_ranking);                         // check if the file is openning
    printf("ranking :\n");
    while (1) // ranking loop
    {
        Players others; // a variable to store the other players
        int read = fread(&others, sizeof(player), 1, fp_ranking);
        count += read;
        if (read == 0) // when the file ends
            break;     // end of file
        printf("%s %d\n", others.nick, others.score);
    }
    if (count == 0) // if the ranking is empty
    {
        printf("The ranking is empty\n");
    }
    printf("\n\n");
    waitInput();
    menu();
}
void updateRanking() // a function to update the ranking
{
    FILE *fp_ranking = fopen("ranking.bin", "rb+"); // open the ranking file
    if (fp_ranking == NULL)                         // makes the file if it doesn't exist
    {
        fp_ranking = fopen("ranking.bin", "wb");
        checkFile(fp_ranking);
        fwrite(&player, sizeof(player), 1, fp_ranking);
        fclose(fp_ranking);
        return;
    }
    fseek(fp_ranking, 0, SEEK_END); // go to the end of the file
    int size = ftell(fp_ranking) / sizeof(player);
    size++;                         // add space for a possible new player
    fseek(fp_ranking, 0, SEEK_SET); // back to the beginning
    Players ranking[size];          // a raking array to store the players
    fread(ranking, sizeof(player), size, fp_ranking);
    int found = 0;                     // flag to check if the player is already in the ranking
    for (int i = 0; i < size - 1; i++) // check if the player is already in the ranking
    {
        if (strcmp(player.nick, ranking[i].nick) == 0) // check if the string is the same and add score if it exists
        {
            ranking[i].score += player.score;
            player.score = 0;
            found = 1;
            break;
        }
    }
    if (!found) // if the player is not in the ranking, it creates a new player in the ranking in the remainig space
    {
        ranking[size - 1] = player;
    }
    else // take off the extra space
    {
        size--;
    }
    qsort(ranking, size, sizeof(player), compare);     // sort the ranking
    fseek(fp_ranking, 0, SEEK_SET);                    // back to the beginning
    fwrite(ranking, sizeof(player), size, fp_ranking); // write the ranking
    fclose(fp_ranking);                                // close the file
}
void menu() // a function to show the main menu of the game
{
    clearScreen();
    char choice;
    green();
    printf("1. Play\n");
    resetColor();
    printf("2. Configs\n");
    printf("3. Instructions\n");
    yellow();
    printf("4. Ranking\n");
    red();
    printf("5. Exit\n");
    resetColor();
    printf("Enter your choice: ");
    fflush(stdin); // clear the buffer
    choice = getchar();
    fflush(stdin); // clear the buffer
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
void main(void) // main function with the menu loop
{
    // set the initial values
    diff = easy;
    level = 0;
    life = 5;

    welcome();
    while (1) // menu loop
    {
        menu();
    }
}