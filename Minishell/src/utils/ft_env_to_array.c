/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:19:24 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/07 15:25:24 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_count_var(t_env *env)
 * </summary>
 *
 * <description>
 * 	ft_count_var count how many env var we have on the linkedlist.
 * </description>
 *
 * <param type="t_env *" name="env">linkedlist of env variable</param>
 *
 * <return>
 * 	number of variable on linkedlist.
 * </return>
 *
 */
static int	ft_count_var(t_env *env)
{
	t_env	*current;
	int		count;

	count = 0;
	if (!env)
		return (count);
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	char	**ft_create_env_array(t_env *env)
 * </summary>
 *
 * <description>
 * 	ft_create_env_array transform a linkedlist in array of env variables.
 * </description>
 *
 * <param type="t_env *" name="env">linkedlist of env variable</param>
 *
 * <return>
 * 	an array of env variables.
 * </return>
 *
 */
char	**ft_create_env_array(t_env *env)
{
	char	*key;
	char	*fusion;
	char	**a_env;
	int		index;
	int		len_array;

	if (!env)
		return (NULL);
	len_array = ft_count_var(env);
	a_env = (char **)ft_calloc((len_array + 1), sizeof(char *));
	if (!a_env)
		return (NULL);
	index = 0;
	while (env)
	{
		key = ft_strjoin(env->key, "=");
		fusion = ft_strjoin(key, env->value);
		a_env[index++] = fusion;
		ft_free(key);
		env = env->next;
	}
	a_env[index] = NULL;
	return (a_env);
}
