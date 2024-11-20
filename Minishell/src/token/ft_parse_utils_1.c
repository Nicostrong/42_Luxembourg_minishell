/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:47:14 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 12:55:39 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_tok_d_s_quote(char *input, int *i, t_token **tokens)
 * </summary>
 *
 * <description>
 *	ft_tok_d_s_quote catch the correct T_DQUOTE or T_SQUOTE token and add this
 *	on the linked list tokens.
 * </description>
 *
 * <param type="char *" name="input">sting to tokonize</param>
 * <param type="int *" name="i">index</param>
 * <param type="t_token **" name="token">linked list of tokens</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
void	ft_tok_d_s_quote(char *input, int *i, t_token **tokens)
{
	char	*value;
	char	quote;
	int		start;

	quote = input[*i];
	start = ++(*i);
	while (input[*i] && input[*i] != quote)
	{
		if (input[*i] == '\\' && input[*i + 1] == quote)
			(*i)++;
		(*i)++;
	}
	if (input[*i] == quote)
	{
		value = ft_strndup(&input[start], *i - start);
		if (quote == '"')
			ft_append_token(tokens, T_DQUOTE, value);
		else
			ft_append_token(tokens, T_SQUOTE, value);
		free(value);
		(*i)++;
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_tok_subshell(char *input, int *i, t_token **tokens)
 * </summary>
 *
 * <description>
 *	ft_tok_subshellcatch the correct T_DQUOTE or T_SQUOTE token and add this on
 *	the linked list tokens.
 * </description>
 *
 * <param type="char *" name="input">sting to tokonize</param>
 * <param type="int *" name="i">index</param>
 * <param type="t_token **" name="token">linked list of tokens</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
void	ft_tok_subshell(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '(')
		ft_append_token(tokens, T_SUBSHELL, "(");
	else if (input[*i] == ')')
		ft_append_token(tokens, T_SUBSHELL, ")");
	(*i)++;
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	ft_pass_char(char *str, int *i)
 * </summary>
 *
 * <description>
 *	ft_pass_char pass all char which isn't a token or a separator char.
 * </description>
 *
 * <param type="char *" name="str">sting to parse</param>
 * <param type="int *" name="i">index</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
void	ft_pass_char(char *str, int *i)
{
	char	quote;

	if (!str)
		return ;
	while (str[*i] && (!ft_strchr("<>|&()", str[*i]) && !ft_issep(str[*i])))
	{
		if (str[*i] == '"' || str[*i] == '\'')
		{
			quote = str[(*i)++];
			while (str[*i] && str[*i] != quote)
				(*i)++;
			if (str[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
}
