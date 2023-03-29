/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:46:02 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/29 12:04:51 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_s;

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
		exit_s = 127;
		exit(exit_s);
	}
}

void	analize_command(char *line, char ***env, t_flags flags)
{
	char	**inputs;
	int		pid;
	int		status;

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
		{
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
					exit_s = 2;
				else if (status == 32512 && ft_strnstr(line, "./", 2))
					exit_s = 126;
				else if (status == 32512)
					exit_s = 127;
			}
			if (flags.write_in == true)
				unlink(".heredoc");
		}
	}
}

// ----------- per il ctrl+c ----------
void	sigint_handler(int prova)
{
	(void) prova;
	exit_s = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	t_flags	flags;
	t_x	*x;

	x = (t_x *)malloc(sizeof(t_x));
	if (!x)
		return (0);
	(void) argc;
	(void) argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	using_history();
	while (1)
	{
		cmd = readline("minishell~$ ");
		cmd = exit_status(cmd);
		cmd = control_ex(x, cmd);
		if (cmd == NULL)
		{
			printf("\n");
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		else if (*cmd != '\0')
		{
			flag_init(&flags);
			flag_finder(cmd, &flags);
			analize_command(cmd, &env, flags);
			add_history(cmd);
			free(cmd);
		}
	}
	return (0);
}
