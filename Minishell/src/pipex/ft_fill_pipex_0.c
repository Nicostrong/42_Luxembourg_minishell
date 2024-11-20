/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_pipex_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:17:38 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 12:45:51 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_pipex_builtin(t_tree *node, t_pipex *pipex)
 * </summary>
 *
 * <description>
 * 	ft_pipex_builtin fill the pipex structure for the token T_BUILTIN.
 * </description>
 *
 * <param type="t_tree *" name="node">node to extract</param>
 * <param type="t_pipex *" name="pipex">pipex structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_pipex_builtin(t_tree *node, t_pipex *pipex)
{
	pipex->builtin = 1;
	pipex->cmd = ft_strdup(node->value);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_pipex_heredoc(t_tree *node, t_pipex *pipex)
 * </summary>
 *
 * <description>
 * 	ft_pipex_heredoc fill the pipex structure for the token T_HEREDOC.
 * </description>
 *
 * <param type="t_tree *" name="node">node to extract</param>
 * <param type="t_pipex *" name="pipex">pipex structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_pipex_heredoc(t_tree *node, t_pipex *pipex)
{
	pipex->here_doc = 1;
	pipex->ishere_doc = 1;
	pipex->limiter = ft_strdup(node->next->value);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_pipex_fout(t_tree *node, t_pipex *pipex, int append)
 * </summary>
 *
 * <description>
 * 	ft_pipex_fout fill the pipex structure for the token T_F_OUT and 
 * 	T_F_OUT_APPEND.
 * </description>
 *
 * <param type="t_tree *" name="node">node to extract</param>
 * <param type="t_pipex *" name="pipex">pipex structure</param>
 * <param type="int" name="append">boolean for append mode</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_pipex_fout(t_tree *node, t_pipex *pipex, int append)
{
	pipex->file_out = ft_append_str(pipex->file_out, node->next->value);
	pipex->append = append;
	pipex->nb_f_out++;
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_fill_files_pipex_2(t_tree *node, t_pipex *pipex)
 * </summary>
 *
 * <description>
 * 	ft_fill_files_pipex_2 fill all the files node in to the pipex structure.
 * 	next to ft_fill_pipex.
 * </description>
 *
 * <param type="t_tree *" name="node">node to extract</param>
 * <param type="t_pipex *" name="pipex">pipex structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_fill_files_pipex(t_tree *node, t_pipex *pipex)
{
	if (!node)
		return ;
	if (node->type == T_F_IN)
	{
		pipex->file_in = ft_append_str(pipex->file_in, node->next->value);
		pipex->nb_f_in++;
		pipex->ishere_doc = 0;
	}
	else if (node->type == T_HEREDOC)
		ft_pipex_heredoc(node, pipex);
	else if (node->type == T_F_OUT)
		ft_pipex_fout(node, pipex, 0);
	else if (node->type == T_F_OUT_APPEND)
		ft_pipex_fout(node, pipex, 1);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_fill_pipex(t_tree *node, t_pipex *pipex)
 * </summary>
 *
 * <description>
 * 	ft_fill_pipex fill the pipex structure with all node of the commande.
 * </description>
 *
 * <param type="t_tree *" name="node">node to extract</param>
 * <param type="t_pipex *" name="pipex">pipex structure</param>
 * <param type="t_tree *" name="last_node">last_node</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_fill_pipex(t_tree *node, t_pipex *pipex, t_tree *last_node)
{
	while (node)
	{
		if (last_node && last_node->type == T_AND)
			pipex->isand = 1;
		else if (last_node && last_node->type == T_OR)
			pipex->isor = 1;
		if (node->type == T_CMD)
			ft_pipex_cmd(node, pipex);
		else if (node->type == T_BUILTIN)
			ft_pipex_builtin(node, pipex);
		else if (node->type == T_END)
			pipex->last_cmd = 1;
		else if (node->type == T_OPT || \
			(node->type >= T_WORD && node->type < T_END))
			pipex->a_cmd_opt = ft_append_str(pipex->a_cmd_opt, node->value);
		else
			ft_fill_files_pipex(node, pipex);
		node = node->next;
	}
}
