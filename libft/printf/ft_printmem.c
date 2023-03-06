/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:00:38 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/13 17:00:39 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_count_mem(unsigned long n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n = n / 16;
		len++;
	}
	return (len);
}

static void	pointer_hex(unsigned long n, int i, char *res)
{
	int		temp;
	char	*base;

	base = "0123456789abcdef";
	if (n > 0)
	{
		temp = n % 16;
		n = n / 16;
		res[i] = base[temp];
		pointer_hex(n, i - 1, res);
	}
}

int	ft_printmem(void *ptr, int *count, t_format *f)
{
	unsigned long	a;
	char			*res;
	int				len;

	if (ptr == NULL)
	{
		res = malloc(6 * sizeof(char));
		ft_strlcpy(res, "(nil)", 6);
		f->pnull = 1;
		ft_printer(f, res, count);
		return (1);
	}
	a = (unsigned long)ptr;
	len = ft_count_mem(a);
	res = (char *)malloc((len + 1) * sizeof(char));
	pointer_hex(a, len - 1, res);
	res[len] = '\0';
	f->width -= 2;
	*count += 2;
	ft_printer(f, res, count);
	return (1);
}
