/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:13:44 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/07 15:34:16 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	t_env	*ft_add_node(t_env *env, char *key, char *value)
 * </summary>
 *
 * <description>
 * 	ft_add_node add a new node on the linked list of environnement variables.
 * </description>
 *
 * <param type="t_env *" name="env">linked list env</param>
 * <param type="char *" name="key">key</param>
 * <param type="char *" name="value">value</param>
 *
 * <return>
 * 	NULL if error or a pointer to the head of list.
 * </return>
 *
 */
t_env	*ft_add_node(t_env *env, char *key, char *value)
{
	t_env	*node;
	t_env	*current;

	node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
		return (ft_free(node), NULL);
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
			return (ft_free(node->key), ft_free(node), NULL);
	}
	else
		node->value = NULL;
	node->next = NULL;
	if (!env)
		return (node);
	current = env;
	while (current->next)
		current = current->next;
	current->next = node;
	return (env);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_update_shlvl(t_shell **shell)
 * </summary>
 *
 * <description>
 * 	ft_update_shlvl increase the value of SHLVL variable on the linked list env.
 * </description>
 *
 * <param type="t_shell **" name="shell">shell structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_update_shlvl(t_shell **shell)
{
	char	*shlvl_value;
	char	*new_shlvl;
	int		shlvl;

	shlvl_value = ft_get_env_value(*shell, "SHLVL");
	if (shlvl_value)
	{
		shlvl = ft_atoi(shlvl_value) + 1;
		new_shlvl = ft_itoa(shlvl);
		if (!new_shlvl)
			return ;
		ft_set_env_value(shell, "SHLVL", new_shlvl);
		free(new_shlvl);
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	t_env	*ft_init_env(t_shell **shell)
 * </summary>
 *
 * <description>
 * 	ft_init_env initialise the linked list env with all value of environnement 
 * 	variable.
 * </description>
 *
 * <param type="t_shell **" name="shell">shell structure</param>
 * 
 * <return>
 * 	void.
 * </return>
 *
 */
static t_env	*ft_init_env(t_shell **shell)
{
	char	**key_value;
	int		index;
	t_env	*env;

	env = NULL;
	index = -1;
	while (environ[++index])
	{
		key_value = ft_split(environ[index], '=');
		env = ft_add_node(env, key_value[0], key_value[1]);
		ft_free_array(key_value);
	}
	ft_update_shlvl(shell);
	return (env);
}

/*
 * <cat>bool</cat>
 *
 * <summary>
 *	t_pipex	*ft_init_shell(void)
 * </summary>
 *
 * <description>
 *	ft_init_shell initialize the structure shell. it init all struct for the 
 *	shell.
 * </description>
 *
 * <param type="void" name="void">void</param>
 *
 * <return>
 *	a pointer to a new shell structure
 * </return>
 *
 */
t_shell	*ft_init_shell(void)
{
	t_shell	*shell;

	shell = (t_shell *)ft_calloc(1, sizeof(t_shell));
	if (!shell)
		exit (EXIT_FAILURE);
	shell->l_env = ft_init_env(&shell);
	return (shell);
}
