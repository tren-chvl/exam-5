#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>

typedef struct s_map
{
    int   rows;
    int   cols;
    char  empty;
    char  obstacle;
    char  full;
    char **grid;
}   t_map;

/* parse.c */
int  read_map_from_stream(FILE *stream, t_map *map);
void free_map(t_map *map);

/* solve.c */
int  solve_bsq(t_map *map);
int  print_map(const t_map *map, FILE *out);

#endif
