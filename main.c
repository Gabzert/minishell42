/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:46:02 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/30 15:43:24 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	sig;

void	execute(char **input, char **env)
{
	char				*cmd;

	if (input == NULL)
		return ;
	if (access(input[0], X_OK) != 0)
		cmd = find_cmd(input[0], env);
	else
		cmd = input[0];
	if (execve(cmd, input, env) == -1)
	{
		if (!(ft_strnstr(input[0], "$?", 2)))
			perror("Esecusione fallita");
		free_split(input);
		sig.g_exit = 127;
		exit(sig.g_exit);
	}
}

static void	analize_help(char **inputs, char *line, char ***env, t_flags flags)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		inputs = handle_redirect(inputs, flags);
		execute(inputs, *env);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (status == 512)
			sig.g_exit = 2;
		else if (status == 32512 && ft_strnstr(line, "./", 2))
			sig.g_exit = 126;
		else if (status == 32512)
			sig.g_exit = 127;
	}
	if (flags.write_in == true)
		unlink(".heredoc");
}

void	analize_command(char *line, char ***env, t_flags flags)
{
	char	**inputs;

	if (flags.pipe == true)
	{
		inputs = ft_split(line, '|');
		pipex(split_size(inputs), inputs, env, flags);
		free_split(inputs);
	}
	else
	{
		inputs = split_cmd(line, flags);
		if (is_builtin(inputs, env) == false)
			analize_help(inputs, line, env, flags);
	}
}

// ----------- per il ctrl+c ----------
void	sigint_handler(int prova)
{
	(void) prova;
	sig.g_exit = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_clear_history();
	rl_on_new_line();
	rl_replace_line("", 0);
	if (sig.cmd_run == false)
		rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	t_flags	flags;
	t_x		*x;

	x = (t_x *)malloc(sizeof(t_x));
	if (!x)
		return (0);
	(void) argc;
	(void) argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	using_history();
	while (1)
		main_helper(x, &env, flags);
	return (0);
}
