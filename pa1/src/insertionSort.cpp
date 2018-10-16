#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include "parser.h"
#include <string>
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

void insertionSort( vector <Word>& wordVector, unsigned int wordCount){
    for(int j=1; j < wordCount; j++){
        Word key = wordVector[j];
        int i = j - 1;
        while( (i > -1) && (wordVector[i]>key) ){
            wordVector[i+1] = wordVector[i];
            i--;
        }
        wordVector[i+1] = key;
    }
};


int main( int argc, char** argv )
{
    MyUsage myusage;
    ofstream outFile;
    AlgTimer t;
    // start the timmer
    t.Begin();
    //Initialization
    vector <Word> words;
    unsigned int wordCount;
    parseWordsIntoVector(argv[1], words, wordCount);
    // insertionsort
    insertionSort(words, wordCount);
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