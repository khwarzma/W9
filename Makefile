BUILD_DIR=build

.PHONY: all build clean run

all: build

build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..
	cd $(BUILD_DIR) && make

run:
	./$(BUILD_DIR)/W9

clean:
	rm -rf $(BUILD_DIR)