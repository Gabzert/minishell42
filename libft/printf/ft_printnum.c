/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:57:49 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/13 12:57:52 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_count_num(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	ft_putnbr(int n, int i, char *res)
{
	int		sign;
	char	c;

	sign = 1;
	if (n < 0)
		sign = -1;
	if (n / 10)
		ft_putnbr(n / 10 * sign, i - 1, res);
	c = '0' + n % 10 * sign;
	res[i] = c;
}

int	ft_printnum(int val, int *count, t_format *f)
{
	char	*res;
	int		len;

	len = ft_count_num(val);
	if (val < 0)
		f->di_sign = -1;
	res = res_malloc_num(*f, &len, 0);
	if (val == 0 && f->pc_check == 1 && f->precision == 0)
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
	ft_putnbr(val, len - 1, res);
	res[len] = '\0';
	ft_printer(f, res, count);
	return (1);
}
