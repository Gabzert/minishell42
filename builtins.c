/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:45:45 by gabriele          #+#    #+#             */
/*   Updated: 2023/05/11 10:59:21 by gfantech         ###   ########.fr       */
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

void	ft_exit(char **inputs, t_x **x)
{
	int	i;

	i = -1;
	if (split_size(inputs) > 2)
	{	
		write(2, "too many arguments\n", 20);
		exit(1);
	}
	if (inputs[1])
	{
		while (inputs[1][++i])
		{
			if (ft_isalpha(inputs[1][i]))
			{
				write(2, "numeric argument required\n", 28);
				exit(2);
			}
		}
		g_sig.g_exit = ft_atoi(inputs[1]);
	}
	free_split(inputs);
	free_x(x);
	exit(g_sig.g_exit);
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
