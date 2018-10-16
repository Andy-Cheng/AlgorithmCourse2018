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

int partition(vector <Word>& A, int p, int r){
    Word x = A[p];
    int i = p - 1, j = r+1;
    while(1){
        do{
            j--;
        }while(A[j] > x);
        do{
            i++;
        }while(x > A[i]);
        if(i < j){
            swap(A[i], A[j]);
        }
        else{
            return j;
        }
    }
}

void quickSort(vector <Word>& A, int p, int r){
    if(p < r){
        int q = partition(A, p, r);
        quickSort(A, p, q);
        quickSort(A, q + 1, r);
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
    // quicksort
    quickSort(words, 0, wordCount - 1);
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