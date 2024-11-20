/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:00:19 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 10:41:30 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_put_error_arg(char *cmd, char *arg, char *msg)
 * </summary>
 *
 * <description>
 * 	ft_put_error_arg print an message error for a bad argument of cmd on STDERR.
 * </description>
 *
 * <param type="char *" name="cmd">command name</param>
 * <param type="char *" name="arg">argument name</param>
 * <param type="char *" name="msg">error message</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_put_error_arg(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd(ERROR_NAME": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd(msg, 2);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_put_errcmd_exit(t_pipex *p, char *cmd, char *arg, char *msg)
 * </summary>
 *
 * <description>
 * 	ft_put_errcmd_exit print an message error for a bad argument of cmd on 
 * 	STDERR and exit with a code error.
 * </description>
 *
 * <param type="t_pipex *" name="p">pipex structure</param>
 * <param type="char *" name="cmd">command name</param>
 * <param type="char *" name="arg">argument name</param>
 * <param type="char *" name="msg">error message</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_put_errcmd_exit(t_pipex *p, char *cmd, char *arg, char *msg)
{
	t_shell	*shell;
	int		err;

	shell = p->shell;
	if (errno)
		err = errno;
	else
		err = shell->code_exit;
	ft_putstr_fd(ERROR_NAME": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': ", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		ft_putendl_fd(strerror(errno), 2);
	ft_free_tokens(&shell);
	ft_free_tree(shell->tree);
	ft_free_pipex_process(shell->l_pipex);
	ft_free_shell(shell);
	rl_clear_history();
	exit(err);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_put_error_cmd(char *cmd, char *msg)
 * </summary>
 *
 * <description>
 * 	ft_put_erro_cmd print an message error for a bad command, 1111 on STDERR.
 * </description>
 *
 * <param type="char *" name="cmd">command name</param>
 * <param type="char *" name="msg">error message</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_put_error_cmd(char *cmd, char *msg)
{
	ft_putstr_fd(ERROR_NAME": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (errno)
		ft_putendl_fd(strerror(errno), 2);
	else
		ft_putendl_fd(msg, 2);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_exit_cmd(t_pipex *p, char *cmd, char *msg)
 * </summary>
 *
 * <description>
 * 	ft_exit_cmd print an message error for a bad command cmd STDERR and
 * 	exit with a code error.
 * </description>
 *
 * <param type="t_pipex *" name="p">pipex structure</param>
 * <param type="char *" name="cmd">command name</param>
 * <param type="char *" name="msg">error message</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_exit_cmd(t_pipex *p, char *cmd, char *msg)
{
	t_shell	*shell;
	int		err;

	shell = p->shell;
	if (errno)
		err = errno;
	else
		err = shell->code_exit;
	ft_putstr_fd(ERROR_NAME": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		ft_putendl_fd(strerror(errno), 2);
	ft_free_tokens(&shell);
	ft_free_tree(shell->tree);
	ft_free_pipex_process(shell->l_pipex);
	ft_free_shell(shell);
	rl_clear_history();
	exit(err);
}
