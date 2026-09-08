CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic

TARGET = graph_runner

SRC = driver/main.cpp src/kmeans.cpp src/fastmap.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
