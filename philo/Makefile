# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 03:59:04 by aasselma          #+#    #+#              #
#    Updated: 2023/07/04 16:50:18 by aasselma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = philo

SRC   = philo.c philo_utils.c philo_routin.c check_errors.c

OBJ	  = $(SRC:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

RM	  = rm -f

cc 	  = cc

# $(NAME): $(OBJ)
# 	$(CC) $(CFLAGS) -fsanitize=address -g $(OBJ) -o $(NAME)

$(NAME) : $(OBJ)
	@$(cc) $(FLAGS) $(OBJ) -o $(NAME)
	@printf "\033[1;32mfiles compiled successfully \033[0m\n"

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@printf "\033[1;32mobjects files removed successfully\033[0m\n"

fclean: clean
	@$(RM) $(NAME)

re : fclean $(NAME)
