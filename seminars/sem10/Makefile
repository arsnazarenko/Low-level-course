CC = clang
FLAGS = -g -O2 -Wall -std=c17 -fsanitize=address,undefined,leak
B_DIR = build
# укажите название исходного С файла
TASK_NAME = prep6

all: $(B_DIR)/$(TASK_NAME) 

$(B_DIR)/$(TASK_NAME): $(TASK_NAME).c build_dir
	$(CC) $(FLAGS) $< -o $@

build_dir:
	mkdir -p $(B_DIR)

clean:
	rm -rf $(B_DIR)

.PHONY: all build_dir clean
