/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:48:11 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/04 12:48:13 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	c;
	char	*sub;

	if (start > ft_strlen(s))
	{
		start = 0;
		len = 0;
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	c = 0;
	while (((char *)s)[start] != '\0' && c < len)
	{
		sub[c] = ((char *)s)[start];
		c++;
		start++;
	}
	sub[c] = '\0';
	return (sub);
}
