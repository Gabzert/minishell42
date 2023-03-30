/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:24:05 by naal-jen          #+#    #+#             */
/*   Updated: 2023/03/30 17:29:51 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exit_status(char *str)
{
	if (ft_strnstr(str, "$?", 2) && ft_strlen(str) == 2)
		printf("%d: command not found\n", sig.g_exit);
	else if (ft_strnstr(str, "echo $?", 7))
		printf("%d", sig.g_exit);
	sig.g_exit = 0;
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