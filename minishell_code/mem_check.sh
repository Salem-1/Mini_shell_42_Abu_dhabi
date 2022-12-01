# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mem_check.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 18:44:27 by ahsalem           #+#    #+#              #
#    Updated: 2022/12/01 15:56:50 by ahsalem          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

valgrind --suppressions=readline.supp  --track-origins=yes --track-fds=yes --leak-check=full --show-leak-kinds=all  ./minishell 
# --child-silent-after-fork=yes 