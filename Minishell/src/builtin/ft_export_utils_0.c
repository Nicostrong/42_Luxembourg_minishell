/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:07:18 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/08 10:36:52 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_valid_key(char *key)
 * </summary>
 *
 * <description>
 * 	ft_valid_key check if the key is a valide format key name.
 * </description>
 *
 * <param type="char *" name="key">value of the key to evaluate</param>
 *
 * <return>
 *  1 if it's a valid key name or
 *	0 if it isn't a valid key name.
 * </return>
 *
 */
int	ft_valid_key(char *key)
{
	if (!key)
		return (0);
	while (*key)
	{
		if (ft_isdigit(*key) || (!ft_isalpha(*key) && *key != '_'))
			return (0);
		key++;
	}
	return (1);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_check_key(t_env *env, char *key)
 * </summary>
 *
 * <description>
 * 	ft_check_key check if the key exist on the struct env.
 * </description>
 *
 * <param type="t_env *" name="env">linked list env</param>
 * <param type="char *" name="key">key to evaluate</param>
 *
 * <return>
 * 	1 if exist or 0 if not exist.
 * </return>
 *
 */
int	ft_check_key(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strequal(env->key, key))
			return (1);
		env = env->next;
	}
	return (0);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_export_value(t_shell **shell, char *key_val)
 * </summary>
 *
 * <description>
 * 	ft_export_value add to the key the value passed after the char '='.
 * </description>
 *
 * <param type="t_shell **" name="shell">shell structure</param>
 * <param type="char **" name="key_val">array of key/value</param>
 *
 * <return>
 * 	0 if success or 1 if error.
 * </return>
 *
 */
void	ft_export_value(t_shell **shell, char *key_val)
{
	char	**a_key_val;
	char	*a_k_v[2];

	a_key_val = ft_split(key_val, '=');
	if (a_key_val[1])
	{
		a_k_v[0] = ft_substr(key_val, 0, ft_charchr(key_val, '='));
		a_k_v[1] = ft_substr(key_val, ft_charchr(key_val, '=') + 1, -1);
		ft_add_node((*shell)->l_env, a_k_v[0], a_k_v[1]);
		ft_free(a_k_v[0]);
		ft_free(a_k_v[1]);
	}
	else
	{
		ft_add_node((*shell)->l_env, a_key_val[0], NULL);
	}
	ft_free_array(a_key_val);
}
