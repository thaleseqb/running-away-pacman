#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'
#define BOMB 'b'

int finish();
void moove(char direction);
int isdirection(char direction);
void phantom_move();
void explode_pill_(int x, int y, int sum_x, int sum_y, int qtt);
void explode_pill();