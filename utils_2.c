/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:24:05 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/26 14:24:26 by naal-jen         ###   ########.fr       */
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

int	locate_cmd(char **inputs)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		if (ft_strncmp(inputs[i], "<", ft_strlen(inputs[i])) == 0
			|| ft_strncmp(inputs[i], "<<", ft_strlen(inputs[i])) == 0
			|| ft_strncmp(inputs[i], ">", ft_strlen(inputs[i])) == 0
			|| ft_strncmp(inputs[i], ">>", ft_strlen(inputs[i])) == 0)
			i += 2;
		else if (ft_strnstr(inputs[i], "<", ft_strlen(inputs[i]))
			|| ft_strnstr(inputs[i], "<<", ft_strlen(inputs[i]))
			|| ft_strnstr(inputs[i], ">", ft_strlen(inputs[i]))
			|| ft_strnstr(inputs[i], ">>", ft_strlen(inputs[i])))
			i++;
		else
			return (i);
	}
	return (i);
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
	if (ft_strcmp(inputs[0], "cd") == 0 || ft_strcmp(inputs[0], "pwd") == 0
		|| ft_strcmp(inputs[0], "echo") == 0 || ft_strcmp(inputs[0], "env") == 0
		|| ft_strcmp(inputs[0], "export") == 0
		|| ft_strcmp(inputs[0], "unset") == 0
		|| ft_strcmp(inputs[0], "exit") == 0)
		return (true);
	else
		return (false);
}

void	reset_io(int fdin, int fdout)
{
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
}
