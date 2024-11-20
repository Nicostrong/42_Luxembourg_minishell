/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wilcard_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:43:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 13:50:56 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	int	ft_is_prefix(char *str, char *prefix)
 * </summary>
 *
 * <description>
 *	ft_is_prefix check if the value of prefix is the prefix of the string.
 * </description>
 *
 * <param type="char *" name="str">string to parse</param>
 * <param type="char *" name="prefix">prefix value to fund</param>
 *
 * <return>
 *	1 if the prefix is the prefix of str or 0 if not.
 * </return>
 *
 */
static int	ft_is_prefix(char *str, char *prefix)
{
	int		len_pref;
	char	*begin;

	len_pref = ft_strlen(prefix);
	begin = ft_strndup(str, len_pref);
	if (ft_strequal(begin, prefix))
		return (ft_free(begin), 1);
	return (ft_free(begin), 0);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	int	ft_is_sufix(char *str, char *sufix)
 * </summary>
 *
 * <description>
 *	ft_is_sufix check if the sufix value is in the str.
 * </description>
 *
 * <param type="char *" name="str">string to parse</param>
 * <param type="char *" name="sufix">sufix value to fund</param>
 *
 * <return>
 *	1 if the sufix is the suix of str or 0 if not.
 * </return>
 *
 */
static int	ft_is_sufix(char *str, char *sufix)
{
	int	len_str;
	int	len_sufix;

	if (!str || !sufix)
		return (0);
	len_str = ft_strlen(str);
	len_sufix = ft_strlen(sufix);
	if (ft_strequal(str + len_str - len_sufix, sufix))
		return (1);
	return (0);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	int	ft_check_fix(char **a_fix, char *str)
 * </summary>
 *
 * <description>
 *	ft_check_fix check on the string the part before and after the wilcard.
 * </description>
 *
 * <param type="char *" name="str">string to parse</param>
 * <param type="char *" name="sufix">sufix value to fund</param>
 *
 * <return>
 *	1 if the sufix is the suix of str or 0 if not.
 * </return>
 *
 */
static int	ft_check_fix(char **a_fix, char *str)
{
	int	error;

	error = 0;
	if (a_fix[0] && a_fix[1])
	{
		if (ft_is_prefix(str, a_fix[0]) && ft_is_sufix(str, a_fix[1]))
			error = 1;
	}
	else if (a_fix[0])
	{
		if (ft_is_prefix(str, a_fix[0]) || ft_is_sufix(str, a_fix[0]))
			error = 1;
	}
	else if (a_fix[1])
	{
		if (ft_is_sufix(str, a_fix[1]) || ft_is_prefix(str, a_fix[1]))
			error = 1;
	}
	a_fix = ft_free_array(a_fix);
	return (error);
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
int	ft_check_patern(char *patern, char *str)
{
	char	**a_fix;

	if (!patern || !str)
		return (0);
	if (ft_strequal(str, ".") || ft_strequal(str, ".."))
		return (0);
	if (ft_strequal(patern, "*"))
		return (1);
	a_fix = ft_split(patern, '*');
	return (ft_check_fix(a_fix, str));
}
