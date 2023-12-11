#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<windows.h>
#include<conio.h>

void draw(char grid[10][10], int i, int j) {
    system("cls");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%c ", grid[i][j]);   
        }
        printf("\n");
    }
}

int main() {

    char grid[10][10] = {
        {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'} ,
        {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'} ,
        {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'} ,
        {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'} ,
        {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'} ,
        {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'} ,
        {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'} ,
        {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'} ,
        {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'} ,
        {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'}
    };

    int x = 0;
    int row = 5;
    int col = 5;
    char input;
    int i;
    int j;

    while (1) {
        if (_kbhit()) {
            input = _getch();

            switch (input) {
                case 'w':
                    if (row > 0) {
                        row--;
                    }
                break;
                case 'a':
                    if (col > 0) {
                        col--;
                    }
                break;
                case 's':
                    if (row < 9) {
                        row++;
                    }
                break;
                case 'd':
                    if (col < 9) {
                        col++;
                    }
                break;
                case 'q':
                    return 0;
                }

        if (x == 0) {
            grid[row][col] = 'C';
            x = 1;
        } else {
            grid[row][col] = 'O';
            x = 0;
        }
        draw(grid, i, j);
    }
    // Sleep(500);
    }
}