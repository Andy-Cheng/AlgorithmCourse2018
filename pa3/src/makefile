CXX = g++
CFLAGS = -O3 -std=c++11

EXE1 = router
OBJ1 = main.o  parser.o

# Executable
all: $(OBJ1)
	$(CXX) -Bstatic -o $(EXE1) $(CFLAGS) $(OBJ1)

# Object file
%.o:  %.cpp
	$(CXX) -c $(CFLAGS) $<

clean:
	rm $(OBJ1) $(EXE1)