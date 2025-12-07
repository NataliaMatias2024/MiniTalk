# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/06 14:57:23 by namatias          #+#    #+#              #
#    Updated: 2025/12/07 11:27:37 by namatias         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#******************************************************************************#
#					              Variables                                    #
#******************************************************************************#

NAME =	$(CLIENT) $(SERVER)
CLIENT = client
SERVER = server

NAME_BONUS = $(CLIENT_BONUS) $(SERVER_BONUS)
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
IFLAGS = -I$(INC_DIR) -I$(LIB_DIR)include
LDFLAGS = -L $(LIB_DIR) -lft

LIBFT = $(LIB_DIR)libft.a

SRC_DIR =	./src/
OBJ_DIR =	./obj/
INC_DIR =	./include/
LIB_DIR =	./Libft/

CLIENT_FILES_C = client.c utils.c
SERVER_FILES_C = server.c utils.c
CLIENT_FILES_O = $(addprefix $(OBJ_DIR), $(CLIENT_FILES_C:.c=.o))
SERVER_FILES_O = $(addprefix $(OBJ_DIR), $(SERVER_FILES_C:.c=.o))

CLIENT_BONUS_C = client_bonus.c utils.c
SERVER_BONUS_C = server_bonus.c utils.c
CLIENT_BONUS_O = $(addprefix $(OBJ_DIR), $(CLIENT_BONUS_C:.c=.o))
SERVER_BONUS_O = $(addprefix $(OBJ_DIR), $(SERVER_BONUS_C:.c=.o))

#******************************************************************************#
#   				              Functions                                    #
#******************************************************************************#

all: $(LIBFT) $(NAME)

$(SERVER): $(SERVER_FILES_O)
	@$(CC) $(CFLAGS) $(SERVER_FILES_O) $(LDFLAGS) -o $(SERVER)
	@echo "Server created"

$(CLIENT): $(CLIENT_FILES_O)
	@$(CC) $(CFLAGS) $(CLIENT_FILES_O) $(LDFLAGS) -o $(CLIENT)
	@echo "Client created"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIB_DIR)

bonus: $(LIBFT) $(NAME_BONUS)

$(SERVER_BONUS): $(SERVER_BONUS_O)
	@$(CC) $(CFLAGS) $(SERVER_BONUS_O) $(LDFLAGS) -o $(SERVER_BONUS)
	@echo "Server bonus created"

$(CLIENT_BONUS): $(CLIENT_BONUS_O)
	@$(CC) $(CFLAGS) $(CLIENT_BONUS_O) $(LDFLAGS) -o $(CLIENT_BONUS)
	@echo "Client bonus created"

clean:
	@rm -f $(OBJ_DIR)*.o
	@$(MAKE) -C $(LIB_DIR) clean
	@echo	"Files *.o removed from $(OBJ_DIR)"

fclean:	clean
	@rm	-f	$(NAME)
	@rm -f	$(NAME_BONUS)
	@$(MAKE) -C $(LIB_DIR) fclean
	@echo "Files executable removed"

re: fclean all

.PHONY: all clean fclean re