/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:04:44 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/14 08:43:17 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_get_last_fd_in(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_get_last_fd_in open all fd_in and close directely the fd if an other file
 * 	to open or if we nned a heredoc mode.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">structure pipex</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static int	ft_get_last_fd_in(t_pipex **pipex)
{
	int			i;
	int			fd_in;

	i = 0;
	fd_in = 0;
	while ((*pipex)->file_in[i] && (i < (*pipex)->nb_f_in))
	{
		fd_in = open((*pipex)->file_in[i], O_RDONLY);
		if (fd_in == -1)
		{
			if ((*pipex)->fd_in > 2)
				close((*pipex)->fd_in);
			(*pipex)->shell->code_exit = 1;
			ft_exit_cmd(*pipex, (*pipex)->file_in[i], NULL);
		}
		if (i + 1 < (*pipex)->nb_f_in || (*pipex)->ishere_doc)
			if (fd_in > 2)
				close(fd_in);
		i++;
	}
	return (fd_in);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_open_file_in(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_open_file_in set the fd_in value in the structure with the last fd_in 
 * 	openned or -1 in error case.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">structure pipex</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_open_file_in(t_pipex **pipex)
{
	int		fd_in;

	fd_in = ft_get_last_fd_in(pipex);
	if (fd_in > 2)
	{
		if ((*pipex)->fd_in > 2)
			close((*pipex)->fd_in);
		(*pipex)->fd_in = fd_in;
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_open_file_out(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_open_file_out open all file_out on the structure and return the last fd 
 * 	or -1 in error case.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">structure pipex</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static int	ft_open_file_out(t_pipex **pipex)
{
	char	*file;
	int		index;
	int		fd_out;

	index = 0;
	fd_out = 0;
	file = (*pipex)->file_out[index];
	while ((*pipex)->file_out && file && index < (*pipex)->nb_f_out)
	{
		if ((*pipex)->append)
			fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
			ft_exit_cmd(*pipex, file, NULL);
		if ((index + 1) < (*pipex)->nb_f_out)
			close(fd_out);
		file = (*pipex)->file_out[++index];
	}
	return (fd_out);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_get_fd_out(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_get_fd_out open a file or set fd_out to the STDOUT.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">structure pipex</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */
static void	ft_get_fd_out(t_pipex **pipex)
{
	int		fd_out;

	fd_out = ft_open_file_out(pipex);
	if (fd_out == -1)
	{
		if ((*pipex)->fd_out > 2)
			close((*pipex)->fd_out);
		(*pipex)->shell->code_exit = 1;
		(*pipex)->fd_out = -1;
		return ;
	}
	if (fd_out > 2)
	{
		if ((*pipex)->fd_out > 2)
			close((*pipex)->fd_out);
		(*pipex)->fd_out = fd_out;
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_get_fd_in_out(t_pipex **pipex)
 * </summary>
 *
 * <description>
 * 	ft_get_fd_in_out open the source file and the destination file and save each
 * 	 file descriptor on the struct.
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
void	ft_get_fd_in_out(t_pipex **pipex)
{
	if ((*pipex)->here_doc)
		ft_run_here_doc(pipex);
	if ((*pipex)->file_in)
		ft_open_file_in(pipex);
	if ((*pipex)->file_out)
		ft_get_fd_out(pipex);
}
