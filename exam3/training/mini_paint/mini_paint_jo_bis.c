#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<math.h>


typedef struct s_global
{
	int w;
	int h;
	char c;
}				t_g;

typedef struct s_circle
{
	char type;
	float x;
	float y;
	float r;
	char c;
}				t_c;

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
	char	*tmp;
	int		res;
	int		i;

	res = fscanf(file, "%d %d %c\n", &(g->w), &(g->h), &(g->c));
	if (res != 3)
		return (NULL);
	if (g->w < 0 | g->w > 300 | g->h < 0 | g->h > 300)
		return (NULL);
	tmp = malloc(sizeof(char) * (g->w * g->h + g->h + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (i < g->h * g->w + g->h)
	{
		if ((i + 1) % (g->w + 1) == 0)
			tmp[i] = '\n';
		else
			tmp[i] = g->c;
		i++;
	}
	tmp[i] = '\0';
	return(tmp);
}

int is_in_circle(float x, float y, t_c *c)
{
	float distance;

	distance = sqrtf(powf(x - c->x, 2) + powf(y - c->y, 2));
	if (distance <= c->r)
	{
		if (c->r - distance < 1)
			return (2);
		return (1);
	}
	return (0);
}

int read_inputs(FILE *file, t_g *g, char *s)
{
	t_c		c;
	int		res;
	int		x;
	int 	y;
	int 	i;

	res = fscanf(file, "%c %f %f %f %c\n", &(c.type), &(c.x), &(c.y), &(c.r), &(c.c));
	while (res == 5)
	{
		if ((c.type != 'C' && c.type != 'c') || c.r <= 0)
			return (1);
		i = 0;
		while (s[i])
		{
			if (s[i] != '\n')
			{
				x = i % (g->w + 1);
				y = i / (g->w + 1);
				if (is_in_circle(x, y, &c) == 2)
					s[i] = c.c;
				if (is_in_circle(x, y, &c) == 1 && c.type == 'C')
					s[i] = c.c;
			}
			i++;
		}
		res = fscanf(file, "%c %f %f %f %c\n", &(c.type), &(c.x), &(c.y), &(c.r), &(c.c));
	}
	if (res != -1)
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	t_g		g;
	FILE	*file;
	char	*s;
	int 	res;

	if (ac != 2)
		return(ft_error("Error: argument\n"));
	file = fopen(av[1], "r");
	if (file == NULL)
		return(ft_error("Error: Operation file corrupted\n"));
	s = read_first_line(file, &g);
	if (s == NULL)
		return(ft_clear(file, NULL,"Error: Operation file corrupted\n"));
	res = read_inputs(file, &g, s);
	if (res == 1)
		return(ft_clear(file, NULL,"Error: Operation file corrupted\n"));
	write(1, s, ft_strlen(s));
	ft_clear(file, s, NULL);
	return(0);
}
