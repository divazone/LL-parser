#include "ffset.h"


first_follow_set::first_follow_set( vector<production> &ps )
	: t( terminals(ps) )
{
	//t = terminals(ps);
#ifdef DEBUG
	t.print();
#endif

	fill_first_set(ps);
	fill_follow_set(ps);

#ifdef DEBUG
	print();
#endif
}

void first_follow_set::fill_first_set( vector<production> &ps )
{
	for_it( it , ps )
	{
		string &LHS = it->LHS;
		vector<string> &RHS = it->RHS;
		
		if( t.isNullable( LHS ) )
			first_set[ LHS ].insert( NIL );

		for_it( iter , RHS )
			if( *iter != NIL && t.isTerminal( *iter ) )
			{
				first_set[*iter].insert( *iter );
				if( iter == RHS.begin() )
					first_set[ LHS ].insert( *iter );
			}

		bool changes = false;

		do {
			changes = false;
			for_it( it , ps )
			{
				string &LHS = it->LHS;

				set<string> first = find_first( it->RHS );
				size_t oldsize = first_set[ LHS ].size();
				first_set[ LHS ].insert( first.begin() , first.end() );
				if( first_set[ LHS ].size() != oldsize )
					changes = true;
			}
		} while( changes );
	}
}

set<string> first_follow_set::find_first( vector<string>& X )
{
	set<string> res;

	if( X.size() == 0 || X.front() == NIL )
		res.insert( NIL );
	else
	{
		res = first_set[ X.front() ];
		size_t i;
		for( i = 1 ; i < X.size() && hasNil(first_set[X[i-1]]) ; ++i )
		{
			set<string> first = first_set[ X[i] ];
			first.erase( NIL );
			res.insert( first.begin() , first.end() );
		}

		if( i == X.size() && hasNil(first_set[X[i-1]]) )
			res.insert( NIL );
		else
			res.erase( NIL );
	}

	return res;
}

void first_follow_set::fill_follow_set( vector<production> &ps )
{
	bool changes = false;
	do {
		changes = false;
		for_it( it , ps )
		{
			for_it( iter , it->RHS )
			{
				string &x = *iter;
				if( !t.isTerminal( x ) )
				{
					vector<string> beta( iter+1 , it->RHS.end() );
					set<string> first = find_first( beta );
					size_t oldsize = follow_set[ x ].size();

					if( FAILURE == first.erase( NIL ) ) 
					{	// means erase nothing , so no lambda here	
						follow_set[ x ].insert( first.begin() , first.end() );
					}
					else
					{ // has lambda then do here
						follow_set[ x ].insert( first.begin() , first.end() );
						first = follow_set[ it->LHS ];
						follow_set[ x ].insert( first.begin() , first.end() );
					}
					if( oldsize != follow_set[ x ].size() )
						changes = true;
				}
			}
		}
	} while( changes );
}

bool first_follow_set::isTerminal( const string &str )
{
	return t.isTerminal(str);
}

bool first_follow_set::isNullable( const string &str )
{
	return t.isNullable(str);
}

void first_follow_set::print()
{
	cout << "first and follow set ===============" << endl;
	printContainer( "first" , first_set );
	printContainer( "follow" , follow_set );
	cout << "====================================" << endl;
}

void first_follow_set::printContainer( const string &hint , const map<string,set<string>> &con )
{
	for_it( it , con )
	{
		cout << hint << "(" << (it->first) << ")=\t{";
		for_it( iter , it->second )
			cout << "(" << (*iter) << ")" << "  ";
		cout << "}" << endl;
	}
	cout << endl;
}

