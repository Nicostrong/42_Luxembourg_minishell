/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:56:16 by phkevin           #+#    #+#             */
/*   Updated: 2024/11/08 13:25:17 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	t_tree	*ft_handle_pp_or_and(t_token **cur, t_tree **head, t_shell *shell)
 * </summary>
 *
 * <description>
 *	ft_handle_pp_or_and create a tree node for the T_PIPE or the T_OR or the 
 *	T_AND token.
 * </description>
 *
 * <param type="t_token **" name="cur">current token</param>
 * <param type="t_tree **" name="head">head of the tree</param>
 * <param type="t_shell *" name="shl">shell structure</param>
 *
 * <return>
 *	a pointer to a new node for the pipe or 'or' or 'and' token.
 * </return>
 *
 */
t_tree	*ft_handle_pp_or_and(t_token **cur, t_tree **head, t_shell *shell)
{
	t_tree	*new_node;

	new_node = ft_create_node_tree((*cur)->type, NULL);
	new_node->left = *head;
	*cur = (*cur)->next;
	if (*cur)
	{
		new_node->right = ft_parse_token_to_tree(cur, shell);
		*head = new_node;
	}
	return (*head);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_handle_file(t_token **cur, t_tree **head, t_tree **parent, \
 *							t_shell *shl)
 * </summary>
 *
 * <description>
 *	ft_handle_file create a tree node for the T_F_IN, T_F_OUT or T_F_OUT_APPEND 
 *	token.
 * </description>
 *
 * <param type="t_token **" name="cur">current token</param>
 * <param type="t_tree **" name="head">head of the tree</param>
 * <param type="t_tree **" name="parent">parent node of this node</param>
 * <param type="t_shell *" name="shl">shell structure</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
void	ft_handle_file(t_token **cur, t_tree **head, t_tree **par, t_shell *shl)
{
	char	*value;	
	t_tree	*new_node;

	new_node = ft_create_node_tree((*cur)->type, NULL);
	*cur = (*cur)->next;
	if (*cur && ((*cur)->type == T_FILENAME || (*cur)->type == T_DQUOTE))
	{
		value = ft_parse_string((*cur)->value, shl);
		new_node->next = ft_create_node_tree(T_FILENAME, value);
		*cur = (*cur)->next;
		ft_free(value);
	}
	if (!*head)
		*head = new_node;
	else
		(*par)->next = new_node;
	*par = new_node->next;
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void ft_handle_sub(t_token **cur, t_tree **head, t_tree **par, t_shell *shl)
 * </summary>
 *
 * <description>
 *	ft_handle_sub create a tree node for the T_SUBSHELL token.
 * </description>
 *
 * <param type="t_token **" name="cur">current token</param>
 * <param type="t_tree **" name="head">head of the tree</param>
 * <param type="t_tree **" name="par">parent node of this node</param>
 * <param type="t_shell *" name="shl">shell structure</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
void	ft_handle_sub(t_token **cur, t_tree **head, t_tree **par, t_shell *shl)
{
	t_tree	*new_node;

	new_node = ft_parse_subshell(cur, shl);
	if (!*head)
		*head = new_node;
	else
		(*par)->next = new_node;
	*par = new_node;
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_handle_option(t_token **cur, t_tree **parent)
 * </summary>
 *
 * <description>
 *	ft_handle_option create a tree node for the T_OPT token.
 * </description>
 *
 * <param type="t_token **" name="cur">current token</param>
 * <param type="t_tree **" name="parent">parent node of this node</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
void	ft_handle_option(t_token **cur, t_tree **parent)
{
	t_tree	*new_node;

	new_node = ft_create_node_tree((*cur)->type, (*cur)->value);
	if (*parent)
		(*parent)->next = new_node;
	*parent = new_node;
	*cur = (*cur)->next;
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_handle_quote(t_token **cur, t_tree **parent, t_shell *shell)
 * </summary>
 *
 * <description>
 *	ft_handle_quote create a tree node for the T_SQUOTE and T_DQUOTE token.
 * </description>
 *
 * <param type="t_token **" name="cur">current token</param>
 * <param type="t_tree **" name="parent">parent node of this node</param>
 * <param type="t_shell *" name="shl">shell structure</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
void	ft_handle_quote(t_token **cur, t_tree **parent, t_shell *shell)
{
	char	*value;
	t_tree	*new_node;

	value = ft_parse_string((*cur)->value, shell);
	if ((*cur)->type == T_DQUOTE)
		new_node = ft_create_node_tree((*cur)->type, value);
	else
		new_node = ft_create_node_tree((*cur)->type, (*cur)->value);
	if (*parent)
		(*parent)->next = new_node;
	*parent = new_node;
	*cur = (*cur)->next;
	ft_free(value);
}
