/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:23:25 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/14 08:33:05 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	char	**ft_get_all_key(t_env *env, int count)
 * </summary>
 *
 * <description>
 * 	ft_get_all_key creat an array with all key of the linked list env.
 * </description>
 *
 * <param type="t_env **" name="env">linked list env</param>
 * <param type="int" name="count">number ok key on linked list env</param>
 *
 * <return>
 *	an array of key.
 * </return>
 *
 */
char	**ft_get_all_key(t_env *env, int count)
{
	char	**a_key;
	int		index;
	t_env	*current;

	current = env;
	a_key = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!a_key)
		return (NULL);
	index = -1;
	while (current)
	{
		if (index < count)
			a_key[++index] = ft_strdup(current->key);
		current = current->next;
	}
	a_key[++index] = NULL;
	return (a_key);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_get_key(char *key_value)
 * </summary>
 *
 * <description>
 * 	ft_get_key get the first part of the string formated like "key=value".
 * </description>
 *
 * <param type="char *" name="key_value">string with key and value</param>
 *
 * <return>
 * 	a new pointer to the key.
 * </return>
 *
 */
static char	*ft_get_key(char *key_value)
{
	char	*key;
	char	**a_key_value;

	if (!key_value)
		return (NULL);
	a_key_value = ft_split(key_value, '=');
	if (!a_key_value)
		return (NULL);
	key = ft_strdup(a_key_value[0]);
	ft_free_array(a_key_value);
	return (key);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	char	*ft_get_value(char *key_value)
 * </summary>
 *
 * <description>
 * 	ft_get_value get the value of the string formated like key=value.
 * </description>
 *
 * <param type="char *" name="key_value">string with key and value</param>
 *
 * <return>
 *  a pointer to a sting with the value.
 * </return>
 *
 */
static char	*ft_get_value(char *key_value)
{
	char	*value;
	int		index_sep;

	if (!key_value)
		return (NULL);
	index_sep = ft_charchr(key_value, '=');
	if (index_sep == -1)
		return (NULL);
	value = ft_substr(key_value, ++index_sep, ft_strlen(key_value));
	return (value);
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	void	ft_run_export(t_pipex **pipex, int *code_retour)
 * </summary>
 *
 * <description>
 * 	ft_run_export export each key/value passed in argument.
 * </description>
 *
 * <param type="t_pipex **" name="pipex">structure pipex</param>
 * <param type="int *" name="code_retour">pointer to the return value</param>
 *
 * <return>
 * 	0 if success or 1 if error.
 * </return>
 *
 */
static void	ft_run_export(t_pipex **pipex, int *code_retour)
{
	char	*key;
	char	*value;
	int		index;

	index = -1;
	while ((*pipex)->a_cmd_opt[++index])
	{
		key = ft_get_key((*pipex)->a_cmd_opt[index]);
		if (ft_valid_key(key))
		{
			value = ft_get_value((*pipex)->a_cmd_opt[index]);
			if (ft_check_key((*pipex)->shell->l_env, key))
				ft_set_env_value(&(*pipex)->shell, key, value);
			else
				ft_export_value(&(*pipex)->shell, (*pipex)->a_cmd_opt[index]);
			ft_free(value);
		}
		else
		{
			ft_put_error_arg("export", (*pipex)->a_cmd_opt[index], E_EXPORT);
			*code_retour = 1;
		}
		ft_free(key);
	}
}

/*
 * <cat>minishell</cat>
 *
 * <summary>
 * 	int	ft_export(t_pipex *pipex)
 * </summary>
 *
 * <description>
 * 	ft_export is like a builtin function en bash. it's execute some function 
 * 	compared to an array of arguments.
 * </description>
 *
 * <param type="t_pipex *" name="pipex">structure pipex</param>
 *
 * <return>
 * 	0 if success or 1 if error.
 * </return>
 *
 */
int	ft_export(t_pipex **pipex)
{
	int		code_retour;

	if (!(*pipex)->a_cmd_opt)
		return (ft_print_export_env((*pipex)->shell, (*pipex)->fd_out));
	code_retour = 0;
	ft_run_export(pipex, &code_retour);
	if ((*pipex)->fd_out > 2)
		close((*pipex)->fd_out);
	return (code_retour);
}
