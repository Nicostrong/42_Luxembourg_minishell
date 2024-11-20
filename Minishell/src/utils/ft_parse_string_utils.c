/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_string_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:36:04 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 13:44:59 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	int	ft_isvarchar(char c)
 * </summary>
 *
 * <description>
 *	ft_isvarchar check if the char is a char of variable name or not.
 * </description>
 *
 * <param type="char" name="c">char to evaluate</param>
 *
 * <return>
 *	1 if the char is a char of variable or
 *	0 if it isn't a char of variable.
 * </return>
 *
 */
static int	ft_isvarchar(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	char	*ft_extract_key(char *string, int *index)
 * </summary>
 *
 * <description>
 *	ft_extract_key extract the key of the variable in the string.
 * </description>
 *
 * <param type="char *" name="string">string original to extract a part</param>
 * <param type="int" name="index">index of start of new string</param>
 *
 * <return>
 *	a pointer to a key of the variable.
 * </return>
 *
 */
static char	*ft_extract_key(char *string, int *index)
{
	int		start;

	start = *index;
	while (string[*index] && ft_isvarchar(string[*index]))
		(*index)++;
	return (ft_strndup(string + start, *index - start));
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	int	ft_add_var(char *string, t_shell *shell, char **new, int index)
 * </summary>
 *
 * <description>
 *	ft_add_var replace the key by the value on the string new.
 * </description>
 *
 * <param type="char *" name="string">string to parse</param>
 * <param type="t_shell *" name="shell">shell structure</param>
 * <param type="char **" name="new">a pointer to new string</param>
 * <param type="int" name="index">index on string</param>
 *
 * <return>
 *	a pointer to a new string with the variable replaced.
 * </return>
 *
 */
static int	ft_add_var(char *string, t_shell *shell, char **new, int index)
{
	char	*key;

	if (string[index] == '?')
	{
		*new = ft_replace_variable(*new, "?", shell);
		index++;
	}
	else
	{
		key = ft_extract_key(string, &index);
		*new = ft_replace_variable(*new, key, shell);
		ft_free(key);
	}
	return (index);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	char	*ft_remove_backslach(char *new)
 * </summary>
 *
 * <description>
 *	ft_remove_backslach remove the backslach in the string.
 * </description>
 *
 * <param type="char *" name="s">string to parse</param>
 *
 * <return>
 *	a pointer to a new string without bqckslach.
 * </return>
 *
 */
static char	*ft_remove_backslach(char *s)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = ft_strdup(s);
	while (s[i])
	{
		if (s[i] == '\\' && (s[i + 1] == '\\' || s[i + 1] == '"' \
			|| s[i + 1] == '\''))
			i++;
		new[j++] = s[i++];
	}
	new[j] = 0;
	ft_free(s);
	return (new);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	char	*ft_parse_string(char *string, t_shell *shell)
 * </summary>
 *
 * <description>
 *	ft_parse_string replace the variable in the string by their value.
 * </description>
 *
 * <param type="char *" name="string">string to parse</param>
 * <param type="t_shell *" name="shell">shell structure</param>
 *
 * <return>
 *	a pointer to a new string with the variable replaced.
 * </return>
 *
 */
char	*ft_parse_string(char *string, t_shell *shell)
{
	char	*new;
	int		index;
	int		start;

	new = ft_strdup("");
	index = 0;
	start = 0;
	while (string[index])
	{
		if (string[index] == '$' && (string[index + 1] == ' ' \
			|| !string[index + 1]))
			index++;
		else if (string[index] == '$')
		{
			new = ft_add_static_text(new, string, start, index);
			index = ft_add_var(string, shell, &new, ++index);
			start = index;
		}
		else
			index++;
	}
	if (start < index)
		new = ft_add_static_text(new, string, start, index);
	new = ft_remove_backslach(new);
	return (new);
}
