#include <struct.h>

int fill(){
	int matrix[10][10] = {0};
	int next[10][10];

	for (int row = 0; row < 10; row++) {
		for (int column = 0; column < 10; column++) {
			next[row][column] = matrix[row][column];
		}
	}

	for (int row = 0; row < 10; row++) {
		for (int column = 0; column < 10; column++) {
			int neighbors = 0;

			for (int row_offset = -1; row_offset <= 1; row_offset++) {
				for (int column_offset = -1; column_offset <= 1; column_offset++) {
					if (row_offset == 0 && column_offset == 0) {
						continue;
					}

					int neighbor_row = row + row_offset;
					int neighbor_column = column + column_offset;
					if (neighbor_row >= 0 && neighbor_row < 10 &&
						neighbor_column >= 0 && neighbor_column < 10) {
						neighbors += matrix[neighbor_row][neighbor_column];
					}
				}
			}

			if (neighbors < 2 || neighbors > 3) {
				next[row][column] = 0;
			} else if (neighbors == 3) {
				next[row][column] = 1;
			}
		}
	}
}