NAME = minishell
FLAGS =  #-Wall -Wextra -Werror
SRC_FOLDER = ./src
BONUS_SRC_FOLDER = ./bonus_src
HEADER_FOLDER = ./includes
LIBFT_HEADER = ./libft/includes
LIBFT_FOLDER = ./libft
OBJECT_FOLDER = ./objects
BONUS_OBJECT_FOLDER = ./bonus_objects
LIBFT_LIB = libft.a
RED = \033[0;31m
GREEN = \033[0;32m
GOLD = \033[0;33m
RESET = \033[0m
BONUS_HEADER_FOLDER = ./bonus_header

SRC_FILES = minishell.c \
			env.c \
			to_delete.c \
			builtin.c \
			here_we_go.c \
			path.c \
			error.c \
			cmd.c \

BONUS_SRC_FILES =

OBJECT_FILES = $(SRC_FILES:.c=.o)
OBJECT_FILES := $(addprefix $(OBJECT_FOLDER)/, $(OBJECT_FILES))
BONUS_OBJECT_FILES = $(BONUS_SRC_FILES:.c=.o)
BONUS_OBJECT_FILES := $(addprefix $(BONUS_OBJECT_FOLDER)/, $(BONUS_OBJECT_FILES))
LIBFT_FILE := $(LIBFT_FOLDER)/$(LIBFT_LIB)

.PHONY = all bonus clean fclean re credit

all: credit $(NAME)

LIB_RULE:
	@make -C $(LIBFT_FOLDER)/

bonus: credit LIB_RULE $(BONUS_OBJECT_FILES)
	@gcc -g -I $(BONUS_HEADER_FOLDER) -I $(LIBFT_FOLDER)  $(BONUS_OBJECT_FILES) $(LIBFT_FOLDER)/$(LIBFT_LIB) $(LIBS) -o $(NAME)_bonus
	@echo
	@echo $(NAME)"_bonus created $(GOLD)successfully$(RESET)"

$(BONUS_OBJECT_FOLDER)/%.o: $(BONUS_SRC_FOLDER)/%.c
	@(mkdir $(BONUS_OBJECT_FOLDER) 2> /dev/null && echo "creating "$(BONUS_OBJECT_FOLDER)" folder $(GOLD){OK}$(RESET)") || true
	@gcc $(FLAGS) -g -I $(BONUS_HEADER_FOLDER) -I $(LIBFT_HEADER)  -o $@ -c $< && echo  "creating" $< "object $(GOLD){OK}$(RESET)"

$(NAME): LIB_RULE $(OBJECT_FILES)
	@gcc -g -I $(HEADER_FOLDER) -I $(LIBFT_FOLDER)  $(OBJECT_FILES) $(LIBFT_FOLDER)/$(LIBFT_LIB) $(LIBS) -o $@
	@echo
	@echo $(NAME)" created $(GREEN)successfully$(RESET)"

$(OBJECT_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	@(mkdir $(OBJECT_FOLDER) 2> /dev/null && echo "creating "$(OBJECT_FOLDER)" folder $(GREEN){OK}$(RESET)") || true
	@gcc $(FLAGS) -g -I $(HEADER_FOLDER) -I $(LIBFT_HEADER)  -o $@ -c $< && echo "creating" $< "object $(GREEN){OK}$(RESET)"

clean:
	@(rm $(OBJECT_FILES) 2> /dev/null && echo "$(RED)deleting$(RESET): " $(OBJECT_FILES)) || true
	@(rm -r $(OBJECT_FOLDER) 2> /dev/null && echo "$(RED)deleting$(RESET): " $(OBJECT_FOLDER)) || true
	@(rm $(BONUS_OBJECT_FILES) 2> /dev/null && echo "$(RED)deleting$(RESET): " $(BONUS_OBJECT_FILES)) || true
	@(rm -r $(BONUS_OBJECT_FOLDER) 2> /dev/null && echo "$(RED)deleting$(RESET): " $(BONUS_OBJECT_FOLDER)) || true
	@make -C $(LIBFT_FOLDER) clean

fclean: clean
	@(rm $(NAME) 2> /dev/null && echo "$(RED)deleting$(RESET): " $(NAME)) || true
	@(rm $(NAME)_bonus 2> /dev/null && echo "$(RED)deleting$(RESET): " $(NAME)_bonus) || true
	@(rm $(LIBFT_FOLDER)/$(LIBFT_LIB) 2> /dev/null && echo "$(RED)deleting$(RESET): " $(LIBFT_LIB)) || true

re: fclean $(NAME)

credit:
	@printf "					$(RED)_minishell made by:_$(RESET)\n"
