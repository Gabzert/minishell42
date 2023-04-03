/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:24:05 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/03 08:53:34 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exit_status(char *str)
{
	if (ft_strnstr(str, "$?", 2) && ft_strlen(str) == 2)
		printf("%d: command not found\n", g_sig.g_exit);
	else if (ft_strnstr(str, "echo $?", 7))
		printf("%d", g_sig.g_exit);
	g_sig.g_exit = 0;
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