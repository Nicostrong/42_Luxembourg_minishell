/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:33:12 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/07 13:43:07 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_free_tokens(t_shell **shell)
 * </summary>
 *
 * <description>
 * 	ft_free_tokens free all tokens on the linked list tokens.
 * </description>
 *
 * <param type="t_token *" name="tokens">linked list token</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_free_tokens(t_shell **shell)
{
	t_token	*cur;
	t_token	*next;

	if (!(*shell)->l_token)
		return ;
	cur = (*shell)->l_token;
	while (cur)
	{
		next = cur->next;
		if (cur->value)
			ft_free(cur->value);
		ft_free(cur);
		cur = next;
	}
}
