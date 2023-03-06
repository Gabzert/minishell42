/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:26:57 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/04 16:26:59 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_libft.h"

static int	set_ctr(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static int	border_check(char const *s1, char const *set,
		int side, int lenght)
{
	int	i;

	i = 0;
	if (side == -1)
	{
		i = lenght - 1;
		while (set_ctr(set, s1[i]))
			i--;
		return (i);
	}	
	while (set_ctr(set, s1[i]))
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		lenght;
	char	*str;
	int		start;
	int		end;

	lenght = ft_strlen(s1);
	start = border_check(s1, set, 1, lenght);
	end = border_check(s1, set, -1, lenght);
	lenght = (end + 1) - start;
	if (lenght < 0)
		lenght = 0;
	str = (char *)malloc((lenght + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1 + start, lenght);
	str[lenght] = '\0';
	return (str);
}
