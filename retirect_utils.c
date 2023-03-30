/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:20:08 by marvin            #+#    #+#             */
/*   Updated: 2023/03/30 17:29:18 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_input(char **inputs, int i, int *fd, int *diff)
{
	if (ft_strncmp(inputs[i], "<", ft_strlen(inputs[i])) == 0
		|| ft_strncmp(inputs[i], "<<", ft_strlen(inputs[i])) == 0)
	{
		if (*fd != 0)
			close(*fd);
		if (ft_strncmp(inputs[i], "<", ft_strlen(inputs[i])) == 0)
			*fd = open(inputs[i + 1], O_RDONLY);
		else if (ft_strncmp(inputs[i], "<<", ft_strlen(inputs[i])) == 0)
			take_input(inputs[i + 1], fd);
		*diff += 2;
	}
	else if (ft_strnstr(inputs[i], "<", ft_strlen(inputs[i]))
		|| ft_strnstr(inputs[i], "<<", ft_strlen(inputs[i])))
	{
		if (*fd != 0)
			close(*fd);
		if (ft_strnstr(inputs[i], "<<", ft_strlen(inputs[i])))
			take_input(inputs[i] + 2, fd);
		else if (ft_strnstr(inputs[i], "<", ft_strlen(inputs[i])))
			*fd = open(inputs[i] + 1, O_RDONLY);
		*diff += 1;
	}
}

void	find_output(char **inputs, int i, int *fd, int *diff)
{
	if (ft_strncmp(inputs[i], ">", ft_strlen(inputs[i])) == 0
		|| ft_strncmp(inputs[i], ">>", ft_strlen(inputs[i])) == 0)
	{
		if (*fd != 0)
			close(*fd);
		if (ft_strncmp(inputs[i], ">", ft_strlen(inputs[i])) == 0)
			*fd = open(inputs[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (ft_strncmp(inputs[i], ">>", ft_strlen(inputs[i])) == 0)
			*fd = open(inputs[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		*diff += 2;
	}
	else if (ft_strnstr(inputs[i], ">", ft_strlen(inputs[i]))
		|| ft_strnstr(inputs[i], ">>", ft_strlen(inputs[i])))
	{
		if (*fd != 0)
			close(*fd);
		if (ft_strnstr(inputs[i], ">>", ft_strlen(inputs[i])))
			*fd = open(inputs[i] + 2, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (ft_strnstr(inputs[i], ">", ft_strlen(inputs[i])))
			*fd = open(inputs[i] + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		*diff += 1;
	}
}

void	change_inout(char **input, int *diff, int i_o)
{
	int		fd;
	int		i;

	i = 0;
	fd = 0;
	while (input[i])
	{
		if (i_o == IN)
			find_input(input, i, &fd, diff);
		else
			find_output(input, i, &fd, diff);
		i++;
	}
	if (fd == -1)
	{
		perror("errore lettura file");
		exit (0);
	}
	if (i_o == IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

char	**extract_command(char **inputs, int diff)
{
	int		i;
	int		j;
	int		c_size;
	char	**new;

	i = -1;
	j = 0;
	c_size = split_size(inputs) - diff;
	j = locate_cmd(inputs);
	new = malloc ((c_size + 1) * sizeof(char *));
	while (++i < c_size)
	{
		new[i] = ft_strdup(inputs[j]);
		j++;
	}
	new[i] = NULL;
	free_split(inputs);
	return (new);
}

char	**handle_redirect(char **input, t_flags f)
{
	int	diff;

	diff = 0;
	if (f.append_out == false && f.write_in == false
		&& f.re_in == false && f.re_out == false)
		return (input);
	if (f.re_in == true || f.write_in == true)
		change_inout(input, &diff, IN);
	if (f.re_out == true || f.append_out == true)
		change_inout(input, &diff, OUT);
	return (extract_command(input, diff));
}
