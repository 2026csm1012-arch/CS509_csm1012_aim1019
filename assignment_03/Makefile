CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic

TARGET = graph_runner


SRC = driver/main.cpp src/graph_io.cpp src/gradient_descent.cpp src/maxflow.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
