#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>

typedef struct s_global
{
	int width;
	int height; 
	char c;
}			t_global;

typedef struct s_operation
{
	char letter;
	float x;
	float y;
	float r;
	char c;
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

	distance = sqrtf((x1 - op->x) * (x1 - op->x) + (y1 - op->y) * (y1 - op->y));
	if ( distance <= op->r)
	{
		if (op->r - distance < 1.0) // pour la bordure
		{
		//	printf("--2--\n");
			return(2);
		}
	//	printf("--1--\n");
		return (1);
	}
//	printf("--0--\n");
	return (0);
}

char *read_first_line(FILE *file, t_global *g)
{
	int res;
	int i;
	char *str;

	res = fscanf(file, "%d %d %c\n", &(g->width), &(g->height), &(g->c));
	if (res != 3)
		return (NULL);
	if (g->width <= 0 || g->width > 300 || g->height <= 0|| g->height > 300)
		return (NULL);
	str = malloc(sizeof(char) * ((g->width * g->height) + g->height + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i <  g->width * g->height + g->height)
	{
		if ((i + 1) % (g->width + 1) == 0)
			str[i] = '\n';
		else
			str[i] = g->c;
		i++;
	}
	str[i] = '\0';
	return(str);
}

int read_input(FILE *file, t_global *g, char *str)
{
	t_op	op;
	int		res;
	float	x;
	float	y;
	int		i;

	res = fscanf(file, "%c %f %f %f %c\n", &(op.letter), &(op.x), &(op.y), &(op.r), &(op.c)); //backslash n important
//	printf("letter = %c | x = %f | y = %f | r = %f | c = %c\n", op.letter, op.x, op.y, op.r, op.c); 
	while (res == 5)
	{
		if ((op.letter != 'C' && op.letter != 'c') || op.r <= 0)
			return (1);
		i = 0;
		while (i <g->width * g->height + g->height)
		{
			if (str[i] != '\n')
			{
				x = i % (g->width + 1); // a retenir
				y = i / g->width; //  a retenir
		//		printf("i = %d | x = %f | y = %f\n",i, x , y);
				if (in_circle(x, y, &op) == 2)
					str[i] = op.c;
				if (in_circle(x, y, &op) == 1 && op.letter == 'C')
					str[i] = op.c;
			}
			i++;
		}
		res = fscanf(file, "%c %f %f %f %c\n", &(op.letter), &(op.x), &(op.y), &(op.r), &(op.c));
	}
	if (res != -1) // - 1 quand fini
		return(1);
	return(0);
}

int ft_clear(FILE *file, char *str, char *error)
{
	if (file)
		fclose(file);
	if(str)
		free(str);
	if(error)
		ft_error(error);
	return(1);
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
	str = read_first_line(file, &g);
	if (str == NULL)
		return(ft_clear(file, NULL, "Error: Operation file corrupted\n")); // quand pbm str
	res = read_input(file, &g, str); 
	if (res == 1)
		return(ft_clear(file, str, "Error: Operation file corrupted\n")); // quand pbm input
	write(1, str, ft_strlen(str));
	ft_clear(file, str, NULL);
	return(0); //tout bon
}
