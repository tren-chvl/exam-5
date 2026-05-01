#define _GNU_SOURCE
#include "bsq.h"
#include <stdlib.h>
#include <sys/types.h>

static size_t my_strlen(const char *s)
{
	size_t len = 0;
	while (s[len])
		len++;
	return len;
}
static int is_printable_nonspace(char c)
{
	return (c >= 33 && c <= 126);
}

static int parse_header_line(const char *line, int *rows, char *empty, char *obstacle, char *full)
{
	size_t i = 0;
	long value = 0;
	int has_digit = 0;

	while (line[i] == ' ')
		i++;

	while (line[i] >= '0' && line[i] <= '9')
	{
		has_digit = 1;
		value = value * 10 + (line[i] - '0');
		if (value > 2147483647)
			return 0;
		i++;
	}
	if (!has_digit || value <= 0)
		return 0;
	*rows = (int)value;
	if (line[i] != ' ')
		return 0;
	while (line[i] == ' ')
		i++;
	if (!is_printable_nonspace(line[i]))
		return 0;
	*empty = line[i++];
	if (line[i] != ' ')
		return 0;
	while (line[i] == ' ')
		i++;
	if (!is_printable_nonspace(line[i]))
		return 0;
	*obstacle = line[i++];
	if (line[i] != ' ')
		return 0;
	while (line[i] == ' ')
		i++;
	if (!is_printable_nonspace(line[i]))
		return 0;
	*full = line[i++];
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != ' ')
			return 0;
		i++;
	}
	if (*empty == *obstacle || *empty == *full || *obstacle == *full)
		return 0;
	return 1;
}

int validate_line_chars(const char *line, int len, char empty, char obstacle)
{
	int j = 0;

	while (j < len)
	{
		if (line[j] != empty && line[j] != obstacle)
			return 0;
		j++;
	}
	return 1;
}

void free_map(t_map *map)
{
	int i;

	if (!map || !map->grid)
		return;
	i = 0;
	while (i < map->rows)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
	map->rows = 0;
	map->cols = 0;
}

int read_map_from_stream(FILE *stream, t_map *map)
{
	char   *line = NULL;
	size_t  cap = 0;
	ssize_t r;
	int     i;
	int     rows;
	char    empty;
	char    obstacle;
	char    full;
	int     cols = -1;
	char  **grid = NULL;

	if (!map)
		return 0;
	r = getline(&line, &cap, stream);
	if (r == -1)
	{
		free(line);
		return 0;
	}
	if (!parse_header_line(line, &rows, &empty, &obstacle, &full))
	{
		free(line);
		return 0;
	}
	if (rows <= 0)
	{
		free(line);
		return 0;
	}
	grid = (char **)malloc(sizeof(char *) * rows);
	if (!grid)
	{
		free(line);
		return 0;
	}
	i = 0;
	while (i < rows)
	{
		r = getline(&line, &cap, stream);
		if (r == -1)
		{
			free(line);
			i--;
			while (i >= 0)
			{
				free(grid[i]);
				i--;
			}
			free(grid);
			return 0;
		}
		if (r > 0 && line[r - 1] == '\n')
			r--;
		if (r <= 0)
		{
			free(line);
			i--;
			while (i >= 0)
			{
				free(grid[i]);
				i--;
			}
			free(grid);
			return 0;
		}
		if (cols == -1)
			cols = (int)r;
		else if (cols != (int)r)
		{
			free(line);
			i--;
			while (i >= 0)
			{
				free(grid[i]);
				i--;
			}
			free(grid);
			return 0;
		}
		if (!validate_line_chars(line, (int)r, empty, obstacle))
		{
			free(line);
			i--;
			while (i >= 0)
			{
				free(grid[i]);
				i--;
			}
			free(grid);
			return 0;
		}
		grid[i] = (char *)malloc((size_t)cols + 1);
		if (!grid[i])
		{
			free(line);
			i--;
			while (i >= 0)
			{
				free(grid[i]);
				i--;
			}
			free(grid);
			return 0;
		}
		{
			int j = 0;
			while (j < cols)
			{
				grid[i][j] = line[j];
				j++;
			}
			grid[i][cols] = '\0';
		}
		i++;
	}
	r = getline(&line, &cap, stream);
	if (r != -1)
	{
		free(line);
		i = 0;
		while (i < rows)
		{
			free(grid[i]);
			i++;
		}
		free(grid);
		return 0;
	}
	free(line);
	map->rows = rows;
	map->cols = cols;
	map->empty = empty;
	map->obstacle = obstacle;
	map->full = full;
	map->grid = grid;
	return 1;
}

int min3(int a, int b, int c)
{
	int m = a;
	if (b < m)
		m = b;
	if (c < m)
		m = c;
	return m;
}

int solve_bsq(t_map *map)
{
	int *prev;
	int *cur;
	int  i;
	int  j;
	int  max_size = 0;
	int  max_i = 0;
	int  max_j = 0;

	if (!map || !map->grid || map->rows <= 0 || map->cols <= 0)
		return 0;
	prev = (int *)calloc((size_t)map->cols, sizeof(int));
	cur = (int *)calloc((size_t)map->cols, sizeof(int));
	if (!prev || !cur)
	{
		free(prev);
		free(cur);
		return 0;
	}
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->grid[i][j] == map->obstacle)
				cur[j] = 0;
			else
			{
				if (i == 0 || j == 0)
					cur[j] = 1;
				else
					cur[j] = 1 + min3(prev[j], cur[j - 1], prev[j - 1]);
				if (cur[j] > max_size)
				{
					max_size = cur[j];
					max_i = i;
					max_j = j;
				}
			}
			j++;
		}
		{
			int *tmp = prev;
			prev = cur;
			cur = tmp;
		}
		i++;
	}
	free(prev);
	free(cur);
	if (max_size > 0)
	{
		int r = max_i;
		while (r > max_i - max_size)
		{
			int c = max_j;
			while (c > max_j - max_size)
			{
				map->grid[r][c] = map->full;
				c--;
			}
			r--;
		}
	}
	return 1;
}

int print_map(const t_map *map, FILE *out)
{
	int i;

	if (!map || !map->grid || !out)
		return 0;
	i = 0;
	while (i < map->rows)
	{
		fputs(map->grid[i], out);
		fprintf(out, "\n");
		i++;
	}
	return 1;
}
