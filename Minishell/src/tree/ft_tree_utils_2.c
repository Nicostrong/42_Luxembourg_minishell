/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:35:41 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 13:04:59 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	t_tree	*ft_create_node_tree(t_tok_type type, char *value)
 * </summary>
 *
 * <description>
 *	ft_create_node_tree create a new node for the tree and set the type and the
 *	cmd value
 * </description>
 *
 * <param type="t_tok_type" name="type">enum of token name</param>
 * <param type="char *" name="value">value to set</param>
 *
 * <return>
 *	a pointer to a new node.
 * </return>
 *
 */
t_tree	*ft_create_node_tree(t_tok_type type, char *value)
{
	t_tree	*node;

	node = (t_tree *)ft_calloc(1, sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = type;
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->left = NULL;
	node->right = NULL;
	node->next = NULL;
	return (node);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	t_tree	*ft_parse_heredoc(t_token **tokens)
 * </summary>
 *
 * <description>
 *	ft_parse_heredoc parse the T_HEREDOC token to create a heredoc node.
 * </description>
 *
 * <param type="t_token **" name="tokens">list of tokens</param>
 *
 * <return>
 *	a pointer to a new node for the heredoc token.
 * </return>
 *
 */
t_tree	*ft_parse_heredoc(t_token **tokens)
{
	t_tree	*heredoc_node;
	t_tree	*new_node;
	t_token	*cur;

	heredoc_node = ft_create_node_tree((*tokens)->type, NULL);
	cur = (*tokens)->next;
	if (cur && cur->type == T_EOF)
	{
		new_node = ft_create_node_tree(cur->type, cur->value);
		heredoc_node->next = new_node;
		cur = cur->next;
	}
	*tokens = cur;
	return (heredoc_node);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_get_wilcard(char *patern, t_tree **par)
 * </summary>
 *
 * <description>
 *	ft_get_wilcard substitu the patern with the wilcard, with all value 
 *	respecting the patern.§
 * </description>
 *
 * <param type="char *" name="patern">patern</param>
 * <param type="t_tree **" name="parent">parent node</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
static void	ft_get_wilcard(char *patern, t_tree **par)
{
	char	**wilcard;
	int		i;
	t_tree	*new_node;

	wilcard = ft_wilcard(patern);
	if (wilcard)
	{
		i = -1;
		while (wilcard[++i])
		{
			new_node = ft_create_node_tree(T_WORD, wilcard[i]);
			if (*par)
				(*par)->next = new_node;
			*par = new_node;
		}
		wilcard = ft_free_array(wilcard);
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_handle_word(t_token **cur, t_tree **par, t_shell *shl)
 * </summary>
 *
 * <description>
 *	ft_handle_word create a tree node for the T_VAR token with the T_KEY value.
 * </description>
 *
 * <param type="t_token **" name="cur">current token</param>
 * <param type="t_tree **" name="head">head of the tree</param>
 * <param type="t_tree **" name="parent">parent node</param>
 * <param type="t_shell *" name="shell">shell structure</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
void	ft_handle_word(t_token **cur, t_tree **head, t_tree **par, t_shell *shl)
{
	char	*value;
	t_tree	*new_node;

	value = ft_parse_string((*cur)->value, shl);
	if (*cur && (*cur)->type == T_WORD)
	{
		if (ft_strchr(value, '*') && ft_check_nb_wilcard(value))
			ft_get_wilcard(value, par);
		else
		{
			new_node = ft_create_node_tree((*cur)->type, value);
			if (*par)
				(*par)->next = new_node;
			*par = new_node;
		}
		*cur = (*cur)->next;
	}
	if (!*head)
		*head = *par;
	ft_free(value);
}
