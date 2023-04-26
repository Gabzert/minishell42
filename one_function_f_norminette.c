/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_function_f_norminette.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:18:18 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/26 12:19:12 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_command_space_helper(char *str, t_x *x)
{
	while (str[x->j] && str[x->j] == ' ')
		x->j++;
}
