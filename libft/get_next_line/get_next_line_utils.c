/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:48:27 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/26 15:48:31 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*strcut(char *str)
{
	char	*cut;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	cut = malloc(sizeof(char *) * (ft_strlen(&str[i]) + 1));
	while (str[i] != '\0')
	{
		cut[j] = str[i];
		i++;
		j++;
	}
	cut[j] = '\0';
	free(str);
	return (cut);
}
