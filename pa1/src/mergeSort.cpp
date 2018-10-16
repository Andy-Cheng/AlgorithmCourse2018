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

void merge(vector <Word>& wordVector, int p, int q, int  r ){
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<Word> L ;
    vector<Word> R ;
    for(int i = p; i < (q+1); i++){
        L.push_back(wordVector[i]);
    }
    for(int i = (q+1); i < r+1; i++){
        R.push_back(wordVector[i]);
    }
    Word INFINITY = Word("~~~~~~", -3);
    L.push_back(INFINITY);
    R.push_back(INFINITY);
    int i = 0;
    int j = 0;
    for(int k = p; k< r+1; k++){
        if(L[i] > R[j]){
            wordVector[k] = R[j];
            j++;
        }
        else{
            wordVector[k] = L[i];            
            i++;
        }
    }
    L.clear();
    R.clear();
}

void mergeSort( vector <Word>& wordVector, int p, int r){
    int q = (p+r)/2;
    if (p<r){
        mergeSort(wordVector,p,q);
        mergeSort(wordVector, q+1, r);
        merge(wordVector, p, q, r);
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
    // mergesort
    mergeSort(words, 0, wordCount-1);
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