/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:49:04 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/01 14:16:45 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_helper(t_x *x, char ***env, t_flags flags)
{
	char	*cmd;

	cmd = readline("minishell~$ ");
	if (cmd != NULL)
	{
		cmd = exit_status(cmd);
		cmd = control_ex(x, cmd);
		if (x->str_split)
			free_split(x->str_split);
	}
	if (cmd == NULL)
	{
		printf("\n");
		rl_clear_history();
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	else if (*cmd != '\0')
	{
		flag_init(&flags);
		flag_finder(cmd, &flags);
		analize_command(cmd, env, flags, x);
		add_history(cmd);
		free(cmd);
	}
}
