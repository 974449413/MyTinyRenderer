#目标文件(无后缀)
draw_line_demo:DrawLine.o tgaimage.o main.o
	g++ main.o DrawLine.o tgaimage.o -o draw_line_demo

main.o:main.cpp
	g++ -c -std=c++11 main.cpp -o main.o

tgaimage.o:tgaimage.cpp
	g++ -c -std=c++11 tgaimage.cpp -o tgaimage.o

DrawLine.o:DrawLine.cpp
	g++ -c -std=c++11 DrawLine.cpp -o DrawLine.o

#清理
clean:
	rm *.o