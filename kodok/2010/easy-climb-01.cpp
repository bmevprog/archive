#include <cstdio>
#include <algorithm>

using namespace std;

#define	BUFFER_SIZE	64*1024
#define INF			10000000

struct Point
{
	int x;
	long long y;

	Point(int x=0, long long y=0) : x(x), y(y) {}
};
 
// Ettõl itt nem kell megijedni, csak a scanf() függvény egy lecsupaszított, gyors változatai.
char buf[BUFFER_SIZE];
int buf_size = 0;
int buf_pos = 0;
 
int fast_getc()
{
	if( buf_pos >= buf_size )
	{
		buf_pos = 0;
		buf_size = fread( buf, sizeof(char), BUFFER_SIZE, stdin );
	}
 
	return buf[buf_pos++];
}

int fast_getint()
{
	bool neg = false;
	int c;
	while( (c=fast_getc()) < '0' )	
		neg = c == '-';
 
	int r = c - '0';
	while( (c=fast_getc()) >= '0' )
		r = r*10 + (c-'0');
 
	return neg ? -r : r;
}
// Egészen eddig.

Point tmp[2][510];

// Ez a d-sugarú minimum-kiválasztó-szúrõ. (Pts a fv. pontjai, n pedig, hogy hány pont van.)
void erode( int delta, Point*& pts, int& n )
{	
	if( delta == 0 )
		return;

	int i=0, i2=0;
	Point* t = (pts == tmp[0]) ? tmp[1] : tmp[0];

	for( ; i<n-1 && pts[i+1].y <= pts[i].y; ++i )
		t[i2++] = Point(pts[i].x - delta, pts[i].y);		

	t[i2++] = Point(pts[i].x - delta, pts[i].y);
	t[i2++] = Point(pts[i].x + delta, pts[i].y);		

	++i;

	for( ; i<n; ++i )
	{
		t[i2++] = Point(pts[i].x + delta, pts[i].y);		
	}

	pts = t;
	n = i2;
}

// Ez adja az x-középpontú, m meredekségû abszolútérték-alakot a függvényünkhöz.
void add( int x, int m, Point*& pts, int& n )
{	
	int i=0, i2=0;
	Point* t = (pts == tmp[0]) ? tmp[1] : tmp[0];

	for( ; i<n && pts[i].x < x; ++i )
		t[i2++] = Point(pts[i].x, pts[i].y + (x-pts[i].x)*(long long)m );

	if( i >= 1 && i < n && pts[i].x > x )
	{
		t[i2++] = Point(x, pts[i-1].y + (x - pts[i-1].x)*((pts[i].y - pts[i-1].y) / (pts[i].x - pts[i-1].x)) );
	}

	for( ; i<n; ++i )
		t[i2++] = Point(pts[i].x, pts[i].y + (pts[i].x-x)*(long long)m );	

	pts = t;
	n = i2;
}

// Kiértékeli a függvényt egy x helyen.
long long eval( int x, const Point* pts, const int n )
{	
	if( n == 1 && x == pts[0].x )
		return pts[0].y;

	for( int i=0; i<n-1; ++i )
	{
		if( x >= pts[i].x && x <= pts[i+1].x )
		{
			return pts[i].y + (x - pts[i].x)*((pts[i+1].y - pts[i].y) / (pts[i+1].x - pts[i].x));
		}
	}

	return -1;
}

int main()
{
	int C = fast_getint();
	while(C--)
	{
		int N = fast_getint();
		int D = fast_getint();
		
		int h0 = fast_getint();
		
		int pts_num = 1;
		Point* pts = tmp[0];
		pts[0] = Point( h0, 0 );

		for( int i=1; i<N-1; ++i )
		{
			int h = fast_getint();
			
			erode( D, pts, pts_num );
			add( h, 1, pts, pts_num );
		}

		erode( D, pts, pts_num );

		int hN = fast_getint();

		long long cost = eval( hN, pts, pts_num );
		if( cost < 0 )
			printf("impossible\n");
		else
			printf("%lld\n", cost);

	}
	return 0;
}