#this target will compile all the files
all: run
	
run: main.o CommandProcessor.o Menu.o
		g++ -std=c++11 main.cpp CommandProcessor.cpp Menu.cpp -o Run

main.o: main.cpp CommandProcessor.cpp Menu.cpp
		g++ -std=c++11  main.cpp CommandProcessor.cpp Menu.cpp

CommandProcessor.o: main.cpp CommandProcessor.cpp Menu.cpp Graph.h Digraph.h 
		g++ -std=c++11 main.cpp CommandProcessor.cpp Menu.cpp Graph.h Digraph.h 

Menu.o: Menu.cpp CommandProcessor.cpp main.cpp 
	g++ -std=c++11 Menu.cpp CommandProcessor.cpp main.cpp 

Clean:
	rm -rf *o run
