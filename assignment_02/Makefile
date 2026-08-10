# ==========================================
# Compiler
# ==========================================
CXX = g++

# ==========================================
# Compiler Flags
# ==========================================
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# ==========================================
# Include Directory
# ==========================================
INCLUDES = -Isrc

# ==========================================
# Executable Name
# ==========================================
TARGET = graph_runner

# ==========================================
# Source Files
# ==========================================
SOURCES = \
	driver/main.cpp \
	src/runner.cpp \
	src/graph_io.cpp \
	src/csr.cpp \
	src/bfs.cpp \
	src/dfs.cpp \
	src/sssp.cpp \
	src/bellman_ford.cpp \
	src/floyd_warshall.cpp \
	src/triangle.cpp \
	src/betweenness.cpp \
	src/components.cpp \
	src/output.cpp \
	src/compare.cpp

# ==========================================
# Object Files
# ==========================================
OBJECTS = $(SOURCES:.cpp=.o)

# ==========================================
# Default Target
# ==========================================
all: $(TARGET)

# ==========================================
# Link
# ==========================================
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# ==========================================
# Compile
# ==========================================
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# ==========================================
# Clean
# ==========================================
clean:
	rm -f $(OBJECTS) $(TARGET)

# ==========================================
# Rebuild
# ==========================================
rebuild: clean all

.PHONY: all clean rebuild