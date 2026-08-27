CXX = c++
INCLUDE = -I include
FLAGS = -Wall -Wextra -Werror -std=c++98 $(INCLUDE)

NAME = phonebook

SRC = src/main.cpp src/Contact.cpp src/PhoneBook.cpp

OBJDIR = obj
OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)

# Colors
ESC = \033[
RESET = $(ESC)0m
BOLD = $(ESC)1m
GREEN = $(ESC)32m
YELLOW = $(ESC)33m
BLUE = $(ESC)34m
MAGENTA = $(ESC)35m
CYAN = $(ESC)36m
WHITE = $(ESC)37m
LILAC_TRUE   = \033[38;2;200;162;200m

$(NAME) :  format $(OBJ)
	@$(CXX) $(FLAGS) $(OBJ) -o $@

$(OBJDIR)/%.o: %.cpp 
	@mkdir -p $(dir $@)
	@$(CXX) $(FLAGS) -c $< -o $@
	@$(call show_progress,$<)

all : $(NAME)

clean:
	@rm -rf $(OBJDIR)
	@echo "$(YELLOW)🧹 .o files cleaned$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)$(BOLD)🧹 $(NAME)$(RESET)$(YELLOW) cleaned\n$(RESET)"

re: fclean all

format:
	@echo "$(LILAC_TRUE) \n made by: mona ✨ — 42 São Paulo, 2026\n$(RESET)"

.PHONY: all re fclean clean format

# # **************************************************************************** #
# # Detect terminal width and adjust behavior
# # **************************************************************************** #
TERM_WIDTH := $(shell tput cols 2>/dev/null || echo 80)
SAFE_WIDTH := $(shell echo $$(($(TERM_WIDTH) - 10)))
PROGRESS_WIDTH := $(shell echo $$(($(SAFE_WIDTH) > 50 ? 30 : $(SAFE_WIDTH) - 20)))

# # **************************************************************************** #
# # Define the progress bar and verbose output functions - CLEAN & SIMPLE
# # **************************************************************************** #
TOTAL_FILES := $(words $(SRC))
COMPILED_COUNT = 0
VERBOSE ?= 0

define show_progress
    @$(eval COMPILED_COUNT=$(shell echo $$(($(COMPILED_COUNT)+1))))
    @$(eval SHORT_PATH=$(shell echo $(1) | sed 's|^.*/||'))
    @$(eval PERCENT=$(shell echo $$(($(COMPILED_COUNT)*100/$(TOTAL_FILES)))))
    @$(eval BAR_SIZE=20)
    @$(eval BARS=$(shell echo $$(($(COMPILED_COUNT)*$(BAR_SIZE)/$(TOTAL_FILES)))))
    @$(eval REMAINING=$(shell echo $$(($(BAR_SIZE) - $(BARS)))))
    @$(eval PROGRESS=$(shell printf '█%.0s' $$(seq 1 $(BARS))))
    @$(eval EMPTY=$(shell printf '░%.0s' $$(seq 1 $(REMAINING))))

    @if [ $(VERBOSE) -eq 1 ]; then \
        echo "$(CYAN)$(BOLD)📄  Compiling $(RESET)$(CYAN)$(SHORT_PATH)$(RESET) ($(COMPILED_COUNT)/$(TOTAL_FILES))"; \
    else \
        printf "\r\033[K$(YELLOW)$(BOLD)🔄  $(RESET)$(GREEN)$(PROGRESS)$(WHITE)$(EMPTY)$(RESET) $(PERCENT)%% $(CYAN)$(SHORT_PATH)$(RESET)"; \
        if [ $(COMPILED_COUNT) -eq $(TOTAL_FILES) ]; then \
            printf "\n$(GREEN)$(BOLD)\n ✅✅✅ $(NAME) OK ✅✅✅$(RESET)\n\n"; \
        fi; \
    fi
endef
