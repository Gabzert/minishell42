/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:45:45 by gabriele          #+#    #+#             */
/*   Updated: 2023/04/26 11:21:37 by gfantech         ###   ########.fr       */
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
		g_sig.g_exit = 0;
		i++;
	}
	while (inputs[i] != NULL)
	{
		if (inputs[i][0])
			printf("%s", inputs[i]);
		if (inputs[i + 1] != NULL)
			printf(" ");
		g_sig.g_exit = 0;
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
		if (strchr(env[i], '='))
			ft_printf("%s\n", env[i]);
		i++;
	}
}

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

void	export(char **inputs, t_x **x)
{
	char	**new_env;
	int		i;

	i = -1;
	if (inputs[1])
	{
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

void	unset(char **inputs, t_x **x)
{
	char	**new_env;
	int		i;
	int		j;
	int		sp;

	i = -1;
	j = 0;
	if (!inputs[1])
		return ;
	while ((*x)->envp[++i])
		if (!ft_strncmp((*x)->envp[i], inputs[1], ft_strlen(inputs[1])))
			break ;
	sp = i;
	if (!(*x)->envp[i])
		return ;
	while ((*x)->envp[i])
		i++;
	new_env = ft_calloc(sizeof(char *), i);
	i = -1;
	while ((*x)->envp[++i])
		if (i != sp)
			new_env[j++] = (*x)->envp[i];
	free((*x)->envp[sp]);
	free((*x)->envp);
	(*x)->envp = new_env;
}
