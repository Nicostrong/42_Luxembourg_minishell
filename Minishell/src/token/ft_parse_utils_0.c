/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:46:48 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 12:53:27 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_tok_pipe_or(char *input, int *i, t_token **tokens)
 * </summary>
 *
 * <description>
 *	ft_tok_pipe_or catch the correct T_PIPE or T_OR token and add this on the 
 *	linked list tokens.
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
static void	ft_tok_pipe_or(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '|')
	{
		if (input[*i + 1] == '|' && input[*i + 2] == ' ')
		{
			ft_append_token(tokens, T_OR, "||");
			*i += 3;
		}
		else if (input[*i + 1] == ' ' || input[*i + 1] != '|')
		{
			ft_append_token(tokens, T_PIPE, "|");
			(*i)++;
		}
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_tok_and(char *input, int *i, t_token **tokens)
 * </summary>
 *
 * <description>
 *	ft_tok_and catch the correct T_AND token and add this on the linked list 
 *	tokens.
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
static void	ft_tok_and(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '&' && input[*i + 1] == '&' && input[*i + 2] == ' ')
	{
		ft_append_token(tokens, T_AND, "&&");
		*i += 3;
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	ft_tok_operator(char *input, int *i, t_token **tokens, t_shell **shl)
 * </summary>
 *
 * <description>
 *	ft_tok_operator call the correct function operator to catch the correct 
 *	token.
 * </description>
 *
 * <param type="char *" name="input">sting to tokonize</param>
 * <param type="int *" name="i">index</param>
 * <param type="t_token **" name="token">linked list of tokens</param>
 * <param type="t_shell **" name="shl">shell structure</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
void	ft_tok_operator(char *input, int *i, t_token **tokens, t_shell **shl)
{
	if (input[*i] == '&')
		ft_tok_and(input, i, tokens);
	if (input[*i] == '|')
	{
		ft_tok_pipe_or(input, i, tokens);
		(*shl)->cmd = 0;
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_tok_file_in(char *input, int *i, t_token **tokens)
 * </summary>
 *
 * <description>
 *	ft_tok_file_in catch the correct T_F_IN or T_HEREDOC or T_WORD token and add
 *	 this on the linked list tokens.
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
void	ft_tok_file_in(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			ft_append_token(tokens, T_HEREDOC, "<<");
			*i += 2;
		}
		else
		{
			ft_append_token(tokens, T_F_IN, "<");
			(*i)++;
		}
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_tok_file_out(char *input, int *i, t_token **tokens)
 * </summary>
 *
 * <description>
 *	ft_tok_file_out catch the correct T_F_OUT or T_F_OUT_APEND or T_WORD token 
 *	and add this on the linked list tokens.
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
void	ft_tok_file_out(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			ft_append_token(tokens, T_F_OUT_APPEND, ">>");
			*i += 2;
		}
		else
		{
			ft_append_token(tokens, T_F_OUT, ">");
			(*i)++;
		}
	}
}
