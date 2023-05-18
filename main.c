/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:46:02 by gfantech          #+#    #+#             */
/*   Updated: 2023/05/18 11:32:05 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

void	execute(char **input, t_x *x)
{
	char				*cmd;

	if (input == NULL)
		return ;
	if (access(input[0], X_OK) != 0)
	{
		cmd = find_cmd(input[0], x->envp);
		if (cmd == NULL)
		{
			free_split(input);
			free_x_1(&x);
			g_sig.g_exit = 127;
			exit(g_sig.g_exit);
		}
	}
	else
		cmd = input[0];
	if (execve(cmd, input, x->envp) == -1)
	{
		if (!(ft_strnstr(input[0], "$?", 2)))
			perror("Esecusione fallita");
		free_split(input);
		g_sig.g_exit = 127;
		exit(g_sig.g_exit);
	}
}

static void	analize_help(char **inputs, t_flags flags, t_x *x)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		inputs = handle_redirect(inputs, flags, true);
		execute(inputs, x);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (status == 512)
			g_sig.g_exit = 2;
		else if (status == 32512 && ft_strnstr(inputs[0], "./", 2))
			g_sig.g_exit = 126;
		else if (status == 32512)
			g_sig.g_exit = 127;
	}
	if (flags.write_in == true)
		unlink(".heredoc");
}

void	analize_command(char *line, t_flags flags, t_x *x)
{
	char	**inputs;

	inputs = NULL;
	if (flags.pipe == true)
	{
		inputs = ft_split(line, '|');
		pipex(split_size(inputs), inputs, x, flags);
		free_split(inputs);
	}
	else
	{
		inputs = split_cmd(line, flags);
		if (is_builtin(inputs, x, flags) == false)
		{
			if (ft_strncmp(line, "$? ", 3) == 0)
			{
				free_split(inputs);
				return ;
			}
			analize_help(inputs, flags, x);
			free_split(inputs);
		}
	}
}

void	sigint_handler(int prova)
{
	(void) prova;
	g_sig.g_exit = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_clear_history();
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_sig.cmd_run == false)
		rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	t_flags	flags;
	t_x		*x;

	x = (t_x *)malloc(sizeof(t_x));
	if (!x)
		return (0);
	init(x);
	envcpy(env, &x);
	(void) argc;
	(void) argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	using_history();
	while (1)
		main_helper(x, flags);
	return (0);
}
