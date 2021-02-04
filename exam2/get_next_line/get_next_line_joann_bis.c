#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>


int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}

char *str_empty(void)
{
	char *temp;

	temp = malloc(sizeof(char));
	if (temp == NULL)
		return(NULL);
	temp[0] = '\0';
	return (temp);
}

char *new_str(char *old, char c)
{
	char *temp;
	int i;

	temp = malloc(sizeof(char) * (ft_strlen(old) + 2));
	if (temp == NULL)
	{
		free(old);
		return (NULL);
	}
	i = 0;
	while (old[i])
	{
		temp[i] = old[i];
		i++;
	}
	temp[i] = c;
	temp[i + 1] = '\0';
	free(old);
	return(temp);
}


int get_next_line(char **line)
{
	int byte;
	char buf;
	char *new;
	char *old;
	char *leak;

	leak = str_empty();
			
	if (line == NULL)
		return (-1);
	byte = 1;
	new = str_empty();
	if (new == NULL)
		return (-1);
	while (byte)
	{
		byte = read(0, &buf, 1);
		if (byte == -1)
		{
			if (old)
				free(old);
			if (new)
				free(new);	
			*line = str_empty();
			return(-1);
		}
		else if (byte == 1)
		{
			if (buf != '\n')
			{
				old = new;
				new = new_str(old, buf);
				if (new == NULL)
					return(-1);
			}
			else
			{
				*line = new;
				return (1);
			}
		}
	}
	*line = new;
	return(0);
}

