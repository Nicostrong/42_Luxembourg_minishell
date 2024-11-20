/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_utils_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:32:16 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/07 15:08:38 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_create_attach_node(t_tree **head, t_tree **par, t_token *cur, \
 *									t_shell *shl)
 * </summary>
 *
 * <description>
 *	ft_create_attach_node create and attache the new node on the tree with the 
 *	correct value.
 * </description>
 *
 * <param type="t_tree **" name="head">head of the tree</param>
 * <param type="t_tree **" name="par">parent node</param>
 * <param type="t_token *" name="cur">current token</param>
 * <param type="t_shell *" name="shl">shell structure</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
static void	ft_create_attach_node(t_tree **head, t_tree **par, t_token *cur, \
									t_shell *shl)
{
	char	*value;
	t_tree	*new_node;

	if (cur->type >= T_WORD && !(cur->type == T_SQUOTE))
	{
		value = ft_parse_string(cur->value, shl);
		new_node = ft_create_node_tree(cur->type, value);
		ft_free(value);
	}
	else
		new_node = ft_create_node_tree(cur->type, cur->value);
	if (!*head)
		*head = new_node;
	else if (cur->type >= T_PIPE && cur->type <= T_AND)
	{
		new_node->left = *head;
		*head = new_node;
	}
	else if (*par && (*par)->type >= T_PIPE && (*par)->type <= T_AND)
		(*par)->right = new_node;
	else if (*par)
		(*par)->next = new_node;
	*par = new_node;
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	static void	ft_validate_closing_sub(t_token **cur, t_token **tokens)
 * </summary>
 *
 * <description>
 *	ft_validate_closigng_sub check the end of the subshell command and pass to 
 *	the next token.
 * </description>
 *
 * <param type="t_token **" name="cur">current token</param>
 * <param type="t_token **" name="tokens">list of tokens</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
static void	ft_validate_closing_sub(t_token **cur, t_token **tokens)
{
	if (*cur && (*cur)->type == T_SUBSHELL && ft_strequal((*cur)->value, ")"))
		*cur = (*cur)->next;
	*tokens = *cur;
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	t_tree	*ft_parse_subshell(t_token **tokens, t_shell *shell)
 * </summary>
 *
 * <description>
 *	ft_parse_subshell parse the T_SUBSHELL token to create a subshell node.
 * </description>
 *
 * <param type="t_token **" name="tokens">list of tokens</param>
 * <param type="t_shell *" name="shl">shell structure</param>
 *
 * <return>
 *	a pointer to a new node for the subshell token.
 * </return>
 *
 */
t_tree	*ft_parse_subshell(t_token **tokens, t_shell *shell)
{
	t_tree	*head;
	t_tree	*parent;
	t_token	*cur;

	head = NULL;
	parent = NULL;
	cur = (*tokens)->next;
	while (cur && !(cur->type == T_SUBSHELL && ft_strequal(cur->value, ")")))
	{
		ft_create_attach_node(&head, &parent, cur, shell);
		cur = cur->next;
	}
	ft_validate_closing_sub(&cur, tokens);
	return (head);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_handle_cmd(t_token **cur, t_tree **head, t_tree **parent)
 * </summary>
 *
 * <description>
 *	ft_handle_cmd create a tree node for the T_CMD token.
 * </description>
 *
 * <param type="t_token **" name="cur">current token</param>
 * <param type="t_tree **" name="head">head of the tree</param>
 * <param type="t_tree **" name="parent">parent node</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
void	ft_handle_cmd(t_token **cur, t_tree **head, t_tree **parent)
{
	t_tree	*new_node;

	new_node = ft_create_node_tree((*cur)->type, (*cur)->value);
	if (!*head)
		*head = new_node;
	else
		(*parent)->next = new_node;
	*parent = new_node;
	*cur = (*cur)->next;
}
