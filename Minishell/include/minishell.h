/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:46:06 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/20 09:33:32 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
 *	Standart library
 */

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

/*
 *	Personal Library
 */

# include "../library/libft/libft.h"
# include "../library/gnl/get_next_line.h"
# include "error.h"

/*
 *	Define
 */

# define TERM_NAME	"\033[0;34mmini$\033[0;31m[🔥🔥🔥HELL🔥🔥🔥]$ \033[0m"

/*
 *	Externe variable
 */

extern char	**environ;

/*
 *	Global variable
 */

extern int	g_status;

/*
 *	Enum
 */

typedef enum e_token_type
{
	T_BUILTIN,			//	builtin			=	0	=>	echo , cd, env, ...
	T_CMD,				//	cmd				=	1	=>	exc
	T_OPT,				//	option			=	2	=>	-alpha
	T_PIPE,				//	pipe			=	3	=>	|
	T_OR,				//	or logical		=	4	=>	||
	T_AND,				//	and logical		=	5	=>	&&
	T_F_IN,				//	file in			=	6	=>	<
	T_F_OUT,			//	file out		=	7	=>	>
	T_F_OUT_APPEND,		//	file out append	=	8	=>	>>
	T_HEREDOC,			//	heredoc mod		=	9	=>	<<
	T_EOF,				//	limiter			=	10	=>	word
	T_FILENAME,			//	file name		=	11	=>	word
	T_SUBSHELL,			//	subshell		=	12	=>	( ou )
	T_WORD,				//	word			=	13	=>	to print
	T_DQUOTE,			//	double quote	=	14	=>	"
	T_SQUOTE,			//	simple quote	=	15	=>	'
	T_END,				//	end				=	16	=>	end of command
}	t_tok_type;

/*
 *	Structure
 */

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	t_tok_type		type;
	char			*value;
	struct s_token	*next;
}	t_token;	

typedef struct s_tree
{
	t_tok_type		type;
	char			*value;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*next;
}	t_tree;

typedef struct s_pipex
{
	int				last_status;		//	code retour last commande
	int				append;				//	bool (>>)
	int				here_doc;			//	bool (<<)
	int				builtin;			//	bool builtin function
	int				squote;				//	bool simple quote
	int				isand;				//	bool &&
	int				isor;				//	bool ||
	int				last_cmd;			//	bool last command
	int				ishere_doc;			//	bool here_doc last input file
	int				is_after_sub;		//	bool is after subshell
	int				nb_f_in;			//	number of file input
	int				nb_f_out;			//	number of file out
	int				fd_in;				//	file in
	int				fd_out;				//	file out
	char			*limiter;			//	limiter EOF
	char			*cmd;				//	commande input
	char			*path_cmd;			//	path of the command
	char			**file_in;			//	array of fichier in
	char			**file_out;			//	array of fichier out
	char			**a_path;			//	array of all path in $PATH
	char			**a_cmd_opt;		//	array for execve->arg[1]
	char			**a_env;			//	array for execve->arg[2]
	struct s_shell	*shell;				//	shell structure
	struct s_pipex	*next;				//	next command
}	t_pipex;

typedef struct s_shell
{
	t_env		*l_env;
	t_token		*l_token;
	t_tree		*tree;
	t_pipex		*l_pipex;
	int			code_exit;
	int			sub_exit;
	int			sub_fd;
	int			cmd;
}	t_shell;

/*
 *	Buildin
 */

int			ft_run_builtin(t_pipex **pipex);

void		ft_exec_builtin(t_pipex **pipex);

	/*
	 *	echo
	 */

int			ft_echo(t_pipex **pipex);

	/*
	 *	env
	 */

int			ft_env(t_pipex **pipex);
int			ft_is_key(t_env *env, char *key);

char		*ft_get_env_value(t_shell *shell, char *key);

void		ft_set_env_value(t_shell **shell, char *key, char *value);

	/*
	 *	exit
	 */

void		ft_exit_ctrl_d(t_shell *shell);
void		ft_exit(t_shell *shell, char *cmd);

	/*
	 *	export
	 */

int			ft_valid_key(char *key);
int			ft_export(t_pipex **pipex);
int			ft_check_key(t_env *env, char *key);
int			ft_print_export_env(t_shell *shell, int fd_out);

char		**ft_get_all_key(t_env *env, int count);

void		ft_export_value(t_shell **shell, char *key_val);

	/*
	 *	cd
	 */

int			ft_cd(t_pipex **pipex);

	/*
	 *	pwd
	 */

