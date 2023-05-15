CXX = g++
TARGET = perspective
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

CXXFLAGS = -c -Wall -I../../Library/

$(TARGET):$(OBJ)
	$(CXX) -o $@ $^

%.o:%.cpp	
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY:clean
clean:
	rm *.o $(TARGET)

