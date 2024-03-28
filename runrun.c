#include <stdio.h>
#include <stdlib.h>

char** map;
int lines;
int columns;

int main() {

    FILE* file;
    file = fopen("mapa.txt", "r");
    if (file == 0) {
        printf("error in reading the file");
        exit(1);
    }

    fscanf(file, "%d %d", &lines, &columns);
    printf("lines %d columns %d\n", lines, columns);

    map = malloc(sizeof(char*) * lines);
    for (int idx = 0; idx < lines; idx++) {
        map[idx] = malloc(sizeof(char) * (columns+1));
    }

    for (int idx = 0; idx < 5; idx++) {
        fscanf(file, "%s", map[idx]);
    }

    for (int idx = 0; idx < 5; idx++) {
        printf("%s\n", map[idx]);
    }
    
    fclose(file);

    for (int idx = 0; idx < lines; idx++) {
        free(map[idx]);
    }

    free(map);


}