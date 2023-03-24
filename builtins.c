/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriele <gabriele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:45:45 by gabriele          #+#    #+#             */
/*   Updated: 2023/03/23 14:07:51 by gabriele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(char **inputs, char ***env)
{
	char	**new_env;
	int		i;

	i = -1;
	if (inputs[1])
	{
		new_env = malloc(split_size(*env) + 1 * sizeof(char **));
		while ((*env)[++i])
		new_env[i] = ft_strdup((*env)[i]);
		new_env[i] = ft_strdup(inputs[1]);
//		free(env);
		*env = new_env;
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
//	free(env);
	*env = new_env;
}