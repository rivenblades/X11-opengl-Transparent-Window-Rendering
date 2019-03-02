all:main.c
	gcc -std=c99 -g3 -o main -DUSE_GLX_CREATE_CONTEXT_ATTRIB=1 -DUSE_GLX_CREATE_WINDOW=1 main.c -lX11 -lXrender -lGL -lm
WindowX11:WindowX11.cpp
	g++ -Wall -g -std=c++11 -c WindowX11.cpp -o WindowX11.o
testWindowX11:testWindowX11.cpp WindowX11
	g++ -Wall -g -std=c++11 -g WindowX11.o testWindowX11.cpp -o testWindowX11 -lX11 -lXrender -lGL -lm
