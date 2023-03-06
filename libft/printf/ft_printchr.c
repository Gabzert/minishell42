/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:22:48 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/13 14:22:49 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_printchr(int c, int *count, t_format *f)
{
	char	*res;

	res = malloc(2 * sizeof(char));
	res[0] = c;
	res[1] = '\0';
	ft_printer(f, res, count);
	return (1);
}
