#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<windows.h>

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

int i;
int j;


void draw() {
    system("cls");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%c ", grid[i][j]);   
        }
        printf("\n");
    }
}

int main() {
    int x = 0;

    
    while (1) {
        if (x == 0) {
            grid[5][5] = 'C';
            x = 1;
        } else {
            grid[5][5] = 'O';
            x = 0;
        }
        draw();
        Sleep(500);
    }
}