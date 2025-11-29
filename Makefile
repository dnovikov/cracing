BUILD_DIR ?= build

CMAKE_GENERATOR ?= "Unix Makefiles"

ifdef DEBUG
	CMAKE_BUILD_TYPE ?= Debug
else
	CMAKE_BUILD_TYPE ?= Release
endif


.PHONY: all configure build clean rebuild

all: build

configure:
	@echo "Configuring $(CMAKE_BUILD_TYPE)..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. -G $(CMAKE_GENERATOR) -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)

build: configure
	@echo "Building $(CMAKE_BUILD_TYPE)..."
	@cmake --build $(BUILD_DIR) --config $(CMAKE_BUILD_TYPE)

clean:
	@rm -rf $(BUILD_DIR)
	@echo "Cleaned up"

rebuild: clean build
