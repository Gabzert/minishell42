/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:43:25 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/04 09:43:27 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*haystack;
	char	*needle;
	size_t	i;

	i = 0;
	if (!*little)
		return (((char *)big));
	if (len == 0)
		return (NULL);
	i = len - ft_strlen(little) + 1;
	while (i-- && *big)
	{
		haystack = (char *)big;
		needle = (char *)little;
		while (*needle && *needle == *haystack)
		{
			++haystack;
			++needle;
		}
		if (!*needle)
			return ((char *)big);
		big++;
	}
	return (NULL);
}
