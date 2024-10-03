# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/13 19:06:53 by lilmende          #+#    #+#              #
#    Updated: 2024/10/03 12:46:34 by lsampiet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wextra -Wall -Werror -g3
LIBFT = ./libs/libft
HEADERS = ./includes/minishell.h
BIN= ./bin/
SRC_D= ./src/
CC = cc
LIBS = $(LIBFT)/libft.a

SRC= minishell.c

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
	@echo "${YELLOW}    --    --     --    Compiled Program >>> ${GREEN}./$(NAME)${YELLOW}    --    --   -- "

libft:
	@make -C $(LIBFT)/ --no-print-directory 

$(BIN)%.o: $(SRC_D)%.c
	mkdir -p $(BIN)
	$(CC) $(C_FLAGS) -o $@ -c $< && echo "${YELLOW}Compiling:${RESET} $(notdir $<)"
	
# %.o: %.c $(HEADERS)
# 	@$(CC) $(FLAGS) -o $@ -c $< && echo "${YELLOW}Compiling:${RESET} $(notdir $<)"

$(NAME): $(OBJS)
	@echo " "
	@echo "Creating file $(NAME) ..."
	@echo " "
	@$(CC) $(OBJS) $(LIBS) $(INCLUDES) -o $(NAME)
	@echo " ${BLUE}===================================================================="
	@echo "||                         ${RESET}${CYAN}PIPEX PROGRAM${RESET}${BLUE}                            ||"
	@echo " ===================================================================="
	@echo "                                                                     "
	@echo "     infile                                              outfile    "
	@echo "       ↓                        PIPE                        ↑       "
	@echo "       ↓           |---------------------------|            ↑       "
	@echo "       ↓             |                       |              ↑       "
	@echo "      cmd1   -->    end[1]       ↔       end[0]   -->     cmd2      "
	@echo "                     |                       |                      "
	@echo "                   |---------------------------|                    "
	@echo "                                                                    "
	@echo " ===================================================================="
	@echo "||               ${MAGEN}./pipex infile "cmd1" "cmd2" outfile${BLUE}                   ||"
	@echo " ====================================================================${RESET}"


clean:
	@make clean -C $(LIBFT)/ --no-print-directory
	@if ls $(BIN)
	echo "${RED}Deleting objects...${RESET}"; \
		rm -f $(BIN); \
		echo "${YELLOW}Done."; 
# @if ls $(OBJS) 1> /dev/null 2>&1; then 
# 	echo "${RED}Deleting objects of pipex...${RESET}"; 
# 	rm -f $(OBJS); 
# 	echo "${YELLOW}Done."; 
	else \
		echo "${YELLOW}No objects to delete."; \
	fi
# fi ???

fclean: clean
	@make fclean -C $(LIBFT)/ --no-print-directory
	@echo "${RED}Removing executable..."
	@rm -rf $(NAME)
	clear
	@echo " ${RED}--    --    --    --    --    --    --    --    --    --    --    --"
	@echo "                          Programa Removed ✔️                         "
	@echo " --    --    --    --    --    --    --    --    --    --    --    --${RESET}"

re: fclean all

.PHONY: all, clean, fclean, re, libft
