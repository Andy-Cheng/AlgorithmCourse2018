CXX = g++
CFLAGS = -g -std=c++11
CFLAGS = -O3 -std=c++11

EXE1 = mps
OBJ1 = maxPlanarSubset.o


# Executable
all: $(OBJ1)
	$(CXX) -Bstatic -o $(EXE1) $(CFLAGS) $(OBJ1)


# Object file
%.o:  %.cpp
	$(CXX) -c $(CFLAGS) $<

clean:
	rm *.o $(EXE1)
	