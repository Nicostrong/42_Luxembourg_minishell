/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:20:52 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 12:39:13 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_free_pipex_array(t_pipex *pipex)
 * </summary>
 *
 * <description>
 * 	ft_free_pipex_array free all array in pipex structure.
 * </description>
 *
 * <param type="t_pipex *" name="pipex">pipex structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_free_pipex_array(t_pipex *pipex)
{
	if (!pipex)
		return ;
	if (pipex->file_in)
		pipex->file_in = ft_free_array(pipex->file_in);
	if (pipex->file_out)
		pipex->file_out = ft_free_array(pipex->file_out);
	if (pipex->a_path)
		pipex->a_path = ft_free_array(pipex->a_path);
	if (pipex->a_cmd_opt)
		pipex->a_cmd_opt = ft_free_array(pipex->a_cmd_opt);
	if (pipex->a_env)
		pipex->a_env = ft_free_array(pipex->a_env);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_free_pipex(t_shell **shell)
 * </summary>
 *
 * <description>
 * 	ft_free_pipex free all element of pipex structure.
 * </description>
 *
 * <param type="t_shell **" name="shell">shell structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_free_pipex(t_shell **shell)
{
	t_pipex	*current;
	t_pipex	*next;

	if (!(*shell)->l_pipex)
		return ;
	current = (*shell)->l_pipex;
	while (current)
	{
		next = current->next;
		if (current->fd_in > 2)
			close(current->fd_in);
		if (current->fd_out > 2)
			close(current->fd_out);
		if (current->limiter)
			ft_free(current->limiter);
		if (current->cmd)
			ft_free(current->cmd);
		if (current->path_cmd)
			ft_free(current->path_cmd);
		ft_free_pipex_array(current);
		ft_free(current);
		current = next;
	}
	(*shell)->l_pipex = NULL;
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_free_pipex_process(t_pipex *pipex)
 * </summary>
 *
 * <description>
 * 	ft_free_pipex_process free all element of pipex structure in a child process
 * </description>
 *
 * <param type="t_pipex *" name="pipex">pipex structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_free_pipex_process(t_pipex *pipex)
{
	t_pipex	*current;
	t_pipex	*next;

	if (!pipex)
		return ;
	current = pipex->shell->l_pipex;
	while (current)
	{
		next = current->next;
		if (current->fd_in > 2)
			close(current->fd_in);
		if (current->fd_out > 2)
			close(current->fd_out);
		if (current->limiter)
			ft_free(current->limiter);
		if (current->cmd)
			ft_free(current->cmd);
		if (current->path_cmd)
			ft_free(current->path_cmd);
		ft_free_pipex_array(current);
		ft_free(current);
		current = next;
	}
	pipex = NULL;
}
