# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 22:34:02 by aobshatk          #+#    #+#              #
#    Updated: 2025/04/11 15:37:21 by aobshatk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

UTILS = ./utils/checkers.c ./utils/helpers.c
SRC = ./src/init_philos.c

UTILOBJS = $(patsubst %.c, ./objs/%.o, $(notdir $(UTILS)))
SRCOBJS = $(patsubst %.c, ./objs/%.o, $(notdir $(SRC)))
OBJS = $(UTILOBJS) $(SRCOBJS)

LIBR = philo.a

NAME = philo

./objs/%.o: ./utils/%.c
	@mkdir -p objs
	@$(CC) $(CFLAGS) -c $< -o $@

./objs/%.o: ./src/%.c
	@mkdir -p objs
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBR)
	@$(CC) $(CFLAGS) main.c objs/$(LIBR) -o $(NAME)
	@echo "Build complete"

all: $(NAME)

$(LIBR): $(OBJS)
	@ar rcs objs/$(LIBR) $(OBJS)

clean:
	@rm -f $(OBJS)
	@echo "Clean complete"

fclean: clean
	@rm -f ./objs/$(LIBR)
	@rm -f $(NAME)
	@rm -d objs
	@echo "Full clean complete"

re: fclean $(NAME)

.PHONY: all clean fclean re
