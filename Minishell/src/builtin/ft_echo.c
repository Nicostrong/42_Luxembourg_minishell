/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 09:55:36 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/07 08:58:54 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_print_echo(char **a_str, int opt_n, int fd_out)
 * </summary>
 *
 * <description>
 * 	ft_print_echo print all string passed in argument on fd.
 * </description>
 *
 * <param type="char **" name="a_str">array of string to print</param>
 * <param type="int" name="opt_n">bolean for option -n</param>
 * <param type="int" name="fd_out">file descriptor for output</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_print_echo(char **a_str, int opt_n, int fd_out)
{
	int	index;

	index = -1;
	while (a_str && a_str[++index])
	{
		ft_putstr_fd(a_str[index], fd_out);
		if (a_str[index + 1])
			ft_putchar_fd(' ', fd_out);
	}
	if (!opt_n)
		ft_putchar_fd('\n', fd_out);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_check_opt(char *str)
 * </summary>
 *
 * <description>
 * 	ft_check_opt check if the function echo has the -n option
 * </description>
 *
 * <param type="char *" name="str">string to evaluate</param>
 *
 * <return>
 * 	1 if option -n defined or 0 if not.
 * </return>
 *
 */
static int	ft_check_opt(char *str)
{
	int	index;

	index = -1;
	if (str[++index] == '-')
	{
		while (str[++index])
			if (str[index] != 'n')
				return (0);
		return (1);
	}
	return (0);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_echo(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_echo is like the echo builtin function in bash.
 * 	It's print all value passed in argument.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">pipex structure</param>
 *
 * <return>
 * 	0 if success or 1 if error.
 * </return>
 *
 */
int	ft_echo(t_pipex **pipex)
{
	int	fd_out;

	fd_out = STDOUT_FILENO;
	if ((*pipex)->fd_out > 2)
		fd_out = (*pipex)->fd_out;
	if (!(*pipex)->a_cmd_opt)
		ft_putendl_fd("", fd_out);
	else if (ft_check_opt((*pipex)->a_cmd_opt[0]))
		ft_print_echo((*pipex)->a_cmd_opt + 1, 1, fd_out);
	else
		ft_print_echo((*pipex)->a_cmd_opt, 0, fd_out);
	if ((*pipex)->fd_out > 2)
		close((*pipex)->fd_out);
	return (0);
}
