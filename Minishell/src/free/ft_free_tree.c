/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:12:37 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/07 13:43:12 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_free_tree(t_tree *tree)
 * </summary>
 *
 * <description>
 * 	ft_free_tree free the complete tree of tokens.
 * </description>
 *
 * <param type="t_tree *" name="tree">tree AST of tokens</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		ft_free_tree(tree->left);
	if (tree->right)
		ft_free_tree(tree->right);
	if (tree->next)
		ft_free_tree(tree->next);
	if (tree->value)
		ft_free(tree->value);
	if (tree)
		ft_free(tree);
}
