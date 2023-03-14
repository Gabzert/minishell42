/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:46:02 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/14 16:29:50 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char **input, char **env)
{
	char	*cmd;

	cmd = find_cmd(input[0], env);
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
		pid = fork();
		if (pid == 0)
		{
			inputs = split_cmd(line, flags);
			inputs = handle_redirect(inputs, flags);
			if (inputs != NULL)
				execute(inputs, env);
		}
		waitpid(pid, NULL, 0);
		if (flags.write_in == true)
			unlink(".heredoc");
	}
}

// ----------- per il ctrl+c ----------
void	sigint_handler(int prova)
{
	(void) prova;
	printf("\n");
	printf("minishell~$ ");
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	t_flags	flags;

	(void) argc;
	(void) argv;
	//------------ ctrl+c -----------
	signal(SIGINT, sigint_handler);
	//------------ ctrl+\ -----------
	signal(SIGQUIT, SIG_IGN);
	using_history();
	while (1)
	{
		cmd = readline("minishell~$ ");
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
