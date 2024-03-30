#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "map.h"

MAP game_map;
POS coord_position;

void phantom_move() {
    MAP copy;
    copy_map(&copy, &game_map);

    for (int i_idx = 0; i_idx < game_map.lines; i_idx++) {
        for (int j_idx = 0; j_idx < game_map.columns; j_idx++) {
            if (copy.matrix[i_idx][j_idx] == PHANTOM) {
                if (isvalid(&game_map, i_idx, j_idx + 1) && isempty(&game_map, i_idx, j_idx + 1)) {
                    walk_on_map(&game_map, i_idx, j_idx, i_idx, j_idx + 1);
                }
            }
        }
    }
}

int finish() {
    return 0;
}

int isdirection(char direction) {
    return direction == LEFT ||
        direction == RIGHT ||
        direction == DOWN ||
        direction == UP;
}

void moove(char direction) {

    if (!isdirection(direction)) return;

    int nextX = coord_position.x;
    int nextY = coord_position.y;

    switch (direction) {
    case UP:
        nextX--;
        break;
    case DOWN:
        nextX++;
        break;
    case RIGHT:
        nextY++;
        break;
    case LEFT:
        nextY--;
        break;
    }

    if (!isvalid(&game_map, nextX, nextY)) return;
    if (!isempty(&game_map, nextX, nextY)) return;

    walk_on_map(&game_map, coord_position.x, coord_position.y, nextX, nextY);
    coord_position.x = nextX;
    coord_position.y = nextY;
    
}

int main() {

    read_map(&game_map);
    find_pos(&game_map, &coord_position, CHAR);

    do
    {
        print_map(&game_map);
        char command;
        scanf(" %c", &command);

        moove(command);
        phantom_move();

    } while (!finish() );
    

    freemap(&game_map);

}