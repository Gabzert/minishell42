/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:20:08 by marvin            #+#    #+#             */
/*   Updated: 2023/03/08 11:20:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_input(char **input, t_flags f)
{
	int	fd;

	if (f.re_in == true || f.write_in == true)
	{
		if (f.re_in == true)
			fd = open(input[1], O_RDONLY);
		else if (f.write_in == true)
			take_input(input[1], &fd);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	change_output(char **input, t_flags f)
{
	int	fd;

	if (f.re_out == true || f.append_out == true)
	{
		if (f.re_out == true)
			fd = open(input[split_size(input)], O_WRONLY | O_CREAT, 0644);
		else if (f.append_out == true)
			fd = open(input[split_size(input)], O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

char	**extract_command(char **inputs, t_flags flags)
{
	int		i;
	int		j;
	int		c_size;
	char	**new;

	i = 0;
	j = 0;
	c_size = split_size(inputs);
	if (flags.re_in == true || flags.write_in == true)
	{
		c_size -= 2;
		j = 2;
	}
	if (flags.re_out == true || flags.append_out == true)
		c_size -= 2;
	new = malloc (c_size * sizeof(char *));
	while (j <= c_size)
	{
		ft_strcpy(new[i], inputs[j]);
		i++;
		j++;
	}
	free_split(inputs);
	return(new);
}

char	**handle_redirect(char **input, t_flags f)
{
	if (f.append_out == false && f.write_in == false
		&& f.re_in == false && f.re_out == false)
		return (input);
	change_input(input, f);
	change_output(input, f);
	return (extract_command(input, f));
}