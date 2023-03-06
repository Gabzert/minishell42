/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:25:24 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/13 14:25:26 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_strnull(int *count, t_format *f)
{
	char	*res;

	res = calloc(7, sizeof(char));
	ft_strlcpy(res, "(null)", 7);
	if (f->pc_check == 1 && f->precision < 6)
		res[0] = '\0';
	ft_printer(f, res, count);
	return (1);
}

int	ft_printstr(char *str, int *count, t_format *f)
{
	char	*res;

	if (str == NULL)
		return (ft_strnull(count, f));
	res = malloc((ft_strlen(str) + 1) * sizeof(char));
	ft_strlcpy(res, str, ft_strlen(str) + 1);
	if (f->pc_check == 1 && f->precision < (int)(ft_strlen(str) + 1))
	{
		res[f->precision] = '\0';
		if (f->width > 0 && f->precision == 0)
		{
			parsing(f, f->width);
			*count += f->width;
			free(res);
			return (1);
		}
	}
	ft_printer(f, res, count);
	return (1);
}
