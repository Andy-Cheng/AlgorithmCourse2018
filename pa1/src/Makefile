CXX = g++
CFLAGS = -g -std=c++11
CFLAGS = -O3 -std=c++11

EXE1 = insertionSort
OBJ1 = insertionSort.o parser.o
EXE2 = mergeSort
OBJ2 = mergeSort.o parser.o
EXE3 = quickSort
OBJ3 = quickSort.o parser.o
EXE4 = heapSort
OBJ4 = heapSort.o parser.o

# Executable
all: $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)
	$(CXX) -Bstatic -o $(EXE1) $(CFLAGS) $(OBJ1)
	$(CXX) -Bstatic -o $(EXE2) $(CFLAGS) $(OBJ2)
	$(CXX) -Bstatic -o $(EXE3) $(CFLAGS) $(OBJ3)
	$(CXX) -Bstatic -o $(EXE4) $(CFLAGS) $(OBJ4)

# Object file
%.o:  %.cpp
	$(CXX) -c $(CFLAGS) $<

clean:
	rm *.o $(EXE1) $(EXE2) $(EXE3) $(EXE4)
	