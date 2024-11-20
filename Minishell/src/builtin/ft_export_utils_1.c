/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:49:34 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 10:17:17 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_get_nb_key(t_env *env)
 * </summary>
 *
 * <description>
 * 	ft_get_nb_key count the number ok key in the linked list.
 * </description>
 *
 * <param type="t_env *" name="env">linked list env</param>
 *
 * <return>
 * 	number of key in linked list.
 * </return>
 *
 */
static int	ft_get_nb_key(t_env *env)
{
	int	count;

	count = 0;
	if (!env)
		return (count);
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_sort_a_str(char **a_key, int count)
 * </summary>
 *
 * <description>
 * 	ft_sort_a_str sort an array of string with buble sort.
 * </description>
 *
 * <param type="char **" name="a_key">array of key</param>
 * <param type="int" name="count">number of key in array</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_sort_a_str(char **a_key, int count)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < count)
	{
		j = -1;
		while (++j < count - 1)
		{
			if (ft_strcmp(a_key[j], a_key[j + 1]) > 0)
			{
				tmp = a_key[j];
				a_key[j] = a_key[j + 1];
				a_key[j + 1] = tmp;
			}
		}
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_put_export(t_shell *shell, char **a_key, int fd)
 * </summary>
 *
 * <description>
 * 	ft_put_export print on fd all key and value in correct format.
 * </description>
 *
 * <param type="t_shell *" name="shell">shell structure</param>
 * <param type="char **" name="a_key">array of key env</param>
 * <param type="int" name="fd">fd of output</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_put_export(t_shell *shell, char **a_key, int fd)
{
	char	*value;
	int		index;

	if (!a_key)
		return ;
	index = -1;
	while (a_key[++index])
	{
		value = ft_get_env_value(shell, a_key[index]);
		if (value)
		{
			ft_putstr_fd("export ", fd);
			ft_putstr_fd(a_key[index], fd);
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(value, fd);
			ft_putstr_fd("\"\n", fd);
		}
		else
		{
			ft_putstr_fd("export ", fd);
			ft_putendl_fd(a_key[index], fd);
		}
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_print_export_env(t_shell *shell, int fd_out)
 * </summary>
 *
 * <description>
 * 	ft_print_export_env get all key in env linked list and print in the correct 
 * 	format all key/value on the fd output.
 * 	format.
 * </description>
 *
 * <param type="t_shell *" name="shell">shell structure</param>
 * <param type="int" name="fd">fd of output</param>
 *
 * <return>
 * 	0 if success or 1 if error.
 * </return>
 *
 */
int	ft_print_export_env(t_shell *shell, int fd_out)
{
	char	**a_key;
	int		count;

	if (!shell->l_env)
	{
		if (fd_out > 2)
			close(fd_out);
		return (1);
	}
	if (fd_out < 2)
		fd_out = STDOUT_FILENO;
	count = ft_get_nb_key(shell->l_env);
	a_key = ft_get_all_key(shell->l_env, count);
	ft_sort_a_str(a_key, count);
	ft_put_export(shell, a_key, fd_out);
	ft_free_array(a_key);
	if (fd_out > 2)
		close(fd_out);
	return (0);
}
