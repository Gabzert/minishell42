/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:54:42 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/14 17:36:46 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_len(char *s, char c, char q)
{
	int	ret;

	ret = 0;
	while (*s)
	{
		if (*s != c)
		{
			ret++;
			if (*s == q)
			{
				s++;
				while (*s && *s != q)
					s++;
			}
			else
				while (*s && *s != c)
					s++;
		}
		else
			s++;
	}
	return (ret);
}

int	read_quoted(char **line, char q)
{
	int	len;

	len = 0;
	(*line)++;
	while (**line && **line != q)
	{
		len++;
		(*line)++;
	}
	return (len);
}

static char	**quotes_splitter(char *line, char c, char q)
{
	int		i;
	int		len;
	char	**ret;

	i = 0;
	ret = malloc(sizeof(char *) * (split_len(line, c, q) + 1));
	while (*line)
	{
		if (*line != c)
		{
			len = 0;
			if (*line == q)
				len += read_quoted(&line, q);
			else
				while (*line && *line != c && ++len)
					line++;
			ret[i++] = ft_substr(line - len, 0, len);
		}
		else
			line++;
	}
	ret[i] = NULL;
	return (ret);
}

char	**split_cmd(char *line, t_flags fl)
{
	if (fl.quote == false && fl.d_quote == false)
		return (ft_split(line, ' '));
	if (fl.quote == true)
		return (quotes_splitter(line, ' ', 39));
	else if (fl.d_quote == true)
		return (quotes_splitter(line, ' ', 34));
	return (NULL);
}
