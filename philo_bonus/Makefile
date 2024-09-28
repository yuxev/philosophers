# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/25 14:33:04 by aasselma          #+#    #+#              #
#    Updated: 2023/06/25 17:58:20 by aasselma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo_bonus

SRC = philo_bonus.c philo_utils_bonus.c philo_routin_bonus.c check_errors_bonus.c

OBJ	  = $(SRC:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

RM	  = rm -f

cc 	  = cc

# $(NAME): $(OBJ)
# 	$(CC) $(CFLAGS) -fsanitize=thread -g $(OBJ) -o $(NAME)

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
