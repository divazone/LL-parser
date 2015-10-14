#ifndef P_H
#define P_H
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#define for_it(a,b) for( auto a = b.begin() ; a != b.end() ; ++a )
#define UNINIT_NUM -1

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::stringstream;



class production {
public:
	string LHS;
	vector<string> RHS;	
	string origin;
	int ruleNum;

	production();
	production( string , int , const string& , const char& );

	void print();
	static string& trim( string& );

private:
	static vector<string> split( string& , const char& );
	static vector<string> split( string& , const string& );

};

#endif
