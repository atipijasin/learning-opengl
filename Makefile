BUILD_DIR = build

TARGET = learning-opengl 

all: clean configure build-local run

configure:
	@echo "Configuring the project..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake ..

build-local:
	@echo "Building the project..."
	@$(MAKE) -C $(BUILD_DIR)

run:
	@echo "Running the project..."
	@./$(BUILD_DIR)/$(TARGET)

clean:
	@echo "Cleaning the build directory..."
	@rm -rf $(BUILD_DIR)

install:
	@echo "Installing the project..."
	@$(MAKE) -C $(BUILD_DIR) install
