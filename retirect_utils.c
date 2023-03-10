/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:20:08 by marvin            #+#    #+#             */
/*   Updated: 2023/03/10 16:41:28 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find(char **inputs, char *str)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		if (ft_strncmp(inputs[i], str, split_size(inputs)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	change_input(char **input, t_flags f)
{
	int	fd;

	if (f.re_in == true)
		fd = open(input[find(input, "<") + 1], O_RDONLY);
	else if (f.write_in == true)
		take_input(input[find(input, "<<") + 1], &fd);
	if (fd == -1)
	{
		perror("errore lettura file");
		exit (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	change_output(char **input, t_flags f)
{
	int	fd;

	if (f.re_out == true)
		fd = open(input[split_size(input) - 1], O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	else if (f.append_out == true)
		fd = open(input[split_size(input) - 1], O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("errore lettura file");
		exit (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
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
	if ((flags.re_in == true || flags.write_in == true) && inputs[0][0] == '<')
		j = 2;
	if (c_size <= 0)
		return (NULL);
	new = malloc ((c_size + 1) * sizeof(char *));
	while (++i < c_size)
	{
		new[i] = ft_strdup(inputs[j]);
		j++;
	}
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
	{
		change_input(input, f);
		diff += 2;
	}
	if (f.re_out == true || f.append_out == true)
	{
		change_output(input, f);
		diff += 2;
	}
	return (extract_command(input, f, diff));
}