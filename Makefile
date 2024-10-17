# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/13 19:06:53 by lilmende          #+#    #+#              #
#    Updated: 2024/10/10 17:24:14 by lilmende         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wextra -Wall -Werror
LIBFT = ./libs/libft
HEADERS = ./includes/minishell.h
BIN= ./bin/
SRC_D= ./src/
CC = cc
LIBS = $(LIBFT)/libft.a -lreadline

SRC= minishell.c \
	 checks.c \

SRC:= $(addprefix $(SRC_D),$(SRC))

INCLUDES= -I includes -I $(LIBFT)/ -I $(LIBFT)/ft_printf/includes -I $(LIBFT)/gnl/includes
OBJS= $(patsubst $(SRC_D)%.c, $(BIN)%.o, $(SRC))

RED     = \033[2;31m
GREEN   = \033[0;32m
BGREEN  = \033[0;41m
YELLOW  = \033[2;33m
BLUE    = \033[2;34m
MAGEN   = \033[0;35m
CYAN    = \033[1;36m
RESET   = \033[0m

all: libft $(NAME)
	@echo "${YELLOW}    --    Compiled Program >>> ${GREEN}./$(NAME)${YELLOW}    --${RESET}"

libft:
	@make -C $(LIBFT)/ --no-print-directory

$(BIN)%.o: $(SRC_D)%.c
	@mkdir -p $(BIN)
	@$(CC) $(FLAGS) -o $@ -c $< && echo "${YELLOW}Compiling:${RESET} $(notdir $<)"

$(NAME): $(OBJS)
	@echo " "
	@echo "Creating file $(NAME) ..."
	@echo " "
	@$(CC) $(OBJS) $(INCLUDES) -o $(NAME) $(LIBS)

clean:
	@make clean -C $(LIBFT)/ --no-print-directory
	@if ls $(BIN) 1> /dev/null 2>&1; then \
	echo "${RED}Deleting objects...${RESET}"; \
		rm -rf $(BIN); \
		echo "${YELLOW}Done."; \
	else \
		echo "${YELLOW}No objects to delete."; \
	fi \

fclean: clean
	@make fclean -C $(LIBFT)/ --no-print-directory
	@echo "${RED}Removing executable..."
	@rm -rf $(NAME)
	@echo " "
	@echo " ${RED}    --    Program Removed ✔️    --${RESET}"
	@echo " "

re: fclean all

.PHONY: all, clean, fclean, re, libft
