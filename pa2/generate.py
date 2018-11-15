import argparse
from random import shuffle


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description = 'generate input.')
    parser.add_argument('-n', type = int, help='total number of edges on the circle')
    args = parser.parse_args()
    vertices = [i for i in range(args.n)]
    shuffle(vertices)
    N = int(args.n/2)
    leftCol = vertices[:N]
    rightCol = vertices[N:]
    pair = []
    for i in range(N):
        if rightCol[i] > leftCol[i]:
            pair.append((leftCol[i], rightCol[i]))
        else:
            pair.append((rightCol[i], leftCol[i]))
    pair.sort(key= lambda e: e[0])
    fileName = str(args.n)+'.in'
    with open(fileName, 'w') as f:
        f.write( str(args.n) + '\n')
        for i in range(N):
            f.write(str(pair[i][0]) + ' ' + str(pair[i][1]) + '\n')
        f.write('0');
            

