/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:36:58 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/17 11:37:01 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	is_flag(char c)
{
	char	*not_flag;

	not_flag = "dicsxXup%.";
	while (*not_flag)
	{
		if (*not_flag == c)
			return (0);
		not_flag++;
	}
	return (1);
}	

static int	atoa(char *str, size_t *i)
{
	int	num;

	num = 0;
	while (is_flag(*str))
	{
		num = (num * 10) + ((*str) - '0');
		str++;
		*i += 1;
	}
	return (num);
}

int	parsecalc(char *str, t_format *format)
{
	size_t	i;

	i = 0;
	if (str[i] == '.')
	{
		i++;
		format->precision = atoa(&str[i], &i);
		format->pc_check = 1;
	}
	else
	{
		format->width = atoa(&str[i], &i);
		if (str[i] == '.')
		{	
			i++;
			format->precision = atoa(&str[i], &i);
			format->pc_check = 1;
		}
	}
	return (i);
}

static char	*res_flags(t_format f, int *len, int is_zero)
{
	char	*res;

	if ((f.spec == 'x' || f.spec == 'X') && f.hash == 1 && is_zero == 0)
	{
		*len += 2;
		res = malloc(*len + 1 * sizeof(char));
		res[0] = '0';
		if (f.spec == 'x')
			res[1] = 'x';
		else
			res[1] = 'X';
	}
	else if ((f.plus == 1 || f.space == 1) && f.di_sign != -1)
	{
		*len += 1;
		res = malloc(*len + 1 * sizeof(char));
		if (f.plus == 1)
			res[0] = '+';
		if (f.space == 1)
			res [0] = ' ';
	}
	else
		res = malloc(*len + 1 * sizeof(char));
	return (res);
}

char	*res_malloc_num(t_format f, int *len, int is_zero)
{
	int		i;
	int		parse;
	char	*res;

	i = 0;
	if ((f.plus == 1 || f.space == 1) && f.di_sign != -1)
		i = 1;
	else if ((f.spec == 'x' || f.spec == 'X') && f.hash == 1 && is_zero == 0)
		i = 2;
	parse = f.precision - *len;
	if (f.pc_check == 1 && *len < f.precision)
		*len = f.precision;
	res = res_flags(f, len, is_zero);
	while (parse-- > 0)
	{
		res[i] = '0';
		i++;
	}
	return (res);
}
