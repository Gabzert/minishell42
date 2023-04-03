/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:49:04 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/02 13:57:20 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_helper(t_x *x, char ***env, t_flags flags)
{
	char	*cmd;

	g_sig.cmd_run = false;
	cmd = readline("minishell~$ ");
	if (cmd == NULL)
	{
		printf("\n");
		rl_clear_history();
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	else if (*cmd != '\0')
	{
		g_sig.cmd_run = true;
		cmd = exit_status(cmd);
		cmd = control_ex(x, cmd);
		if (x->str_split)
			free_split(x->str_split);
		flag_init(&flags);
		flag_finder(cmd, &flags);
		analize_command(cmd, env, flags, x);
		add_history(cmd);
		free(cmd);
	}
}
