#第二版本的Makefile
CXX = g++
TARGET = resterization.exe
OBJ = main.o tgaimage.o triangle.o model.o

$(TARGET):$(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

main.o:main.cpp
	$(CXX) -c main.cpp 

	
tgaimage.o:tgaimage.cpp
	$(CXX) -c tgaimage.cpp 

	
triangle.o:triangle.cpp
	$(CXX) -c triangle.cpp 

model.o:model.cpp
	$(CXX) -c model.cpp 

clean:
	rm *.o