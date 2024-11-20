/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 08:42:45 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/07 13:43:03 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_free_shell(t_shell *shell)
 * <\summary>
 * 
 * <description>
 * 	ft_free_all free all structure allocated for the program.
 * </description>
 *
 * <param type="t_shell *" name="shell">structure with all other struct</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_free_shell(t_shell *shell)
{
	if (shell->l_env != NULL)
		ft_free_env(shell->l_env);
	ft_free(shell);
}