int			ft_pwd(t_pipex **pipex);

	/*
	 *	unset
	 */

int			ft_unset(t_pipex **pipex);

/*
 *	token
 */

void		ft_pass_char(char *str, int *i);
void		ft_tok_file_in(char *input, int *i, t_token **toks);
void		ft_tok_file_out(char *input, int *i, t_token **toks);
void		ft_tok_operator(char *input, int *i, t_token **toks, t_shell **shl);
void		ft_tok_subshell(char *input, int *i, t_token **toks);
void		ft_tok_d_s_quote(char *input, int *i, t_token **toks);
void		ft_append_token(t_token **head, t_tok_type type, char *value);
void		ft_tok_word(char *input, int *i, t_token **toks, t_shell **shell);

t_token		*ft_parse_cmd(char *input, t_shell *shell);

/*
 *	tree
 */

void		ft_handle_option(t_token **cur, t_tree **parent);
void		ft_handle_cmd(t_token **cur, t_tree **head, t_tree **parent);
void		ft_handle_quote(t_token **cur, t_tree **parent, t_shell *shell);
void		ft_tree_to_pipex(t_tree *node, t_shell **shell, t_tree *last_node);
void		ft_handle_word(t_token **cur, t_tree **head, t_tree **parent, \
							t_shell *shell);
void		ft_handle_sub(t_token **cur, t_tree **head, t_tree **parent, \
							t_shell *shl);
void		ft_handle_file(t_token **cur, t_tree **head, t_tree **parent, \
							t_shell *shell);

t_tree		*ft_parse_heredoc(t_token **tokens);
t_tree		*ft_create_node_tree(t_tok_type type, char *value);
t_tree		*ft_parse_subshell(t_token **tokens, t_shell *shell);
t_tree		*ft_parse_token_to_tree(t_token **tokens, t_shell *shell);
t_tree		*ft_handle_pp_or_and(t_token **cur, t_tree **head, t_shell *shell);

/*
 *	pipex
 */

char		*ft_concat_path_cmd(t_env *env, char *cmd);

char		**ft_get_path(t_env *env);
char		**ft_create_env_array(t_env *env);

void		ft_run_cmd(t_shell **shell);
void		ft_run_here_doc(t_pipex **pipex);
void		ft_get_fd_in_out(t_pipex **pipex);
void		ft_pipex_cmd(t_tree *node, t_pipex *pipex);
void		ft_execute_child(t_pipex **pipex, int *pipe_fd);
void		ft_execute_parent(t_pipex **pipex, int *pipe_fd);
void		ft_fill_pipex(t_tree *node, t_pipex *pipex, t_tree *last_node);

t_pipex		*ft_init_pipex(t_shell **shell);

/*
 *	utils
 */

int			ft_check_file(char *cmd, char c);
int			ft_check_nb_wilcard(char *pattern);
int			ft_check_patern(char *patern, char *str);
int			ft_check_syntax_input(char *cmd, t_shell *shell);

char		*ft_parse_string(char *string, t_shell *shell);
char		*ft_replace_variable(char *new, char *key, t_shell *shell);
char		*ft_add_static_text(char *new, char *string, int start, int end);

char		**ft_wilcard(char *input);

void		ft_signal(void);
void		ft_print_error(char *cmd);
void		ft_replace_var(char *string, char *new, int *start, t_shell *shell);

t_env		*ft_add_node(t_env *env, char *key, char *value);

t_shell		*ft_init_shell(void);

/*
 *	error
 */

void		ft_put_error_cmd(char *cmd, char *msg);
void		ft_put_error_arg(char *cmd, char *arg, char *msg);
void		ft_exit_cmd(t_pipex *pipex, char *cmd, char *msg);
void		ft_put_errcmd_exit(t_pipex *pipex, char *cmd, char *arg, char *msg);

/*
 *	free
 */

void		ft_free_env(t_env *env);
void		ft_free_tree(t_tree *tree);
void		ft_free_cmd(t_shell **shell);
void		ft_free_shell(t_shell *shell);
void		ft_free_pipex(t_shell **shell);
void		ft_free_tokens(t_shell **shell);
void		ft_free_pipex_process(t_pipex *pipex);

/*
 *	DEBUG
 */

char		*ft_get_token_name(t_tok_type token);

void		ft_print_all(t_shell *shell);
void		ft_print_all_pipex(t_pipex *pipex);
void		ft_print_pipex(t_pipex *pipex, int i);

#endif
