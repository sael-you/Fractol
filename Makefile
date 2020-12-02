NAME = fractol

LFT = libft/libft.a

#LINALG = linearlib/linear_alg.a

SRCS = ./srcs/main.c

#SRCS = ./srcs/main1.c ./srcs/vec2.c ./srcs/vec1.c

INC = fractol.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -I /usr/X11/include -g -L /usr/X11/lib -lXext -lmlx -lX11 

EXEC = gcc -g $(CFLAGS) $(MLXFLAGS) -lmlx -framework OpenGL -framework AppKit

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(OBJ): $(SRCS)
	@echo "\033[2;33m"
	gcc -c $(SRCS)
	mv *.o ./srcs/
	@echo "\033[0m"

$(LFT):
	@echo "\033[2;33m"
	make -C libft
	@echo "\033[0m"

# $(LINALG):
# 	@echo "\033[2;33m"
# 	make -C linearlib
# 	@echo "\033[0m"

$(NAME): $(OBJ) $(LFT) 
	@echo "\033[2;33m"
	$(EXEC) $^ -o $@ $(MLXFLAGS)
	@echo "\033[0m"
	@echo "\033[32;3mAll Set !\n\033[0m"

clean:
	@echo "\033[2;31m"
	make -C libft clean
	# make -C linearlib clean
	rm -rf $(OBJ)
	@echo "\033[0m"
	@echo "\033[4;31mObject Files Deleted\033[0m"

fclean: clean
	@echo "\033[2;31m"
	make -C libft fclean
	# make -C linearlib fclean
	rm -rf $(NAME)
	@echo "\033[0m"
	@echo "\033[4;31mBinary File Deleted\n\033[0m"

re: fclean all