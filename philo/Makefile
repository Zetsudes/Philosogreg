CC = gcc
CFLAGS = -Wall -Wextra -Werror -lpthread

SRC = parsing.c \
	  utils.c \
	  init.c \
	  monitoring.c \
	  create.c \
	  philo.c \

OBJ = $(SRC:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re
