
#include "gnl_joann.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char *ft_null(void)
{
	char * tmp;

	tmp = malloc(sizeof(char));
	tmp[0] = '\0';
	return (tmp);
}

char *ft_strcopy(char *src, char *dest, char c)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = c;
	dest[i + 1] = '\0';
	return (dest);
}


char *new_str(char *old, int count, char c)
{
	char *temp;

	temp = malloc(sizeof(char) * (count + 1));
	if (temp == NULL)
		return (NULL);
	temp = ft_strcopy(old, temp, c);
	free(old);
	return(temp);
}
	
void ft_free(char *tmp, char *new)
{
	if (tmp)
		free(tmp);
	if (new)
		free(new);
}

int get_next_line(char **line)
{
	char buf;
	int bytes;
	int count;
	char *tmp;
	char *new;
	int fd;

//	fd = open(av, O_RDONLY);
	if (line == NULL)
		return (-1);
	fd = 0;
	count = 0;
	bytes = 1; 	
	tmp = ft_null();
	new = ft_null();
	while (bytes)
	{
		bytes = read(fd, &buf, 1); 
		if (bytes == 0)	
		{
			*line = new;
			free(tmp);
			return (0);
		}
		else if (bytes == -1)
		{
			ft_free(tmp, new);
			return (-1);
		}
		else if (buf != '\n')
		{
			count++;
			tmp = new; 
			new = new_str(tmp, count, buf);
			if (new == NULL)
				return (-1);
		//	printf("tmp line = %s\n", new);
		}
		else 
		{
			*line = new;
		//	printf("final line = %s\n", *line);
			return (1);
		}
	}
	if (count == 0)
	{
		free(tmp);
		*line = new;
	}
	return (0);
}
/*
int main(int ac, char **av)
{
	char *line;

	(void)ac;
	printf("ok\n");
	get_next_line(&line, av[1]);
	printf("next line is : %s\n", line);
	return (1);
}
*/	

