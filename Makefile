# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/17 13:27:43 by oivanyts          #+#    #+#              #
#    Updated: 2019/01/14 16:36:42 by oivanyts         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		    = lem-in

SRC_DIR         := ./src/
OBJ_DIR 	    := ./obj/
INC_DIR 	    := ./includes/
LIB_DIR         := ./libft/

LIBFT           := $(LIB_DIR)libft.a
LIBFT_INC       := $(LIB_DIR)includes/
LIBFT_FLAGS     := -lft -L $(LIB_DIR)

SRC             += find_way.c
SRC             += func.c
SRC             += func1.c
SRC             += main.c
SRC             += parce.c
SRC             += run_ants.c

CC              := gcc

LINK_FLAGS      := $(LIB_FLAGS)

INCLUDES 	    := $(addprefix $(INC_DIR), libftprintf.h)

HEADER_FLAGS    := -I $(INC_DIR) -I $(LIBFT_INC)

FLAGS		    := -Wall -Wextra -Werror

OBJ 		    := $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc $(OBJ) -lft -L libft -o $(NAME)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c $(INC_DIR)lem_in.h
	$(CC) -c $< -o $@ $(FLAGS) $(HEADER_FLAGS);

$(LIBFT):
	make -C $(LIB_DIR)

clean:
	rm -f $(OBJ)
	make clean -C $(LIB_DIR)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	make fclean -C $(LIB_DIR)

re: fclean all

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re
