#include "bsq.h"
#include <stdlib.h>

int main(int ac, char **av)
{
    if (ac == 1) {
        t_map m;
        if (!read_map(stdin,&m)) return fprintf(stderr,"map error\n"),0;
        solve(&m); print_map(&m);
        return 0;
    }
    for (int i=1;i<ac;i++){
        FILE *f=fopen(av[i],"r");
        if (!f){ fprintf(stderr,"map error\n"); continue; }
        t_map m;
        if (!read_map(f,&m)) fprintf(stderr,"map error\n");
        else { solve(&m); print_map(&m); }
        fclose(f);
        if (i<ac-1) printf("\n");
    }
}
