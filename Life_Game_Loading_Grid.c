#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define HEIGHT 10
#define WIDTH 10

void load_grid_from_file(int grid[HEIGHT][WIDTH], const char *filename) {
    FILE *file = fopen(filename, "r");
    int row = 0, col = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (row >= HEIGHT) break;

        if (ch == '1') {
            grid[row][col] = 1;
            col++;
        } else if (ch == '0') {
            grid[row][col] = 0;
            col++;
        }

        if (col >= WIDTH) {
            col = 0;
            row++;
        }
    }
    fclose(file);
}

int main() {
        int current[HEIGHT][WIDTH] = {0};
        load_grid_from_file(current, "Initial_State.txt");
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                printf("%d ", current[i][j]);
            }
        printf("\n");
    }

}

