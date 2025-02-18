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

NAME = push_swap
CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEBUGGER = -g3
RM = rm -f
NORMINETTE = norminette
# ========================= DIRECTORIOS Y ARCHIVOS =========================== #
DIR_HEADERS = Inc/libft Inc/utils Inc
DIR_PS     = src/
DIR_UTILS  = Inc/utils
DIR_LIBFT  = Inc/libft

HEADERS = $(wildcard $(DIR_HEADERS)/*.h) \


DIRSOURCE   = src/
SOURCES.h = $(wildcard $(DIR_UTILS)/*.c) \
			$(wildcard $(DIR_LIBFT)/*.c)


SOURCES     = $(wildcard $(DIRSOURCE)*.c)
SRCS        = $(SOURCES.h) $(SOURCES)

OBJSDIR     = ./obj/
OBJS        = $(addprefix $(OBJSDIR), $(notdir $(SRCS:.c=.o)))

# ========================= COLORES PARA EL OUTPUT =========================== #

GREEN			= \033[0;32m
YELLOW			= \033[0;33m
CYAN			= \033[0;36m
MAGENTA			= \033[0;35m
RESET			= \033[0m

# ========================= REGLAS PRINCIPALES =============================== #
.PHONY: all clean fclean re n

all: n $(NAME)

$(NAME): $(OBJS)
	@echo "\n${MAGENTA}Compilando el ejecutable $(NAME)...${RESET}\n"
	$(CC) $(OBJS) $(CFLAGS) $(DEBUGGER) -o $(NAME)
	@echo "${CYAN}=================================================================================================================${RESET}"
	@echo "${GREEN}                                       [✔] $(NAME) successfully compiled.${RESET}                               "
	@echo "${CYAN}=================================================================================================================${RESET}"
	@echo "${MAGENTA}You should use: valgrind --leak-check=full -s./$(NAME) argv[1] argv[2] ....${RESET}"
# ========================= REGLAS PARA LOS OBJETOS ========================== #
$(OBJSDIR)%.o: $(DIRSOURCE)%.c
	@mkdir -p $(dir $@)
	@echo "${CYAN}Compilando objeto: $<${RESET}"
	$(CC) $(CFLAGS) $(addprefix -I, $(DIR_HEADERS)) -c $< -o $@

$(OBJSDIR)%.o: $(DIR_PS)/%.c
	@mkdir -p $(dir $@)
	@echo "${CYAN}Compilando objeto: $<${RESET}"
	$(CC) $(CFLAGS) $(addprefix -I, $(DIR_HEADERS)) -c $< -o $@

$(OBJSDIR)%.o: $(DIR_UTILS)/%.c
	@mkdir -p $(dir $@)
	@echo "${CYAN}Compilando objeto: $<${RESET}"
	$(CC) $(CFLAGS) $(addprefix -I, $(DIR_HEADERS)) -c $< -o $@

$(OBJSDIR)%.o: $(DIR_LIBFT)/%.c
	@mkdir -p $(dir $@)
	@echo "${CYAN}Compilando objeto: $<${RESET}"
	$(CC) $(CFLAGS) $(addprefix -I, $(DIR_HEADERS)) -c $< -o $@


# ========================= LIMPIEZA DE ARCHIVOS ============================= #

clean:
	@echo "${YELLOW}Limpiando archivos objeto...${RESET}"
	 $(RM) -r $(OBJSDIR)

fclean: clean
	@echo "${YELLOW}Eliminando el ejecutable $(NAME)...${RESET}"
	$(RM)	$(NAME)

re: fclean all
# ========================= OTRAS REGLAS ===================================== #
n:
	@echo "${CYAN}=================================${RESET}"
	@echo "${GREEN}         Norminette.      ${RESET}"
	@echo "${CYAN}=================================${RESET}"
	@echo "\n"
	-$(NORMINETTE) $(HEADERS) $(SRCS)
	@echo "\n"
	@echo "${GREEN}[✔] Norminette completa.${RESET}\n"

