/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_pipex_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:06:17 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 12:45:56 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	char	*ft_get_cmd(char *path_cmd)
 * </summary>
 *
 * <description>
 * 	ft_get_cmd return just the command at the end of the path.
 * </description>
 *
 * <param type="char *" name="path_cmd">path of the command</param>
 *
 * <return>
 * 	a pointer to a command.
 * </return>
 *
 */
static char	*ft_get_cmd(char *path_cmd)
{
	char	*cmd;
	int		i;

	if (!path_cmd)
		return (NULL);
	i = ft_strlen(path_cmd);
	while (i >= 0 && path_cmd[i] != '/')
		i--;
	cmd = ft_strdup(&path_cmd[i + 1]);
	return (cmd);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_pipex_cmd(t_tree *node, t_pipex *pipex)
 * </summary>
 *
 * <description>
 * 	ft_pipex_cmd fill the pipex structure for the token T_CMD.
 * </description>
 *
 * <param type="t_tree *" name="node">node to extract</param>
 * <param type="t_pipex *" name="pipex">pipex structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_pipex_cmd(t_tree *node, t_pipex *pipex)
{
	char	*cmd;

	cmd = ft_get_cmd(node->value);
	pipex->cmd = ft_strdup(cmd);
	pipex->path_cmd = ft_strdup(node->value);
	pipex->a_cmd_opt = ft_append_str(pipex->a_cmd_opt, node->value);
	ft_free(cmd);
}
