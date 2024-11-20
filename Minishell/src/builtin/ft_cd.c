/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:22:28 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 10:14:51 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_exec_cd(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_exec_cd change the directory and update somes env.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">pipex structure</param>
 *
 * <return>
 * 	0 if success or 1 if error.
 * </return>
 *
 */
static int	ft_exec_cd(t_pipex **pipex)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ft_get_env_value((*pipex)->shell, "PWD");
	if (chdir((*pipex)->a_cmd_opt[0]) == -1)
	{
		ft_put_error_arg((*pipex)->cmd, (*pipex)->a_cmd_opt[0], E_BADFILE);
		return (1);
	}
	if (old_pwd)
		ft_set_env_value(&(*pipex)->shell, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
		ft_set_env_value(&(*pipex)->shell, "PWD", new_pwd);
	ft_free(new_pwd);
	return (0);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_go_home(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_go_home change the directory to the home directory and update somes env.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">pipex structure</param>
 *
 * <return>
 * 	0 if success or 1 if error.
 * </return>
 *
 */
static int	ft_go_home(t_pipex **pipex)
{
	char	*home;
	char	*oldpwd;

	home = ft_get_env_value((*pipex)->shell, "HOME");
	if (!home || chdir(home) == -1)
	{
		ft_put_error_cmd((*pipex)->cmd, E_HOME);
		return (1);
	}
	oldpwd = ft_get_env_value((*pipex)->shell, "PWD");
	if (oldpwd)
		ft_set_env_value(&(*pipex)->shell, "OLDPWD", oldpwd);
	if (home)
		ft_set_env_value(&(*pipex)->shell, "PWD", home);
	return (0);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_go_back(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_go_back change the directory to the oldpwd directory and update somes env.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">pipex structure</param>
 *
 * <return>
 * 	0 if success or 1 if error.
 * </return>
 *
 */
static int	ft_go_back(t_pipex **pipex)
{
	char	*old_pwd;
	char	*pwd;

	pwd = ft_strdup(ft_get_env_value((*pipex)->shell, "PWD"));
	old_pwd = ft_strdup(ft_get_env_value((*pipex)->shell, "OLDPWD"));
	if (!old_pwd || chdir(old_pwd) == -1)
	{
		ft_put_error_cmd((*pipex)->cmd, E_OLDPWD);
		return (ft_free(pwd), ft_free(old_pwd), 1);
	}
	if ((*pipex)->fd_out > 2)
	{
		ft_putendl_fd(old_pwd, (*pipex)->fd_out);
		close((*pipex)->fd_out);
	}
	else
		ft_putendl_fd(old_pwd, STDOUT_FILENO);
	ft_set_env_value(&(*pipex)->shell, "OLDPWD", pwd);
	ft_set_env_value(&(*pipex)->shell, "PWD", old_pwd);
	return (ft_free(pwd), ft_free(old_pwd), 0);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_cd(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_cd is like a bultin function cd in bash. It's checking the number of 
 * 	argument and call a different function compared to argument list.
 * 	It's change the directory.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">structure pipex</param>
 *
 * <return>
 * 	0 if success or a code error.
 * </return>
 *
 */
int	ft_cd(t_pipex **pipex)
{
	if ((*pipex)->a_cmd_opt && (*pipex)->a_cmd_opt[0] && (*pipex)->a_cmd_opt[1])
	{
		ft_put_error_cmd((*pipex)->cmd, E_ARG);
		return (1);
	}
	else if (!(*pipex)->a_cmd_opt || ft_strequal((*pipex)->a_cmd_opt[0], "~")
		|| ft_strequal((*pipex)->a_cmd_opt[0], "--"))
		return (ft_go_home(pipex));
	else if ((*pipex)->a_cmd_opt && ft_strequal((*pipex)->a_cmd_opt[0], "-"))
		return (ft_go_back(pipex));
	else if ((*pipex)->a_cmd_opt[0])
		return (ft_exec_cd(pipex));
	else
		return (ft_go_home(pipex));
}
