#目标文件(无后缀)
draw_line_demo.exe:DrawLine.o tgaimage.o main.o model.o 
	g++ main.o DrawLine.o tgaimage.o model.o -o draw_line_demo

main.o:main.cpp
	g++ -c -std=c++11 main.cpp -o main.o

tgaimage.o:tgaimage.cpp
	g++ -c -std=c++11 tgaimage.cpp -o tgaimage.o

DrawLine.o:DrawLine.cpp
	g++ -c -std=c++11 DrawLine.cpp -o DrawLine.o

model.o:model.cpp
	g++ -c -std=c++11 model.cpp -o model.o

#清理
clean:
	rm *.o