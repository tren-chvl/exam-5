#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>

typedef struct s_map {
    int rows, cols;
    char empty, obstacle, full;
    char **g;
} t_map;

int  read_map(FILE *f, t_map *m);
void solve(t_map *m);
void print_map(t_map *m);

#endif
