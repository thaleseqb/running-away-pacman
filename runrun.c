#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "map.h"

MAP game_map;
POS coord_position;

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

    walk_on_map(&game_map, &coord_position, nextX, nextY);
    
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

    } while (!finish() );
    

    freemap(&game_map);

}