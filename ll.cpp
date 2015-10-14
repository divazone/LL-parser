#include "ll.h"

ll::ll( vector<production> &ps )
	: f( first_follow_set(ps) )
{
	//f = first_follow_set(ps);
	
	for_it( it , ps )
	{
		set<string> pset = find_predict_set( *it );

		for_it( iter , pset )
		{
			production &p = table[ it->LHS ][ *iter ];
			if( p.ruleNum != UNINIT_NUM )
			{
				cout << "ERROR find conflict entry(more than one):" << endl;
				cout << "ll table[" << (it->LHS) << "][" << (*iter) << "] already have rule:" << endl;
				cout << p.ruleNum << ":" << p.origin << endl;
				cout << "but I am trying to fill rule:" << endl;
				cout << (it->ruleNum) << ":" << (it->origin) << endl;
				exit(1);
			}
			
			table[ it->LHS ][ *iter ] = *it;
		}
	}

	print();

}

void ll::parse( const string& start_symbol , deque<string> context )
{
	vector<string> pool;
	pool.push_back( start_symbol );

	deque<string> context_c(context);

#ifndef DEBUG
std::fstream fout( "/dev/null" , std::fstream::out );
#else
ostream &fout = cout;
#endif

	while( !pool.empty() && !context.empty() )
	{
		fout<<"----Status------------------------------------"<<endl;
		printStack(fout,pool);
		printDeque(fout,context);

		string nt = pool.back();
		string code = context.front();
		fout << "current Non-terminal:(" << nt << ")\t" << "terminal symbol:(" << code << ")" << endl;
		fout<<"----Action------------------------------------"<<endl;

		if( nt == code )
		{
			fout << "- Match symbol (" << code << ")" << endl;
			pool.pop_back();
			context.pop_front();
		}
		else if( !f.isTerminal(nt) &&
				table[nt].find(code) != table[nt].end() )
		{
			production &p = table[nt][code];
			fout << "- Apply rule (" << p.ruleNum << ")." << p.origin;
			pool.pop_back();

			for( auto it = p.RHS.rbegin() ; it != p.RHS.rend() ; ++it )
			{
				if( *it != NIL )
				{
					pool.push_back( *it );
				}
				else
				{
					fout << "--- Ignore null in rhs" << endl;
				}
			}
		}
		else if( table[nt].find( NIL ) != table[nt].end() || f.isNullable(nt) )
		{
			fout << "- REMOVE null (shouldn't do this)." << endl;
			pool.pop_back();
		}
		else
		{
			puts("- ERROR no action can do. exited.");
			return;
		}
		fout << "----------------------------------------------\n" << endl;
	}

	while( !pool.empty() )
	{
		string nt = pool.back();
		fout << " WARN: still not empty in stack (" << nt << ")" << endl;
		if( table[nt].find( NIL ) != table[nt].end() || f.isNullable(nt) )
		{
			pool.pop_back();
			fout << "    " << nt << "has been removed." << endl;
		}
		else
		{
			fout << "    " << nt << "is not null. exited." << endl;
			break;
		}
	}

	if( context.size() == 0 && pool.size() == 0 )
	{
		puts("===================");
		puts("|context accepted.|");
		puts("===================");
		parse_dfs( start_symbol , context_c );
	}
	else
	{
		puts("=======================");
		puts("|context NOT accepted.|");
		puts("=======================");
		puts("----Status-----------------------------------");
		printStack(cout,pool);
		printDeque(cout,context);
		puts("---------------------------------------------");
	}
}


void ll::parse_dfs( 
					const string& start_symbol ,
				    deque<string> context
		)
{

	cout << " parsing tree =================================" << endl;
	dfs( context , start_symbol , "- " );

	cout << " ==============================================" << endl;
}

void ll::dfs(  
		  deque<string> &context ,
		  string ntp ,
		  string prefix
		)
{
		if( context.size() == 0 )
			return;

		string nt = ntp;
		string code = context.front();


		if( nt == code )
		{
			cout << prefix << nt << " == " << code << endl;
			context.pop_front();
		}
		else if( !f.isTerminal(nt) &&
				 hasEle( table[nt] , code ) )
		{
			cout << prefix << nt << endl;
			prefix = "   " + prefix;


			production &p = table[nt][code];

			for_it( it , p.RHS )
			{
					if( *it != NIL )
						dfs( context , *it , prefix );
					else
						cout << prefix << NIL << " == " << NIL << endl;
			}
		}
}

set<string> ll::find_predict_set( production &p )
{
	set<string> res;
	set<string> first = f.find_first( p.RHS );

	if( SUCCESS == first.erase( NIL ) )
		res.insert( f.follow_set[p.LHS].begin() , f.follow_set[p.LHS].end() );

	res.insert(first.begin() , first.end());

	return res;
}

void ll::print()
{
	cout << " ll table result ===================" << endl;
	set<string> column;

	for_it( it , table )
	{
		for_it( iter , it->second )
			column.insert( iter->first );
	}

	for( size_t i = 0 ; i < (column.size()+1)*9-1 ; ++i )
		putchar('-');
	putchar('\n');

	cout << "|\t\t";
	for_it( iter , column )
		cout << "|" << (*iter) << "\t";
	cout << "|" << endl;

	for( size_t i = 0 ; i < (column.size()+1)*9-1 ; ++i )
		putchar('-');
	putchar('\n');


	for_it( it , table )
	{
		cout << "|" << (it->first) << "\t\t";
		map<string,production>& smap = it->second;
		for_it( iter , column )
		{
			auto t = smap.find( *iter );
			if( t != smap.end() )
				cout << "|" << (smap[*iter].ruleNum) << "\t";
			else
				cout << "|" << "    "   << "\t";
		}
		cout << "|" << endl;
	}

	for( size_t i = 0 ; i < (column.size()+1)*9-1 ; ++i )
		putchar('-');
	putchar('\n');

	cout << "====================================" << endl;

}

void ll::printStack( ostream &out , vector<string> &stk )
{
	out << "Stack :" << endl;
	out << "bottom [ ";
	for_it( it , stk )
	{
		out << "\t" << (*it);
	}
	out << " ] top";
	out << endl;
}

void ll::printDeque( ostream &out , deque<string> &que )
{
	out << "Queue :" << endl;
	out << "front [ ";
	for_it( it , que )
	{
		out << "\t" << (*it);
	}
	out << " ] back";
	out << endl;
}




