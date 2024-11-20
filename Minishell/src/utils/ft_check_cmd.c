/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:26:46 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 13:44:00 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* <cat>bool</cat>
*
* <summary>
*	int	ft_check_error(char c)
* </summary>
*
* <description>
*	ft_check_error print a message error in rapport of the char evaluated.
* </description>
*
* <param type="char" name="c">char eveluated</param>
*
* <return>
*	0.
* </return>
*
*/
static int	ft_check_error(char c, int count)
{
	if (c == '|')
		return (ft_put_error_cmd("bash", E_PIPE), 0);
	else if (c == '&')
		return (ft_put_error_cmd("bash", E_AND), 0);
	else if (count != 0)
		return (ft_put_error_cmd("bash", E_SUB), 0);
	else
		return (1);
}

/*
* <cat>bool</cat>
*
* <summary>
*	int	ft_check_token(char *cmd, char c)
* </summary>
*
* <description>
*	ft_check_token check on the string command if the syntaxe with the char
*	passed in parameter is correct. It check '|' and '&'.
* </description>
*
* <param type="char *" name="cmd">string to check</param>
* <param type="char" name="c">char to eveluate</param>
*
* <return>
*	0 in error case.
*	1 if no error.
* </return>
*
*/
static int	ft_check_token(char *cmd, char c)
{
	int	i;
	int	dquote;
	int	squote;

	i = 0;
	dquote = 0;
	squote = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '"' || cmd[i] == '\'') && (i > 0) && cmd[i - 1] == '\\')
			i++;
		else if (cmd[i] == '"' && !squote)
			dquote = !dquote;
		else if (cmd[i] == '\'' && !dquote)
			squote = !squote;
		else if (!dquote && !squote && cmd[i] == c && i > 1 \
			&& cmd[i - 1] == c && i > 2 && cmd[i - 2] == c)
			ft_check_error(c, 0);
		else if (cmd[i] == c && !cmd[i + 1])
			return (ft_put_error_cmd("bash", E_SYNTAX), 0);
		i++;
	}
	return (1);
}

/*
* <cat>bool</cat>
*
* <summary>
*	int	ft_check_quote(char *cmd, char quote)
* </summary>
*
* <description>
*	ft_check_quote check the correct token for the char '"' and "'"".
* </description>
*
* <param type="char *" name="cmd">sting to check</param>
* <param type="char" name="quote">quote to eveluate</param>
*
* <return>
*	0 in error case.
*	1 if no error.
* </return>
*
*/
static int	ft_check_quote(const char *cmd)
{
	int	i;
	int	len;
	int	in_dquote;
	int	in_squote;

	i = 0;
	len = ft_strlen(cmd);
	in_dquote = 0;
	in_squote = 0;
	while (i < len)
	{
		if ((cmd[i] == '\'' || cmd[i] == '"') && i > 0 && cmd[i - 1] == '\\')
			;
		else if (cmd[i] == '"' && (i == 0 || cmd[i - 1] != '\\') && !in_squote)
			in_dquote = !in_dquote;
		else if (cmd[i] == '\'' && (i == 0 || cmd[i - 1] != '\\') && !in_dquote)
			in_squote = !in_squote;
		i++;
	}
	if (in_dquote)
		return (ft_put_error_cmd("bash", E_DQUOTE), 0);
	if (in_squote)
		return (ft_put_error_cmd("bash", E_SQUOTE), 0);
	return (1);
}

/*
* <cat>bool</cat>
*
* <summary>
*	int	ft_check_parenteses(char *cmd)
* </summary>
*
* <description>
*	ft_check_parenteses check if the parenteses are close.
* </description>
*
* <param type="char *" name="cmd">sting to check</param>
*
* <return>
*	0 in error case.
*	1 if no error.
* </return>
*
*/
static int	ft_check_parenteses(char *cmd)
{
	int	i;
	int	count;
	int	dquote;
	int	squote;

	i = 0;
	count = 0;
	dquote = 0;
	squote = 0;
	while (cmd[i] && count >= 0)
	{
		if ((cmd[i] == '\'' || cmd[i] == '"') && i > 0 && cmd[i - 1] == '\\')
			i++;
		else if (cmd[i] == '"' && !squote)
			dquote = !dquote;
		else if (cmd[i] == '\'' && !dquote)
			squote = !squote;
		if (cmd[i] == '(' && !dquote && !squote)
			count++;
		else if (cmd[i] == ')' && !dquote && !squote)
			count--;
		i++;
	}
	return (ft_check_error(0, count));
}

/*
* <cat>bool</cat>
*
* <summary>
*	int	ft_check_syntax_input(char *cmd, t_shell *shell)
* </summary>
*
* <description>
*	ft_check_syntax_input check all syntax error cases.
* </description>
*
* <param type="char *" name="cmd">sting to check</param>
* <param type="t_shell *" name="shell">shell structure</param>
*
* <return>
*	1 if the syntax is correct or
*	0 in case of error syntax.
* </return>
*
*/
int	ft_check_syntax_input(char *cmd, t_shell *shell)
{
	if (!ft_check_token(cmd, '|')
		|| !ft_check_token(cmd, '&')
		|| !ft_check_file(cmd, '<')
		|| !ft_check_file(cmd, '>')
		|| !ft_check_parenteses(cmd)
		|| !ft_check_quote(cmd))
		shell->code_exit = 2;
	else
		return (1);
	return (0);
}
