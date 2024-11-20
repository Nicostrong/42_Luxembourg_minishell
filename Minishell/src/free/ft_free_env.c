/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:34:33 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/07 13:35:10 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_free_env(t_env *env)
 * </summary>
 *
 * <description>
 * 	ft_free_env free all pointer and node of the linked list env.
 * </description>
 *
 * <param type="t_env *" name="env">linked list env</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_free_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	next = env;
	while (next)
	{
		current = next;
		next = current->next;
		if (current->key)
			ft_free(current->key);
		if (current->value)
			ft_free(current->value);
		ft_free(current);
	}
	env = NULL;
}
