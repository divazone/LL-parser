#include "production.h"


production::production()
{
	LHS = "NULL";
	origin = "NULL";
	ruleNum = UNINIT_NUM;
}

production::production( string str , int num , const string& delimL , const char& delimR )
{
	ruleNum = num;
	origin = str;

	vector<string> ret = split( str , delimL );

	LHS = ret[0];
	RHS = split( ret[1] , delimR );
}

void production::print()
{
	cout << "LHS: (" << LHS << ") RHS: ";
	for_it( iter , RHS )
		cout << "("<< (*iter) << ")  ";
	cout << endl;
}

string& production::trim( string &s )
{
	if( s.empty() )
		return s;

	for( int i = 0 ; i < 5 ; ++i )
	{
		s.erase( 0 , s.find_first_not_of("\r"));
		s.erase(s.find_last_not_of("\r") +1 );

		s.erase( 0 , s.find_first_not_of("\n"));
		s.erase(s.find_last_not_of("\n") +1 );

		s.erase( 0 , s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") +1 );
	}

	return s;
}

vector<string> production::split( string& str ,  const char& delim )
{
	vector<string> res;
	stringstream ss(str);
	string tmp;

	while( getline( ss , tmp , delim ) )
	{
		if( tmp != "" )
			res.push_back( trim(tmp) );
	}

	return res;
}

vector<string> production::split( string& str , const string& delim )
{
	size_t pos = str.find( delim );

	if( pos == string::npos )
	{
		cout << "can't found: " << delim << " in " << str << endl;
		exit(1);
	}

	string lhs = str.substr( 0 , pos );
	string rhs = str.substr( pos + delim.length() );

	vector<string> res = {
		str.substr( 0 , pos ) ,
		str.substr( pos + delim.length() )
	};

	trim(res[0]);

	return res;
}




