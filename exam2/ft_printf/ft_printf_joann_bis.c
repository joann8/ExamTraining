/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_joann_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:57:07 by jacher            #+#    #+#             */
/*   Updated: 2021/02/04 17:15:47 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>


typedef struct s_data
{
	char			type;
	unsigned int	 precision;
	int				precision_bol;
	unsigned int	 width;
	char			 *str;
	unsigned int	 str_len;
	int				dec;
	unsigned int	 dec_len;
	int 			dec_neg;
	unsigned int 	hex;
	unsigned int 	hex_len;
}              t_data;

void data_init(t_data *d)
{
	d->precision = 0;
	d->precision_bol = 0;
	d->width = 0;
	d->str_len = 0;
	d->dec_len = 0;
	d->dec_neg = 0;
	d->hex = 0;
	d->hex_len = 0;
}

unsigned int ft_strlen(const char *str)
{
	unsigned int i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}

unsigned int ft_hexlen(unsigned int hex)
{
	unsigned int count;

	count = 1;
	while (hex / 16 > 0)
	{
		count++;
		hex = hex / 16;
	}
	return(count);
}

unsigned int ft_declen(int dec)
{
	unsigned int nb;
	unsigned int count;

	if (dec < 0)
		nb = -dec;
	else
		nb = dec;
	count = 1;
	while (nb / 10 > 0)
	{
		count++;
		nb = nb / 10;
	}
	return(count);
}

void ft_putchar(char c,  int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		write(1, &c, 1);
		i++;
	}
}

void ft_putnbr(unsigned int nb, unsigned int len, unsigned int b, char *base)
{
	unsigned int div;
	unsigned int pow;
	char c;
	unsigned int k;

	k = 0;
	pow = len - 1;
	div = 1;
	while (k < pow)
	{
		div *=b;
		k++;
	}
	while (nb > b)
	{
		c = base[nb / div]; 
		write(1, &c, 1);
		nb = nb % div;
		div = div / b;
	}
	c = base[nb]; 
	write(1, &c, 1);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return(1);
	return(0);
}

unsigned int ft_atoi(const char *str ,unsigned int *pos)
{
	unsigned int i;
	unsigned int atoi;

	i = *pos;
	atoi = 0;
	while(is_digit(str[i]) == 1)
	{
		atoi = atoi * 10 + str[i] - 48;
		i++;
	}
	*pos = i;
	return(atoi);
}

int parse(const char *str, va_list args, t_data *d,  unsigned int *pos)
{
	unsigned int i;
	char *null;

	null= "(null)";
	if(d->type == 's')
	{
		d->str = va_arg(args, char *);
		if (d->str == NULL)	
			d->str = null;
		d->str_len = ft_strlen(d->str);
		d->width = ft_strlen(d->str);
		d->precision = ft_strlen(d->str);
	}
	if(d->type == 'd')
	{
		d->dec = va_arg(args, int);
		if (d->dec < 0)
			d->dec_neg = 1;
		d->dec_len = ft_declen(d->dec);
		d->width = ft_declen(d->dec) + d->dec_neg;
		d->precision = ft_declen(d->dec);
	}
	if(d->type == 'x')
	{
		d->hex = va_arg(args, unsigned int);
		d->hex_len = ft_hexlen(d->hex);
		d->width = ft_hexlen(d->hex);
		d->precision = ft_hexlen(d->hex);
	}

	
	i = *pos;
	if (is_digit(str[i]) == 1)
		d->width = ft_atoi(str, &i);
	if (str[i] == '.')
	{
		d->precision_bol = 1;
		i++;
		if (is_digit(str[i]) == 1)
			d->precision = ft_atoi(str, &i);
		else if (str[i] == d->type)
			d->precision = 0;
	}
	if (str[i] != d->type)
		return (-1);
	*pos = i;
	return (1);
}

void print_str(t_data *d, int *res)
{
	unsigned int i;
	int temp;

	if (d->precision > d->str_len)
		d->precision = d->str_len;
	if (d->width < d->precision || d->precision == 0)
		d->width = d->precision;	
//if (d->width < d->precision)
	//	d->width = d->precision;
//	printf("width = %u, precision = %u\n", d->width, d->precision);
	temp = d->width - d->precision;
//	printf("temp = %d\n", temp);
	ft_putchar(' ', temp);
	*res += temp;
	i = 0;
	while (i < d->precision)
	{
		write(1, &(d->str[i]), 1);
		i++;
		*res += 1;
	}
}

void print_hex(t_data *d, int *res)
{
	int temp;
	int 		warning;

	warning = 0;
	if (d->precision == 0 && d->hex == 0)
	{
		warning = 1;
		d->precision++;
	}
	if (d->width < d->precision)
		d->width = d->precision;
	temp = d->width - d->precision;
	if (temp > 0)
	{
		ft_putchar(' ', temp);
		*res += temp;
	}
	temp = d->precision - d->hex_len;
	//printf("temp = %d\n", temp);
	//printf("len_hex = %u, precision = %u\n", d->hex_len, d->precision);
	//printf("temp = %d\n", temp);
	if (temp > 0)
	{
		ft_putchar('0', temp);
		*res += temp;
	}
	if (warning == 0)
	{
		ft_putnbr(d->hex, d->hex_len, 16, "0123456789abcdef");
		*res += d->hex_len;
	}
}	

void print_dec(t_data *d, int *res)
{
	int temp;
	unsigned int dec2;
	int 		warning;

	if (d->dec < 0)
		dec2 = -d->dec;
	else 
		dec2 = d->dec;
	warning = 0;
	if (d->precision == 0 && d->dec == 0)
	{
		warning = 1;
	}
	if (d->width < d->precision + d->dec_neg)
		d->width = d->precision + d->dec_neg;
	
	temp = d->width - d->precision - d->dec_neg;
	if (temp > 0)
//	printf("width = %u, precision = %u\n", d->width, d->precision);
//	printf("temp = %d\n", temp);
	{
		ft_putchar(' ', temp);
		*res += temp;
	}	
	if (d->dec_neg == 1)
	{
		write(1, "-", 1);
		*res += 1;
	}
	if (d->precision > 0)
	{
		temp = d->precision - d->dec_len;
//	printf("temp = %d\n", temp);
		ft_putchar('0', temp);
		*res += temp;
	}
	if (warning == 0)
	{
		ft_putnbr(dec2, d->dec_len, 10, "0123456789");
		*res += d->dec_len;
	}
}	


int ft_printf(const char *input, ...)
{
	va_list			args;
	unsigned int	i;
	int	j;
	int				res;
	t_data			d;

	res = 0;
	i = 0;
	va_start(args, input);
	while(input[i])
	{
		if (input[i] != '%')
		{
			write(1, &input[i], 1);
			i++;
			res++;
		}
		else
		{
			i++;
			data_init(&d);
			j = i;
		   	while (input[j] && input[j] != 's' && input[j]	!= 'd' && input[j] != 'x')
				j++;
			if (input[j] == '\0')
				return(-1);
			d.type = input[j];
			if (parse(input, args, &d, &i) == -1)
				return(-1);
			if (d.type == 's')
				print_str(&d, &res);
			if (d.type == 'd')
				print_dec(&d, &res);
			if (d.type == 'x')
				print_hex(&d, &res);
			i++;
		}
	}
	va_end(args);
	return(res);
}

int main(void)
{
	printf("res = %d\n", printf("simple : %14.4s |\n", NULL));
	printf("res = %d\n",ft_printf("simple : %14.4s |\n", NULL));
	printf("res = %d\n", printf("simple : %s | %15.0d | %d | %.x.\n", "hello", 0, -15, 0));
	printf("res = %d\n", ft_printf("simple : %s | %15.0d | %d | %.x.\n", "hello", 0, -15, 0));
}

