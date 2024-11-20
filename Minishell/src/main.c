/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:41:47 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/20 09:37:52 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status = 0;

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	static void	ft_header(void)
 * </summary>
 *
 * <description>
 *	ft_header print the header of Minishell.
 * </description>
 * 
 * <param type="void" name="void">void</param>
 *
 * <return>
 *	void.
 * </return>
 */
static void	ft_header(void)
{
	printf("%s%s\n", LINE1, LINE1A);
	printf("%s\n", LINE2);
	printf("%s\n", LINE3);
	printf("%s%s%s\n", LINE4, LINE4A, LINE4B);
	printf("%s%s%s\n", LINE5, LINE5A, LINE5B);
	printf("%s%s%s\n", LINE6, LINE6A, LINE6B);
	printf("%s%s%s\n", LINE7, LINE7A, LINE7B);
	printf("%s%s%s\n", LINE8, LINE8A, LINE8B);
	printf("%s%s%s\n", LINE9, LINE9A, LINE9B);
	printf("%s%s%s\n", LINE10, LINE10A, LINE10B);
	printf("%s%s%s\n", LINE11, LINE11A, LINE11B);
	printf("%s%s%s\n", LINE12, LINE12A, LINE12B);
	printf("%s%s\n", LINE13, LINE13A);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	void	ft_execute_command(char *command, t_shell **shell)
 * </summary>
 *
 * <description>
 *	ft_execute_command execute the command passed in parameter.
 *	It's transform the command in token and create a tree with this token.
 *	After that, it's create a pipex structure and fill it with the tree.
 *	And finaly, it's run the command.
 * </description>
 * 
 * <param type="char *" name="command">command to execute</param>
 * <param type="t_shell **" name="shell">shell structure of Minishell</param>
 *
 * <return>
 *	void.
 * </return>
 */
static void	ft_execute_command(char *command, t_shell **shell)
{
	if (!ft_strncmp(command, "exit", 4))
		ft_exit(*shell, command);
	(*shell)->l_token = ft_parse_cmd(command, *shell);
	ft_free(command);
	(*shell)->tree = ft_parse_token_to_tree(&(*shell)->l_token, *shell);
	//ft_print_all(*shell);	//	TO REMOVE
	ft_tree_to_pipex((*shell)->tree, shell, NULL);
	//ft_print_all_pipex((*shell)->l_pipex);	//	TO REMOVE
	ft_run_cmd(shell);
	ft_free_cmd(shell);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	minishell
 * </summary>
 *
 * <description>
 *	minishell is like a bash shell. It 's running with the same isue of bash
 *	and contant some builtin function.
 *	Builtin function :
 *		- env without options/arguments;
 *		- pwd without options;
 *		- cd with relative or absolut path;
 *		- unset without options;
 *		- export without options;
 *		- echo with -n option;
 *		- exit without options;
 *	Minishell is available to interpret :
 *		- multiple pipi;
 *	It've got a history commands.
 * </description>
 * 
 * <param type="void" name=""></param>
 *
 * <return>
 *	the exit code of the last command.
 * </return>
 */
int	main(void)
{
	char	*command;
	t_shell	*shell;

	shell = ft_init_shell();
	ft_signal();
	ft_header();
	while (1)
	{
		command = readline(TERM_NAME);
		if (!command)
			ft_exit_ctrl_d(shell);
		if (ft_strlen(command))
		{
			add_history(command);
			if (ft_check_syntax_input(command, shell))
				ft_execute_command(command, &shell);
		}
		else
			ft_free(command);
		if (g_status)
			shell->code_exit = g_status;
		g_status = 0;
	}
}
