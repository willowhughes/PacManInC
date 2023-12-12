#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

// Constants for demon directions
#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

void removeCage(char grid[31][28]) {
    grid[16][10] = ' ';
    grid[16][11] = ' ';
    grid[16][12] = ' ';
    grid[16][13] = ' ';
    grid[16][14] = ' ';
    grid[16][15] = ' ';
    grid[16][16] = ' ';
    grid[16][17] = ' ';
    grid[15][10] = ' ';
    grid[14][10] = ' ';
    grid[13][10] = ' ';
    grid[12][10] = ' ';
    grid[15][17] = ' ';
    grid[14][17] = ' ';
    grid[13][17] = ' ';
    grid[12][17] = ' ';
    grid[12][16] = ' ';
    grid[12][15] = ' ';
    grid[12][14] = ' ';
    grid[12][13] = ' ';
    grid[12][12] = ' ';
    grid[12][11] = ' ';
}

void getAvailableMoves(char grid[31][28], int demonRow, int demonCol, int demonLastMove, int* availableMoves, int* numMoves) {
    *numMoves = 0;

    // Check if moving up is possible
    if (demonLastMove != DOWN && grid[demonRow - 1][demonCol] != '#' && grid[demonRow - 1][demonCol] != 'X') {
        availableMoves[*numMoves] = UP;
        (*numMoves)++;
    }

    // Check if moving left is possible
    if (demonLastMove != RIGHT && grid[demonRow][demonCol - 1] != '#' && grid[demonRow][demonCol - 1] != 'X') {
        availableMoves[*numMoves] = LEFT;
        (*numMoves)++;
    }

    // Check if moving down is possible
    if (demonLastMove != UP && grid[demonRow + 1][demonCol] != '#' && grid[demonRow + 1][demonCol] != 'X') {
        availableMoves[*numMoves] = DOWN;
        (*numMoves)++;
    }

    // Check if moving right is possible
    if (demonLastMove != LEFT && grid[demonRow][demonCol + 1] != '#' && grid[demonRow][demonCol + 1] != 'X') {
        availableMoves[*numMoves] = RIGHT;
        (*numMoves)++;
    }
}

void demonsNextMove(char grid[31][28], int *demonRow, int *demonCol, int *demonLastMove) {
    // Seed the random number generator
    srand(time(NULL));

    // Array to store available moves
    int availableMoves[4];
    int numMoves;

    // Get available moves for the demon
    getAvailableMoves(grid, *demonRow, *demonCol, *demonLastMove, availableMoves, &numMoves);

    // Choose the next move based on available options
    int randomIndex;
    if (numMoves > 0) {
        // If there are available moves, pick a random one
        randomIndex = rand() % numMoves;
        *demonLastMove = availableMoves[randomIndex];

        // Move the demon accordingly
        //implement checks so demon doesn't eat food
        switch (*demonLastMove) {
            case UP:
                grid[*demonRow][*demonCol] = ' ';
                (*demonRow)--;
                break;
            case LEFT:
                grid[*demonRow][*demonCol] = ' ';
                (*demonCol)--;
                break;
            case DOWN:
                grid[*demonRow][*demonCol] = ' ';
                (*demonRow)++;
                break;
            case RIGHT:
                grid[*demonRow][*demonCol] = ' ';
                (*demonCol)++;
                break;
        }

        // Update the grid
        grid[*demonRow][*demonCol] = 'X';
    }
    // If there are no available moves, the demon stays in the current position
}

void pacmanAnimation(char grid[31][28], int row, int col, int i, int j, int score) {
    //implement direction detection (^v<>)
    grid[row][col] = 'C';
    draw(grid, i, j, score, row, col);
    //removed for preformance
    // grid[row][col] = 'O';
    // draw(grid, i, j, score, row, col);
    // Sleep(100);
    // grid[row][col] = 'C';
    // draw(grid, i, j, score, row, col);
}

void draw(char grid[31][28], int i, int j, int score, int row, int col) {
    system("cls");
    for (i = 0; i < 31; i++) {
        for (j = 0; j < 28; j++) {
            if (grid[i][j] == 'X') {
                printf("\033[0;31mX \033[0m");
            } else if (grid[i][j] == 'C') {
                printf("\033[0;33mC \033[0m");
            } else if (grid[i][j] == '#') {
                printf("\033[0;34m# \033[0m");
            } else {
                printf("%c ", grid[i][j]);
            }  
        }
        printf("\n");
    }
    printf("\nScore: %d ", score);
    printf("\nrow: %d\ncol: %d", row, col); //debuging purposes
}

