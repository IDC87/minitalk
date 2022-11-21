# -*- Makefile -*-

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLIENT = client
SERVER = server
SRCS_Client =	client.c\
SRCS_server = server.c\

INCLUDES = -I ./libft 

LIBFT_A = ./libft/libft.a

LIBFT_DIR = ./libft

BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

OBJS = $(SRCS:%.c=%.o)
BOBJS = $(BONUS:%.c=%.o)       

all: $(NAME)

$(NAME):

$(SERVER): $(LIBFT)
	$(CC) $(CFLAGS) -o SRCS_server

$(CLIENT): $(LIBFT)

$(LIBFT): make all -C $(LIBFT_DIR)

$(NAME) : $(OBJS)
	@make all -C $(LIBFT_DIR) --no-print-directory
	@make -C $(MLX_LIB) --no-print-directory
	@$(CC) -o $(NAME) $(OBJS) $(LIBFT_A) 

bonus : $(BOBJS)
	@make all -C $(LIBFT_DIR) --no-print-directory
	@make -C $(MLX_LIB) --no-print-directory
	@$(CC) -o $(NAME) $(BOBJS) $(LIBFT_A) 


%.o : %.c
	$(CC) $(CFLAGS) -c -o $@  $<
#	$(CC) $(CFLAGS) -c -o $@ -I./ $<
	@echo ">>>>FILE $(NAME) CREATED!<<<<"

clean:
	@rm -f $(OBJS)
	@rm -f $(BOBJS)
	@make clean -C $(LIBFT_DIR) --no-print-directory

fclean:	clean
		@rm -f $(NAME)		
		@make fclean -C $(LIBFT_DIR) --no-print-directory
		@echo ">>>>FILE $(NAME) & Objects DELETED!<<<<"

re: fclean all

compile: 
	rm -rf valgrind-out.txt

valgrind:	$(NAME)
		valgrind $(valgrind) ./$(NAME) $(MAPS)
		

play:
	./so_long Maps/map2.ber

#$(shell find ./mainfiles/ -name "*.c")
#$(CC) -g -std=c11 $(CFLAGS) -ggdb3 $(INCLUDES) $(SRCS) $(LIBFT) $(MLX) && valgrind $(valgrind) ./a.out $(MAPS)
 

.PHONY: all clean fclean re