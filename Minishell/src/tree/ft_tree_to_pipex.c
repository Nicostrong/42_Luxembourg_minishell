/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_to_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:48:01 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 13:03:42 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_add_pipex(t_shell **shell, t_pipex *new_pipex)
 * </summary>
 *
 * <description>
 *	ft_add_pipex add a new pipex structure at the end of the linked struct of
 *	pipex.
 * </description>
 *
 * <param type="t_shell **" name="shell">shell structure</param>
 * <param type="t_pipex *" name="new_pipex">new struct pipex</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
static void	ft_add_pipex(t_shell **shell, t_pipex *new_pipex)
{
	t_pipex	*current;

	if (!*shell || !new_pipex)
		return ;
	if (!(*shell)->l_pipex)
		(*shell)->l_pipex = new_pipex;
	else
	{
		current = (*shell)->l_pipex;
		while (current->next)
			current = current->next;
		current->next = new_pipex;
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_tree_to_pipex(t_tree *node, t_shell **shell, t_tree *last_node)
 * </summary>
 *
 * <description>
 *	ft_tree_to_pipex execute the tree with the pipex structure.
 * </description>
 *
 * <param type="t_tree **" name="node">node to parse</param>
 * <param type="t_shell **" name="shell">shell structure</param>
 * <param type="t_tree **" name="last_node">last node</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
void	ft_tree_to_pipex(t_tree *node, t_shell **shell, t_tree *last_node)
{
	t_pipex	*new_pipex;

	if (!node)
		return ;
	if (node->type >= T_PIPE && node->type <= T_AND)
	{
		ft_tree_to_pipex(node->left, shell, NULL);
		ft_tree_to_pipex(node->right, shell, node);
		if (node->next)
			ft_tree_to_pipex(node->next, shell, NULL);
	}
	else
	{
		new_pipex = ft_init_pipex(shell);
		if (!new_pipex)
			return ;
		ft_fill_pipex(node, new_pipex, last_node);
		ft_add_pipex(shell, new_pipex);
	}
}
