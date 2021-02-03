#include <unistd.h>

int	is_in_str(char c, char *str, int mod, int pos)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (mod == 1)
			{
				if (i == pos)
					return (1);
				else
					return (0);
			}
			else	
				return (1);
		}
		i++;
	}
	return (0);
}


int main(int ac, char **av)
{
	int i;

	if (ac == 3)
	{
	i = 0;
	while (av[1][i])
	{
		if (is_in_str(av[1][i], av[1], 1, i) == 1)
			if (is_in_str(av[1][i], av[2], 2, i) == 1)
				write(1, &av[1][i], 1);
		i++;
	}
	}
	write(1, "\n", 1);
	return (1);
}
	


