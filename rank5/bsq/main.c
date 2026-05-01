#include "bsq.h"
#include <stdio.h>
#include <stdlib.h>

static void print_map_error(void)
{
    fputs("map error\n", stderr);
}

static void process_stream(FILE *stream)
{
    t_map map;
    int   ok;

    map.rows = 0;
    map.cols = 0;
    map.grid = NULL;
    ok = read_map_from_stream(stream, &map);
    if (!ok)
    {
        print_map_error();
        return;
    }
    if (!solve_bsq(&map))
    {
        free_map(&map);
        print_map_error();
        return;
    }
    print_map(&map, stdout);
    free_map(&map);
}

int main(int argc, char **argv)
{
    int   i;
    FILE *f;

    if (argc == 1)
    {
        process_stream(stdin);
        return 0;
    }
    i = 1;
    while (i < argc)
    {
        f = fopen(argv[i], "r");
        if (!f)
        {
            print_map_error();
        }
        else
        {
            process_stream(f);
            fclose(f);
        }
        i++;
    }
    return 0;
}
