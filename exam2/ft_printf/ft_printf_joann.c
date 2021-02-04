#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>


typedef struct s_flags
{
	char				type;
	unsigned int		width;
	unsigned int		precision;
	char				*str;
	unsigned int		str_len;
	int					dec;
	unsigned int		dec_len;
	int					dec_neg;
	unsigned int		hex;
	unsigned int		hex_len;
} 					t_flag;


unsigned int	ft_declen(int nb)
{
	int count;
	unsigned int nb2;

	if (nb < 0)
		nb2 = -nb;
	else
		nb2 = nb;
	count = 1;
	while (nb2 / 10 > 0)
	{
		nb2 = nb2 /10;
		count++;
	}
	return (count);
}

unsigned int	ft_hexlen(unsigned int nb)
{
	int count; 

	count = 1;
	while (nb / 16 > 0)
	{
		nb = nb / 16;
		count++;
	}
	return (count);
}
	

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_search_char(char c, char *set)
{
	int j;

	j = 0;
	while (set[j])
	{
		if (c == set[j])
			return(j);
		j++;
	}
	return (-1);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

unsigned int ft_atoi(const char *str, int *pos)
{
	int i;
	unsigned int res;

	i = *pos;
	res = 0;
	while (is_digit(str[i]) == 1)
	{
		res = res * 10 + str[i] - 48;
	//	printf("str[%d] = %c\n", i, str[i]);
	//	printf("tour %d : res = %d\n", i, res);
		i++;
	}
	*pos = i;
	return (res);
}

int manage_type(va_list args, const char *input, t_flag *flag, char *set2, int pos)
{
	int i;
	char *null;

	i = 0;
	null = "(null)";
	while ((i = ft_search_char(input[pos], set2)) < 0)
	{
		pos++;
	}
	//	return (-1);
	flag->type = set2[i];
	i = pos;
	if (flag->type == 's')
	{
		flag->str = (char *)va_arg(args, char*);
		if (flag->str == NULL)
			flag->str = null;
		flag->str_len= ft_strlen(flag->str);
		flag->width = ft_strlen(flag->str);
		flag->precision = ft_strlen(flag->str);
	}
	if (flag->type == 'd')
	{
		flag->dec = (int)va_arg(args, int);
		if (flag->dec < 0)
			flag->dec_neg = 1;
		else
			flag->dec_neg = 0;
		flag->dec_len= ft_declen(flag->dec);
		flag->width = ft_declen(flag->dec) + flag->dec_neg;
		flag->precision = ft_declen(flag->dec);
	}
	if (flag->type == 'x')
	{
		flag->hex = (unsigned int)va_arg(args, unsigned int);
		flag->hex_len= ft_hexlen(flag->hex);
		flag->width = ft_hexlen(flag->hex);
		flag->precision = ft_hexlen(flag->hex);
;
	}
//	printf("type = %c\n", flag->type);
//	printf("flag->width = %u\n", flag->width);
//	printf("flag->precision = %u\n", flag->precision);
//	printf("\n***EXIT MANAGE TYPE***\n");
	return (1);
} 	

void	print_char(char c, unsigned int nb)
{
	unsigned int i;

	i = 0;
	while (i < nb)
	{
		//printf("chqr c = %c\n", c);
		//printf("nb = %u\n", nb);
		write(1, &c, 1);
		i++;
	}
}
	
void	print_str(t_flag *flag, int *print)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;

	if (flag->precision > flag->str_len)
		flag->precision = flag->str_len;
	if (flag->width < flag->precision || flag->precision == 0)
		flag->width = flag->precision;
	//printf("flag prec = %d | flag width = %d\n", flag->precision, flag->widthig;
	i = flag->width - flag->precision;
	print_char(' ', i);
	*print += i;
	while (j < flag->precision)
	{
		write(1, &(flag->str[j]), 1);
		j++;
		*print += 1;
	}
}

void	ft_putnbr(unsigned int res1, unsigned int len, char *base, int b)
{
	unsigned int k;
	int div;
	int div2;
	char c;
	unsigned int res;

		res = res1;
	k = 0;
	while (k < len)
	{
	//	printf("res = %u\n", res);
		div = len - 1 - k;
	//	printf("div = %d\n", div);
		if (div > 0)
		{
			div2 = 1;
			while (div > 0)
			{
				div2 *= b;
				div--;
			}
		c = base[res / div2] ;
		res = res - (res / div2) * div2;
		}
		else
		{
			c = base[res];
		}
		write(1, &c, 1);
		k++;
	}
}

