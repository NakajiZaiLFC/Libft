NAME	= libft.a
CC		= gcc
CFLAGS	= -Werror -Wall -Wextra
CFILES	= $(wildcard *.c)
OBJ		= $(CFILES:.c=.o)


$(NAME): $(OBJ)
	ar rs $(NAME) $(OBJ)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
