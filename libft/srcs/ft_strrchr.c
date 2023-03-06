/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:20:22 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/03 19:20:24 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*pointer;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
		{
			pointer = &((char *)s)[i];
			return (pointer);
		}
		i--;
	}
	return (0);
}
