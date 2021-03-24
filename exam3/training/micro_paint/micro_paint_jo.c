#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<unistd.h>


typedef struct s_rect
{
	int width;
	int height;
	char c;
}				t_rect;

typedef struct s_draw
{
	char type;
	float x;
	float y;
	float width;
	float height;
	char c;
}				t_draw;

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while(s[i])
		i++;
	return(i);
}

int ft_error(char *s)
{
	write(1, s, ft_strlen(s));
	return(1);
}

char *read_first_line(t_rect *r, FILE *file)
{
	char *tmp;
	int res;
	int i;

	res = fscanf(file, "%d %d %c\n", &(r->width), &(r->height), &(r->c));
	if (res != 3)
		return (NULL);
	if (r->width <= 0 || r->width > 300 || r->height <= 0 || r->height > 300)
		return (NULL);
	tmp = malloc(sizeof(char) * (r->width * r->height + r->height + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (i < r->width * r->height + r->height)
	{
		if ( (i + 1) % (r->width + 1) == 0)
			tmp[i] = '\n';
		else
			tmp[i] = r->c;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int is_in_rect(float x, float y, t_draw *d)
{
	if( x < d->x || x > d->x + d->width || y < d->y  || y > d->y + d->height)
		  return (0);	
	//if((d->x <= x && x <= d->x + d->width) && (d->y <= y && y <= d->y + d->height)) 
//	{
	//	printf("d->x %f <= x %f <= d->x + d->width %f\n", d->x, x, d->x + d->width); 
	//	printf("d->y %f <= y %f <= d->y + d->height %f\n", d->y, y, d->y + d->height); 
	if ((x - d->x < 1.0 || d->x + d->width - x < 1.0) 
			|| (y - d->y < 1.0 || d->y + d->height - y < 1.0)) // attention || partout
		return (2);

	return (1);
	}
/*	
	{
			//printf("--2\n");
			return (2);
		}
	//	printf("--1\n");
		return (1);
	}
//	printf("--0\n");
	return (0);	
}*/

int read_inputs(t_rect *r, FILE *file, char *str) 
{
	t_draw	d;
	int		res;
	float	x;
	float	y;
	int		i;

	res = fscanf(file, "%c %f %f %f %f %c\n", &(d.type), &(d.x), &(d.y), &(d.width), &(d.height), &(d.c));
	while (res == 6)
	{
		if (d.width <= 0 || d.height <= 0 || (d.type != 'R' && d.type != 'r'))
			return (1);
		i = 0;
		while (str[i])
		{
			if (str[i] != '\n')
			{
				x = i % (r->width + 1) ; // A RETENIR
				y = i / (r->width + 1); // A RETENIR
//				printf("i = %d | x = %f | y = %f\n", i, x, y);
				if (is_in_rect((float)x, (float)y, &d) == 2)
					str[i] = d.c;
				if (is_in_rect((float)x, (float)y, &d) == 1 && d.type == 'R')
					str[i] = d.c;
			}
			i++;
		}
		res = fscanf(file, "%c %f %f %f %f %c\n", &(d.type), &(d.x), &(d.y), &(d.width), &(d.height), &(d.c));
	}
	if (res != -1)
		return (1);
	return(0);
}

int ft_clear(FILE *file, char *str, char *error)
{
	if (file)
		fclose(file);
	if (str)
		free(str);
	if(error)
		ft_error(error);
	return(1);
}


int main(int ac, char **av)
{
	FILE	*file;
	t_rect	r;	
	char	*str;
	int		res;

	if (ac != 2)
		return(ft_error("Error: argument\n"));
	file = fopen(av[1], "r");
	if (file == NULL)
		return(ft_error("Error: Operation file corrupted\n"));
	str = read_first_line(&r, file);
	if (str == NULL)
		return(ft_clear(file, NULL, "Error: Operation file corrupted\n"));
	res = read_inputs(&r, file, str);
	if (res == 1)
		return(ft_clear(file, str, "Error: Operation file corrupted\n"));
	write(1, str, ft_strlen(str));
	ft_clear(file, str, NULL);
	return (0);
}
