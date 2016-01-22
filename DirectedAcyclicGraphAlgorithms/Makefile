SRC=dagDriver.cpp topologicalSort.cpp shortestPath.cpp longestPath.cpp numberOfPaths.cpp
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o dagAlgorithms

.C.o: $<
	g++ -g -I./headers -c $<

clean:
	rm *.o dagAlgorithms
