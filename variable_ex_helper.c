/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:12:16 by naal-jen          #+#    #+#             */
/*   Updated: 2023/03/24 11:26:19 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*simple_v(char *var, char *new_str)
{
	char	*cmd;

	cmd = getenv(var);
	if (cmd == NULL)
	{
		printf("simple_v\n");
		free(cmd);
		free(new_str);
	}
	else
	{
		new_str = ft_strjoin(new_str, cmd);
		new_str = ft_strjoin(new_str, " ");
	}
	return (new_str);
}

char	*not_v(char *new_str, char *str)
{
	new_str = ft_strjoin(new_str, str);
	new_str = ft_strjoin(new_str, " ");
	return (new_str);
}

char	*split_dollar(char *new_str, char *str)
{
	char	**new_split;
	char	*var;
	char	*cmd;
	int		i;

	i = 0;
	new_split = ft_split(str, '$');
	while (new_split[i])
	{
		var = new_split[i];
		cmd = getenv(var);
		if (cmd == NULL)
		{
			printf("split_dollar\n");
			free(cmd);
			free(var);
			//!free new_split;
		}
		else
		{
			new_str = ft_strjoin(new_str, cmd);
			new_str = ft_strjoin(new_str, " ");
		}
		i++;
	}
	return (new_str);
}