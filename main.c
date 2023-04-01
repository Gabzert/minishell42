/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:46:02 by gfantech          #+#    #+#             */
/*   Updated: 2023/04/01 14:06:40 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

void	execute(char **input, char **env)
{
	char	*cmd;

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
		g_exit = 127;
		exit(g_exit);
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
			g_exit = 2;
		else if (status == 32512 && ft_strnstr(line, "./", 2))
			g_exit = 126;
		else if (status == 32512)
			g_exit = 127;
	}
	if (flags.write_in == true)
		unlink(".heredoc");
}

void	analize_command(char *line, char ***env, t_flags flags, t_x *x)
{
	char	**inputs;

	inputs = NULL;
	if (flags.pipe == true)
	{
		inputs = ft_split(line, '|');
		pipex(split_size(inputs), inputs, env, flags);
		free_split(inputs);
	}
	else
	{
		inputs = split_cmd(line, flags);
		if (is_builtin(inputs, env, x) == false)
			analize_help(inputs, line, env, flags);
		free_split(inputs);
	}
}

// ----------- per il ctrl+c ----------
void	sigint_handler(int prova)
{
	(void) prova;
	g_exit = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
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
