CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC = \
src/main.cpp \
src/graph/GraphAML.cpp src/graph/GraphAL.cpp \
src/algorithm/DFS.cpp src/algorithm/DFSStack.cpp src/algorithm/BFS.cpp \
src/algorithm/TreeBuilder.cpp src/algorithm/ShortestPath.cpp \
src/container/Stack.cpp

TARGET = project4

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
