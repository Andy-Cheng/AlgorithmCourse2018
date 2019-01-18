#include <cstdio>
#include <vector>
#include <set>
#include <list>
#include <utility>
#include <map>
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include "parser.h"

using namespace std;

class Graph 
{ 
    int V;
    int height;
    int width;
    int capacity;
	vector< pair<int, double> > *adj; 

public: 
	Graph(int height, int width, int capacity);
	void addEdge(int u, int v, double w); 
	void shortestPath(int src_x, int src_y, int dst_x, int dst_y, ofstream& outFile, int id); 
    void decreaseWeight(int u, int v);
    void increaseWeight(int u, int v);
    void printParent(int u, ofstream& outFile,  map< int, int >& PI, int src, int& size);
    
}; 

Graph::Graph(int height, int width, int capacity)
{ 
	this->V = height * width;
    this->capacity = capacity;
    this->height = height;
    this->width = width;
	adj = new vector< pair<int, double> >[V]; 
    // Add horizontal edges
    for(int j = 0; j < height; ++j){
        for(int i = 0; i < width - 1; ++i){
            int current = j * width + i;
            this->addEdge(current, current+1, 1);
        }
    }
    // Add vertical edges
    for(int i = 0; i < width; ++i){
        for(int j = 0; j < height - 1; ++j){
            int current = j * width + i;
            this->addEdge(current, current+width, 1);
        }
    }

} 
void Graph::printParent(int u, ofstream& outFile,  map< int, int >& PI, int src, int& size){
    int p_x = PI[u] % width;
    int p_y = PI[u] / width;
    int x = u % width;
    int y = u / width;
    if( (p_x == src % width) && (p_y == src / width) ){
        size++;
        outFile<< size;
    }
    else{
        size++;
        printParent(PI[u], outFile, PI, src, size);
    }
    outFile<< "\n" <<p_x<< " "<<p_y<< " "<< x<< " "<<y;
}

void Graph::addEdge(int u, int v, double w) 
{ 
	adj[u].push_back(make_pair(v, w)); 
	adj[v].push_back(make_pair(u, w)); 
}

void Graph::decreaseWeight(int u, int v) 
{ 
    for(int i = 0; i< adj[u].size(); ++i){
        if(adj[u][i].first==v){
            adj[u][i].second = adj[u][i].second/2;
            break;
        }
    }
    for(int i = 0; i< adj[v].size(); ++i){
        if(adj[v][i].first==u){
            adj[v][i].second = adj[v][i].second/2;
            break;
        }
    }
}

void Graph::increaseWeight(int u, int v) 
{    
    double capacity_div = pow(2, capacity);
    for(int i = 0; i< adj[u].size(); ++i){
        if(adj[u][i].first==v){
            if(adj[u][i].second == 1){
                adj[u][i].second = adj[u][i].second * 2 / capacity_div;
            }
            else{
                adj[u][i].second = adj[u][i].second*2;
            }
            break;
        }
    }
    for(int i = 0; i< adj[v].size(); ++i){
        if(adj[v][i].first==u){
            if(adj[v][i].second == 1){
                adj[v][i].second = adj[v][i].second * 2 / capacity_div;
            }
            else{
                adj[v][i].second = adj[v][i].second*2;
            }
            break;
        }
    }

}



void Graph::shortestPath(int src_x, int src_y, int dst_x, int dst_y, ofstream& outFile, int id) 
{
    int src = width * src_y + src_x;
	// Create a set to store vertices that are being 
	// prerocessed 
    map<int, int> parent;
    double capacity_div = pow(2, capacity);
	set< pair<double, int> > setds; 
	// Create a vector for distances and initialize all 
	// distances as infinite (INF) 
	vector<double> dist(V, numeric_limits<double>::infinity()); 

	// Insert source itself in Set and initialize its 
	// distance as 0. 
	setds.insert(make_pair(0, src)); 
	dist[src] = 0; 

	while (!setds.empty()) 
	{

		pair<double, int> tmp = *(setds.begin()); 
		setds.erase(setds.begin()); 
		// vertex label is stored in second of pair (it 
		// has to be done this way to keep the vertices 
		// sorted distance (distance must be first item 
		// in pair) 
		int u = tmp.second; 

		// 'i' is used to get all adjacent vertices of a vertex 
		list< pair<int, double> >::iterator i; 
		for (int i = 0; i < adj[u].size(); ++i)
		{ 
			// Get vertex label and weight of current adjacent 
			// of u. 
			int v = adj[u][i].first;
			double weight = adj[u][i].second; 
            if(weight == 1){
                weight = weight * 2/ capacity_div;
            }
            else{
                weight *= 2;
            }

			// If there is shorter path to v through u. 
			if (dist[v] > dist[u] + weight) 
			{ 
				/* If distance of v is not INF then it must be in 
					our set, so removing it and inserting again 
					with updated less distance. 
					Note : We extract only those vertices from Set 
					for which distance is finalized. So for them, 
					we would never reach here. */
				if (dist[v] != numeric_limits<double>::infinity()){
					setds.erase(setds.find(make_pair(dist[v], v)));
                    int u_old = parent[v];
                    decreaseWeight(u_old, v);
                    parent.erase(v);
                }
				// Updating distance of v 
				dist[v] = dist[u] + weight; 
				setds.insert(make_pair(dist[v], v)); 
                increaseWeight(u, v);
                parent[v] = u;
			} 
		} 
	} 
    int size = 0;
    outFile<<id<< " ";
    int dst = dst_y * width + dst_x;
    printParent(dst, outFile, parent, src, size);
} 

int main(int argc, char **argv)
{
    if( argc < 3 ){ cout << "Usage: ./router [input_file_name] [output_file_name]" << endl; return 1; }

    AlgParser parser;
    // read the file in the first argument
    if( ! parser.read( argv[1] ) ) { return 1; }
    int H = parser.gNumHTiles();
    int W = parser.gNumVTiles();
    int C = parser.gCapacity();
    int N = parser.gNumNets();

    ofstream outFile(argv[2]);
    Graph g( H, W, C);

    pair<int, int> S = parser.gNetStart( 0 );
    pair<int, int> E = parser.gNetEnd( 0 );
    g.shortestPath(S.first, S.second, E.first, E.second, outFile, 0);
    for (int idNet = 1; idNet < N; ++idNet){
        pair<int, int> posS = parser.gNetStart( idNet );
        pair<int, int> posE = parser.gNetEnd( idNet );
        outFile<< "\n";
        g.shortestPath(posS.first, posS.second, posE.first, posE.second, outFile, idNet);
    }
    return 0;
}