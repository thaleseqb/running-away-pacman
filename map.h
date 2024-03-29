#define CHAR '@'
#define VOID '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'

struct map {
    char** matrix;
    int lines;
    int columns;
};

typedef struct map MAP;

struct char_position {
    int x;
    int y;
};

typedef struct char_position POS;


void freemap(MAP * game_map);
void read_map(MAP * game_map);
void dynamic_allocation(MAP * game_map);
void print_map(MAP * game_map);
void find_pos(MAP* game_map,POS* coord_position, char c);
int isvalid(MAP* game_map, int x, int y);
int isempty(MAP* game_map, int x, int y);
void walk_on_map(MAP* game_map, POS* coord_position, int x, int y);