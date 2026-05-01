#ifndef LIFE_H
# define LIFE_H

typedef struct s_board {
    int w, h;
    unsigned char *c;
} t_board;

int  init(t_board *b, int w, int h);
void draw(t_board *b);
void simulate(t_board *b, int it);
void print_trimmed(t_board *b);

#endif
