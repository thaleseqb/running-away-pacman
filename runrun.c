#include <stdio.h>
#include <stdlib.h>
#include "header.h"

char** map;
int lines;
int columns;

void dynamic_allocation() {
    map = malloc(sizeof(char*) * lines);
    for (int idx = 0; idx < lines; idx++) {
        map[idx] = malloc(sizeof(char) * (columns+1));
    }
}

void freemap() {
    for (int idx = 0; idx < lines; idx++) {
        free(map[idx]);
    }

    free(map);
}

void read_map() {
    FILE* file;
    file = fopen("mapa.txt", "r");
    if (file == 0) {
        printf("error in reading the file");
        exit(1);
    }

    fscanf(file, "%d %d", &lines, &columns);
    printf("lines %d columns %d\n", lines, columns);

    dynamic_allocation();

    for (int idx = 0; idx < 5; idx++) {
        fscanf(file, "%s", map[idx]);
    }

    fclose(file);
}

void print_map() {
    for (int idx = 0; idx < 5; idx++) {
        printf("%s\n", map[idx]);
    }
}

int finish() {
    return 0;
}

void moove(char direction) {
    int x;
    int y;

    for (int i_idx = 0; i_idx < lines; i_idx++) {
        for (int j_idx = 0; j_idx < columns; j_idx++) {
            if (map[i_idx][j_idx] == '@') {
                x = i_idx;
                y = j_idx;
                break;
            }
        }
    }

    switch (direction) {
    case 'w':
        map[x-1][y] = '@';
        break;
    case 's':
        map[x+1][y] = '@';
        break;
    case 'd':
        map[x][y+1] = '@';
        break;
    case 'a':
        map[x][y-1] = '@';
        break;
    }

    map[x][y] = '.';
}

int main() {

    read_map();

    do
    {
        print_map();
        char command;
        scanf(" %c", &command);

        moove(command);

    } while (!finish() );
    

    freemap(map);

}