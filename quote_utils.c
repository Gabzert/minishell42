/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:54:42 by gfantech          #+#    #+#             */
/*   Updated: 2023/04/26 10:56:44 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
char	*read_quoted(char **line, char q)
{
	char	*s;
	int		l;

	l = 0;
	(*line)++;
	while (**line && **line != q)
	{
		l++;
		(*line)++;
	}
	s = ft_substr(*line - l, 0, l);
	(*line)++;
	return (s);
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
				ret[i++] = read_quoted(&line, q);
			else
			{
				while (*line && *line != c && *line != q && ++len)
					line++;
				ret[i++] = ft_substr(line - len, 0, len);
			}
		}
		else
			line++;
	}
	ret[i] = NULL;
	return (ret);
}
*/

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

static int	read_quoted(char **line, char q)
{
	int		l;

	l = 1;
	(*line)++;
	while (**line && **line != q)
	{
		l++;
		(*line)++;
	}
	return (l);
}

char	*remove_quote(char *line, int len, char q)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (line[i] && i < len)
	{
		if (line[i] != q)
		{
			str[j] = line[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
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
			while (*line && *line != c && ++len)
			{
				if (*line == q)
					len += read_quoted(&line, q);
				line++;
			}
			ret[i++] = remove_quote(line - len, len, q);
		}
		else
			line++;
	}
	ret[i] = NULL;
	return (ret);
}

char	**split_cmd(char *line, t_flags fl)
{
	int	i;

	i = -1;
	while (line [++i])
	{
		if (line[i] == 39 && ft_strchr(line + i + 1, 39))
		{
			fl.quote = true;
			break ;
		}
		if (line[i] == 34 && ft_strchr(line + i + 1, 34))
		{
			fl.d_quote = true;
			break ;
		}
	}
	if (fl.quote == false && fl.d_quote == false)
		return (ft_split(line, ' '));
	if (fl.quote == true)
		return (quotes_splitter(line, ' ', 39));
	else if (fl.d_quote == true)
		return (quotes_splitter(line, ' ', 34));
	return (NULL);
}
