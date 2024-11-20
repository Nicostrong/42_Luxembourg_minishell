/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:31:41 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/14 08:44:43 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_create_pipeline(int *pipe_fd, t_pipex *pipex)
 * </summary>
 *
 * <description>
 * 	ft_create_pipeline create a pipeline with the function pipe.
 * </description>
 *
 * <param type="int *" name="pipe_fd">pipe for process communication</param>
 * <param type="t_pipex *" name="pipex">structure pipex</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_create_pipeline(int *pipe_fd, t_pipex *pipex)
{
	if (pipe(pipe_fd) < 0)
		ft_exit_cmd(pipex, "pipe", "pipe error");
	pipex->fd_out = pipe_fd[1];
	if (pipex->next)
		pipex->next->fd_in = pipe_fd[0];
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_create_process(t_pipex *pipex)
 * </summary>
 *
 * <description>
 * 	ft_create_process create a child process.
 * </description>
 *
 * <param type="t_pipex *" name="pipex">structure info</param>
 *
 * <return>
 * 	the pid of the process.
 * </return>
 *
 */
static int	ft_create_process(t_pipex *pipex)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_exit_cmd(pipex, "fork", "fork error");
	return (pid);
}

/*
 * <cat>process</cat>
 *
 * <summary>
 * 	int	ft_wait_pid(int pid)
 * </summary>
 *
 * <description>
 * 	ft_wait_pid wait all children process will ending and return the exit code
 * 	of the last children.
 * </description>
 *
 * <param type="int" name="pid">pid of the process</param>
 *
 * <return>
 * 	the status value of the last process or the code error.
 * </return>
 *
 */
static int	ft_wait_pid(int pid)
{
	int		status_value;
	int		status;

	status_value = -1;
	if (waitpid(pid, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			status_value = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			status_value = WTERMSIG(status);
	}
	while (wait(NULL) > 0)
		;
	return (status_value);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_run_pipex(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_run_pipex execute all bash command in the struct pipex and create an 
 * 	output file with the result if needed.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">structure pipex</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_run_pipex(t_pipex **pipex)
{
	int		pipe_fd[2];
	int		pid;
	int		last_pid;
	t_pipex	*cur;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	last_pid = 0;
	cur = (*pipex);
	while (cur)
	{
		if (!cur->last_cmd)
			ft_create_pipeline(pipe_fd, cur);
		pid = ft_create_process(cur);
		if (pid == 0)
			ft_execute_child(&cur, pipe_fd);
		else
		{
			ft_execute_parent(&cur, pipe_fd);
			last_pid = pid;
		}
		cur = cur->next;
	}
	(*pipex)->shell->code_exit = ft_wait_pid(last_pid);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * void	ft_run_cmd(t_shell **shl)
 * </summary>
 *
 * <description>
 * 	ft_run_cmd call the correct function to run the command.
 * 	if only a builtin function => ft_exec_builtin in current process.
 * 	if a pipeline command => ft_run_pipex with call to fork() function.
 * </description>
 *
 * <param type="t_shell **" name="shell">shell structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_run_cmd(t_shell **shl)
{
	if (!shl || !(*shl))
		return ;
	if (!(*shl)->l_pipex->next && (*shl)->l_pipex->builtin)
		ft_exec_builtin(&(*shl)->l_pipex);
	else
		ft_run_pipex(&(*shl)->l_pipex);
}
