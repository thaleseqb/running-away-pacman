#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "map.h"

MAP game_map;
POS coord_position;

int finish() {
    return 0;
}

void moove(char direction) {
    int x;
    int y;

    game_map.matrix[coord_position.x][coord_position.y] = '.';


    switch (direction) {
    case 'w':
        game_map.matrix[coord_position.x-1][coord_position.y] = '@';
        coord_position.x--;
        break;
    case 's':
        game_map.matrix[coord_position.x+1][coord_position.y] = '@';
        coord_position.x++;
        break;
    case 'd':
        game_map.matrix[coord_position.x][coord_position.y+1] = '@';
        coord_position.y++;
        break;
    case 'a':
        game_map.matrix[coord_position.x][coord_position.y-1] = '@';
        coord_position.y--;
        break;
    }
    
}

int main() {

    read_map(&game_map);
    find_pos(&game_map, &coord_position, '@');

    do
    {
        print_map(&game_map);
        char command;
        scanf(" %c", &command);

        moove(command);

    } while (!finish() );
    

    freemap(&game_map);

}