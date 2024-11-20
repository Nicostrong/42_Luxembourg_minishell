/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:22:10 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 12:44:16 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_redirect(t_pipex **pipex, int *pipe_fd)
 * </summary>
 *
 * <description>
 * 	ft_redirect make all redirection of fd_in and fd_out on the structure pipex.
 * 	Or redirect to the pipe fd.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">pipex structure</param>
 * <param type="int *" name="pipe_fd">file descriptor of pipe</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_redirect(t_pipex **pipex, int *pipe_fd)
{
	if ((*pipex)->fd_in > 2)
	{
		dup2((*pipex)->fd_in, STDIN_FILENO);
		close((*pipex)->fd_in);
	}
	if ((*pipex)->fd_out > 2)
	{
		dup2((*pipex)->fd_out, STDOUT_FILENO);
		if ((*pipex)->fd_out != pipe_fd[1])
			close((*pipex)->fd_out);
	}
	else if ((*pipex)->next)
		dup2(pipe_fd[1], STDOUT_FILENO);
	if (pipe_fd[0] > 2)
		close(pipe_fd[0]);
	if (pipe_fd[1] > 2 && (*pipex)->fd_out != pipe_fd[1])
		close(pipe_fd[1]);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_execute_child(t_pipex **pipex, int *pipe_fd)
 * </summary>
 *
 * <description>
 * 	ft_execute_child make all redirection and execute the commande on the child
 * 	process.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">pipex structure</param>
 * <param type="int *" name="pipe_fd">file descriptor of pipe</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_execute_child(t_pipex **pipex, int *pipe_fd)
{
	ft_get_fd_in_out(pipex);
	ft_redirect(pipex, pipe_fd);
	if ((*pipex)->builtin)
	{
		ft_exec_builtin(pipex);
		exit((*pipex)->shell->code_exit);
	}
	else
	{
		execve((*pipex)->path_cmd, (*pipex)->a_cmd_opt, (*pipex)->a_env);
		(*pipex)->shell->code_exit = 127;
		ft_exit_cmd(*pipex, (*pipex)->cmd, E_CMD);
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_execute_parent(t_pipex **pipex, int *pipe_fd))
 * </summary>
 *
 * <description>
 * 	ft_execute_parent close all file descriptor and redirect le pipe_fd[0] in 
 * 	the next structure.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">pipex structure</param>
 * <param type="int *" name="pipe_fd">file descriptor of pipe</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_execute_parent(t_pipex **pipex, int *pipe_fd)
{
	if (pipe_fd[1] > 2)
		close(pipe_fd[1]);
	if ((*pipex)->fd_in > 2)
		close((*pipex)->fd_in);
	if ((*pipex)->fd_out > 2)
		close((*pipex)->fd_out);
	if ((*pipex)->next && !(*pipex)->next->file_in)
		(*pipex)->next->fd_in = pipe_fd[0];
	else if (pipe_fd[0] > 2)
		close(pipe_fd[0]);
}
