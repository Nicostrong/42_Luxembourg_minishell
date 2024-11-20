/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:07:29 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/13 12:49:26 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_exit_here_doc(char **line, int *pipe_fd, t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_exit_here_doc free the line and close the write fd.
 * </description>
 *
 * <param type="char **" name="line">line getting on STDIN</param>
 * <param type="int *" name="pipe_fd">pipe for process communication</param>
 * <param type="t_pipex **" name="pipex">structure pipex</param>
 * 
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_exit_here_doc(char **line, int *pipe_fd, t_pipex **pipex)
{
	free(*line);
	get_next_line(-1);
	if (pipe_fd[1] > 2)
		close(pipe_fd[1]);
	if ((*pipex)->fd_in > 2)
		close((*pipex)->fd_in);
	(*pipex)->fd_in = pipe_fd[0];
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_run_here_doc(int *pipe_fd, t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_run_here_doc wait the input on STDIN and save all input in a pipe while 
 * 	the string isn't equal to a limiter word.
 * </description>
 *
 * <param type="int *" name="pipe_fd">pipe for process communication</param>
 * <param type="t_pipex **" name="pipex">structure pipex</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
void	ft_run_here_doc(t_pipex **pipex)
{
	int		pipe_fd[2];
	char	*line;
	size_t	len_limiter;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	len_limiter = ft_strlen((*pipex)->limiter);
	while (1)
	{
		ft_putstr_fd(RED"🔥H🔥E🔥L🔥L🔥"WHITE"doc🔥> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (line)
		{
			if (!ft_strncmp(line, (*pipex)->limiter, len_limiter) \
				&& line[len_limiter] == '\n')
				return (ft_exit_here_doc(&line, pipe_fd, pipex));
			write(pipe_fd[1], line, ft_strlen(line));
			free(line);
		}
		else
			return (ft_exit_here_doc(&line, pipe_fd, pipex));
	}
}
