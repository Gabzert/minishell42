/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:30:19 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/21 18:30:22 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_count_num(unsigned int n)
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

static void	ft_putunsigned(unsigned int n, int i, char *res)
{
	char	c;

	if (n / 10)
		ft_putunsigned(n / 10, i - 1, res);
	c = '0' + n % 10;
	res[i] = c;
}

int	ft_printun(unsigned int n, int *count, t_format *f)
{
	char	*res;
	int		len;

	len = ft_count_num(n);
	res = res_malloc_num(*f, &len, 0);
	ft_putunsigned(n, len - 1, res);
	if (n == 0 && f->pc_check == 1 && f->precision == 0)
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
	res[len] = '\0';
	ft_printer(f, res, count);
	return (1);
}
