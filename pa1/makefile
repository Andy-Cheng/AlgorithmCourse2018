# EXEDIR = ./exe
# SRCDIR = ./src
# OBJDIR = ./obj
CC=g++ -std=c++11 
CFLAGS= -I 
DEPS = parser.h
# example: ${OBJ}
# 	${CC} -o $@ $^ $(CFLAGS) 
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS).

insertionSort: insertionSort.o parser.o
	${CC} -o $@ $^ ${CFLAGS}. 
mergeSort: mergeSort.o parser.o
	${CC} -o $@ $^ ${CFLAGS}. 
heapSort: heapSort.o parser.o
	${CC} -o $@ $^ ${CFLAGS}. 
quickSort: quickSort.o parser.o
	${CC} -o $@ $^ ${CFLAGS}. 

.PHONY: cleanInsertion cleanMerge cleanHeap cleanQuick 
cleanInsertion:
	rm parser.o insertionSort.o insertionSort
cleanMerge:
	rm parser.o mergeSort.o mergeSort
cleanHeap:
	rm parser.o heapSort.o heapSort
cleanQuick:
	rm parser.o quickSort.o quickSort
# $@ denote the left side of :, $^ denote the right side of :, $< is the first item in the dependencies list
