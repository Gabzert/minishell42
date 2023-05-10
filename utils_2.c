/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:24:05 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/28 14:42:05 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exit_status(char *str)
{
	if (ft_strnstr(str, "$?", 2) && ft_strlen(str) == 2)
	{
		printf("%d: command not found\n", g_sig.g_exit);
		g_sig.g_exit = 0;
		// free(str);
		// char *new_str = (char *)malloc(2 * sizeof(char));
		// new_str[0] = '0';
		// new_str[1] = '\0';
		// exit(1);
		return ("petter");
	}
	return (str);
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
