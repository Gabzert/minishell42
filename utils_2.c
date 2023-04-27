/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:24:05 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/27 16:10:17 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exit_status(char *str)
{
	if (ft_strnstr(str, "$?", 2) && ft_strlen(str) == 2)
	{
		printf("%d: command not found\n", g_sig.g_exit);
		g_sig.g_exit = 0;
	}
	return (str);
}

void	locate_cmd(char **inputs, int *i)
{
	while (1)
	{
		if (ft_strncmp(inputs[*i], "<", ft_strlen(inputs[*i])) == 0
			|| ft_strncmp(inputs[*i], "<<", ft_strlen(inputs[*i])) == 0
			|| ft_strncmp(inputs[*i], ">", ft_strlen(inputs[*i])) == 0
			|| ft_strncmp(inputs[*i], ">>", ft_strlen(inputs[*i])) == 0)
			*i += 2;
		else if (ft_strnstr(inputs[*i], "<", ft_strlen(inputs[*i]))
			|| ft_strnstr(inputs[*i], "<<", ft_strlen(inputs[*i]))
			|| ft_strnstr(inputs[*i], ">", ft_strlen(inputs[*i]))
			|| ft_strnstr(inputs[*i], ">>", ft_strlen(inputs[*i])))
			(*i)++;
		else
			break ;
	}
}

void	envcpy(char **env, t_x **x)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	(*x)->envp = ft_calloc(sizeof(char *), (i + 1));
	i = -1;
	while (env[++i])
		(*x)->envp[i] = ft_strdup(env[i]);
}

bool	is_any(char **inputs)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		if (ft_strcmp(inputs[i], "cd") == 0 || ft_strcmp(inputs[i], "pwd") == 0
			|| ft_strcmp(inputs[i], "echo") == 0
			|| ft_strcmp(inputs[i], "env") == 0
			|| ft_strcmp(inputs[i], "export") == 0
			|| ft_strcmp(inputs[i], "unset") == 0
			|| ft_strcmp(inputs[i], "exit") == 0)
			return (true);
		i++;
	}
	return (false);
}

void	reset_io(int fdin, int fdout)
{
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
}
