/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formatter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:52:34 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/17 15:52:37 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_formatter(t_format *f)
{
	if (f->plus == 1 && f->space == 1)
		f->space = 0;
	if (f->minus == 1 && f->zero == 1)
		f->zero = 0;
	if (f->pc_check == 1 && f->precision < f->width)
		f->zero = 0;
	if ((f->spec == 'd' || f->spec == 'i' || f->spec == 'u' || f->spec == 'X'
			|| f->spec == 'x' || f->spec == 'p') && f->zero == 1)
		f->parse = '0';
}

void	format_initializer(t_format *f)
{
	f->minus = 0;
	f->plus = 0;
	f->space = 0;
	f->hash = 0;
	f->zero = 0;
	f->width = 0;
	f->precision = 0;
	f->pc_check = 0;
	f->di_sign = 0;
	f->parse = ' ';
	f->pnull = 0;
}
