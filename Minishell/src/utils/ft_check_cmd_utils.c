/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:39:45 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 13:44:21 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* <cat>bool</cat>
*
* <summary>
*	int	ft_check_file(char *cmd, char c)
* </summary>
*
* <description>
*	ft_check_file check the correct token for the char '<' and '>'.
* </description>
*
* <param type="char *" name="cmd">sting to check</param>
* <param type="char" name="c">char to eveluate</param>
*
* <return>
*	0 in error case.
*	1 if no error.
* </return>
*
*/
int	ft_check_file(char *cmd, char c)
{
	int	i;
	int	len;
	int	dquote;
	int	squote;

	i = 0;
	len = ft_strlen(cmd);
	dquote = 0;
	squote = 0;
	while (cmd[i] && i < len)
	{
		if (cmd[i] == '\\' && (i + 1 < len) && (cmd[i + 1] == '"' \
			|| cmd[i + 1] == '\''))
			i++;
		else if (cmd[i] == '"' && !squote)
			dquote = !dquote;
		else if (cmd[i] == '\'' && !dquote)
			squote = !squote;
		else if (!dquote && !squote && cmd[i] == c && (i + 1 < len) \
			&& cmd[i + 1] == c && (i + 2 < len) && cmd[i + 2] == c)
			return (ft_put_error_cmd("bash", E_SYNTAX), 0);
		i++;
	}
	return (1);
}
