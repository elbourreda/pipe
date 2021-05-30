NAME = pipex

CC = gcc 

CFLAGS = -Wall -Wextra -Werror 

SRC = *.c
	
all : $(NAME)

$(NAME): $(SRC)
	@$(CC)  $(SRC) -o $(NAME)
clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME) 
re:	fclean all
	