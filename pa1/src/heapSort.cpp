#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include "parser.h"
#include <string>
#include <iterator>
#include "myUsage.h"

using namespace std;

class Word{
    public:
        string thisWord;
        int position;
        Word (string word, int positionNumber);
        bool operator> (const Word& theOtherWord);
};
Word:: Word(string word, int positionNumber){
    thisWord = word;
    position = positionNumber;
}
bool Word:: operator> (const Word& theOtherWord){
    int stringLen1 = thisWord.length();
    int stringLen2 = theOtherWord.thisWord.length();

    if(stringLen1 > stringLen2){
        for(int i = 0; i< stringLen2; i++){
            int asci1 = (int) thisWord.at(i);
            int asci2 = (int) theOtherWord.thisWord.at(i);
            if(asci2 > asci1){
                return false;
            }
            else if(asci1 > asci2){
                return true;
            }
        }
        return true;
    }
    else if(stringLen1 == stringLen2){
        for(int i = 0; i< stringLen2; i++){
            int asci1 = (int) thisWord.at(i);
            int asci2 = (int) theOtherWord.thisWord.at(i);
            if(asci1 > asci2){
                return true;
            }
            else if(asci1 < asci2){
                return false;
            }
        }
        return false;
    }
    else{
        for(int i = 0; i< stringLen1; i++){
            int asci1 = (int) thisWord.at(i);
            int asci2 = (int) theOtherWord.thisWord.at(i);
            if(asci1 > asci2){
                return true;
            }
            else if(asci1 < asci2) {
                return false;
            }
        }
        return false;
    }
}

void parseWordsIntoVector( const string & inputFile, vector <Word>& wordVector , unsigned int& wordCount){
    AlgParser p ;
    p.Parse(inputFile);
    wordCount = p.QueryTotalStringCount();
    for(int i = 0 ; i< wordCount; i++){
        Word newWord = Word(p.QueryString(i), i+1);
        wordVector.push_back(newWord);
    }
}

void maxHeapify(vector <Word>& A, int i, int length ){
    int l = (2 * i) + 1;
    int r = (2 * i) + 2;
    int largest = -1;
    if ( (l<length)&&(A[l]>A[i]) ){
        largest = l;
    } 
    else{
        largest = i;
    }
    if ( (r<length)&&(A[r]>A[largest]) ){
        largest = r;
    }
    if(largest != i){
        swap(A[i], A[largest]);
        maxHeapify(A, largest, length);
    } 
}

void buildMaxHeap(vector <Word>& A, int length){
    for(int i = length/2-1; i> -1; i--){
        maxHeapify(A, i, length);
    }
}

void heapSort(vector <Word>& A, int length){
    buildMaxHeap(A, length);
    for(int i = length-1; i> 0; i--){
        swap(A[0], A[i]);
        --length;
        maxHeapify(A, 0, length);
    }
}

int main( int argc, char** argv )
{
    MyUsage myusage;
    AlgTimer t;
    ofstream outFile;
    // Start timer
    t.Begin();
    //Initialization
    vector <Word> words;
    unsigned int wordCount;
    parseWordsIntoVector(argv[1], words, wordCount);
    //heapSort
    heapSort(words, wordCount);
    outFile.open(argv[2], ios::trunc);
    if (outFile.is_open())
    {
        outFile<<wordCount<<endl;
        for (int i = 0; i < wordCount; i++)
        {
            outFile << words[i].thisWord <<" "<< words[i].position<< endl;
        }
    }
    else {
        cout<< "Can't open "<<argv[2]<<endl;
    }
    // Report time and memory usage
    cout << "The execution spends " << t.End() << " seconds" << endl;
    myusage.report(false, true);
    return 0; 
}