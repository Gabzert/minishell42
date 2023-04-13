/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_process_9.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:03:08 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/13 17:21:43 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case_31_helper_wa7ed(t_x *x)
{
	new_join(x, x->str_split[x->i]);
	new_join(x, " ");
}

void	case_11_helper_wa7ed(t_x *x)
{
	char	*new;

	new = ft_strtrim(x->str_split[x->i], "\'");
	new_join(x, new);
	new_join(x, " ");
	free(new);
}

void	case_11_helper_tnen(t_x *x)
{
	new_join(x, "\1\"");
	new_join(x, " ");
}

void	case_11_helper_tlate(t_x *x)
{
	new_join(x, x->str_split[x->i]);
	new_join(x, " ");
}
