/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:33:09 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/11/14 10:27:57 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*
 *	Define
 */

# define BLUE		"\033[0;34m"
# define RED		"\033[0;31m"
# define WHITE		"\033[0m"
# define ERROR_NAME	"\033[0;31mERROR$[🔥🔥🔥HELL🔥🔥🔥]$\033[0m"
# define E_PIPE		"syntax error near unexpected token '|'"
# define E_AND		"syntax error near unexpected token '&&'"
# define E_SYNTAX	"syntax error near unexpected token `newline'"
# define E_BADFILE	"No such file or directory"
# define E_NOPERM	"permission denied"
# define E_CMD		"Command not found"
# define E_ISDIR	"is a directory"
# define E_DQUOTE	"missing '\"'"
# define E_SQUOTE	"missing '"
# define E_SUB		"missing ')'"
# define E_HOME		"HOME not set"
# define E_OLDPWD	"OLDPWD not set"
# define E_PWD		"PWD not set"
# define E_ARG		"too many arguments"
# define E_EXIT		"numeric argument required"
# define E_EXPORT	"not a valid identifier"
# define E_CWD		"getcwd error"

/*
 *	Banniere init
 */

# define LINE1	"\033[1;94m ###################################################"
# define LINE1A "#########################################"
# define LINE2	"\033[1;94m #\033[1;91m     _.-^^---....,,--"
# define LINE3	"\033[1;94m #\033[1;91m _--                  --_"
# define LINE4	"\033[1;94m #\033[1;91m<                        >)"
# define LINE4A "\033[1;33m┌────────────────────────────────────────────────"
# define LINE4B "──────────────┐"
# define LINE5	"\033[1;94m #\033[1;91m|                         |"
# define LINE5A "\033[1;33m│ \033[1;36m______  _____ ______  _____  _     _ __"
# define LINE5B "_____ _       _       \033[1;33m│"
# define LINE6	"\033[1;94m #\033[1;91m \\._                   _./ "
# define LINE6A "\033[1;33m│\033[1;36m|  ___ \\(_____|  ___ \\(_____)| |   |"
# define LINE6B " (_______| |     | |      \033[1;33m│"
# define LINE7	"\033[1;94m #\033[1;91m    ```--. . , ; .--'''    "
# define LINE7A "\033[1;33m│\033[1;36m| | _ | |  _  | |   | |  _   | |__ | "
# define LINE7B "|_____  | |     | |      \033[1;33m│"
# define LINE8	"\033[1;94m #\033[1;91m          | |   |          "
# define LINE8A "\033[1;33m│\033[1;36m| || || | | | | |   | | | |  |  __)| "
# define LINE8B "|  ___) | |     | |      \033[1;33m│"
# define LINE9	"\033[1;94m #\033[1;91m       .-=||  | |=-.       "
# define LINE9A "\033[1;33m│\033[1;36m| || || |_| |_| |   | |_| |_ | |   "
# define LINE9B "| | |_____| |_____| |_____ \033[1;33m│"
# define LINE10	"\033[1;94m #\033[1;91m       `-=#$8&8$#=-'       "
# define LINE10A "\033[1;33m│\033[1;36m|_||_||_(_____|_|   |_(_____||_|   "
# define LINE10B "|_|_______|_______|_______)\033[1;33m│"
# define LINE11	"\033[1;94m #\033[1;91m          | ;  :|          "
# define LINE11A "\033[1;33m│                                       "
# define LINE11B "                       \033[1;33m│"
# define LINE12	"\033[1;94m #\033[1;91m _____.,-#8&$@8#&#~,._____ "
# define LINE12A "\033[1;33m└─────────────────────────────────────────"
# define LINE12B "─────────────────────┘"
# define LINE13	"\033[1;94m #############################################"
# define LINE13A "###############################################"

#endif