#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

//todo:
//efficient pacman animations
//demons dont eat food
    //deleteFood function (called when pacman visits a food's coordinates)
    //isFoodAtCordinates Function (called every time grid is drawn--> ignores places with #, C or X)
    //how do I print pacman and demons in draw for loop. Pass in coordinates?
//bug where if the demon and pacman are facing eachother, they can go past eachother

// Constants for demon directions
#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

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

    //implement: if no avail moves, bounce back
    if (*numMoves == 0) {
        if (demonLastMove == UP) {
            availableMoves[*numMoves] = DOWN;
            (*numMoves)++;
        } else if (demonLastMove == LEFT) {
            availableMoves[*numMoves] = RIGHT;
            (*numMoves)++;
        } else if (demonLastMove == DOWN) {
            availableMoves[*numMoves] = UP;
            (*numMoves)++;
        } else {
            availableMoves[*numMoves] = LEFT;
            (*numMoves)++;
        }
    }
}

void demonsNextMove(char grid[31][28], int *demonRow, int *demonCol, int *demonLastMove) {
    srand(time(NULL));

    int availableMoves[4];
    int numMoves;

    getAvailableMoves(grid, *demonRow, *demonCol, *demonLastMove, availableMoves, &numMoves);

    int randomIndex;
    if (numMoves > 0) {
        randomIndex = rand() % numMoves;
        *demonLastMove = availableMoves[randomIndex];

        // Move the demon
        switch (*demonLastMove) {
            case UP:
                (*demonRow)--;
                break;
            case LEFT:
                if (*demonCol == 1) {
                    *demonCol = 26;
                } else {
                    (*demonCol)--;
                }
                break;
            case DOWN:
                (*demonRow)++;
                break;
            case RIGHT:
                if (*demonCol == 26) {
                    *demonCol = 1;
                } else {
                    (*demonCol)++;
                }
                break;
        }
    }
}

int isDemonHere (int i, int j, int demonOneRow, int demonOneCol, int demonTwoRow, 
                int demonTwoCol, int demonThreeRow, int demonThreeCol, 
                int demonFourRow, int demonFourCol) {
    if (i == demonOneRow && j == demonOneCol) {
        return 1;
    } else if (i == demonTwoRow && j == demonTwoCol) {
        return 1;
    } else if (i == demonThreeRow && j == demonThreeCol) {
        return 1;
    } else if (i == demonFourRow && j == demonFourCol) {
        return 1;
    } else {
        return 0;
    }
}

