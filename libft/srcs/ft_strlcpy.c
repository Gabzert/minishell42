/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:42:32 by gfantech          #+#    #+#             */
/*   Updated: 2022/05/11 10:43:03 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	c;
	size_t	i;

	c = 0;
	i = 0;
	while (src[c] != '\0')
		c++;
	if (size != 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (c);
}

size_t	ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
		dest[i] = '\0';
	return (i);
}