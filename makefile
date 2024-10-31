PROJECT_NAME := atsp
BUILD_DIR := build

all: run

run: $(BUILD_DIR)/$(PROJECT_NAME)
	@echo "Running $(PROJECT_NAME) with maximum nice priority..."
	@sudo nice -n -20 ./$(BUILD_DIR)/$(PROJECT_NAME)

$(BUILD_DIR)/$(PROJECT_NAME): cmake_check
	@echo "Building $(PROJECT_NAME)..."
	@cmake --build $(BUILD_DIR)

cmake_check:
	@if [ ! -d "$(BUILD_DIR)" ]; then cmake -S . -B $(BUILD_DIR); fi

clean:
	@echo "Cleaning build dir..."
	@rm -rf $(BUILD_DIR)

rebuild: clean all

