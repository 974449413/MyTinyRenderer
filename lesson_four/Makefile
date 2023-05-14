CXX = g++
TARGET = perspective
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

CXXFLAGS = -c -Wall

$(TARGET):$(OBJ)
	$(CXX) -o $@ $^

%.o:%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY:clean
	rm *.o