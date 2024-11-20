/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:12:26 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/11 10:30:30 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	handle_signal(int sign)
 * </summary>
 *
 * <description>
 * 	handle_signal is the function to execute when the program catch a signal.
 * </description>
 *
 * <param type="int" name="sign">value of signal</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	handle_signal(int sign)
{
	if (sign == SIGINT)
	{
		g_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sign == SIGQUIT)
		return ;
	else if (sign == SIGTERM)
	{
		g_status = -1;
		printf("exit\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(EXIT_SUCCESS);
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_signal(void)
 * </summary>
 *
 * <description>
 *	ft_signal initialize the handler for the specific signal.
 * </description>
 *
 * <param type="void" name="void">void</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}