int main() {

    int x = 0;
    int row = 23;
    int col = 14;
    int demonOneRow = 15;
    int demonOneCol = 15;
    int demonOneLastMove = 1;
    int demonTwoRow = 15;
    int demonTwoCol = 14;
    int demonTwoLastMove = 2;
    int demonThreeRow = 15;
    int demonThreeCol = 13;
    int demonThreeLastMove = 3;
    int demonFourRow = 15;
    int demonFourCol = 12;
    int demonFourLastMove = 4;
    char input;
    int score = 0;
    int i;
    int j;
    int cage = 1;

    char grid[31][28] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} ,
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'} ,
        {'#', '.', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '.', '#'} ,
        {'#', '.', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '.', '#'} ,
        {'#', '.', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '.', '#'} ,
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'} ,
        {'#', '.', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '.', '#'} ,
        {'#', '.', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '.', '#'} ,
        {'#', '.', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '#'} ,
        {'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', ' ', '#', '#', ' ', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#'} ,
        {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', '#', '#', '#', ' ', '#', '#', ' ', '#', '#', '#', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '} ,
        {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '} ,
        {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '} ,
        {'#', '#', '#', '#', '#', '#', '.', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '.', '#', '#', '#', '#', '#', '#'} ,
        {' ', ' ', ' ', ' ', ' ', ' ', '.', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '.', ' ', ' ', ' ', ' ', ' ', ' '} ,
        {'#', '#', '#', '#', '#', '#', '.', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '.', '#', '#', '#', '#', '#', '#'} ,
        {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '} ,
        {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '} ,
        {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '} ,
        {'#', '#', '#', '#', '#', '#', '.', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '.', '#', '#', '#', '#', '#', '#'} ,
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'} ,
        {'#', '.', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '.', '#'} ,
        {'#', '.', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '.', '#'} ,
        {'#', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '#'} ,
        {'#', '#', '#', '.', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '.', '#', '#', '#'} ,
        {'#', '#', '#', '.', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '.', '#', '#', '#'} ,
        {'#', '.', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '#'} ,
        {'#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#'} ,
        {'#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#'} ,
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'} ,
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };

    // grid[14][15] = 'X';
    // grid[14][14] = 'X'; 
    // grid[14][13] = 'X';
    grid[demonOneRow][demonOneCol] = 'X';
    grid[demonTwoRow][demonTwoCol] = 'X';
    grid[demonThreeRow][demonThreeCol] = 'X';
    grid[demonFourRow][demonFourCol] = 'X';
    grid[row][col] = 'C';
    draw(grid, i, j, score, row, col);

    while (1) {
        if (_kbhit()) {
            input = _getch();

            switch (input) {
                case 'w':
                    if (grid[row - 1][col] != '#') {
                        if (grid[row - 1][col] == '.') {
                            score++;
                        }
                        grid[row][col] = ' ';
                        row--;
                    }
                break;
                case 'a':
                    if (grid[row][col - 1] != '#') {
                        if (grid[row][col - 1] == '.') {
                            score++;
                        }
                        grid[row][col] = ' ';
                        if (col == 1) {
                            col = 26;
                        } else {
                           col--; 
                        }
                    }
                break;
                case 's':
                    if (grid[row + 1][col] != '#') {
                        if (grid[row + 1][col] == '.') {
                            score++;
                        }
                        grid[row][col] = ' ';
                        row++;
                    }
                break;
                case 'd':
                    if (grid[row][col + 1] != '#') {
                        if (grid[row][col + 1] == '.') {
                            score++;
                        }
                        grid[row][col] = ' ';
                        if (col == 26) {
                            col = 1;
                        } else {
                           col++; 
                        }
                    }
                break;
                case 'q':
                    return 0;
            }
            demonsNextMove(grid, &demonOneRow, &demonOneCol, &demonOneLastMove);
            demonsNextMove(grid, &demonTwoRow, &demonTwoCol, &demonTwoLastMove);
            demonsNextMove(grid, &demonThreeRow, &demonThreeCol, &demonThreeLastMove);
            demonsNextMove(grid, &demonFourRow, &demonFourCol, &demonFourLastMove);
            if (grid[row][col] == 'X') {
                pacmanAnimation(grid, row, col, i, j, score);
                printf("\nGAME OVER");
                return 0;
            } else {
                pacmanAnimation(grid, row, col, i, j, score);
            }  
            cage++;
            if (cage == 10) {
                removeCage(grid);
            }
        }
    }
}


    //check upleftdownright (1234)
    //elliminate posibilities based on walls
    //check demonLastMove value to eliminate that from next move
    //generate random move value from remaining moves