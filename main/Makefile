CXX = g++
TARGET = a
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

CXXFLAGS = -c -Wall -std=c++17

$(TARGET):$(OBJ)
	$(CXX) -o $@ $^

%.o:%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY:clean
clean:
	rm *.o