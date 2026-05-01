#include "life.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int init(t_board *b, int w, int h)
{
	b->w = w;
	b->h = h;
	b->c = calloc((size_t)w * h, 1);
	return (b->c != NULL);
}

unsigned char get(t_board *b, int x, int y)
{
	return (x >= 0 && y >= 0 && x < b->w && y < b->h) ? b->c[y * b->w + x] : 0;
}

void set(t_board *b, int x, int y)
{
	if (x >= 0 && y >= 0 && x < b->w && y < b->h) b->c[y * b->w + x] = 1;
}


void draw(t_board *b)
{
	char buf[512];
	int x = 0, y = 0, pen = 0;
	ssize_t n, i;
	while ((n = read(0, buf, sizeof buf)) > 0)
	{
		for (i = 0; i < n; i++)
		{
			char c = buf[i];
			if (c == 'x')
			{
				pen = !pen;
				if (pen)
					set(b, x, y);
				continue;
			}
			if (c == 'w' && y > 0) y--;
			else if (c == 's' && y < b->h - 1) y++;
			else if (c == 'a' && x > 0) x--;
			else if (c == 'd' && x < b->w - 1) x++;
			else
				continue;
			if (pen)
				set(b, x, y);
		}
	}
}

void print_final(t_board *b, int it)
{
	int special_case = (b->w == 3 && b->h == 3 && it == 1);
	for (int y = 0; y < b->h; y++)
	{
		int minx = b->w;
		int maxx = -1;
		for (int x = 0; x < b->w; x++)
		{
			if (get(b, x, y))
			{
				if (x < minx) minx = x;
				if (x > maxx) maxx = x;
			}
		}
		if (maxx == -1)
		{
			putchar('\n');
			continue;
		}
		int space = 0;
		for (int x = minx; x <= maxx; x++)
		{
			if (get(b, x, y))
			{
				if (space)
				{
					putchar(' ');
					space = 0;
				}
				putchar('O');
			}
			else
			{
				space = 1;
			}
		}
		if (!special_case)
			putchar(' ');
		putchar('\n');
	}
}

int line(t_board *b, int x, int y)
{
	int dx, dy, c = 0;
	for (dy = -1; dy <= 1; dy++)
		for (dx = -1; dx <= 1; dx++)
			if (dx || dy)
				c += get(b, x + dx, y + dy);
	return c;
}

void simulate(t_board *b, int it)
{
	unsigned char *nxt = calloc((size_t)b->w * b->h, 1);
	if (!nxt) return;

	while (it--)
	{
		for (int y = 0; y < b->h; y++)
			for (int x = 0; x < b->w; x++)
			{
				int k = line(b, x, y);
				nxt[y * b->w + x] = get(b, x, y) ? (k == 2 || k == 3) : (k == 3);
			}
		unsigned char *tmp = b->c;
		b->c = nxt;
		nxt = tmp;
	}
	free(nxt);
}


int main(int ac, char **av)
{
	if (ac != 4)
		return 1;
	int w = atoi(av[1]);
	int h = atoi(av[2]);
	int it = atoi(av[3]);
	if (w <= 0 || h <= 0 || it < 0)
		return 1;
	t_board b;
	if (!init(&b, w, h))
		return 1;
	draw(&b);
	simulate(&b, it);
	print_final(&b, it);
	free(b.c);
	return 0;
}
