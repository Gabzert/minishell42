/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:20:08 by marvin            #+#    #+#             */
/*   Updated: 2023/05/10 15:20:07 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_input(char **inputs, int i, int *fd, int *diff)
{
	int	check;

	check = 0;
	if (ft_strncmp(inputs[i], "<", ft_strlen(inputs[i])) == 0
		|| ft_strncmp(inputs[i], "<<", ft_strlen(inputs[i])) == 0)
	{
		if (ft_strncmp(inputs[i], "<", ft_strlen(inputs[i])) == 0)
			check = check_fd(fd, inputs[i + 1], IN, false);
		else if (ft_strncmp(inputs[i], "<<", ft_strlen(inputs[i])) == 0)
			take_input(inputs[i + 1], fd);
		*diff += 2;
	}
	else if (ft_strnstr(inputs[i], "<", ft_strlen(inputs[i]))
		|| ft_strnstr(inputs[i], "<<", ft_strlen(inputs[i])))
	{
		if (ft_strnstr(inputs[i], "<<", ft_strlen(inputs[i])))
			take_input(inputs[i] + 2, fd);
		else if (ft_strnstr(inputs[i], "<", ft_strlen(inputs[i])))
			check = check_fd(fd, inputs[i] + 1, IN, false);
		*diff += 1;
	}
	if (check == -1)
		return (-1);
	else
		return (0);
}

static int	find_output(char **inputs, int i, int *fd, int *diff)
{
	int	check;

	check = 0;
	if (ft_strncmp(inputs[i], ">", ft_strlen(inputs[i])) == 0
		|| ft_strncmp(inputs[i], ">>", ft_strlen(inputs[i])) == 0)
	{
		if (ft_strncmp(inputs[i], ">", ft_strlen(inputs[i])) == 0)
			check = check_fd(fd, inputs[i + 1], OUT, false);
		else if (ft_strncmp(inputs[i], ">>", ft_strlen(inputs[i])) == 0)
			check = check_fd(fd, inputs[i + 1], OUT, true);
		*diff += 2;
	}
	else if (ft_strnstr(inputs[i], ">", ft_strlen(inputs[i]))
		|| ft_strnstr(inputs[i], ">>", ft_strlen(inputs[i])))
	{
		if (ft_strnstr(inputs[i], ">>", ft_strlen(inputs[i])))
			check = check_fd(fd, inputs[i] + 2, OUT, true);
		else if (ft_strnstr(inputs[i], ">", ft_strlen(inputs[i])))
			check = check_fd(fd, inputs[i] + 1, OUT, false);
		*diff += 1;
	}
	if (check == -1)
		return (-1);
	else
		return (0);
}

static int	change_inout(char **input, int *diff, int i_o)
{
	int		fd;
	int		i;
	int		check;

	i = 0;
	fd = 0;
	while (input[i])
	{
		if (i_o == IN)
			check = find_input(input, i, &fd, diff);
		else
			check = find_output(input, i, &fd, diff);
		i++;
		if (check == -1)
			return (1);
	}
	if (i_o == IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
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
	new = malloc ((c_size + 1) * sizeof(char *));
	while (++i < split_size(inputs))
	{
		locate_cmd(inputs, &i);
		if (i < split_size(inputs))
		{
			new[j] = ft_strdup(inputs[i]);
			j++;
		}
	}
	free_split(inputs);
	new[j] = NULL;
	return (new);
}

char	**handle_redirect(char **input, t_flags f, bool in_child)
{
	int	diff;
	int	check;

	diff = 0;
	if (f.append_out == false && f.write_in == false
		&& f.re_in == false && f.re_out == false)
		return (input);
	if (f.re_in == true || f.write_in == true)
		check = change_inout(input, &diff, IN);
	if (f.re_out == true || f.append_out == true)
		check = change_inout(input, &diff, OUT);
	if (check == 1)
	{
		free_split(input);
		perror(" ");
		if (in_child)
			exit (1);
		else
		{
			g_sig.g_exit = 1;
			return (NULL);
		}
	}
	return (extract_command(input, diff));
}
