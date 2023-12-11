#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<windows.h>
#include<conio.h>

void pacmanAnimation(char grid[10][10], int row, int col, int i, int j, int score) {
    grid[row][col] = 'C';
    draw(grid, i, j, score);
    grid[row][col] = 'O';
    draw(grid, i, j, score);
    Sleep(100);
    grid[row][col] = 'C';
    draw(grid, i, j, score);
}

void draw(char grid[10][10], int i, int j, int score) {
    system("cls");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%c ", grid[i][j]);   
        }
        printf("\n");
    }
    printf("Score: %d ", score);
}

int main() {

    //make generate map here instead
    char grid[10][10] = {
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'} ,
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'} ,
        {'.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.'} ,
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'} ,
        {'.', '.', 'X', '.', '.', '.', '.', '.', '.', '.'} ,
        {'#', '#', '#', '#', '.', '.', '.', '.', '.', '.'} ,
        {'.', '.', '.', '#', '.', '.', '.', '.', 'X', '.'} ,
        {'.', '.', '.', '#', '#', '#', '#', '#', '#', '.'} ,
        {'.', '.', '.', '.', '.', '.', '.', '.', '#', '.'} ,
        {'.', '.', '.', '.', '.', '.', '.', '.', '#', '.'}
    };



    int x = 0;
    int row = 5;
    int col = 5;
    char input;
    int score = 0;
    int i;
    int j;

    grid[row][col] = 'C';
    draw(grid, i, j, score);

    while (1) {
        if (_kbhit()) {
            input = _getch();

            switch (input) {
                case 'w':
                    if (row > 0 && grid[row - 1][col] != '#') {
                        if (grid[row - 1][col] == '.') {
                            score++;
                        }
                        grid[row][col] = ' ';
                        row--;
                    }
                break;
                case 'a':
                    if (col > 0 && grid[row][col - 1] != '#') {
                        if (grid[row][col - 1] == '.') {
                            score++;
                        }
                        grid[row][col] = ' ';
                        col--;
                    }
                break;
                case 's':
                    if (row < 9 && grid[row + 1][col] != '#') {
                        if (grid[row + 1][col] == '.') {
                            score++;
                        }
                        grid[row][col] = ' ';
                        row++;
                    }
                break;
                case 'd':
                    if (col < 9 && grid[row][col + 1] != '#') {
                        if (grid[row][col + 1] == '.') {
                            score++;
                        }
                        grid[row][col] = ' ';
                        col++;
                    }
                break;
                case 'q':
                    return 0;
            }

            if (grid[row][col] == 'X') {
                pacmanAnimation(grid, row, col, i, j, score);
                printf("\nGAME OVER");
                return 0;
            } else {
                pacmanAnimation(grid, row, col, i, j, score);
            }
            
        }
    }
}