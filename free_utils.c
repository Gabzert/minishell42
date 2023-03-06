/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:31:42 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/06 16:32:14 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(int **fd, int i)
{
	while (i >= 0)
	{
		close(fd[i][1]);
		close(fd[i][0]);
		i--;
	}
}

void	free_pipes(int **fd, int i)
{
	while (i >= 0)
	{
		close(fd[i][1]);
		close(fd[i][0]);
		free(fd[i]);
		i--;
	}
	free(fd);
}