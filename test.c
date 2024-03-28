// printing a matrix in temrinal with looping structures

#include <stdio.h>
#include <stdlib.h>

int** matrix;
int lines = 5;
int columns = 10;

int main() {

    // allocating memory dynamically
    matrix = malloc(sizeof(int*) * lines);
    for (int idx = 0; idx < lines; idx++) {
        matrix[idx] = malloc(sizeof(int) * columns);
    }

    printf("lines %d columns %d\n\n", lines, columns);

    int count = 0;

    for (int i_idx = 0; i_idx < lines; i_idx++) {
        printf("[");
        for (int j_idx = 0; j_idx < columns; j_idx++) {
            count +=1;
            matrix[i_idx][j_idx] = count;
            if (j_idx != columns-1) {
                printf("%d, ", matrix[i_idx][j_idx]);
            } else {
                printf("%d", matrix[i_idx][j_idx]);
            }
        }
        printf("]");
        printf("\n");
    }

    // step necessary to free memory dynamically allocated
    for (int idx = 0; idx < lines; idx++) {
        free(matrix[idx]);
    }
    free(matrix);

}