/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:19:19 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/14 08:40:22 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_run_builtin(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_run_builtin call the builtin function and return the exit code of this 
 * 	builtin.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">pipex structure</param>
 *
 * <return>
 * 	1 in case of error or the exit value of the builtin function called.
 * </return>
 *
 */
int	ft_run_builtin(t_pipex **pipex)
{
	if (pipex && *pipex && ft_strequal((*pipex)->cmd, "cd"))
		return (ft_cd(pipex));
	else if (pipex && *pipex && ft_strequal((*pipex)->cmd, "pwd"))
		return (ft_pwd(pipex));
	else if (pipex && *pipex && ft_strequal((*pipex)->cmd, "env"))
		return (ft_env(pipex));
	else if (pipex && *pipex && ft_strequal((*pipex)->cmd, "export"))
		return (ft_export(pipex));
	else if (pipex && *pipex && ft_strequal((*pipex)->cmd, "unset"))
		return (ft_unset(pipex));
	else if (pipex && *pipex && ft_strequal((*pipex)->cmd, "echo"))
		return (ft_echo(pipex));
	else if (pipex && *pipex && ft_strequal((*pipex)->cmd, "exit"))
	{
		if ((*pipex)->fd_out > 2)
			close((*pipex)->fd_out);
		ft_exit((*pipex)->shell, (*pipex)->cmd);
	}
	if (pipex && *pipex && (*pipex)->fd_out > 2)
		close((*pipex)->fd_out);
	return (1);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_get_fd_out_builtin(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_get_fd_out_builtin get the last file descriptor for the output.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">pipex structure</param>
 *
 * <return>
 * 	0 if success or 1 if error.
 * </return>
 *
 */
static int	ft_get_fd_out_builtin(t_pipex **pipex)
{
	char	*file;
	int		index;
	int		fd_out;

	index = 0;
	fd_out = 0;
	while ((*pipex)->file_out && index < (*pipex)->nb_f_out)
	{
		file = (*pipex)->file_out[index];
		if ((*pipex)->append)
			fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
			return (ft_put_error_cmd(file, NULL), 0);
		if ((index + 1) < (*pipex)->nb_f_out)
			close(fd_out);
		index++;
	}
	if (fd_out > 2)
		(*pipex)->fd_out = fd_out;
	else
		(*pipex)->fd_out = STDOUT_FILENO;
	return (1);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_exec_builtin(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_exec_builtin open the output file descriptor if needed and call the 
 * 	builtin function.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">pipex structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_exec_builtin(t_pipex **pipex)
{
	if (pipex && *pipex && (*pipex)->nb_f_out)
		if (!ft_get_fd_out_builtin(pipex))
			return ;
	if (pipex && *pipex && (*pipex)->shell)
		(*pipex)->shell->code_exit = ft_run_builtin(pipex);
}
