#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN() system("cls")
    #define SLEEP_1S()     Sleep(1000)
#endif

#define HEIGHT 10
#define WIDTH  10
#define GENERATIONS 100

void print_grid(int grid[HEIGHT][WIDTH], int generation)
{
    CLEAR_SCREEN();

    
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            printf("%c ", grid[row][col] ? '#' : '.');
        }
        printf("\n");
    }
    fflush(stdout);

    SLEEP_1S();
}


void next_generation(int current[HEIGHT][WIDTH], int next[HEIGHT][WIDTH])
{
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            int neighbors = 0;

            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr == 0 && dc == 0) continue;

                    int nr = row + dr;
                    int nc = col + dc;
                    if (nr >= 0 && nr < HEIGHT && nc >= 0 && nc < WIDTH) {
                        neighbors += current[nr][nc];
                    }
                }
            }

            if (current[row][col]) {
                next[row][col] = (neighbors == 2 || neighbors == 3);
            } else {
                next[row][col] = (neighbors == 3);
            }
        }
    }
}

int load_grid_from_file(int grid[HEIGHT][WIDTH], const char *filename)
{
    FILE *file = fopen(filename, "r");
    int row = 0, col = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF && row < HEIGHT) {
        if (ch == '0' || ch == '1') {
            grid[row][col] = (ch == '1');
            col++;
            if (col >= WIDTH) {
                col = 0;
                row++;
            }
        }
    }

    fclose(file);
    return 1;
}

int main(void)
{
    int current[HEIGHT][WIDTH] = {0};
    int next[HEIGHT][WIDTH]    = {0};

    if (!load_grid_from_file(current, "Initial_State.txt")) {
        return 1;
    }

    for (int gen = 0; gen < GENERATIONS; gen++) {
        print_grid(current, gen);
        next_generation(current, next);

        for (int row = 0; row < HEIGHT; row++)
            for (int col = 0; col < WIDTH; col++)
                current[row][col] = next[row][col];
    }

    return 0;
}