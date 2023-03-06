/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:08:15 by gfantech          #+#    #+#             */
/*   Updated: 2022/05/11 13:08:30 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_libft.h"

int	ft_atoi(const char *str)
{
	int	num;
	int	neg;

	num = 0;
	neg = 1;
	while (*str == 32 || *str == 9 || *str == '\r' || *str == '\v'
		|| *str == '\n' || *str == '\f')
	{
		str++;
	}
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		neg = -1;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		num = (num * 10) + ((*str) - '0');
		str++;
	}
	return (num * neg);
}

int	ft_atoi_free(char *str)
{
	int	n;

	n = ft_atoi(str);
	free(str);
	return (n);
}
