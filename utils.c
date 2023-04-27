/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:48:33 by gfantech          #+#    #+#             */
/*   Updated: 2023/04/27 16:15:39 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	flag_finder(char *input, t_flags *flags)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == 39)
			i = (ft_strlen(input) - ft_strlen(ft_strchr(input + i + 1, 39)));
		if (input[i] == 34)
			i = (ft_strlen(input) - ft_strlen(ft_strchr(input + i + 1, 34)));
		if (ft_strnstr(&input[i], "<<", 2))
			flags->write_in = true;
		if (ft_strnstr(&input[i], ">>", 2))
			flags->append_out = true;
		if (input[i] == '<' && flags->write_in == false)
			flags->re_in = true;
		if (input[i] == '>' && flags->append_out == false)
			flags->re_out = true;
		if (input[i] == '|')
			flags->pipe = true;
		i++;
	}
}

void	flag_init(t_flags *f)
{
	f->append_out = false;
	f->d_quote = false;
	f->pipe = false;
	f->quote = false;
	f->re_in = false;
	f->re_out = false;
	f->write_in = false;
	f->stdin = dup(STDIN_FILENO);
	f->stdout = dup(STDOUT_FILENO);
}

int	**create_pipe(int size)
{
	int	i;
	int	**fd;

	i = 0;
	fd = (int **)malloc((size - 1) * sizeof(int *));
	while (i < size - 1)
	{
		fd[i] = (int *)malloc(2 * sizeof(int));
		if (pipe(fd[i]) == -1)
		{
			free_pipes(fd, i);
			return (NULL);
		}
		i++;
	}
	return (fd);
}

void	pipex_init(t_pipex *p, int size)
{
	p->i = 0;
	p->pidn = -1;
	p->fd_count = size - 1;
	p->fd = create_pipe(size);
}
