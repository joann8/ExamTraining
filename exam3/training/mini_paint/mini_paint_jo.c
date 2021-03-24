#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>

typedef struct s_global
{
	int width;
	int height; 
	char *c;
}			t_global;

typedef struct s_operation
{
	char *letter;
	float x;
	float y;
	float r;
	char *c;
}			t_op;

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_error(char *s)
{
	write(1, s, ft_strlen(s));
	return(1);
}

void	draw(char *s)
{
	write(1, s, ft_strlen(s));
}


int in_circle(float x1, float y1, t_op *op)
{
	float distance;

	distance = sqrtf((x1 - op->x) * (x1 - op->x) + (y1 - op->y) * (y1 -op->y));
	if ( distance <= op->r)
	{
		if (distance < op->r)
			return(2);
		return (1);
	}
	return (0);
}

char *read_first_line(FILE *file, t_global *g)
{
	int res;
	int i;
	char *str;

	res = fscanf(file, "%d %d %s\n", &(g->width), &(g->height), g->c);
	printf("width = %d | height = %d | letter = %c\n", g->width, g->height, g->c[0]);
	if (res != 3)
		return (NULL);
	printf("width = %d | height = %d | letter = %c\n", g->width, g->height, g->c[0]);
	if (g->width <= 0 || g->width > 300 || g->height <= 0|| g->height > 300)
		return (NULL);
	printf("width = %d | height = %d | letter = %c\n", g->width, g->height, g->c[0]);
	str = malloc(sizeof(char) * ((g->width * g->height) + g->height + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i <  g->width * g->height + g->height)
	{
		if ((i + 1) % (g->width + 1) == 0)
			str[i] = '\n';
		else
			str[i] = g->c[0];
		i++;
	}
	str[i] = '\0';
	write(1, str, ft_strlen(str));
	return(str);
}

int read_input(FILE *file, t_global *g, char *str)
{
	t_op	op;
	int		res;
	float	x;
	float	y;
	int		i;

	res = fscanf(file, "%s %f %f %f %s\n", op.letter, &(op.x), &(op.y), &(op.r), op.c);
	while (res == 5)
	{
		if ((op.letter[0] != 'C' && op.letter[0] != 'c')
			|| op.r <= 0)
			return (1);
		i = 0;
		while (i <g->width * g->height + g->height)
		{
			x = i % g->height;
			y = i % g->width;
			if (in_circle(x, y, &op) == 2)
				str[i] = op.c[0];
			if (in_circle(x, y, &op) == 1 && op.letter[0] == 'C')
				str[i] = op.c[0];
			i++;
		}
		res = fscanf(file, "%s %f %f %f %s", op.letter, &(op.x), &(op.y), &(op.r), op.c);
	}
	if (res != 0)
		return(1);
	return(0);
	//comment trouver une erreur de lecture?
}

int main(int ac, char **av)
{
	FILE		*file;
	char		*str;
	t_global	g;
	int			res;
	
	if (ac != 2)
		return(ft_error("Error: argument\n"));
	file = fopen(av[1], "r");
	if (file == NULL)//ouvre ou lit le fichier
		return(ft_error("Error: Operation file corrupted\n"));
	printf("ok1\n");
	str = read_first_line(file, &g);
	printf("ok1\n");
	if (str == NULL)
	{
		fclose(file);
		return (1);
	}
	write(1, str, ft_strlen(str));
	res = read_input(file, &g, str); 
	if (res == 0)
		write(1, str, ft_strlen(str));
	free(str);
	fclose(file);
	return(res); //tout bon
}
