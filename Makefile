CXX = g++
TARGET = Myrenderer
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

#CXXFLAGS = -c -Wall -I../../Library/ -std=c++11 
CXXFLAGS = -c -Wall -std=c++11 

$(TARGET):$(OBJ)
	$(CXX) -o $@ $^

%.o:%.cpp	
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY:clean
clean:
	rm *.o $(TARGET)

