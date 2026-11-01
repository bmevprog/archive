// Megj.: Ez így önmagában fut, illetve a jelölt helyeken kivágva (törölve) TC-re is beküldhetõ.

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
using namespace std;

// BEGIN CUT HERE
#define ARRSIZE(x) (sizeof(x)/sizeof(x[0]))

template<typename T> void print( T a ) {
    cerr << a;
}
static void print( long long a ) {
    cerr << a << "L";
}
static void print( string a ) {
    cerr << '"' << a << '"';
}
template<typename T> void print( vector<T> a ) {
    cerr << "{";
    for ( int i = 0 ; i != a.size() ; i++ ) {
        if ( i != 0 ) cerr << ", ";
        print( a[i] );
    }
    cerr << "}" << endl;
}
template<typename T> void eq( int n, T have, T need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
template<typename T> void eq( int n, vector<T> have, vector<T> need ) {
    if( have.size() != need.size() ) {
        cerr << "Case " << n << " failed: returned " << have.size() << " elements; expected " << need.size() << " elements.";
        print( have );
        print( need );
        return;
    }
    for( int i= 0; i < have.size(); i++ ) {
        if( have[i] != need[i] ) {
            cerr << "Case " << n << " failed. Expected and returned array differ in position " << i << ".";
            print( have );
            print( need );
            return;
        }
    }
    cerr << "Case " << n << " passed." << endl;
}
static void eq( int n, string have, string need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
// END CUT HERE
class BatchSystemRoulette {
public:
    vector <double> expectedFinishTimes(vector <int> duration, vector <string> user) {
        vector <double> res;		
		map<string,double> sums;
		int n=user.size();

		for( size_t i=0; i<n; ++i )
			sums[user[i]] += duration[i];

		for( size_t i=0; i<n; ++i )
		{
			double shorterTotal = 0;
			double equalTotal = 0;

			for( map<string,double>::iterator it=sums.begin(); it!=sums.end(); ++it )
			{
				if( it->second < sums[user[i]] )
					shorterTotal += it->second;
				else if( it->second == sums[user[i]] )
					equalTotal += it->second;
			}

			res.push_back( shorterTotal + (equalTotal - duration[i]) / 2.0 + duration[i] );
		}

        return res;
    }
};
// BEGIN CUT HERE
void main( int argc, char* argv[] ) {
    {
        int durationARRAY[] = {3, 2, 4, 1};
        vector <int> duration( durationARRAY, durationARRAY+ARRSIZE(durationARRAY) );
        string userARRAY[] = {"Gil Grissom", "Sarah Sidle", "Warrick Brown", "Catherine Willows"};
        vector <string> user( userARRAY, userARRAY+ARRSIZE(userARRAY) );
        double retrunValueARRAY[] = {6.0, 3.0, 10.0, 1.0 };
        vector <double> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BatchSystemRoulette theObject;
        eq(0, theObject.expectedFinishTimes(duration, user),retrunValue);
    }
    {
        int durationARRAY[] = {3, 2, 4, 1};
        vector <int> duration( durationARRAY, durationARRAY+ARRSIZE(durationARRAY) );
        string userARRAY[] = {"mac taylor", "Mac Taylor", "Mac Taylor", "Peyton Driscoll"};
        vector <string> user( userARRAY, userARRAY+ARRSIZE(userARRAY) );
        double retrunValueARRAY[] = {4.0, 8.0, 9.0, 1.0 };
        vector <double> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BatchSystemRoulette theObject;
        eq(1, theObject.expectedFinishTimes(duration, user),retrunValue);
    }
    {
        int durationARRAY[] = {13, 14, 15, 56, 56};
        vector <int> duration( durationARRAY, durationARRAY+ARRSIZE(durationARRAY) );
        string userARRAY[] = {"Tim Speedle", "Tim Speedle", "Tim Speedle", "Horatio Caine", "YEEEAAAAAAAAAAH"};
        vector <string> user( userARRAY, userARRAY+ARRSIZE(userARRAY) );
        double retrunValueARRAY[] = {27.5, 28.0, 28.5, 126.0, 126.0 };
        vector <double> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        BatchSystemRoulette theObject;
        eq(2, theObject.expectedFinishTimes(duration, user),retrunValue);
    }
}
// END CUT HERE
