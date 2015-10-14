#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <deque>
#include <stack>

#include "production.h"
#include "terminals.h"
#include "ffset.h"
#include "ll.h"

using namespace std;

vector<production> readcfg( const char* name , const string& a , const char& b )
{
	FILE* fin = fopen( name , "r" );
	
	if( !fin )
	{
		cout << "error: unable to open file: " << name << endl;
		exit(1);
	}
	
	char buff[256] = {};
	
	vector<production> res;

	int count = 1;
	while( fgets( buff , 256 , fin ) )
	{
		res.push_back(production( string(buff) , count++ , a , b ));	
	}

	fclose(fin);

#ifdef DEBUG
	for_it( it , res )
	{
		printf("  (%2d)LHS=%s\n\t\tRHS=" , it->ruleNum , it->LHS.c_str() );
		for_it( itr , it->RHS )
			printf("%s,",itr->c_str());
		printf("\n");
	}

	cout << endl;
#endif

	return res;
}

deque<string> readcode( const char* name , const char* delim )
{
	FILE* fin = fopen( name , "r" );
	
	if( !fin )
	{
		cout << "error: unable to open file: " << name << endl;
		exit(1);
	}

	char buff[256] = {};
	
	deque<string> res;

	while( fgets( buff , 256 , fin ) )
	{
		char* pch = strtok( buff , delim );
		while( pch )
		{
			string tmp = pch;
			tmp = production::trim(tmp);
			if( tmp != "" )
				res.push_back(tmp);
			pch = strtok( NULL , delim );
		}
	}

	fclose(fin);

	return res;
}


int main()
{
	const char		code_delim[]= " " ; // only use in code split
	const string	prod_delim	= ">" ;
	const char		rhs_delim	= ' ' ;
	const char*		grammer		= "grammer.txt" ;
	const char*		code		= "code.txt" ;

	vector<production> productions = readcfg( grammer , prod_delim , rhs_delim );
	deque<string> context = readcode( code , code_delim );

	ll( productions ).parse( productions[0].LHS , context );
		
	return 0;
}
