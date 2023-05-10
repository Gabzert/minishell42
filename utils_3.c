/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:18:28 by gfantech          #+#    #+#             */
/*   Updated: 2023/05/10 16:36:10 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_fd(int *fd, char *filename, int i_o, bool append)
{
	if (access(filename, F_OK) == 0)
	{
		if (access(filename, X_OK))
		{
			if (*fd != 0)
				close(*fd);
			if (i_o == IN)
				*fd = open(filename, O_RDONLY);
			else
			{
				if (append)
					*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
				else
					*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
			return (0);
		}
	}
	return (-1);
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
