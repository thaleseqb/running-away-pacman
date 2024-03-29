#include <stdio.h>
#include <stdlib.h>
#include "map.h"

int isvalid(MAP* game_map, int x, int y) {
    if (x >= game_map->lines) return 0;
    if (y >= game_map->columns) return 0;

    return 1;
}

int isempty(MAP* game_map, int x, int y) {
    return game_map->matrix[x][y] == VOID;
}

void walk_on_map(MAP* game_map, POS* coord_position, int x, int y) {
    game_map->matrix[x][y] = '@';
    game_map->matrix[coord_position->x][coord_position->y] = VOID;
    coord_position->x = x;
    coord_position->y = y;
}

void find_pos(MAP* game_map, POS* coord_position, char c) {
    for (int i_idx = 0; i_idx < game_map->lines; i_idx++) {
        for (int j_idx = 0; j_idx < game_map->columns; j_idx++) {
            if (game_map->matrix[i_idx][j_idx] == c) {
                coord_position->x = i_idx;
                coord_position->y = j_idx;
                break;
            }
        }
    }
}

void freemap(MAP* game_map) {
    for (int idx = 0; idx < game_map->lines; idx++) {
        free(game_map->matrix[idx]);
    }

    free(game_map->matrix);
}

void dynamic_allocation(MAP* game_map) {
    game_map->matrix = malloc(sizeof(char*) *game_map->lines);
    for (int idx = 0; idx < game_map->lines; idx++) {
        game_map->matrix[idx] = malloc(sizeof(char) * (game_map->columns+1));
    }
}

void read_map(MAP* game_map) {
    FILE* file;
    file = fopen("mapa.txt", "r");
    if (file == 0) {
        printf("error in reading the file");
        exit(1);
    }

    fscanf(file, "%d %d", &(game_map->lines), &(game_map->columns));
    printf("lines %d columns %d\n", game_map->lines, game_map->columns);

    dynamic_allocation(game_map);

    for (int idx = 0; idx < 5; idx++) {
        fscanf(file, "%s", game_map->matrix[idx]);
    }

    fclose(file);
}

void print_map(MAP* game_map) {
    for (int idx = 0; idx < 5; idx++) {
        printf("%s\n", game_map->matrix[idx]);
    }
}