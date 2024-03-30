#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <time.h>
#include "map.h"

MAP game_map;
POS coord_position;
int have_pill = 0;

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

    if (ischaracter(&game_map, nextX, nextY, PILL)) {
        have_pill = 1;
    }

    walk_on_map(&game_map, coord_position.x, coord_position.y, nextX, nextY);
    coord_position.x = nextX;
    coord_position.y = nextY;
    
}

void explode_pill() {

    if (!have_pill) return;

    explode_pill_(coord_position.x, coord_position.y, 0, 1, 3);
    explode_pill_(coord_position.x, coord_position.y, 0, -1, 3);
    explode_pill_(coord_position.x, coord_position.y, 1, 0, 3);
    explode_pill_(coord_position.x, coord_position.y, -1, 0, 3);

    have_pill = 0;

}

void explode_pill_(int x, int y, int sum_x, int sum_y, int qtt) {
    
    if (qtt == 0) return;

    int new_x = x + sum_x;
    int new_y = y + sum_y;
    
    if (!isvalid(&game_map, new_x, new_y)) return;
    if (iswall(&game_map, new_x, new_y)) return;

    game_map.matrix[new_x][new_y] = VOID;
    explode_pill_(new_x, new_y, sum_x, sum_y, qtt-1);
}

int main() {

    read_map(&game_map);
    find_pos(&game_map, &coord_position, CHAR);

    do
    {
        printf("Pill is available ? -> %s\n", (have_pill ? "yes :)" : "no :("));
        print_map(&game_map);
        char command;
        scanf(" %c", &command);

        moove(command);
        if (command == BOMB) explode_pill();
        phantom_move();

    } while (!finish() );
    

    freemap(&game_map);

}