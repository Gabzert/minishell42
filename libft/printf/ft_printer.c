/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:34:27 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/20 13:34:29 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	parsing(t_format *f, int i)
{	
	while (i > 0)
	{
		write(1, &f->parse, 1);
		i--;
	}
}

static void	put_flag(t_format *f, int diff, int *count)
{
	if (f->di_sign == -1 && f->zero == 1)
	{
		write(1, "-", 1);
		*count += 1;
	}
	if (f->spec == 'p' && f->zero == 1 && f->pnull != 1)
		write(1, "0x", 2);
	if (f->minus != 1 && f->width > 0)
		parsing(f, diff);
	if (f->spec == 'p' && f->zero == 0 && f->pnull != 1)
		write(1, "0x", 2);
	if (f->di_sign == -1 && f->zero != 1)
	{
		write(1, "-", 1);
		*count += 1;
	}
}

void	ft_printer(t_format *f, char *str, int *count)
{
	int	diff;
	int	len;
	int	i;

	diff = 0;
	i = 0;
	if (str[0] < 32 && f->spec == 'c')
		len = 1;
	else
		len = (int)ft_strlen(str);
	if ((len - f->di_sign) < f->width)
		diff = f->width - (len - f->di_sign);
	*count += len;
	*count += diff;
	put_flag(f, diff, count);
	if (str[0] == '\0' && f->spec == 'c')
		write(1, &str[0], 1);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	if (f->minus == 1 && f->width > 0)
		parsing(f, diff);
	free(str);
}
