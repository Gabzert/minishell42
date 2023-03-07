/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:42:19 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/07 11:16:38 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_pipex
{
	int	**fd;
	int	fd_count;
	int	pid1;
	int	pid2;
	int	pidn;
	int	i;
	int	here_doc;
}	t_pipex;

typedef struct s_flags
{
	bool	re_in;
	bool	re_out;
	bool	write_in;
	bool	append_out;
	bool	pipe;
	bool	quote;
	bool	d_quote;
}	t_flags;

char	*find_path(char **env);
char	*find_cmd(char *cmd, char **env);
void	free_child(char **input, t_pipex *pipe);
void	take_input(char *eof, int *file);

void	close_pipes(int **fd, int i);
void	free_pipes(int **fd, int i);
int		split_size(char **split);
void	flag_finder(char *input, t_flags *flags);
#endif