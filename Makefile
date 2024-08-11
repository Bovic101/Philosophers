# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/08 21:42:27 by vodebunm          #+#    #+#              #
#    Updated: 2024/08/11 05:35:48 by vodebunm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the executable
NAME = philo

# Source files - all .c files in the Philosophers directory
SRCS = $(wildcard ../Philosophers/*.c)

# Header files directory
HEADER_DIR = ../Philosophers

# Hidden directory for object files
OBJDIR = .objs

# Compiler and flags
CC = cc
CFLAGS = -I$(HEADER_DIR)

# Object files
OBJS = $(SRCS:../Philosophers/%.c=$(OBJDIR)/%.o)

# All Rules
all: $(NAME)

# Link the final executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compile object files from source files
$(OBJDIR)/%.o: ../Philosophers/%.c $(HEADER_DIR)/*.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to hide (move) all object files to the hidden directory
hide: all
	@mkdir -p $(OBJDIR)
	@mv *.o $(OBJDIR) 2>/dev/null || true

# Clean object files
clean:
	rm -f $(OBJDIR)/*.o

# Clean everything including the final executable
fclean: clean
	rm -f $(NAME)

# Recompile everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re hide

