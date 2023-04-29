/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:10:18 by gfantech          #+#    #+#             */
/*   Updated: 2023/04/26 15:10:42 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	find_in_split(char ***arr, char *str)
{
	char	**input;
	int		i;

	i = -1;
	input = ft_split(str, '=');
	while ((*arr)[++i])
	{
		if (ft_strncmp((*arr)[i], input[0], ft_strlen(input[0])) == 0)
		{
			free((*arr)[i]);
			(*arr)[i] = ft_strdup(str);
			free_split(input);
			return (true);
		}
	}
	free_split(input);
	return (false);
}

static bool	check_args(char *inputs)
{
	char	**temp;
	int		i;

	i = 0;
	if (ft_strchr(inputs, '='))
	{
		if (inputs[0] == '=')
			return (false);
		temp = ft_split(inputs, '=');
		while (temp[0][++i])
		{
			if (!ft_isalpha(temp[0][i]))
				return (false);
		}
	}
	else
	{
		while (inputs[++i])
		{
			if (!ft_isalpha(inputs[i]))
				return (false);
		}
	}
	return (true);
}

void	export(char **inputs, t_x **x)
{
	char	**new_env;
	int		i;

	i = -1;
	if (inputs[1])
	{
		if (!check_args(inputs[1]))
		{
			write(2, "not a valid identifier\n", 24);
			g_sig.g_exit = 1;
			return ;
		}
		if (find_in_split(&(*x)->envp, inputs[1]) == false)
		{
			new_env = malloc((split_size((*x)->envp) + 2) * sizeof(char *));
			while ((*x)->envp[++i])
				new_env[i] = (*x)->envp[i];
			new_env[i] = ft_strdup(inputs[1]);
			new_env[i + 1] = NULL;
			free((*x)->envp);
			(*x)->envp = new_env;
		}
	}
	else
	{
		while ((*x)->envp[++i])
			ft_printf("declare -x %s\n", (*x)->envp[i]);
	}
}
