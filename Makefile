all: demo.cpp demo2.cpp
	rm -f demo cdemo demo2
#	gcc cdemo.c -o cdemo
	g++ -Wall demo.cpp -o demo
	g++ -Wall demo2.cpp -o demo2