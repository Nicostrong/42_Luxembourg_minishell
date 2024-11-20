/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_access.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:42:23 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 12:46:29 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	char	**ft_concat_cmd_path(char **path, char *cmd)
 * </summary>
 *
 * <description>
 * 	ft_concat_cmd_path concat all path with a simple command.
 * </description>
 *
 * <param type="char **" name="path">aray of path</param>
 * <param type="char *" name="cmd">command to join with all path</param>
 *
 * <return>
 * 	an array of path with the command.
 * </return>
 *
 */
static char	**ft_concat_cmd_path(char **path, char *cmd)
{
	char	**path_cmd_array;
	char	*joined;
	int		index;
	int		nb_row;

	index = 0;
	nb_row = 0;
	while (path[nb_row])
		nb_row++;
	path_cmd_array = (char **)ft_calloc((nb_row + 1), sizeof(char *));
	if (!path_cmd_array)
		return (NULL);
	while (*path)
	{
		joined = ft_strjoin(*path++, "/");
		path_cmd_array[index] = ft_strjoin(joined, cmd);
		ft_free(joined);
		index++;
	}
	return (path_cmd_array);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	char	*ft_concat_path_cmd(t_env *env, char *cmd)
 * </summary>
 *
 * <description>
 * 	ft_concat_path_cmd test all path to find a binary of the command and return 
 * 	the complet path with the command.
 * </description>
 *
 * <param type="t_env *" name="env">environnement variable</param>
 * <param type="char *" name="cmd">command to find path</param>
 *
 * <return>
 * 	a pointer to an excecutable path with the cmd.
 * </return>
 *
 */
char	*ft_concat_path_cmd(t_env *env, char *cmd)
{
	char	**path;
	char	**path_tmp;
	char	*exec_path;
	int		index;

	path = ft_get_path(env);
	if (!path)
		return (ft_strdup(cmd));
	path_tmp = ft_concat_cmd_path(path, cmd);
	if (!path_tmp)
		return (ft_strdup(cmd));
	index = 0;
	while (path_tmp[index] && (access(path_tmp[index], X_OK) != 0))
		index++;
	if (path_tmp[index])
		exec_path = ft_strdup(path_tmp[index]);
	else
		exec_path = ft_strdup(cmd);
	if (!exec_path)
		return (NULL);
	path_tmp = ft_free_array(path_tmp);
	path = ft_free_array(path);
	return (exec_path);
}
