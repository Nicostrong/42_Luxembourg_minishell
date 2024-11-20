/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:57:09 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/07 13:57:43 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	t_pipex	*ft_init_pipex(t_shell **shell)
 * </summary>
 *
 * <description>
 *	ft_init_pipex initialize the structure pipex with the default values.
 * </description>
 *
 * <param type="t_shell **" name="shell">shell structure</param>
 *
 * <return>
 *	a pointer to a new pipex structure.
 * </return>
 *
 */
t_pipex	*ft_init_pipex(t_shell **shell)
{
	char	**env;
	t_pipex	*pipex;

	env = ft_create_env_array((*shell)->l_env);
	pipex = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	if (!pipex)
	{
		free(*shell);
		exit (EXIT_FAILURE);
	}
	pipex->a_path = ft_get_path((*shell)->l_env);
	pipex->a_env = ft_create_env_array((*shell)->l_env);
	pipex->shell = *shell;
	env = ft_free_array(env);
	return (pipex);
}
