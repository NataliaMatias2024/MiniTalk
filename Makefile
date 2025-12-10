# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/06 14:57:23 by namatias          #+#    #+#              #
#    Updated: 2025/12/10 15:51:46 by namatias         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#******************************************************************************#
#					              Variables                                    #
#******************************************************************************#

NAME =	$(CLIENT) $(SERVER)
CLIENT = client
SERVER = server

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

#******************************************************************************#
#   				              Functions                                    #
#******************************************************************************#

all: $(LIBFT) $(NAME)

$(SERVER): $(SERVER_FILES_O) $(LIBFT)
	@$(CC) $(CFLAGS) $(SERVER_FILES_O) $(LDFLAGS) -o $(SERVER)
	@echo "Server created"

$(CLIENT): $(CLIENT_FILES_O) $(LIBFT)
	@$(CC) $(CFLAGS) $(CLIENT_FILES_O) $(LDFLAGS) -o $(CLIENT)
	@echo "Client created"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIB_DIR)

clean:
	@rm -f $(OBJ_DIR)*.o
	@$(MAKE) -C $(LIB_DIR) clean
	@echo	"Files *.o removed from $(OBJ_DIR)"

fclean:	clean
	@rm	-f	$(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean
	@echo "Files executable removed"

re: fclean all

.PHONY: all clean fclean re