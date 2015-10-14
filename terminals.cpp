#include "terminals.h"

terminals::terminals( vector<production> &ps )
{
	for_it( it , ps )
	{
		nonterms.insert( it->LHS );
		for_it( itRHS , it->RHS )
			if( *itRHS != NIL )
				terms.insert( *itRHS );
			else
				nullable.insert( it->LHS );
	}

	for_it( it , nonterms )
		terms.erase( *it );

	deriveNull( ps );
}

void terminals::deriveNull( vector<production> &ps )
{
	bool changes = false;

	do {
		changes = false;
		for_it( it , ps )
		{
			if( isNullable( it->LHS ) )
				continue;

			bool hasNotNull = false;
			for_it( itRHS , it->RHS )
				if( !isNullable( *itRHS ) )
					hasNotNull = true;

			if( !hasNotNull )
			{
				nullable.insert( it->LHS );
				changes = true;
			}
		}
	} while( changes );
}

bool terminals::isTerminal( const string &str )
{
	if( str == NIL )
		return true;
	if( isInTerminal( str ) && !isInNonTerminal( str ) )
		return true;
	if( !isInTerminal( str ) && isInNonTerminal( str ) )
		return false;

	cout << "ERROR when determine terminal:" << str << endl;
	exit(1);
}

bool terminals::isInTerminal( const string &str )
{
	return terms.find(str) != terms.end();
}

bool terminals::isInNonTerminal( const string &str )
{
	return nonterms.find(str) != nonterms.end();
}

bool terminals::isNullable( const string &str )
{
	return nullable.find(str) != nullable.end();
}

void terminals::print()
{
	cout << "terminals ==========================" << endl;
	printContainer( "Terminals:" , terms );
	printContainer( "Non-Terminals:" , nonterms );
	printContainer( "Nullable:" , nullable );
	cout << "====================================" << endl;
}

void terminals::printContainer( const string &hint , const set<string> &con )
{
	cout << hint << endl;
	for_it( it , con )
		cout << "(" << (*it) << ")" << "   ";
	cout << endl;
}

