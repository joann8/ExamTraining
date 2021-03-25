#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>

typedef struct s_global
{
	int w;
	int h;
	char c;
}				t_g;

typedef struct s_rect
{
	char type;
	float x;
	float y;
	float w;
	float h;
	char c;
}				t_r;

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return(i);
}

int ft_error(char *s)
{
	write(1, s, ft_strlen(s));
	return (1);
}

int ft_clear(FILE *file, char *s, char *error)
{
	if (file)
		fclose(file);
	if (s)
		free(s);
	if (error)
		ft_error(error);
	return (1);
}

char *read_first_line(FILE *file, t_g *g)
{
	int res;
	char *tmp;
	int i;

	res = fscanf(file, "%d %d %c\n", &(g->w), &(g->h), &(g->c));
	if (res != 3)
		return (NULL);
	if (g->w <= 0 || g->w > 300 || g->h <=0 || g->h > 300)
		return (NULL);
	tmp = malloc(sizeof(char) * (g->w * g->h + g->h + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (i < g->w * g->h + g->h)
	{
		if (((i + 1) % (g->w + 1)) == 0)
			tmp[i] = '\n';
		else
			tmp[i] = g->c;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int is_in_rect(float x, float y, t_r *r)
{
	if (r->x <= x && x <= r->x + r->w && r->y <= y && y <= r->y + r->h)
	{
		if (x - r->x < 1 || r->x + r->w -x < 1 || y - r->y < 1 || r->y + r->h - y < 1)
			return (2);
		return (1);
	}
	return (0);
}

int	read_inputs(FILE *file, char *s, t_g *g)
{
	t_r r;
	int res;
	int i;
	int x;
	int y;

	res = fscanf(file, "%c %f %f %f %f %c\n", &(r.type), &(r.x), &(r.y), &(r.w), &(r.h), &(r.c));
	while (res == 6)
	{
		if ((r.type != 'r' && r.type != 'R') || r.w <= 0 || r.h <= 0)
			return (1);
		i = 0;
		while (s[i])
		{
			if (s[i] != '\n')
			{	
				x = i % (g->w + 1);
				y = i / (g->w  + 1);
				if (is_in_rect(x, y, &r) == 2)
					s[i] = r.c;
				if (is_in_rect(x, y, &r) == 1 && r.type == 'R')
					s[i] = r.c;
			}
			i++;
		}
		res = fscanf(file, "%c %f %f %f %f %c\n", &(r.type), &(r.x), &(r.y), &(r.w), &(r.h), &(r.c));
	}
	if (res != -1)
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	int		res;
	t_g		g;
	FILE	*file;
	char 	*s;

	if (ac != 2)
		return(ft_error("Error: argument\n"));
	file = fopen(av[1], "r");
	if (file == NULL)
		return(ft_error("Error: Operation file corrupted\n"));
	s = read_first_line(file, &g);
	if (s == NULL)
		return(ft_clear(file, NULL, "Error: Operation file corrupted\n"));
	res = read_inputs(file, s, &g);
	if (res == 1)
		return(ft_clear(file, s, "Error: Operation file corrupted\n"));
	write(1, s, ft_strlen(s));
	ft_clear(file, s , NULL);
	return(0);
}


