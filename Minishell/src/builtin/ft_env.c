/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:24:30 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 10:12:41 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_print_env(t_env *current, int fd_out)
 * </summary>
 *
 * <description>
 * 	ft_print_env print the key with the value on fd_out.
 * </description>
 *
 * <param type="t_env *" name="current">env node to print</param>
 * <param type="int" name="fd_out">file descriptor for output</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_print_env(t_env *current, int fd_out)
{
	if (!current)
		return ;
	ft_putstr_fd(current->key, fd_out);
	ft_putstr_fd("=", fd_out);
	ft_putendl_fd(current->value, fd_out);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_env(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_env is like the builtin function in bash. It's print all environemment
 *  variables.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">structure pipex</param>
 *
 * <return>
 * 	0 if success or
 * 	1 if error.
 * </return>
 *
 */
int	ft_env(t_pipex **pipex)
{
	char	*value;
	int		fd_out;
	t_env	*current;

	fd_out = STDOUT_FILENO;
	if ((*pipex)->fd_out > 2)
		fd_out = (*pipex)->fd_out;
	value = ft_get_env_value((*pipex)->shell, "PATH");
	if (!(*pipex)->shell->l_env || !value || (*pipex)->a_cmd_opt)
	{
		ft_put_error_cmd((*pipex)->cmd, E_BADFILE);
		if ((*pipex)->fd_out > 2)
			close((*pipex)->fd_out);
		return (127);
	}
	current = (*pipex)->shell->l_env;
	while (current)
	{
		if (current->value)
			ft_print_env(current, fd_out);
		current = current->next;
	}
	if ((*pipex)->fd_out > 2)
		close((*pipex)->fd_out);
	return (0);
}
