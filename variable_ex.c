/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:55:54 by naal-jen          #+#    #+#             */
/*   Updated: 2023/03/18 09:55:41 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	full_size(char *str)
{
	int i;
	int j;
	int	size_cmd;
	int		size_full;
	char	*cmd;
	char	*var;

	i = 0;
	j = 0;
	size_cmd = 0;
	size_full = 0;
	size_full = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i + 1;
			while (str[j] && (!(str[j] >= 9 && str[j] <= 13)))
			{
				j++;
			}
			var = ft_substr(str, i + 1, j - i);
			size_full -= ft_strlen(var) + 1;
			cmd = getenv(var);
			if (cmd)
			{
				size_cmd += ft_strlen(cmd);
			}
			else
				size_full += ft_strlen(var) + 1;
			i = j - 1;
		}
		i++;
	}
	size_cmd += size_full;
	return (size_cmd);
}

char	*control_ex(char *str)
{
	int		size_for_malloc;
	int	i;
	int	j;
	char	*var; // variable to be expanded
	char	*cmd; // hold the value of the variable expanded
	char	*new_str; // final string to be returned
	char	**str_split;

	i = 0;
	j = 0;
	size_for_malloc = full_size(str);
	str_split = ft_split(str, ' ');
	new_str = (char *)malloc(sizeof(char) * size_for_malloc + 1);
	while (str_split[i][j])
	{
		new_str[j] = str_split[i][j];
		j++;
	}
	new_str[j] = ' ';
	j++;
	new_str[j] = '\0';
	i++;
	j = 0;
	while (str_split[i])
	{
		if (ft_strnstr(str_split[i], "$", 1))
		{
			var = ft_substr(str_split[i], 1, ft_strlen(str_split[i]));
			cmd = getenv(var);
			if (cmd == NULL)
			{
				// free everything then exit
				// and print a newline
				printf("i have a problem with the cmd man help!!\n");
				new_str = ft_strjoin(new_str, " ");
			}
			else
			{
				new_str = ft_strjoin(new_str, cmd);
				new_str = ft_strjoin(new_str, " ");
			}
		}
		else
		{
			new_str = ft_strjoin(new_str, str_split[i]);
			new_str = ft_strjoin(new_str, " ");
		}
		i++;
	}
	return (new_str);
}