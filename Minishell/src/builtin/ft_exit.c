/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:24:40 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/14 08:30:39 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_calcul_code(char *arg, char **a_arg)
 * </summary>
 *
 * <description>
 * 	ft_calcul_code calcul the value of exit code.
 * </description>
 *
 * <param type="char *" name="env_val">environnement value</param>
 * <param type="char **" name="a_arg">array of argument</param>
 *
 * <return>
 * 	the exit code typed integer.
 * </return>
 *
 */
static int	ft_calcul_code(char *env_val, char **a_arg)
{
	int	value;

	value = ft_atoi(env_val);
	if (a_arg[1] && value)
	{
		if (value < 0)
			return (256 - ((value * -1) % 256));
		else
			return (value % 256);
	}
	else if (a_arg[1])
	{
		ft_put_error_arg("exit", env_val, E_EXIT);
		return (2);
	}
	else
		return (0);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_free_exit(t_shell *shell, char **a_arg, char *cmd, char *env_val)
 * </summary>
 *
 * <description>
 * 	ft_free_exit clear the history of readline, free the shell structure and 
 * 	free the command.
 * </description>
 *
 * <param type="t_shell *" name="shell">shell structure</param>
 * <param type="char **" name="a_arg">array of argument</param>
 * <param type="char *" name="cmd">command</param>
 * <param type="char **" name="a_arg">array of argument</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_free_exit(t_shell *shell, char **a_arg, char *cmd, char *env_val)
{
	rl_clear_history();
	if (shell)
		ft_free_shell(shell);
	if (cmd)
		ft_free(cmd);
	if (a_arg)
		ft_free_array(a_arg);
	if (env_val)
		ft_free(env_val);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_exit(t_shell *shell, char *cmd)
 * </summary>
 *
 * <description>
 * 	ft_exit clear all history command and free all struct and linked list.
 * 	Exit with the number passed in argument.
 * </description>
 *
 * <param type="t_shell *" name="shell">shell structure</param>
 * <param type="char *" name="cmd">command</param>
 *
 * <return>
 * 	0 if success or the number passed in argument.
 * </return>
 *
 */
void	ft_exit(t_shell *shell, char *cmd)
{
	char	**a_arg;
	char	*env_val;
	int		code_exit;

	a_arg = ft_split(cmd, ' ');
	if (a_arg[1] && a_arg[2])
	{
		ft_put_error_cmd("exit", E_ARG);
		ft_free_array(a_arg);
		exit(1);
	}
	else if (a_arg[1] && a_arg[1][0] == '$')
		env_val = ft_strdup(ft_get_env_value(shell, a_arg[1]));
	else
		env_val = ft_strremoveset(a_arg[1], "'\"");
	code_exit = ft_calcul_code(env_val, a_arg);
	printf("exit\n");
	ft_free_exit(shell, a_arg, cmd, env_val);
	exit(code_exit);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_exit_ctrl_d(t_shell *shell)
 * </summary>
 *
 * <description>
 * 	ft_exit_ctrl_d exit the program when ctrl + d is pressed.
 * 	Clear all history command and free all struct and linked list.
 * </description>
 *
 * <param type="t_shell *" name="shell">shell structure</param>
 *
 * <return>
 * 	EXIT_SUCCESS.
 * </return>
 *
 */
void	ft_exit_ctrl_d(t_shell *shell)
{
	printf("exit\n");
	rl_clear_history();
	ft_free_shell(shell);
	exit (EXIT_SUCCESS);
}
