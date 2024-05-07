NAME        = philo
INCLUDES    = includes/
SRC_DIR     = src/
OBJ_DIR     = obj/

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -fsanitize=thread
PRFLAGS     = -ldl  -pthread -lm
RM          = rm -rf


SRC_FILES  += main utils init death fork threads
SRC         = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

OBJ         = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJ_CACHE   = .cache_exists

###

all: 			 $(NAME)

$(NAME): 		$(OBJ)
					$(CC) $(CFLAGS) $(PRFLAGS) $(OBJ) -o $(NAME)
					@echo "\033[0;32m$(shell echo $(NAME) | tr '[:lower:]' '[:upper:]') : COMPILED\033[0m"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_CACHE)
					@echo "Compiling $<"
					@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJ_CACHE):
					@mkdir -p $(OBJ_DIR)

clean:
					$(RM) $(OBJ_DIR)
					$(RM) $(OBJ_CACHE)
					@echo "Philo and libs object files cleaned!"

fclean: 		clean
					$(RM) $(NAME)
					@echo "Philo and libs executable files cleaned!"
					rm -f $(MLX_DIR)build/CMakeCache.txt

re: 			fclean all
					@echo "Cleaned and rebuilt everything for Philo!"

.PHONY:			all clean fclean re

.SILENT:
