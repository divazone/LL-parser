#ifndef LH
#define LH

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <stack>

#include "terminals.h"
#include "production.h"
#include "ffset.h"

#define for_it(a,b) for( auto a = b.begin() ; a != b.end() ; ++a )
#define hasEle(a,b) a.find(b) != a.end()

#define SUCCESS 1
#define FAILURE 0

#define END_SYM "$"

using std::map;
using std::vector;
using std::set;
using std::cout;
using std::endl;
using std::deque;
using std::ostream;

class ll {
public:

	ll( vector<production>& );
	void parse( const string& , deque<string> );
	
	void print();
	static void printStack( ostream& , vector<string>& );
	static void printDeque( ostream& , deque<string>& );

	void dfs( 
			  deque<string>& ,
			  string ,
			  string 
			);

	void parse_dfs( 
			  const string& ,
			  deque<string> 
			);

private:
	map<string ,map<string,production>> table;
	first_follow_set f;
	
	set<string> find_predict_set( production& );
};

#endif
