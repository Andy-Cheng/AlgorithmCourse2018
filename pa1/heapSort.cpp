#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include "parser.h"
#include <string>
#include <deque>
#include <iterator>
using namespace std;
// class Word
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
            if ( (asci1>122)||((asci1<97)&&(asci1>90))||(asci1<65) ){
                continue;
            }
            if ( (asci2>122)||((asci2<97)&&(asci2>90))||(asci2<65) ){
                continue;
            }
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
            if ( (asci1>122)||((asci1<97)&&(asci1>90))||(asci1<65) ){
                continue;
            }
            if ( (asci2>122)||((asci2<97)&&(asci2>90))||(asci2<65) ){
                continue;
            }
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
            if ( (asci1>122)||((asci1<97)&&(asci1>90))||(asci1<65) ){
                continue;
            }
            if ( (asci2>122)||((asci2<97)&&(asci2>90))||(asci2<65) ){
                continue;
            }

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

string extractFileName(const string & fileName){
    string outputFileName;
    for (int i = 0; i < fileName.length(); i++){
        if(fileName[i]=='.'){
            break;
        } 
        outputFileName.push_back(fileName[i]);
    }
    outputFileName += "_out.dat";
    return outputFileName;
}
void maxHeapify(vector <Word>& A, int i, int length ){
    // cout<<" start maxheapify, A[i] is"<<A[i].thisWord<<endl;
    int l = (2 * i) + 1;
    int r = (2 * i) + 2;
    int largest = -1;
    if ( (l<length)&&(A[l]>A[i]) ){
        // cout<< "A[l] is bigger, A[l] is : "<< A[l].thisWord<< " A[i] is "<<A[i].thisWord<<endl;
        largest = l;
    } 
    else{
        largest = i;
    }
    if ( (r<length)&&(A[r]>A[largest]) ){
        // cout<< "A[r] is bigger, A[r] is : "<< A[r].thisWord<< " A[i] is "<<A[i].thisWord<<endl;
        largest = r;
    }
    if(largest != i){
        swap(A[i], A[largest]);
        // cout<< "after swap, A[i] is "<<A[i].thisWord<<" A[largest] is: "<<A[largest].thisWord<<endl;
        maxHeapify(A, largest, length);
    } 
    // cout<< "i is largest, i:  "<<i<<endl;

}

void buildMaxHeap(vector <Word>& A, int length){
    for(int i = length/2-1; i> -1; i--){
        maxHeapify(A, i, length);
    }
}

void heapSort(vector <Word>& A, int length){
    buildMaxHeap(A, length);
    // cout<< "the max heap is:"<< endl;
    for(int i = 0; i< length; i++){
        // cout<<A[i].thisWord<<endl;
    }
    for(int i = length-1; i> 0; i--){
        swap(A[0], A[i]);
        --length;
        maxHeapify(A, 0, length);
    }
}

int main( int argc, char** argv )
{
    // Declare the functional objects
    AlgTimer t;
    ofstream outFile;
    string outFileName = extractFileName(argv[1]);
    // Start timer
    t.Begin();
    //initialization
    vector <Word> words;
    unsigned int wordCount;
    parseWordsIntoVector(argv[1], words, wordCount);
    // cout<<"initial vector:"<<endl;
    // for(int i = 0; i< wordCount; i++){
    //     cout<< words[i].thisWord<< endl;
    // }
    //heapSort
    heapSort(words, wordCount);
    // The result
    // cout<<"Result:"<<endl;
    // cout<<wordCount<<endl;
    
    // for(int i = 0; i< wordCount; i++){
    //     cout<< words[i].thisWord<< endl;
    // }
    Word dummy = Word("1", 0);
    words.push_back(dummy);
    // initialization for the below for loop
    string nowIterString = words[0].thisWord;
    int currentWordCount = 0;
    deque <int> position;
    outFile.open(outFileName, ios::trunc);
    if (outFile.is_open())
    {
        outFile<<wordCount<<endl;
        for (int i = 0; i<wordCount+1; i++)
        {
            if (nowIterString != words[i].thisWord)
            {
                // print out result
                outFile << nowIterString << " " << currentWordCount;
                for (deque<int>::iterator iter = position.begin(); iter != position.end(); ++iter)
                {
                    outFile << " " << *iter;
                }
                outFile << endl;
                //reset
                nowIterString = words[i].thisWord;
                position.clear();
                currentWordCount = 1;
                position.push_back(words[i].position);
                continue;
            }
            currentWordCount++;
            position.push_back(words[i].position);
        }
    }
    else {
        cout<< "Can't open "<<outFileName<<endl;
    }
// Display the accumulated time
    cout << "The execution spends " << t.End() << " seconds" << endl;
return 0; 
}