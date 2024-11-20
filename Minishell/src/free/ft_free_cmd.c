/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:31:52 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/07 13:35:06 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_free_cmd(t_shell **shell)
 * <\summary>
 * 
 * <description>
 * 	ft_free_all free all structure allocated for the program.
 * </description>
 *
 * <param type="t_shell **" name="shell">structure with all other struct</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_free_cmd(t_shell **shell)
{
	if ((*shell)->l_token)
		ft_free_tokens(shell);
	if ((*shell)->tree)
		ft_free_tree((*shell)->tree);
	if ((*shell)->l_pipex)
		ft_free_pipex(shell);
}
