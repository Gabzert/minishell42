/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:42:19 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/24 23:22:13 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h> 
# include <readline/history.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>

typedef struct s_pipex
{
	int	**fd;
	int	fd_count;
	int	pid1;
	int	pid2;
	int	pidn;
	int	i;
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
void	take_input(char *eof, int *file);
int		split_size(char **split);
void	flag_finder(char *input, t_flags *flags);
void	flag_init(t_flags *f);
char	**split_cmd(char *line, t_flags fl);

/*
**	FREE UTILS
*/
void	free_child(char **input, t_pipex *pipe);
void	free_pipes(int **fd, int i);
void	close_pipes(int **fd, int i);
void	free_split(char **a);

/*
**	REDIRECT UTILS
*/
char	**handle_redirect(char **input, t_flags f);
int		change_output(char **input, t_flags f);
int		change_input(char **input, t_flags f);
char	**extract_command(char **inputs, t_flags flags, int diff);

void	pipex(int size, char **inputs, char ***env, t_flags flag);
void	pipex_init(t_pipex *p, int size);

/*
**	BUILTINS
*/
bool	is_builtin(char **inputs, char ***env);
void	unset(char **inputs, char ***env);
void	export(char **inputs, char ***env);

//------------- variable_ex.c --------------
char	*control_ex(char *str);

/* --------------------- variable_ex_helper.c --------------------- */
char	*simple_v(char *var, char *new_str);
char	*not_v(char *new_str, char *str);
char	*split_dollar(char *new_str, char *str);
char	*begin_and_end_with_quote(char *new_str, char *cmd);
char	*begin_with_quote(char *new_str, char *var);
char	*end_with_quote(char *new_str, char *str);
char	*end_with_dquote(char *new_str, char *str);
#endif