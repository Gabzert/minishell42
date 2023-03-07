/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:48:33 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/07 11:17:31 by gfantech         ###   ########.fr       */
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
	while (*input)
	{
		if (*input == '<')
			flags->re_in = true;
		if (*input == '>')
			flags->re_out = true;
		if (*input == '<<')
			flags->write_in = true;
		if (*input == '>>')
			flags->append_out = true;
		if (*input == '|')
			flags->pipe = true;
		if (*input == 39)
			flags->quote = true;
		if (*input == 34)
			flags->d_quote = true;
		input++;
	}
}