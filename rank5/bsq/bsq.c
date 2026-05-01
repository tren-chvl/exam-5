#define _GNU_SOURCE
#include "bsq.h"
#include <stdlib.h>

static int parse_header(char *l, t_map *m)
{
    int i = 0, d = 0;
    long v = 0;

    while (l[i] == ' ') i++;
    while (l[i] >= '0' && l[i] <= '9') { v = v*10 + (l[i]-'0'); i++; d = 1; }
    if (!d || v <= 0) return 0;
    m->rows = v;

    if (l[i] != ' ') return 0;
    while (l[i] == ' ') i++;
    if (l[i] < 33 || l[i] > 126) return 0;
    m->empty = l[i++];

    if (l[i] != ' ') return 0;
    while (l[i] == ' ') i++;
    if (l[i] < 33 || l[i] > 126) return 0;
    m->obstacle = l[i++];

    if (l[i] != ' ') return 0;
    while (l[i] == ' ') i++;
    if (l[i] < 33 || l[i] > 126) return 0;
    m->full = l[i++];

    while (l[i] && l[i] != '\n') if (l[i++] != ' ') return 0;

    if (m->empty == m->obstacle || m->empty == m->full || m->obstacle == m->full)
        return 0;

    return 1;
}

int read_map(FILE *f, t_map *m)
{
    char *l = NULL; size_t c = 0; ssize_t r;
    int i, j;

    if ((r = getline(&l, &c, f)) == -1) return free(l), 0;
    if (!parse_header(l, m)) return free(l), 0;

    m->g = malloc(sizeof(char*) * m->rows);
    for (i = 0; i < m->rows; i++)
    {
        if ((r = getline(&l, &c, f)) == -1) return free(l), 0;
        if (r > 0 && l[r-1] == '\n') r--;
        if (r <= 0) return free(l), 0;

        if (i == 0) m->cols = r;
        else if (m->cols != r) return free(l), 0;

        m->g[i] = malloc(r+1);
        for (j = 0; j < r; j++)
            if (l[j] != m->empty && l[j] != m->obstacle)
                return free(l), 0;
            else m->g[i][j] = l[j];
        m->g[i][r] = 0;
    }
    free(l);
    return 1;
}

void solve(t_map *m)
{
    int *p = calloc(m->cols,4), *c = calloc(m->cols,4);
    int i,j,ms=0,mi=0,mj=0;

    for (i=0;i<m->rows;i++){
        for (j=0;j<m->cols;j++){
            if (m->g[i][j]==m->obstacle) c[j]=0;
            else {
                if (!i || !j) c[j]=1;
                else {
                    int a=p[j], b=c[j-1], d=p[j-1];
                    int mn = a<b?a:b; if (d<mn) mn=d;
                    c[j]=mn+1;
                }
                if (c[j]>ms){ ms=c[j]; mi=i; mj=j; }
            }
        }
        int *t=p; p=c; c=t;
    }
    free(p); free(c);

    for (i=mi; i>mi-ms; i--)
        for (j=mj; j>mj-ms; j--)
            m->g[i][j] = m->full;
}

void print_map(t_map *m)
{
    for (int i=0;i<m->rows;i++)
        printf("%s\n", m->g[i]);
}
