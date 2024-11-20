/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:03:46 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 13:02:56 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	t_token	*ft_get_last_token(t_token **tokens)
 * </summary>
 *
 * <description>
 *	ft_get_last_token return the last token of the tokenslist.
 * </description>
 *
 * <param type="t_tokens **" name="tokens">linked list of tokens</param>
 *
 * <return>
 *	a pointer to the last token of the linked list.
 * </return>
 *
 */
static t_token	*ft_get_last_token(t_token **tokens)
{
	t_token	*last;

	if (!tokens || !*tokens)
		return (NULL);
	last = *tokens;
	while (last->next)
		last = last->next;
	return (last);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	int	ft_is_builtin(char *cmd)
 * </summary>
 *
 * <description>
 *	ft_is_builtin check if the command is a builtin function or not.
 * </description>
 *
 * <param type="char *" name="cmd">command to evaluate</param>
 *
 * <return>
 *	1 if cmd is a builtin function or
 *	0 if cmd isn't a builtin function.
 * </return>
 *
 */
static int	ft_is_builtin(char *cmd)
{
	if (ft_strequal(cmd, "echo"))
		return (1);
	else if (ft_strequal(cmd, "cd"))
		return (1);
	else if (ft_strequal(cmd, "pwd"))
		return (1);
	else if (ft_strequal(cmd, "env"))
		return (1);
	else if (ft_strequal(cmd, "export"))
		return (1);
	else if (ft_strequal(cmd, "unset"))
		return (1);
	else if (ft_strequal(cmd, "exit"))
		return (1);
	else
		return (0);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_assign(t_token **last, t_token **tokens, char *value, char *cmd)
 * </summary>
 *
 * <description>
 *	ft_assign assign all value with a token.
 * </description>
 *
 * <param type="t_token *" name="last">last token</param>
 * <param type="t_token **" name="token">linked list of tokens</param>
 * <param type="char *" name="value">value of the token</param>
 * <param type="char *" name="cmd">juste the command</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
static int	ft_assign(t_token **last, t_token **tokens, char *value, char *cmd)
{
	if (*last && (*last)->type >= T_F_IN && (*last)->type <= T_F_OUT_APPEND)
		ft_append_token(tokens, T_FILENAME, value);
	else if (*last && (*last)->type == T_HEREDOC)
		ft_append_token(tokens, T_EOF, value);
	else if (ft_is_builtin(value))
		ft_append_token(tokens, T_BUILTIN, value);
	else if (*last && ((*last)->type == T_WORD || (*last)->type == T_BUILTIN))
		ft_append_token(tokens, T_WORD, value);
	else if (*last && (*last)->type == T_PIPE)
		return (ft_append_token(tokens, T_CMD, cmd), 1);
	else if (!*last || (*last)->type == T_EOF)
		return (ft_append_token(tokens, T_CMD, cmd), 1);
	else if (ft_strequal(value, "-") || ft_strequal(value, "--") \
		|| value[0] == '$')
		ft_append_token(tokens, T_WORD, value);
	else if (value[0] == '-')
		ft_append_token(tokens, T_OPT, value);
	else if (!ft_strequal(value, cmd) && (!*last || (*last)->type != T_CMD))
		return (ft_append_token(tokens, T_CMD, cmd), 1);
	else
		ft_append_token(tokens, T_WORD, value);
	return (0);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void  ft_tok_word(char *input, int *i, t_token **tokens, t_shell *shell)
 * </summary>
 *
 * <description>
 *	ft_tok_word catch the string and select the correct token for the string.
 * </description>
 *
 * <param type="char *" name="input">sting to tokonize</param>
 * <param type="int *" name="i">index</param>
 * <param type="t_token **" name="token">linked list of tokens</param>
 * <param type="t_shell *" name="shell">shell structure</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */
void	ft_tok_word(char *input, int *i, t_token **tokens, t_shell **shell)
{
	char	*value;
	char	*tmp;
	char	*cmd;
	int		start;
	t_token	*last;

	last = ft_get_last_token(tokens);
	start = *i;
	ft_pass_char(input, i);
	tmp = ft_strndup(&input[start], *i - start);
	value = ft_strremoveset(tmp, "\"'");
	cmd = ft_concat_path_cmd((*shell)->l_env, value);
	(*shell)->cmd = ft_assign(&last, tokens, value, cmd);
	ft_free(cmd);
	ft_free(value);
	ft_free(tmp);
}
