/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:27:11 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/04 09:27:14 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	x;
	char	*pointer;

	x = 0;
	while (x < n)
	{
		if (((unsigned char *)s)[x] == (unsigned char)c)
		{
			pointer = &((char *)s)[x];
			return (pointer);
		}
		x++;
	}
	return (0);
}
