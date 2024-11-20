/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:08:59 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 11:52:02 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	t_token	*ft_create_token(t_tok_type type, char *value)
 * </summary>
 *
 * <description>
 *	ft_create_token create a new node on the linked list tokens and set the type
 *	ans the value in the node.
 * </description>
 *
 * <param type="t_tok_type" name="type">type of tokens</param>
 * <param type="char *" name="value">value of the token</param>
 *
 * <return>
 *	the new token with the type and the value setting.
 * </return>
 *
 */
static t_token	*ft_create_token(t_tok_type type, char *value)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_append_token(t_token **head, t_tok_type type, char *value)
 * </summary>
 *
 * <description>
 *	ft_append_token call the ft_create_token function with the type and the
 *	value and put this new node at the end of the linked list tokens.
 * </description>
 *
 * <param type="t_token **" name="head">head of linked list tokens</param>
 * <param type="t_tok_type" name="type">type of tokens</param>
 * <param type="char *" name="value">value of the token</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
void	ft_append_token(t_token **head, t_tok_type type, char *value)
{
	t_token	*new;
	t_token	*current;

	new = ft_create_token(type, value);
	if (!head)
		return ;
	if (!*head)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	t_token	*ft_parse_cmd(char *input, t_shell *shell)
 * </summary>
 *
 * <description>
 *	ft_parse_cmd parse the command string and call the correct tokennizer 
 *	function to transforme the string command on linked list of token.
 * </description>
 *
 * <param type="char *" name="input">sting to tokonize</param>
 * <param type="t_shell *" name="shell">shell structure</param>
 *
 * <return>
 *	a token list linked.
 * </return>
 *
 */
t_token	*ft_parse_cmd(char *input, t_shell *shell)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_issep(input[i]))
			i++;
		else if (input[i] == '|' || input[i] == '&')
			ft_tok_operator(input, &i, &tokens, &shell);
		else if (input[i] == '<')
			ft_tok_file_in(input, &i, &tokens);
		else if (input[i] == '>')
			ft_tok_file_out(input, &i, &tokens);
		else if (input[i] == '"' || input[i] == '\'')
			ft_tok_d_s_quote(input, &i, &tokens);
		else if (input[i] == '(' || input[i] == ')')
			ft_tok_subshell(input, &i, &tokens);
		else
			ft_tok_word(input, &i, &tokens, &shell);
	}
	ft_append_token(&tokens, T_END, "END_CMD");
	return (tokens);
}
