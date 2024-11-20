# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_minishell.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 14:34:30 by nfordoxc          #+#    #+#              #
#    Updated: 2024/11/03 15:36:51 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

cmd_env=(
	"env;exit"
	"env toto;exit"
	"env toto tata pipi;exit"
	"env -toto;exit"
	"envtoto;exit"
)

cmd_pwd=(
	"pwd;exit"
	"pwd toto;exit"
	"pwd toto tata pipi;exit"
	"pwd -toto;exit"
	"pwdtoto;exit"
)

cmd_cd=(
	"pwd;cd;pwd;exit"
	"pwd;cd ;pwd;exit"
	"pwd;cd ~;pwd;exit"
	"pwd;cd .;pwd;exit"
	"pwd;cd ..;pwd;exit"
	"pwd;cd - ;pwd;exit"
	"pwd;cd --;pwd;exit"
	"pwd;cd -toto;pwd;exit"
	"pwd;cd ---;pwd;exit"
	"pwd;cd ../toto;pwd;exit"
	"pwd;cd /home/toto;pwd;exit"
	"pwd;cd /tmp/;pwd;exit"
	"pwd;cdtoto;pwd;exit"
)

cmd_unset=(
	"unset;exit"
	"unset USERNAME;exit"
	"unset USERNAME MAIL;exit"
	"unset USERNAME TOTO MAIL;exit"
	"unset -toto USERNAME;exit"
	"unseting;exit"
)

cmd_export=(
	"export;exit"
	"export TOTO=toto;exit"
	"export -toto tototo;exit"
	"export toto toto;exit"
	"export toto=tata;exit"
	"export toto=tata=$TOTO=tata;exit"
	"export -;exit"
	"exporting;exit"
)

cmd_echo=(
	"echo;exit"
	"echo -n;exit"
	"echo toto;exit"
	"echo -n toto;exit"
	"echo -----------;exit"
	"echo -nnnnnnnnn;exit"
	"echo -nnnnn totot;exit"
	"echo -no toto;exit"
	"echo \"toto;exit"
	"echo \"toto\";exit"
	"echo \"$toto\";exit"
	"echo \"$USER\";exit"
	"echo \"$USER\" \"$PATH\";exit"
	"echo \"$USER\" \"$PATH;exit"
)


cmd_builtin=(
	"pwd;cd ..;pwd;cd;pwd;exit"
	"pwd;cd /home;pwd;cd -;pwd;cd --;pwd;exit"
	"pwd;cd ./src/builtin;pwd;cd;pwd;cd -;pwd;exit"
	"pwd;cd ..;pwd;cd;pwd;exit"
	"echo $OLDPWD;echo $PWD;echo $MAIL;exit"
	"env;unset MAIL SHELL;env;unset PWD OLDPWD;env;exit"
)

pipeline=(
	"cat Makefile -e | grep "CC" | wc -l > out;exit"
	"(cat -e main || cat -e ./src/main.c) | wc -l >> out;exit"
	"<< FIN cat -e | wc -l > out;exit"
	"cat <<< toto | tr 'o' 'i' | cat;exit"
)
all_cmd_arrays=(
	cmd_env
	cmd_pwd
	cmd_cd
	cmd_unset
	cmd_export
	cmd_echo
	cmd_builtin
	pipeline
)

crash=(
	"< > toto cat"
	"< Makefile cat >"
	"< Makefile cat >  >"
	"< Makefile cat > 	>"
	"> out cat <"
	"> out cat <		<"
)

execute_cmd_array() {
	local array_name=$1[@]
	local commands=("${!array_name}")
	for cmd in "${commands[@]}"; do
		echo "\033[1;94mExécution du test: $cmd\033[1;93m"
		echo -e "$cmd" | tr ';' '\n' | valgrind --tool=memcheck --leak-check=full --show-leak-kinds=definite,indirect,possible --track-fds=yes ./minishell > $MINIOUT
	done
}

