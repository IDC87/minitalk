# -*- Makefile -*-

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLIENT = client
SERVER = server
SRCS_Client = client.c\
SRCS_Server = server.c\

LIBFT = ./libft/libft.a

LIBFT_DIR = ./libft 

all: $(SERVER) $(CLIENT)

$(SERVER): $(LIBFT)
	@gcc -Wall -Wextra -Werror -o server server.c minitalk.h ./libft/libft.a
	@echo "Server ready to start!"

$(CLIENT): $(LIBFT)
	@gcc -Wall -Wextra -Werror -o client client.c minitalk.h ./libft/libft.a
	@echo "Client ready to start!"
# Make libft
bonus: $(LIBFT)
	@gcc -Wall -Wextra -Werror -o server server_bonus.c minitalk.h ./libft/libft.a
	@gcc -Wall -Wextra -Werror -o client client_bonus.c minitalk.h ./libft/libft.a

$(LIBFT):  
	make -C $(LIBFT_DIR) --no-print-directory


clean:
	@rm -f $(SERVER)
	@rm -f $(CLIENT)
	@make clean -C $(LIBFT_DIR) --no-print-directory

fclean:	clean
		@rm -f $(NAME)		
		@make fclean -C $(LIBFT_DIR) --no-print-directory
		@echo ">>>>FILE $(NAME) & Objects DELETED!<<<<"

re: fclean all
		

.PHONY: all clean fclean re