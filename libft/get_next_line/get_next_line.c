/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:48:09 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/26 15:48:13 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*find_end(char *str, int res)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (ft_substr(str, 0, i + 1));
		i++;
	}
	if (res == 0 && str[0] != '\0')
		return (ft_substr(str, 0, i));
	return (NULL);
}

char	*read_line(int fd, char **stat, char *temp)
{
	int		res;
	char	*str;
	char	*sup;

	res = 1;
	while (res != 0)
	{
		res = read(fd, temp, BUFFER_SIZE);
		if (res == -1)
			return (NULL);
		temp[res] = '\0';
		sup = *stat;
		*stat = ft_strjoin(sup, temp);
		free(sup);
		str = find_end(*stat, res);
		if (str != NULL)
		{
			sup = *stat;
			*stat = strcut(sup);
			return (str);
		}
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*str;
	static char	*offset;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	if (offset == NULL)
	{
		offset = malloc(sizeof(char *) * 1);
		if (offset == NULL)
			return (NULL);
		offset[0] = '\0';
	}
	buffer = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	str = read_line(fd, &offset, buffer);
	if (str == NULL || *offset == '\0')
	{
		free(offset);
		offset = NULL;
	}
	free(buffer);
	return (str);
}
