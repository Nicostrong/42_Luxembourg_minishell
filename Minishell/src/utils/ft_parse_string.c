/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:35:53 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/07 16:20:24 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	char	*ft_add_static_text(char *new, char *string, int start, int end)
 * </summary>
 *
 * <description>
 *	ft_add_static_text add the static text to the new string.
 * </description>
 *
 * <param type="char *" name="new">new string with value</param>
 * <param type="char *" name="string">string original to extract a part</param>
 * <param type="int" name="start">index of start of new string</param>
 * <param type="int" name="end">index of end of new string</param>
 *
 * <return>
 *	a pointer to a new string with the static text added.
 * </return>
 *
 */
char	*ft_add_static_text(char *new, char *string, int start, int end)
{
	char	*txt;
	char	*tmp;

	txt = ft_strndup(string + start, end - start);
	tmp = ft_strjoin(new, txt);
	ft_free(new);
	ft_free(txt);
	return (tmp);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	char	*ft_replace_variable(char *new, char *key, t_shell *shell)
 * </summary>
 *
 * <description>
 *	ft_replace_variable replace the variable in the string by their value.
 * </description>
 *
 * <param type="char *" name="new">string to add value</param>
 * <param type="char *" name="key">key variable to replace by the value</param>
 * <param type="t_shell *" name="shell">shell structure</param>
 *
 * <return>
 *	a pointer to a new string with the variable replaced.
 * </return>
 *
 */
char	*ft_replace_variable(char *new, char *key, t_shell *shell)
{
	char	*value;
	char	*tmp;

	if (ft_strequal(key, "?"))
	{
		value = ft_itoa(shell->code_exit);
		tmp = ft_strjoin(new, value);
		ft_free(new);
		ft_free(value);
		new = tmp;
	}
	else
	{
		value = ft_get_env_value(shell, key);
		if (value)
		{
			tmp = ft_strjoin(new, value);
			ft_free(new);
			new = tmp;
		}
	}
	return (new);
}
