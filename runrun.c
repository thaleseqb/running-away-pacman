#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <time.h>
#include "map.h"

MAP game_map;
POS coord_position;

int phantom_direction(int x_cur, int y_cur, int* xf, int *yf) {

    int options[4][2] = {
        {x_cur, y_cur+1},
        {x_cur+1, y_cur},
        {x_cur, y_cur-1},
        {x_cur-1, y_cur},
    };

    srand(time(0));
    for (int idx = 0; idx < 10; idx++) {
        int position = rand() % 4;
        if (access_granted(&game_map, options[position][0], options[position][1], PHANTOM)) {
            *xf = options[position][0];
            *yf = options[position][1];

            return 1;
        }
    }

    return 0;

}

void phantom_move() {
    MAP copy;
    copy_map(&copy, &game_map);

    for (int i_idx = 0; i_idx < game_map.lines; i_idx++) {
        for (int j_idx = 0; j_idx < game_map.columns; j_idx++) {
            if (copy.matrix[i_idx][j_idx] == PHANTOM) {

                int xf;
                int yf;

                int found = phantom_direction(i_idx, j_idx, &xf, &yf);

                if (found) {
                    walk_on_map(&game_map, i_idx, j_idx, xf, yf);
                }
            }
        }
    }

    freemap(&copy);
}

int finish() {
    POS position;
    int runing_away = find_pos(&game_map, &position, CHAR);
     return !runing_away;
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

    if (!access_granted(&game_map, nextX, nextY, CHAR)) return;

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