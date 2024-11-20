/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wilcard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:51:48 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/07 18:47:02 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	char	*ft_parse_string(char *string, t_shell *shell)
 * </summary>
 *
 * <description>
 *	ft_parse_string replace the variable in the string by their value.
 * </description>
 *
 * <param type="char *" name="string">string to parse</param>
 * <param type="t_shell *" name="shell">shell structure</param>
 *
 * <return>
 *	a pointer to a new string with the variable replaced.
 * </return>
 *
 */
int	ft_check_nb_wilcard(char *pattern)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*')
			count++;
		i++;
	}
	if (count == 1)
		return (1);
	return (0);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 *	char	*ft_parse_string(char *string, t_shell *shell)
 * </summary>
 *
 * <description>
 *	ft_parse_string replace the variable in the string by their value.
 * </description>
 *
 * <param type="char *" name="string">string to parse</param>
 * <param type="t_shell *" name="shell">shell structure</param>
 *
 * <return>
 *	a pointer to a new string with the variable replaced.
 * </return>
 *
 */
static char	**ft_create_a_wilcard(DIR *directory, char **a_files, char *pattern)
{
	struct dirent	*entry;
	int				count;	

	count = 0;
	entry = readdir(directory);
	while (entry)
	{
		if (ft_check_patern(pattern, entry->d_name))
		{
			a_files = ft_append_str(a_files, entry->d_name);
			if (!a_files[count])
			{
				closedir(directory);
				a_files = ft_free_array(a_files);
				return (NULL);
			}
			count++;
		}
		entry = readdir(directory);
	}
	closedir(directory);
	a_files[count] = NULL;
	return (a_files);
}

char	**ft_wilcard(char *pattern)
{
	DIR				*directory;
	char			**a_files;

	if (!pattern)
		return (NULL);
	a_files = (char **)calloc(1, sizeof(char *));
	if (!a_files)
		return (perror("calloc"), NULL);
	directory = opendir(".");
	if (!directory)
		return (perror("opendir"), ft_free(a_files), NULL);
	a_files = ft_create_a_wilcard(directory, a_files, pattern);
	return (a_files);
}
