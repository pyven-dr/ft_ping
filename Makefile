NAME := ft_ping

SRC_DIR		:= src
INCLUDE_DIR	:= include
BUILD_DIR	:= .build

CC		:= cc
MKDIR	:= mkdir -p

CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -I $(INCLUDE_DIR) -MD -MP
LDFLAGS		:= -lm

include src.mk
OBJ := $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))
DEP := $(OBJ:.o=.d)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) 

-include $(DEP)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
