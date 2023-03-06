/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:48:10 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/13 14:48:12 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_count_hex(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	while (n != 0)
	{
		n = n / 16;
		len++;
	}
	return (len);
}

static void	convert(unsigned int n, char c, int i, char *res)
{
	int		temp;
	char	*base;

	if (c == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n != 0)
	{
		temp = n % 16;
		n = n / 16;
		convert(n, c, i - 1, res);
		res[i] = base[temp];
	}
}

static int	precision_handler(char *res, int *count, t_format *f)
{
	if (f->width > 0)
	{
		parsing(f, f->width);
		*count += f->width;
		free(res);
		return (1);
	}
	res[0] = '\0';
	ft_printer(f, res, count);
	return (1);
}

int	ft_printhex(unsigned int n, char c, int *count, t_format *f)
{
	char	*res;
	int		len;

	len = ft_count_hex(n);
	if (n == 0)
	{
		res = res_malloc_num(*f, &len, 1);
		res[len - 1] = '0';
	}
	else
		res = res_malloc_num(*f, &len, 0);
	convert(n, c, len - 1, res);
	if (n == 0 && f->pc_check == 1 && f->precision == 0)
		return (precision_handler(res, count, f));
	res[len] = '\0';
	ft_printer(f, res, count);
	return (1);
}
