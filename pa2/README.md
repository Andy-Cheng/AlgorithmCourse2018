## Maximum Planar Subset
pa2 contains the implementation of *Finding a Maximum Planar Subset of a Set of Nets in a Channel 1987 by K.J. Supowit* .

## Notes:
1. To compile:
In the terminal at ./src,
make clean
make
The binary file e.g mps will appear at ./src
2. To run the program:
In the terminal:
```
    ./mps <dir in>/<xxx>.in <dir out>/<xxx>.out
```
3. To generate test data
```
    python3 -n <total number of edges on the circle> generate.py
```