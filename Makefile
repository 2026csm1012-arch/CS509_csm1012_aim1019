# ============================================================
# Common Makefile
# ============================================================

ASSIGNMENTS := assignment_01 assignment_02 assignment_03

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# ------------------------------------------------------------
# Default
# ------------------------------------------------------------

all: build

# ------------------------------------------------------------
# Build all assignments
# ------------------------------------------------------------

build:
	@echo "=========================================="
	@echo "Building all assignments"
	@echo "=========================================="
	@$(MAKE) -C assignment_01 all
	@$(MAKE) -C assignment_02 all
	@$(MAKE) -C assignment_03 all
	@echo ""
	@echo "All assignments built successfully."

# ------------------------------------------------------------
# Build individual assignments
# ------------------------------------------------------------

assignment_01:
	$(MAKE) -C assignment_01 all

assignment_02:
	$(MAKE) -C assignment_02 all

assignment_03:
	$(MAKE) -C assignment_03 all

# ------------------------------------------------------------
# Run individual assignments
# ------------------------------------------------------------

run1: assignment_01
	@cd assignment_01 && ./graph_runner

run2: assignment_02
	@cd assignment_02 && ./graph_runner

run3: assignment_03
	@cd assignment_03 && ./graph_runner

# ------------------------------------------------------------
# Build common wrapper
# ------------------------------------------------------------

common_wrapper: common_wrapper.cpp
	$(CXX) $(CXXFLAGS) common_wrapper.cpp -o common_wrapper

# ------------------------------------------------------------
# Run through common wrapper
# ------------------------------------------------------------

run: build common_wrapper
	@./common_wrapper

# ------------------------------------------------------------
# Clean everything
# ------------------------------------------------------------

clean:
	@echo "=========================================="
	@echo "Cleaning all assignments"
	@echo "=========================================="
	@$(MAKE) -C assignment_01 clean
	@$(MAKE) -C assignment_02 clean
	@$(MAKE) -C assignment_03 clean
	@rm -f common_wrapper
	@echo ""
	@echo "Clean completed."

# ------------------------------------------------------------
# Rebuild everything
# ------------------------------------------------------------

rebuild: clean build

# ------------------------------------------------------------
# Help
# ------------------------------------------------------------

help:
	@echo ""
	@echo "Available commands:"
	@echo ""
	@echo "  make              Build all assignments"
	@echo "  make build        Build all assignments"
	@echo "  make run          Run common assignment selector"
	@echo "  make run1         Run Assignment 1"
	@echo "  make run2         Run Assignment 2"
	@echo "  make run3         Run Assignment 3"
	@echo "  make clean        Clean all assignments"
	@echo "  make rebuild      Clean and rebuild"
	@echo "  make help         Show this help"
	@echo ""

.PHONY: all build assignment_01 assignment_02 assignment_03 \
        run1 run2 run3 run common_wrapper clean rebuild help
