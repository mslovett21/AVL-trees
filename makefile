all: main

main: main.o tree.o avl.o tree_collection.o
	 g++ -std=c++11 -g main.o tree.o avl.o tree_collection.o -o main
	
main.o: main.cpp tree.h tree.cpp avl.h avl.cpp tree_collection.h tree_collection.cpp 
	g++ -std=c++11 -c main.cpp

tree_collection.o: tree_collection.h tree_collection.cpp avl.h avl.cpp tree.h tree.cpp
	g++ -std=c++11 -c tree_collection.cpp

avl.o: avl.h avl.cpp tree.h tree.cpp
	g++ -std=c++11 -c avl.cpp

tree.o: tree.cpp tree.h
	g++ -std=c++11 -c tree.cpp

 clean:
	rm *.o
	rm main
