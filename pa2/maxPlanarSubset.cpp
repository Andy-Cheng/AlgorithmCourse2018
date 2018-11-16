#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "myUsage.h"


using namespace std;



struct Circle{
    int* chords;
    int N;
};

struct MIS{
    int size;
    int edge[2]; 
    MIS* succesor[2];
    bool operator<(int beCompared);
    int operator+(const MIS& mis2);
    int operator+(int added);
    void assign1(MIS* leftMis, MIS* rightMis, int k, int j);
    void assign2(MIS* smallerMIS);
};
bool MIS:: operator<(int beCompared){
    if(size < beCompared){
        return true;
    }
    else{
        return false;
    }
}
int MIS:: operator+(const MIS& mis2){
    return (size + mis2.size);
}
int MIS:: operator+(int added){
    return (size + added);
}
void MIS:: assign1(MIS* leftMis, MIS* rightMis, int k,  int j){
    succesor[0] = leftMis;
    succesor[1] = rightMis;
    edge[0] = k;
    edge[1] = j;
    size = leftMis->size + rightMis->size + 1;
}   
void MIS:: assign2(MIS* smallerMIS){
    succesor[0] = smallerMIS;
    size = smallerMIS->size;
}

void parseFile(string fileName, Circle& circle ){
    fstream inFile;
    inFile.open(fileName, ios::in);
    if(inFile.is_open()){
        string line;
        getline(inFile, line);
        circle.N = stoi(line.substr(0, line.length()));
        circle.chords = new int[circle.N];
        for(int i = 0; i < circle.N/2 ; ++i){
            getline(inFile, line);
            istringstream ss(line);
            string start_s, end_s;
            getline(ss, start_s, ' ');
            getline(ss, end_s);
            int start = stoi(start_s);
            int end = stoi(end_s);
            circle.chords[start] = end;
            circle.chords[end] = start;
        }
        inFile.close();
    }
    else{
        cout<<"Unable to read in file"<<endl;
    }
}

void traceEdge(MIS* mis, ofstream& outFile){
    if(mis->succesor[0] != nullptr){
        traceEdge(mis->succesor[0], outFile);
    }
    if( mis->edge[0] != -1){
        // cout<< mis->edge[0]<< " "<<mis->edge[1]<<endl;
        outFile<<"\n"<< mis->edge[0]<< " "<<mis->edge[1];
    }
    if(mis->succesor[1] != nullptr){
        traceEdge(mis->succesor[1], outFile);
    }
    return;
}


int main(int argc, char** argv ){
    MyUsage myusage;
    Circle circle;
    parseFile(argv[1], circle);
    // |MIS(i, j)| is stored in dynamic array 2Nx2N.
    MIS** misTable = new MIS* [circle.N];
    // Initialization MIS  table
    for(int i = 0; i <  circle.N; ++i){
        misTable[i] = new MIS [circle.N];
        for(int j = 0; j < circle.N; ++j){
            misTable[i][j].size = 0;
            misTable[i][j].succesor[0] = nullptr;
            misTable[i][j].succesor[1] = nullptr;
            misTable[i][j].edge[0] = -1;
            misTable[i][j].edge[1] = -1;
        }
    }
    // FIND-MIS(0, 2N-1) Algorithm call

    
    for(int j = 0; j < circle.N; ++j){
        int k = circle.chords[j];
        for(int i = 0; i < j; ++i){
            // cout<< "globally  "<<"i: "<< i<< "j: "<<j<<"k: "<<k<<endl;
            if(k == 0){
                // cout<< "else "<<"i: "<< i<< "j: "<<j<<"k: "<<k<<endl;         

                if(i == 0){
                    // cout<< "here3 "<<"i: "<< i<< "j: "<<j<<"k: "<<k<<endl;         
                    misTable[i][j].succesor[1] = &misTable[k+1][j-1];
                    misTable[i][j].edge[0] = k;
                    misTable[i][j].edge[1] = j;
                    misTable[i][j].size = misTable[k+1][j-1].size + 1;
                }
                else{
                    // cout<< "here4 "<<"i: "<< i<< "j: "<<j<<"k: "<<k<<endl;         

                    misTable[i][j].assign2(&misTable[i][j-1]);
                }
            }
            else{
                // cout<< "here1 "<<"i: "<< i<< "j: "<<j<<"k: "<<k<<endl;         

                if( (i <= k) && (k < j) && ( misTable[i][j-1] < (misTable[i][(k-1)] + misTable[k+1][j-1]+ 1)) ){
                    // cout<<i<<j<<k;           
                    // cout<< "here1 "<<"i: "<< i<< "j: "<<j<<"k: "<<k<<endl;                            
                    misTable[i][j].assign1(&misTable[i][k - 1], &misTable[k+1][j-1], k, j);
                }
                else{
                    // cout<< "here2 "<<"i: "<< i<< "j: "<<j<<"k: "<<k<<endl;         

                    misTable[i][j].assign2(&misTable[i][j-1]);
                }
            }

        }
    }
    cout<<"Circle"<<endl;
    cout<<"Number of vertices:"<< circle.N<<endl;
    cout<< "edges:"<<endl;
    for(int i = 0; i < circle.N; ++i ){
        cout<<i<<"<--->"<<circle.chords[i]<<endl;
    }
    /*
    cout<< "result"<<endl;
    for(int j = 0; j <  circle.N; ++j){
        for(int i = 0; i < circle.N; ++i){
            // cout<<"(i, j)"<<i<<", "<<j<<endl;
            // traceEdge(&misTable[i][j]);
            cout<< misTable[i][j].size<<" ";
        }
        cout<<endl;
    }
    */
    ofstream outFile(argv[2]);
    outFile<< misTable[0][circle.N - 1].size;
    traceEdge(&misTable[0][circle.N -1], outFile);
    myusage.report(true, true);
}