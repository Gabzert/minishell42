/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:45:45 by gabriele          #+#    #+#             */
/*   Updated: 2023/03/30 14:14:33 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **inputs)
{
	int		i;
	bool	supp_nl;

	i = 1;
	supp_nl = false;
	if (inputs[i] != NULL && ft_strcmp(inputs[i], "-n") == 0)
	{
		supp_nl = true;
		g_exit = 0;
		i++;
	}
	while (inputs[i] != NULL)
	{
		printf("%s ", inputs[i]);
		g_exit = 0;
		i++;
	}
	if (!supp_nl)
	{
		printf("\n");
	}
}

void	l_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}

void	export(char **inputs, char ***env)
{
	char	**new_env;
	int		i;

	i = -1;
	if (inputs[1])
	{
		new_env = malloc((split_size(*env) + 1) * sizeof(char **));
		while ((*env)[++i])
			new_env[i] = ft_strdup((*env)[i]);
		new_env[i] = ft_strdup(inputs[1]);
		new_env[i + 1] = NULL;
		*env = new_env;
		free_split(new_env);
	}
	else
	{
		while ((*env)[++i])
			ft_printf("declare -x %s\n", (*env)[i]);
	}
}

void	unset(char **inputs, char ***env)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_env = malloc(split_size(*env) - 1 * sizeof(char **));
	while ((*env)[i])
	{
		if (ft_strcmp((*env)[i], inputs[0]) != 0)
		{
			new_env[j] = ft_strdup((*env)[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	*env = new_env;
	free_split(new_env);
}
