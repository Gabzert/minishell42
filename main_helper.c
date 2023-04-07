/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:49:04 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/07 14:38:57 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_x_1(t_x **x)
{
	int	i;

	i = -1;
	if ((*x)->new_split)
		while ((*x)->new_split[++i])
			free((*x)->new_split[i]);
	free((*x)->new_split);
	i = -1;
	if ((*x)->envp)
		while ((*x)->envp[++i])
			free((*x)->envp[i]);
	free((*x)->envp);
	if ((*x)->var)
		free((*x)->var);
	if ((*x)->cmd)
		free((*x)->cmd);
	if ((*x)->new_str)
		free((*x)->new_str);
	free((*x));
}

void	free_x(t_x **x)
{
	int	i;

	i = -1;
	if ((*x)->str_split)
		while ((*x)->str_split[++i])
			free((*x)->str_split[i]);
	free((*x)->str_split);
	i = -1;
	if ((*x)->new_split)
		while ((*x)->new_split[++i])
			free((*x)->new_split[i]);
	free((*x)->new_split);
	i = -1;
	if ((*x)->envp)
		while ((*x)->envp[++i])
			free((*x)->envp[i]);
	free((*x)->envp);
	if ((*x)->var)
		free((*x)->var);
	if ((*x)->new_str)
		free((*x)->new_str);
	free((*x));
}

void	main_helper_1(t_x **x)
{
	if ((*x)->str_split)
		free_split((*x)->str_split);
	(*x)->str_split = NULL;
	(*x)->var = NULL;
}

void	main_helper(t_x *x, char ***env, t_flags flags)
{
	char	*cmd;

	g_sig.cmd_run = false;
	cmd = readline("minishell~$ ");
	if (cmd == NULL)
	{
		printf("\n");
		free(cmd);
		free_x(&x);
		exit(EXIT_SUCCESS);
	}
	else if (*cmd != '\0')
	{
		add_history(cmd);
		g_sig.cmd_run = true;
		cmd = exit_status(cmd);
		cmd = control_ex(x, cmd);
		main_helper_1(&x);
		flag_init(&flags);
		flag_finder(cmd, &flags);
		analize_command(cmd, env, flags, x);
		free(cmd);
		x->new_str = NULL;
	}
}
