#ifndef _DEFINE_PARSER_
#define _DEFINE_PARSER_

#include <string>
#include <cstdio>
#include <iostream>
using namespace std;

class AlgString{
	public:
	string m_string; 
	int m_line_number;
	int m_word_number;
	//int m_apperance_count;
	AlgString(void);
	AlgString( const string& set_string, const int& set_line_number, const int& set_word_number );
};

class AlgParser
{
	public:
	AlgParser(void);
	// Specify the parsing file name and then parse the file
	void Parse( const string& input_file_name );
	// Return the total number of strings in the file
	int QueryTotalStringCount(void);
	// Return the ith string in the file
	string QueryString(const int& ith);
	// Return the line number of the ith string in the file
	int QueryLineNumber(const int& ith);
	// Return the word order of the ith string in the corresponding line
	int QueryWordOrder( const int& ith );
};

class AlgTimer
{
	public:
	long begin_clock;
	AlgTimer(void);
	// Strat the timer
	void Begin(void);
	// Return the accumulated time in seconds
	double End(void);
};
#endif
