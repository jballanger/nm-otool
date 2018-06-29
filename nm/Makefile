NAME = ft_nm
LIBFT = lft
SRC_NAME = main.c\
			nm.c\
			handle.c\
			section.c\
			symbol.c\
			sort.c\
			swap.c\
			check.c
OBJ_NAME = $(SRC_NAME:.c=.o)
SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
CC = clang
CPPFLAGS = -Iincludes
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

all: $(LIBFT) $(NAME)

lft:
	$(MAKE) -C libft

$(NAME): $(OBJ)
	$(CC) $^ -o $@  -Llibft -lft -fsanitize=address

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@$(MAKE) clean -C libft
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY : all, clean, fclean, re, lft
