# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# Target executable
TARGET = or_program

# Source and header files
SRC = main.cpp
HEADERS = simplex.hpp dual_simplex.hpp assignment.hpp transportation.hpp integer.hpp
OBJS = $(SRC:.cpp=.o)

# Default rule
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run rule
run: $(TARGET)
	./$(TARGET)

# Clean rule
clean:
	rm -f $(TARGET) $(OBJS)
