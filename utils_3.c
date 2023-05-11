/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:18:28 by gfantech          #+#    #+#             */
/*   Updated: 2023/05/11 09:37:59 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_fd(int *fd, char *filename, int i_o, bool append)
{
	if (access(filename, F_OK) == -1 && i_o == IN)
		return (-1);
	if ((access(filename, R_OK) == 0 && i_o == IN)
		|| (access(filename, W_OK) == 0 && i_o == OUT)
		|| (access(filename, F_OK) == -1 && i_o == OUT))
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
