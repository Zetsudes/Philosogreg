
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = philo_bonus.c \
	  parsing_bonus.c \
	  utils_bonus.c \
	  create_bonus.c \

OBJ = $(SRC:.c=.o)

NAME = philo_bonus

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