void	print_dec(t_flag *flag, int *print)
{
	unsigned int i;
	unsigned int j;
	unsigned int res;
	int warn ;

	i = 0;
	j = 0;
	warn = 0;
	if (flag->dec < 0)
		res = -flag->dec;
	else
		res = flag->dec;
	if (flag->precision == 0 && flag->dec == 0)
		warn = 1;
	if (flag->precision < flag->dec_len)
		flag->precision = flag->dec_len;
	if (flag->width < flag->precision + flag->dec_neg)
		flag->width = flag->precision + flag->dec_neg;
	//printf("flag prec = %d | flag width = %d\n", flag->precision, flag->width);
	i = flag->width - flag->precision - flag->dec_neg;
	print_char(' ', i);
	*print += i;
	if (flag->dec_neg == 1)
	{
		write(1, "-", 1);
		*print += 1;
	}
	j = flag->precision - flag->dec_len;
	print_char('0', j);
	*print += j;
	if (warn == 0)
	{	
		ft_putnbr(res, flag->dec_len, "0123456789", 10);
		*print += flag->dec_len;
	}
}

void	print_hex(t_flag *flag, int *print)
{
	unsigned int i;
	unsigned int j;
	unsigned int res;
	int warn;

	i = 0;
	j = 0;
	warn = 0;
	res = flag->hex;
	if (flag->precision == 0 && flag->hex == 0)
		warn = 1;
	if (flag->precision < flag->hex_len)
		flag->precision = flag->hex_len;
	if (flag->width < flag->precision )
		flag->width = flag->precision ;
//	printf("flag prec = %d | flag width = %d\n", flag->precision, flag->width);	
	i = flag->width - flag->precision ;
//	printf("i = %u\n", i);
	print_char(' ', i);
	*print += i;
	if (flag->dec_neg == 1)
	{
		write(1, "-", 1);
		*print += 1;
	}
	j = flag->precision - flag->hex_len;
//	printf("j = %u\n", j);
	print_char('0', j);
	*print += j;
	if (warn == 0)
	{
		ft_putnbr(res, flag->hex_len, "0123456789abcdef", 16);
		*print += flag->hex_len;
	}
}

	
int analyse_arg(const char *str, int *pos, char *set2, t_flag *flag)
{
	int				i;
	unsigned int temp;

	i = *pos;
	//printf("char str[%d] = %c\n", i, str[i]);
	if (is_digit(str[i]) == 1)
	{
		temp = ft_atoi(str, &i);
//		printf("width atoi = %d\n", temp);
		flag->width = temp;
	}
	if (str[i] == '.')
	{
		i++;	
		if (is_digit(str[i]) == 1)
		{
			temp = ft_atoi(str, &i);
			flag->precision = temp;
		}
		else if (ft_search_char(str[i], set2) >= 0)
		{
			flag->precision = 0;
		}
		else
			return (-1);
	}
//	printf("str[%d] = %c", i, str[i]);
	if (str[i] != flag->type)
		return (-1);
	*pos = i;
//	printf("type = %c\n", flag->type);
//	printf("flag->width = %u\n", flag->width);
//	printf("flag->precision = %u\n", flag->precision);
	
	return (1);
}

int ft_printf(const char *input, ...)
{
	va_list	args;
	int		res;
	int		i;
	int		pos;
	char 	*set1;
	char 	*set2;
	t_flag	flag;


	va_start(args, input);
	set1 = "%";
	set2= "sdx";
	res = 0;
	i = 0;
	while (input[i])
	{
		if (ft_search_char(input[i], set1) == -1)
		{
			write(1, &input[i], 1);
			i++;
			res++;
		}
		else
		{
			pos = i + 1;
			if (manage_type(args, input, &flag, set2, i + 1) == -1) // ne marche pas si *
				return (-1);
			if (analyse_arg(input, &pos, set2, &flag) == -1)
				return (-1);
			if (flag.type == 's')
				print_str(&flag, &res);
			if(flag.type == 'd')
				print_dec(&flag, &res);
			if(flag.type == 'x')
				print_hex(&flag, &res);
			i = pos + 1;
			//printf("input[%d] = %c\n",i, input[i] );
		}
	}
	va_end(args);
	return(res);
}

int main (void)
{
	char *str = malloc(10);
	
	str = NULL;
	printf("%d\n", printf("j'espere que ca marche? %15s! Une autre? %.x!\n", "yes", 0));
	printf("%d\n", ft_printf("j'espere que ca marche? %15s! une autre? %.x!\n", "yes", 0));
	while(1);
}
	
