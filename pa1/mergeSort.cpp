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

// void midIterator(const vector <Word>:: iterator &start,  const vector <Word>:: iterator &end, vector <Word> :: iterator& mid){
//     int elementNumbers = distance(start, end);    
//     cout<< "elementNumbers is"<< elementNumbers<<endl; 
//     advance(mid, elementNumbers/2 - 1 );
//     cout<<"mid iterator is:"<< mid->thisWord<<endl;

// }

void merge(vector <Word>& wordVector, int p, int q, int  r ){
    int n1 = q - p + 1;
    int n2 = r - q;
    // cout<< "p is "<<p<< " q is "<< q<<" r is "<<r<<endl;
    vector<Word> L ;
    vector<Word> R ;
    for(int i = p; i < (q+1); i++){
        L.push_back(wordVector[i]);
        // cout<<"left push "<< it->thisWord<<endl;
    }
    for(int i = (q+1); i < r+1; i++){
        R.push_back(wordVector[i]);
        // cout<<"left push "<< it->thisWord<<endl;
    }
    Word INFINITY = Word("zzzzzzzzzz", -3);
    L.push_back(INFINITY);
    R.push_back(INFINITY);
    // vector <Word>:: iterator i = L->begin();
    // vector <Word>:: iterator j = R->begin();
    int i = 0;
    int j = 0;
    for(int k = p; k< r+1; k++){
        if(L[i] > R[j]){
            // cout<< "left larger delete:"<<" "<<k->thisWord<<" "<< "insert"<< j->thisWord<<endl ;
            // cout<<"left bigger "<<" Left: "<<L[i].thisWord<<" Right: "<< R[j].thisWord<<endl;
            wordVector[k] = R[j];
            j++;
        }
        else{
            // cout<< "right larger delete:"<<" "<<k->thisWord<<" "<< "insert"<< i->thisWord<<endl ;
            // cout<<"right bigger "<<" Left: "<<L[i].thisWord<<" Right: "<< R[j].thisWord<<endl;
            wordVector[k] = L[i];            
            i++;
        }
    }
    L.clear();
    R.clear();
    // cout<< "after deletion"<<endl;
}

void mergeSort( vector <Word>& wordVector, int p, int r){
    int q = (p+r)/2;
    // cout<< "start point to"<<" "<< p->thisWord<< " "<<"end point to"<<" "<< r->thisWord<<endl;
    if (p<r){
        // cout<< "mid iter point to"<<" "<<q->thisWord<<endl;
        mergeSort(wordVector,p,q);
        // cout<< "complete mergeSort 1"<<endl;
        mergeSort(wordVector, q+1, r);
        // cout<< "complete mergeSort 2"<<endl;
        merge(wordVector, p, q, r);
        // cout<< "complete merge"<<endl;        
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
    mergeSort(words, 0, wordCount-1);
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