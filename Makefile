# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djoao <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/18 18:36:01 by djoao             #+#    #+#              #
#    Updated: 2024/09/18 18:36:07 by djoao            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = minitalk

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft -Ift_printf

LIBFT_DIR = ./libft
PRINTF_DIR = ./ft_printf

LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a

SERVER_SRCS = ./srcs/server.c
CLIENT_SRCS = ./srcs/client.c

GREEN = \033[32m
RESET = \033[0m
RED = \033[31m

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

$(NAME):	$(LIBFT) $(PRINTF) $(SERVER_OBJS) $(CLIENT_OBJS)
	@$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIBFT) $(PRINTF) -o server
	@$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBFT) $(PRINTF) -o client
	@sleep 1
	clear
	@printf "$(GREEN)." ; sleep 1
	@printf "$(GREEN)." ; sleep 1
	@printf "$(GREEN)." ; sleep 1
	@printf "$(GREEN)Server And Client Are ONLINE!$(RESET)\n"

all:	$(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(PRINTF):
	@make -C $(PRINTF_DIR)

clean:
	@rm -f $(SERVER_OBJS) $(CLIENT_OBJS)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(PRINTF_DIR)

fclean: clean
	@rm -f client server
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)
	@sleep 1
	clear
	@printf "$(RED)." ; sleep 1
	@printf "$(RED)." ; sleep 1
	@printf "$(RED)." ; sleep 1
	@printf "$(RED)Server and Client Are OFFLINE!$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
