/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:59:20 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/07 15:01:22 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_pttt_2(t_token **cur, t_tree **head, t_tree ** par, t_shell *shl)
 * </summary>
 *
 * <description>
 *	ft_pttt_2 transform the second part of the linked list tokens of the
 *	command on a AST tree for execute each command correctly.
 * </description>
 *
 * <param type="t_token **" name="cur">current token</param>
 * <param type="t_tree **" name="head">head node</param>
 * <param type="t_tree **" name="par">parent node</param>
 * <param type="t_shell *" name="shl">shell structure</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
static void	ft_pttt_2(t_token **cur, t_tree **head, t_tree **par, t_shell *shl)
{
	if ((*cur)->type >= T_F_IN && (*cur)->type <= T_F_OUT_APPEND)
		ft_handle_file(cur, head, par, shl);
	else if ((*cur)->type <= T_CMD)
		ft_handle_cmd(cur, head, par);
	else if ((*cur)->type == T_WORD)
		ft_handle_word(cur, head, par, shl);
	else if ((*cur)->type == T_SUBSHELL && (*cur)->value
		&& ft_strequal((*cur)->value, "("))
		ft_handle_sub(cur, head, par, shl);
	else if ((*cur)->type == T_OPT)
		ft_handle_option(cur, par);
	else if ((*cur)->type == T_DQUOTE || (*cur)->type == T_SQUOTE)
		ft_handle_quote(cur, par, shl);
	else if ((*cur)->type == T_END)
		ft_handle_cmd(cur, head, par);
	else
		*cur = (*cur)->next;
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	t_tree	*ft_parse_token_to_tree(t_token **tokens, t_shell *shell)
 * </summary>
 *
 * <description>
 *	ft_parse_token_to_tree transform the linked list tokens of the command on a 
 *	AST tree for execute each command correctly.
 * </description>
 *
 * <param type="t_token **" name="tokens">linked list of tokens</param>
 * <param type="t_shell *" name="shell">shell structure</param>
 *
 * <return>
 *	a pointer to the first node of the tree.
 * </return>
 *
 */
t_tree	*ft_parse_token_to_tree(t_token **tokens, t_shell *shell)
{
	t_token	*cur;
	t_tree	*head;
	t_tree	*parent;
	t_tree	*new;

	cur = *tokens;
	head = NULL;
	parent = NULL;
	while (cur)
	{
		if (cur->type >= T_PIPE && cur->type <= T_AND)
			return (ft_handle_pp_or_and(&cur, &head, shell));
		else if (cur->type == T_HEREDOC)
		{
			new = ft_parse_heredoc(&cur);
			if (!head)
				head = new;
			else
				parent->next = new;
			parent = new->next;
		}
		else
			ft_pttt_2(&cur, &head, &parent, shell);
	}
	return (head);
}