execute_and_compare() {
    local array_name=$1[@]
    local commands=("${!array_name}")
    for cmd in "${commands[@]}"; do
        # echo -e "$cmd" | tr ';' '\n' | ./minishell > minishell_output 2> minishell_error
        # echo -e "$cmd" | tr ';' '\n' | bash > bash_output 2> bash_error
        # diff minishell_output bash_output > diff_output
        # diff minishell_error bash_error > diff_error
        
        # if [[ -s diff_output || -s diff_error ]]; then
        #     echo "Differences found for command: $cmd"
        #     echo "Output differences:"
        #     cat diff_output
        #     echo "Error differences:"
        #     cat diff_error
        # else
        #     echo "No differences for command: $cmd"
        # fi

        echo -e "$cmd" | tr ';' '\n' | valgrind --tool=memcheck --leak-check=full --show-leak-kinds=definite,indirect,possible --track-fds=yes ./minishell # > valgrind_output 2>&1
        # if grep -q "ERROR SUMMARY: 0 errors from 0 contexts" valgrind_output && grep -q "All heap blocks were freed -- no leaks are possible" valgrind_output; then
        #     echo "Valgrind: No memory leaks or file descriptor issues for command: $cmd"
        # else
        #      echo "Valgrind: Memory leaks or file descriptor issues found for command: $cmd"
        #     cat valgrind_output
        # fi

        # rm -f minishell_output minishell_error bash_output bash_error diff_output diff_error valgrind_output
    done
}

if [ $# -eq 1 ]; then
    case "$1" in
        "env") cmd_array="cmd_env";;
        "pwd") cmd_array="cmd_pwd";;
        "cd") cmd_array="cmd_cd";;
        "unset") cmd_array="cmd_unset";;
        "export") cmd_array="cmd_export";;
        "echo") cmd_array="cmd_echo";;
        "builtin") cmd_array="cmd_builtin";;
        *) echo "Invalid argument. Use one of: env, pwd, cd, unset, export, echo, builtin"; exit 1;;
    esac
	error_count=0
	make
	clear

	echo -e "\033[1;94m _______   ______   _______    _______ \033[0m"
	echo -e "\033[1;94m|__   __| |  ____| |   ____|  |__   __|\033[0m"
	echo -e "\033[1;94m   | |    | |___   |  |____      | |\033[0m"
	echo -e "\033[1;94m   | |    |  ___|  |_____  |     | |\033[0m"
	echo -e "\033[1;94m   | |    | |____   _____| |     | |\033[0m"
	echo -e "\033[1;94m   |_|    |______| |_______|     |_|\033[0m"
	echo ""
	echo -e "\t\t\033[1;93mBUILTIN $1\033[0m"
	echo ""
    execute_and_compare "$cmd_array"
else
	make
	clear

	echo -e "\033[1;94m _______   ______   _______    _______        _\033[0m"
	echo -e "\033[1;94m|__   __| |  ____| |   ____|  |__   __|      | |\033[0m"
	echo -e "\033[1;94m   | |    | |___   |  |____      | |         | |\033[0m"
	echo -e "\033[1;94m   | |    |  ___|  |_____  |     | |         | |\033[0m"
	echo -e "\033[1;94m   | |    | |____   _____| |     | |         | |\033[0m"
	echo -e "\033[1;94m   |_|    |______| |_______|     |_|         |_|\033[0m"
	echo ""
	echo -e "\t\t\033[1;93mBUILTIN ENV\033[0m"
	echo ""

	for cmd_array in "${all_cmd_arrays[@]}"; do

		execute_and_compare "$cmd_array"
	done

	echo ""
	echo -e "\033[1;94m _______   ______   _______    _______        _   _\033[0m"
	echo -e "\033[1;94m|__   __| |  ____| |   ____|  |__   __|      | | | |\033[0m"
	echo -e "\033[1;94m   | |    | |___   |  |____      | |         | | | |\033[0m"
	echo -e "\033[1;94m   | |    |  ___|  |_____  |     | |         | | | |\033[0m"
	echo -e "\033[1;94m   | |    | |____   _____| |     | |         | | | |\033[0m"
	echo -e "\033[1;94m   |_|    |______| |_______|     |_|         |_| |_|\033[0m"
	echo ""
	echo -e "\t\t\033[1;93mVALGRIND\033[0m"
	echo ""

fi