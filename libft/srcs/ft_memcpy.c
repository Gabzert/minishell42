/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:01:24 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/03 17:01:28 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	c;

	c = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (c < n)
	{
		((char *)dest)[c] = ((char *)src)[c];
		c++;
	}	
	return (dest);
}
