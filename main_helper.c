/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:49:04 by naal-jen          #+#    #+#             */
/*   Updated: 2023/03/30 15:43:20 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_helper(t_x *x, char ***env, t_flags flags)
{
	char	*cmd;

	sig.cmd_run = false;
	cmd = readline("minishell~$ ");
	if (cmd == NULL)
	{
		printf("\n");
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	else if (*cmd != '\0')
	{
		sig.cmd_run = true;
		cmd = exit_status(cmd);
		cmd = control_ex(x, cmd);
		flag_init(&flags);
		flag_finder(cmd, &flags);
		analize_command(cmd, &env, flags);
		add_history(cmd);
		free(cmd);
	}
}