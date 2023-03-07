/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:48:33 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/07 12:15:12 by gfantech         ###   ########.fr       */
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
	if (ft_strnstr(input, "<<", ft_strlen(input)))
		flags->write_in = true;
	if (ft_strnstr(input, ">>", ft_strlen(input)))
		flags->append_out = true;
	while (*input)
	{
		if (*input == '<' && flags->write_in == false)
			flags->re_in = true;
		if (*input == '>' && flags->append_out == false)
			flags->re_out = true;
		if (*input == '|')
			flags->pipe = true;
		if (*input == 39 && ft_strchr(input + 1, 39))
			flags->quote = true;
		if (*input == 34 && ft_strchr(input + 1, 34))
			flags->d_quote = true;
		input++;
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
}