# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgalvez- <fgalvez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/08 14:04:17 by fgalvez-          #+#    #+#              #
#    Updated: 2024/12/05 15:02:16 by fgalvez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ========================= VARIABLES GLOBALES =============================== #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEBUGGER = -g3
RM = rm -f
NORMINETTE = norminette

# ========================= DIRECTORIOS Y ARCHIVOS =========================== #

DIR_SRC  = src/
DIR_PIPEX = Inc/
DIR_UTILS  = Inc/utils/
DIR_LIBFT  = Inc/libft/

HEADERS = $(wildcard $(DIR_LIBFT)*.h) $(wildcard $(DIR_UTILS)*.h) $(wildcard $(DIR_PIPEX)*.h)

SOURCES      = $(wildcard $(DIR_SRC)*.c)
SOURCES_UTILS = $(wildcard $(DIR_UTILS)*.c)
SOURCES_LIBFT = $(wildcard $(DIR_LIBFT)*.c)

SRCS = $(SOURCES) $(SOURCES_UTILS) $(SOURCES_LIBFT)

OBJSDIR = obj/
OBJS = $(addprefix $(OBJSDIR), $(notdir $(SRCS:.c=.o)))

# ========================= COLORES PARA EL OUTPUT =========================== #

GREEN   = \033[0;32m
YELLOW  = \033[0;33m
CYAN    = \033[0;36m
MAGENTA = \033[0;35m
RESET   = \033[0m

# ========================= REGLAS PRINCIPALES =============================== #

.PHONY: all clean fclean re n

all: n $(NAME)

$(NAME): $(OBJS)
	@echo "\n${MAGENTA}Compilando el ejecutable $(NAME)...${RESET}\n"
	$(CC) $(OBJS) $(CFLAGS) $(DEBUGGER) -o $(NAME)
	@echo "${CYAN}=================================================${RESET}"
	@echo "${GREEN}  [✔] $(NAME) compilado con éxito. ${RESET}"
	@echo "${CYAN}=================================================${RESET}"
	@echo "${MAGENTA}Puedes usar: valgrind --trace-children=yes --leak-check=full -s ./$(NAME) infile "cmd1" "cmd2" outfile${RESET}"

# ========================= REGLAS PARA COMPILAR OBJETOS ===================== #

$(OBJSDIR)%.o: $(DIR_LIBFT)%.c | $(OBJSDIR)
	@echo "${CYAN}Compilando objeto: $<${RESET}"
	$(CC) $(CFLAGS) -I$(DIR_PIPEX) -c $< -o $@

$(OBJSDIR)%.o: $(DIR_SRC)%.c | $(OBJSDIR)
	@echo "${CYAN}Compilando objeto: $<${RESET}"
	$(CC) $(CFLAGS) -I$(DIR_PIPEX) -c $< -o $@

$(OBJSDIR)%.o: $(DIR_UTILS)%.c | $(OBJSDIR)
	@echo "${CYAN}Compilando objeto: $<${RESET}"
	$(CC) $(CFLAGS) -I$(DIR_PIPEX) -c $< -o $@

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)

# ========================= LIMPIEZA DE ARCHIVOS ============================= #

clean:
	@echo "${YELLOW}Eliminando archivos objeto...${RESET}"
	$(RM) -r $(OBJSDIR)

fclean: clean
	@echo "${YELLOW}Eliminando el ejecutable $(NAME)...${RESET}"
	$(RM) $(NAME)

re: fclean all

# ========================= NORMINETTE =============================== #
n:
	@echo "${CYAN}=================================${RESET}"
	@echo "${GREEN}         Norminette.      ${RESET}"
	@echo "${CYAN}=================================${RESET}"
	@echo "\n"
	-$(NORMINETTE) $(HEADERS) $(SRCS)
	@echo "\n"
	@echo "${GREEN}[✔] Norminette completa.${RESET}\n"
