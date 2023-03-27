/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:42:19 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/27 11:55:45 by gfantech         ###   ########.fr       */
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

# define IN 1
# define OUT 0

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

typedef struct s_size
{
	int		i;
	int		j;
	int		size_cmd;
	int		size_full;
	char	*cmd;
	char	*var;
}	t_size;

typedef struct s_x
{
	int		size_for_malloc;
	int		i; //? index
	int		j; //? index
	int		y; //? helper index
	int		case_1; //? the case where we have "''"
	int		case_2; //? the case where we have '""'
	int		case_3; //? 
	int		case_4; //? know am after a '
	int		case_5; //? where you have this struct '"$USER"'
	int		case_qdq;
	int		start;
	int		bk;
	char	*var; // variable to be expanded
	char	*cmd; // hold the value of the variable expanded
	char	*new_str; // final string to be returned
	char	**str_split;
	char	**new_split;
}	t_x;

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
void	change_inout(char **input, int *diff, int i_o);
char	**extract_command(char **inputs, t_flags flags, int diff);

void	pipex(int size, char **inputs, char ***env, t_flags flag);
void	pipex_init(t_pipex *p, int size);

/*
**	BUILTINS
*/
bool	is_builtin(char **inputs, char ***env);
void	echo(char **inputs);
void	l_env(char **env);
void	unset(char **inputs, char ***env);
void	export(char **inputs, char ***env);

//------------- variable_ex.c --------------
char	*control_ex(char *str);

/* --------------------- variable_ex_helper.c --------------------- */
char	*begin_and_end_with_quote(char *new_str, char *cmd);
char	*begin_with_quote(char *new_str, char *var);
char	*end_with_quote(char *new_str, char *str);
char	*end_with_dquote(char *new_str, char *str);

/* --------------------- variable_ex_helper_1.c --------------------- */
void	init(t_x *x);
int		full_size(char *str);
char	*simple_v(char *var, char *new_str);
char	*not_v(char *new_str, char *str);
char	*split_dollar(char *new_str, char *str);




/* ------------------------- variable_ex_process_1.c ------------------------ */
void	add_command(t_x *x);
void	check_for_dq_and_qd_helper(t_x *x);
void	check_for_dq_and_qd(t_x *x);
void	add_q_s(t_x *x);
void	add_cmd_q_c3(t_x *x);

/* ------------------------- variable_ex_process_2.c ------------------------ */
void	begin_w_q_c3(t_x *x);
void	clean_var(t_x *x);
void	remove_last_q_add_q(t_x *x);
void	case_3_helper(t_x *x);
void	case_1_helper(t_x *x);

/* ------------------------- variable_ex_process_3.c ------------------------ */
void	add_var(t_x *x);
void	add_q_var_c3(t_x *x);
void	remove_lase_dq_add_dq(t_x *x);
void	case_1_helper_0(t_x *x);
void	helper_dq_2(t_x *x);

/* ------------------------- variable_ex_process_4.c ------------------------ */
void	helper_dq_1(t_x *x);
void	helper_dq_d(t_x *x);
void	helper_d(t_x *x);
void	helper_q_c(t_x *x);
void	add_cmd_with_fq_or_with_flq(t_x *x);

/* ------------------------- variable_ex_process_5.c ------------------------ */
void	case_1_and_dollar_and_quote(t_x *x);
void	clear_case_1_and_dollar(t_x *x);
void	dq_with_var(t_x *x);
void	quote(t_x *x);
void	identify_start_dq_q(t_x *x);

/* ------------------------- variable_ex_process_6.c ------------------------ */
void	identify_end_dq_q(t_x *x);
void	identify_start_q_dq(t_x *x);
void	identify_end_q_dq(t_x *x);
void	identify(t_x *x);
void	helper_dq_var(t_x *x);

/* ------------------------- variable_ex_process_7.c ------------------------ */
void	case_31_helper(t_x *x);
void	case_11_helper(t_x *x);
void	helper_1(t_x *x);
void	helper_2(t_x *x);
void	helper_3(t_x *x);

#endif