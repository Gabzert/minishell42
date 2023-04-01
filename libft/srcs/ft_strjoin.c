/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:45:33 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/30 16:52:17 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		c;
	int		x;

	c = 0;
	x = 0;
	new = (char *)malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1)
			* sizeof(char));
	if (new == NULL)
		return (NULL);
	while (((char *)s1)[x] != '\0')
	{
		new[c] = ((char *)s1)[x];
		c++;
		x++;
	}
	x = 0;
	while (((char *)s2)[x] != '\0')
	{
		new[c] = ((char *)s2)[x];
		c++;
		x++;
	}
	new[c] = '\0';
	return (new);
}
