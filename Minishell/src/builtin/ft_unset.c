/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:24:10 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/07 13:33:19 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_unset_key(t_env **env, char *key)
 * </summary>
 *
 * <description>
 * 	ft_unset_key remove properly the key on the linked list env.
 * </description>
 *
 * <param type="t_env **" name="env">linked list env</param>
 * <param type="tchar *" name="key">key of node to remove</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_unset_key(t_env **env, char *key)
{
	t_env	*current;
	t_env	*before;

	if (!env || !*env || !key)
		return ;
	current = *env;
	before = NULL;
	while (current && !ft_strequal(current->key, key))
	{
		before = current;
		current = current->next;
	}
	if (current)
	{
		if (before)
			before->next = current->next;
		else
			*env = current->next;
		ft_free(current->key);
		ft_free(current->value);
		ft_free(current);
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_unset(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_unset is like a builtin function in bash.it can take many arguments to 
 * 	remove of the linked list.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">structure pipex</param>
 *
 * <return>
 * 	0 if success or 1 if error.
 * </return>
 *
 */
int	ft_unset(t_pipex **pipex)
{
	int		index;

	if ((*pipex)->fd_out > 2)
		close((*pipex)->fd_out);
	if (!(*pipex)->a_cmd_opt)
		return (0);
	index = -1;
	while ((*pipex)->a_cmd_opt[++index])
		ft_unset_key(&(*pipex)->shell->l_env, (*pipex)->a_cmd_opt[index]);
	return (0);
}
