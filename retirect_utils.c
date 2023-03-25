/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:20:08 by marvin            #+#    #+#             */
/*   Updated: 2023/03/24 17:26:45 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find(char **inputs, int i, int *fd, int *diff)
{
	if (ft_strncmp(inputs[i], "<", ft_strlen(inputs[i])) == 0 || ft_strncmp(inputs[i], "<<", ft_strlen(inputs[i])) == 0)
	{
		if (ft_strncmp(inputs[i], "<", ft_strlen(inputs[i])) == 0)
			*fd = open(inputs[i + 1], O_RDONLY);
		else if (ft_strncmp(inputs[i], "<<", ft_strlen(inputs[i])) == 0)
			take_input(inputs[i + 1], fd);
		*diff += 2;
	}
	else if (ft_strnstr(inputs[i], "<", ft_strlen(inputs[i])) || ft_strnstr(inputs[i], "<<", ft_strlen(inputs[i])))
	{
		if (ft_strnstr(inputs[i], "<<", ft_strlen(inputs[i])))
			take_input(inputs[i] + 2, fd);
		else if (ft_strnstr(inputs[i], "<", ft_strlen(inputs[i])))
			*fd = open(inputs[i] + 1, O_RDONLY);
		*diff += 1;
	}
}

int	change_input(char **input, t_flags f)
{
	int		fd;
	int		diff;
	int		i;

	diff = 0;
	i = 0;
	fd = 0;
	while (inputs[i])
	{
		if (fd != 0)
			close(fd);
		find(input, i, &fd, &diff);
		i++;
	}
	if (fd == -1)
	{
		perror("errore lettura file");
		exit (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (diff);
}

int	change_output(char **input, t_flags f)
{
	int	fd;
	int	diff;

	diff = 0;
	if (f.re_out == true)
		fd = open(find(input, ">", &diff), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (f.append_out == true)
		fd = open(find(input, ">>", &diff), O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("errore lettura file");
		exit (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (diff);
}

char	**extract_command(char **inputs, t_flags flags, int diff)
{
	int		i;
	int		j;
	int		c_size;
	char	**new;

	i = -1;
	j = 0;
	c_size = split_size(inputs) - diff;
	if (flags.re_in == true || flags.write_in == true)
	{
		if (ft_strncmp(inputs[0], "<", ft_strlen(inputs[0])) == 0)
			j = 2;
		else
			j = 1;
	}
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
		diff += change_input(input, f);
	if (f.re_out == true || f.append_out == true)
		diff += change_output(input, f);
	return (extract_command(input, f, diff));
}
