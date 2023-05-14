#第三个版本

CXX = g++
TARGET = zBuffer
OBJ = DrawLine.o main.o model.o tgaimage.o z_buffer.o

CXXFLAGS = -c -Wall

#$^：表示全部依赖，即$(OBJ)的全部
$(TARGET):$(OBJ)
	$(CXX) -o $@ $^

#$<：表示依赖的第一项，即%.cpp中的第一项
#%：表示上面生成最终目标的全部文件
%.o:%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
.PHONY:clean	
	rm -f *.o