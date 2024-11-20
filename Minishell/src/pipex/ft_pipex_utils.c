/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:14:14 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/07 13:57:33 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	char	**ft_get_path(t_env *env)
 * </summary>
 *
 * <description>
 * 	ft_get_path read all env variables in env (is define in header file like 
 * 	extern char **environ) catch the $PATH variable and split the path in an 
 * 	array of path.
 * </description>
 *
 * <param type="t_env *" name="env">structure of all env variables</param>
 *
 * <return>
 * 	an array with all path in the var $PATH.
 * </return>
 *
 */
char	**ft_get_path(t_env *env)
{
	char	**a_env;
	char	**path_array;
	char	*path;
	int		index;

	index = 0;
	a_env = ft_create_env_array(env);
	if (!a_env)
		return (NULL);
	while (a_env[index] && ft_strncmp(a_env[index], "PATH=", 5))
		index++;
	if (!a_env[index])
	{
		ft_free_array(a_env);
		return (NULL);
	}
	path = a_env[index] + 5;
	path_array = ft_split(path, ':');
	ft_free_array(a_env);
	return (path_array);
}