void draw(char grid[31][28], int *score, int *row, int *col, bool isFood[31][28], int *demonOneRow, 
        int *demonOneCol, int *demonTwoRow, int *demonTwoCol, int *demonThreeRow, int *demonThreeCol, 
        int *demonFourRow, int *demonFourCol) {
    int i;
    int j;
    system("cls");
    for (i = 0; i < 31; i++) {
        for (j = 0; j < 28; j++) {
            if (grid[i][j] == '#') {
                printf("\033[0;34m# \033[0m");
            } else if (isDemonHere(i, j, demonOneRow, demonOneCol, demonTwoRow, demonTwoCol, 
                                    demonThreeRow, demonThreeCol, demonFourRow, demonFourCol)) { 
                   printf("\033[0;31mX \033[0m");
            } else if (isFood[i][j] == true) {
                printf(". ");
            } else if (i == row && j == col) { 
                printf("\033[0;33mC \033[0m");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\nScore: %d ", score);
    printf("\nrow: %d\ncol: %d", row, col); //debuging purposes
}

void pacmanAnimation(char grid[31][28], int *row, int *col, int *score, bool isFood[31][28],
                    int *demonOneRow, int *demonOneCol, int *demonTwoRow, int *demonTwoCol, 
                    int *demonThreeRow, int *demonThreeCol, int *demonFourRow, int *demonFourCol) {
    //implement direction detection (^v<>)
    //grid[*row][*col] = 'C';
    draw(grid, *score, *row, *col, isFood, *demonOneRow, *demonOneCol, *demonTwoRow, *demonTwoCol, 
        *demonThreeRow, *demonThreeCol, *demonFourRow, *demonFourCol);
    //removed for preformance
    // grid[row][col] = 'O';
    // draw(grid, i, j, score, row, col);
    // Sleep(100);
    // grid[row][col] = 'C';
    // draw(grid, i, j, score, row, col);
}

int main() {

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
    //demonOneRow, demonOneCol, demonTwoRow, demonTwoCol, demonThreeRow, demonThreeCol, demonFourRow, demonFourCol
    char input;
    int score = 0;
    int i;
    int j;
    bool isFood[31][28] = {
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false} ,
        {false, true, true, true, true, true, true, true, true, true, true, true, true, false, false, true, true, true, true, true, true, true, true, true, true, true, true, false} ,
        {false, true, false, false, false, false, true, false, false, false, false, false, true, false, false, true, false, false, false, false, false, true, false, false, false, false, true, false} ,
        {false, true, false, false, false, false, true, false, false, false, false, false, true, false, false, true, false, false, false, false, false, true, false, false, false, false, true, false} ,
        {false, true, false, false, false, false, true, false, false, false, false, false, true, false, false, true, false, false, false, false, false, true, false, false, false, false, true, false} ,
        {false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false} ,
        {false, true, false, false, false, false, true, false, false, true, false, false, false, false, false, false, false, false, true, false, false, true, false, false, false, false, true, false} ,
        {false, true, false, false, false, false, true, false, false, true, false, false, false, false, false, false, false, false, true, false, false, true, false, false, false, false, true, false} ,
        {false, true, true, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, true, true, false} ,
        {false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false} ,
        {false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false} ,
        {false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false} ,
        {false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false} ,
        {false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false} ,
        {false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false} ,
        {false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false} ,
        {false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false} ,
        {false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false} ,
        {false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false} ,
        {false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false} ,
        {false, true, true, true, true, true, true, true, true, true, true, true, true, false, false, true, true, true, true, true, true, true, true, true, true, true, true, false} ,
        {false, true, false, false, false, false, true, false, false, false, false, false, true, false, false, true, false, false, false, false, false, true, false, false, false, false, true, false} ,
        {false, true, false, false, false, false, true, false, false, false, false, false, true, false, false, true, false, false, false, false, false, true, false, false, false, false, true, false} ,
        {false, true, true, true, false, false, true, true, true, true, true, true, true, true, false, true, true, true, true, true, true, true, false, false, true, true, true, false} ,
        {false, false, false, true, false, false, true, false, false, true, false, false, false, false, false, false, false, false, true, false, false, true, false, false, true, false, false, false} ,
        {false, false, false, true, false, false, true, false, false, true, false, false, false, false, false, false, false, false, true, false, false, true, false, false, true, false, false, false} ,
        {false, true, true, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, true, true, false} ,
        {false, true, false, false, false, false, false, false, false, false, false, false, true, false, false, true, false, false, false, false, false, false, false, false, false, false, true, false} ,
        {false, true, false, false, false, false, false, false, false, false, false, false, true, false, false, true, false, false, false, false, false, false, false, false, false, false, true, false} ,
        {false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false} ,
        {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false}
    };

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
        {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', ' ', '#', '#', '#', ' ', ' ', '#', '#', '#', ' ', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '} ,
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

    pacmanAnimation(grid, &row, &col, &score, isFood, &demonOneRow, &demonOneCol, &demonTwoRow, 
                    &demonTwoCol, &demonThreeRow, &demonThreeCol, &demonFourRow, &demonFourCol);

    while (1) {
        if (_kbhit()) {
            demonsNextMove(grid, &demonOneRow, &demonOneCol, &demonOneLastMove);
            demonsNextMove(grid, &demonTwoRow, &demonTwoCol, &demonTwoLastMove);
            demonsNextMove(grid, &demonThreeRow, &demonThreeCol, &demonThreeLastMove);
            demonsNextMove(grid, &demonFourRow, &demonFourCol, &demonFourLastMove);
            //todo: (does demon cordinate == pacman coordinate) before and after player move
            input = _getch();

            switch (input) {
                case 'w':
                    if (grid[row - 1][col] != '#') { //if user selected direction isn't facing a wall
                        if (isFood[row - 1][col] == true) { //if user selected direction is facing food
                            score++;                       //eat food and increase score
                        }
                        isFood[row - 1][col] = false; //remove food from coordinate (eat)
                        row--; //move pacman up
                    }
                break;
                case 'a':
                    if (grid[row][col - 1] != '#') {
                        if (isFood[row][col - 1] == true) {
                            score++;
                        }
                        isFood[row][col - 1] = false;
                        if (col == 1) { //if user selected direction is towards teleportation tile
                            col = 26;  //teleport user to other side of map
                        } else {
                           col--; //move pacman left
                        }
                    }
                break;
                case 's':
                    if (grid[row + 1][col] != '#') {
                        if (isFood[row + 1][col] == true) {
                            score++;
                        }
                        isFood[row + 1][col] = false;
                        row++; //move pacman down
                    }
                break;
                case 'd':
                    if (grid[row][col + 1] != '#') {
                        if (isFood[row][col + 1] == true) {
                            score++;
                        }
                        isFood[row][col + 1] = false;
                        if (col == 26) {
                            col = 1;
                        } else {
                           col++; //move pacman right
                        }
                    }
                break;
                case 'q':
                    return 0;
            }
            //todo: (does demon cordinate == pacman coordinate) before and after player move
            if (grid[row][col] == 'X') {
                pacmanAnimation(grid, &row, &col, &score, isFood, &demonOneRow, &demonOneCol, 
                                &demonTwoRow, &demonTwoCol, &demonThreeRow, &demonThreeCol, 
                                &demonFourRow, &demonFourCol);
                printf("\nGAME OVER");
                return 0;
            } else {
                pacmanAnimation(grid, &row, &col, &score, isFood, &demonOneRow, &demonOneCol, 
                                &demonTwoRow, &demonTwoCol, &demonThreeRow, &demonThreeCol, 
                                &demonFourRow, &demonFourCol);
            }  
        }
    }
}