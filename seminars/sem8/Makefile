CC = clang
FLAGS = -g -O2 -Wall -fsanitize=address,undefined,leak
BUILD_DIR = build
# указать название исходного C файла
TASK_NAME = barrier

all: $(BUILD_DIR)/$(TASK_NAME)

$(BUILD_DIR)/$(TASK_NAME): $(TASK_NAME).c build_dir
	$(CC) $(FLAGS) $< -o $@

build_dir:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all build_dir clean
