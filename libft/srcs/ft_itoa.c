/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:31:02 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/05 11:31:04 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_libft.h"

static void	convert(long n, char *res, int i)
{
	if (n != 0)
	{
		convert(n / 10, res, i - 1);
		res[i] = (n % 10) + '0';
	}
}

static char	*check_num(long *n, int *lenght)
{
	char	*res;

	if (*n < 0)
	{
		*n *= -1;
		*lenght += 1;
		res = (char *)malloc((*lenght + 1) * sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '-';
	}
	else if (*n == 0)
	{
		res = (char *)malloc(2 * sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '0';
		res[1] = '\0';
	}
	else
		res = (char *)malloc((*lenght + 1) * sizeof(char));
	if (!res)
		return (NULL);
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	long	n1;
	int		lenght;

	lenght = 0;
	n1 = n;
	while (n != 0)
	{
		n = n / 10;
		lenght++;
	}
	res = check_num(&n1, &lenght);
	if (!res)
		return (NULL);
	if (res[0] == '0')
		return (res);
	convert(n1, res, lenght - 1);
	res[lenght] = '\0';
	return (res);
}
