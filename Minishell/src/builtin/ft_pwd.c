/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:23:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 12:10:27 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_run_cwd(t_pipex **pipex, int fd_out, char *pwd)
 * </summary>
 *
 * <description>
 * 	ft_pwd print just the env variable $PWD or if $PWD not set, call the getcwd
 * 	function to know the currect directory.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">structure pipex</param>
 * <param type="int" name="fd_out">fd for output</param>
 *
 * <return>
 * 	0 if success or 1 if error.
 * </return>
 *
 */
static int	ft_run_cwd(t_pipex **pipex, int fd_out)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
		ft_putendl_fd(cwd, fd_out);
	else
	{
		ft_free(cwd);
		if ((*pipex)->fd_out > 2)
			close((*pipex)->fd_out);
		ft_put_error_cmd((*pipex)->cmd, E_CWD);
		return (1);
	}
	if ((*pipex)->fd_out > 2)
		close((*pipex)->fd_out);
	ft_free(cwd);
	return (0);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_pwd(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_pwd print just the env variable $PWD or if $PWD not set, call the getcwd
 * 	function to know the currect directory.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">structure pipex</param>
 *
 * <return>
 * 	0 if success or 1 if error.
 * </return>
 *
 */
int	ft_pwd(t_pipex **pipex)
{
	char	*pwd;
	int		fd_out;

	pwd = ft_get_env_value((*pipex)->shell, "PWD=");
	fd_out = STDOUT_FILENO;
	if ((*pipex)->fd_out > 2)
		fd_out = (*pipex)->fd_out;
	if (pwd && !access(pwd, F_OK))
		ft_putendl_fd(pwd, fd_out);
	else
	{
		ft_free(pwd);
		return (ft_run_cwd(pipex, fd_out));
	}
	if ((*pipex)->fd_out > 2)
		close((*pipex)->fd_out);
	return (0);
}
