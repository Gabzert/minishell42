/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:46:02 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/18 14:57:25 by gfantech         ###   ########.fr       */
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
		perror("Esecusione fallita");
		free_split(input);
		exit(0);
	}
}

void	analize_command(char *line, char **env, t_flags flags)
{
	char	**inputs;
	int		pid;

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
				execute(inputs, env);
			}
			waitpid(pid, NULL, 0);
			if (flags.write_in == true)
				unlink(".heredoc");
		}
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
	char	*cmd;
	t_flags	flags;

	(void) argc;
	(void) argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	using_history();
	while (1)
	{
		cmd = readline("minishell~$ ");

		//------- variable expansion ----
		cmd = control_ex(cmd);
		// printf("%s\n", cmd);
		
		//---------- ctrl+d -----------
		//------ ritorna un EOF ------- 
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
			analize_command(cmd, env, flags);
			add_history(cmd);
			free(cmd);
		}
	}
	return (0);
}
