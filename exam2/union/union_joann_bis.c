#include <unistd.h>

int is_in_str(char c, char *str, int i, int mod)
{
	int j;
	j = 0;
	while(str[j])
	{
		if (str[j] == c)
		{
			if (mod == 1)
			{
				if (j == i)
					return(1);
				else
					return(0);
			}
			if(mod == 2)
				return(1);
		}
		j++;
	}
	return(0);
}

int main(int ac, char **av)
{
	int i;

	if (ac == 3)
	{
		i = 0;
		while (av[1][i])
		{
			if (is_in_str(av[1][i], av[1], i, 1) == 1)
				write(1, &av[1][i], 1);
			i++;
		}
		i = 0;
		while(av[2][i])
		{
			if(is_in_str(av[2][i], av[2], i, 1) == 1)
				if(is_in_str(av[2][i], av[1], i, 2) == 0)
					write(1, &av[2][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return(1);
}
