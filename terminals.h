#ifndef T_H
#define T_H
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <set>

#include "production.h"

#define for_it(a,b) for( auto a = b.begin() ; a != b.end() ; ++a )
#define NIL "#"

using std::vector;
using std::cout;
using std::endl;
using std::set;


class terminals {
public:

	terminals(){;}
	terminals( vector<production>& );
	void deriveNull( vector<production>& );
	bool isTerminal( const string& );
	bool isNullable( const string& );
	void print();
	static void printContainer( const string& , const set<string>& );
	bool isInTerminal( const string& );
	bool isInNonTerminal( const string& );

private:
	set<string> terms , nonterms , nullable;
};

#endif
