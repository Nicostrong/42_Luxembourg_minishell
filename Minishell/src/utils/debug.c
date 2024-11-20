/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:52:37 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/14 08:27:12 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

///////////////////////////////////////////////////////////////////////////////
//		DEBUG	DEBUG	DEBUG	DEBUG	DEBUG	DEBUG	DEBUG	DEBUG	DEBUG
///////////////////////////////////////////////////////////////////////////////

char	*ft_get_token_name(t_tok_type token)
{
	switch (token)
	{
		case T_WORD:			return "T_WORD";
		case T_BUILTIN:			return "T_BUILTIN";
		case T_CMD:				return "T_CMD";
		case T_OPT:				return "T_OPT";
		case T_PIPE:			return "T_PIPE";
		case T_OR:				return "T_OR";
		case T_AND:				return "T_AND";
		case T_F_IN:			return "T_F_IN";
		case T_HEREDOC:			return "T_HEREDOC";
		case T_EOF:				return "T_EOF";
		case T_F_OUT:			return "T_F_OUT";
		case T_F_OUT_APPEND:	return "T_F_OUT_APPEND";
		case T_FILENAME:		return "T_FILENAME";
		case T_SUBSHELL:		return "T_SUBSHELL";
		case T_DQUOTE:			return "T_DQUOTE";
		case T_SQUOTE:			return "T_SQUOTE";
		case T_END:				return "T_END";
		default:				return "UNKNOWN";
	}
}

static void	ft_print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->value)
			printf("Token = %s\t\ttype = %s\n", current->value, \
				ft_get_token_name(current->type));
		current = current->next;
	}
}

static void	ft_print_tree(t_tree *node, int depth)
{
	int	i;

	i = -1;
	if (!node)
		return ;
	while (++i < depth)
		printf("\t");
	printf("NODE : %s\n", ft_get_token_name(node->type));
	if (node->value)
	{
		i = -1;
		while (++i < depth)
			printf("\t");
		printf("Value : %s\n", node->value);
	}
	if (node->left)
	{
		i = -1;
		while (++i < depth)
			printf("\t");
		printf("LEFT :\n");
		ft_print_tree(node->left, depth + 1);
	}
	if (node->right)
	{
		i = -1;
		while (++i < depth)
			printf("\t");
		printf("RIGHT :\n");
		ft_print_tree(node->right, depth + 1);
	}
	if (node->next)
	{
		i = -1;
		while (++i < depth)
			printf("\t");
		printf("Next :\n");
		ft_print_tree(node->next, depth);
	}
}

void	ft_print_pipex(t_pipex *pipex, int i)
{
	printf("***************************************************************\n");
	printf("\t\t\tPIPEX N° %d\n", i);
	printf("***************************************************************\n");
	printf("last status code = %d\n", pipex->last_status);
	printf("===============================================================\n");
	printf("bool last cmd	= %s\n", pipex->last_cmd ? "TRUE" : "FALSE");
	printf("bool append	= %s\n", pipex->append ? "TRUE" : "FALSE");
	printf("bool here_doc	= %s\n", pipex->here_doc ? "TRUE" : "FALSE");
	printf("bool builtin	= %s\n", pipex->builtin ? "TRUE" : "FALSE");
	printf("bool squote	= %s\n", pipex->squote ? "TRUE" : "FALSE");
	printf("bool isand	= %s\n", pipex->isand ? "TRUE" : "FALSE");
	printf("bool isor	= %s\n", pipex->isor ? "TRUE" : "FALSE");
	printf("bool isheredoc	= %s\n", pipex->ishere_doc ? "TRUE" : "FALSE");
	printf("===============================================================\n");
	printf("Limiter = %s\n", pipex->limiter ? pipex->limiter : "(null)");
	printf("===============================================================\n");
	printf("Nb file in = %d\n", pipex->nb_f_in);
	printf("\tARRAY FD_FILE_IN\n");
	printf("fd du file_in => %d\n", pipex->fd_in);
	printf("\tARRAY FILE_IN\n");
	pipex->file_in ? ft_putstrarray(pipex->file_in) : printf("f_in == NULL\n");
	printf("Nb file out = %d\n", pipex->nb_f_out);
	printf("\tARRAY FD_FILE_OUT\n");
	printf("fd du file_out => %d\n", pipex->fd_out);
	printf("\tARRAY FILE_OUT\n");
	pipex->file_out ? ft_putstrarray(pipex->file_out) : printf("f_out = NUL\n");
	printf("===============================================================\n");
	printf("commande = %s\n", pipex->cmd ? pipex->cmd : "(null)");
	printf("path_cmd = %s\n", pipex->path_cmd ? pipex->path_cmd : "(null)");
	printf("===============================================================\n");/*
	printf("\t\tPATH ARRAY :\n");
	pipex->a_path ? ft_putstrarray(pipex->a_path) : printf("A_PATH == NULL\n");
	printf("===============================================================\n");
	printf("\t\tCMD OPT ARRAY :\n");
	pipex->a_cmd_opt ? ft_putstrarray(pipex->a_cmd_opt) : printf("A_CMD = N\n");
	printf("===============================================================\n");
	printf("\t\tENV ARRAY :\n");
	pipex->a_env ? ft_putstrarray(pipex->a_env) : printf("A_ENV == NULLLLLL");
	printf("===============================================================\n");*/
}

void	ft_print_all_pipex(t_pipex *pipex)
{
	int		i;
	t_pipex	*cur;

	i = 0;
	cur = pipex;
	while (cur)
	{
		ft_print_pipex(cur, ++i);
		cur = cur->next;
	}
}

void	ft_print_all(t_shell *shell)
{
	printf("Tokens de la commande :\n");
	ft_print_tokens(shell->l_token);
	printf("Arbre de la commande :\n");
	ft_print_tree(shell->tree, 0);
}
