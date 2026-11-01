/* Copyright Derek Kisman (ACM ICPC ECNA 1999) */

#include <math.h>

typedef struct {
	double x, y;
} Point;

typedef struct {
	Point c1, c2;
} Line;

Line w[50];
int nw;

int vw[1000];
Point vp[1000];
int vc[1000][1000];
int nv;
int vd[1000];

int DoLinesIntersect( Line l1, Line l2 ) {
	double n1, n2;
	Point d1, d2;
	d1.x = l1.c2.x-l1.c1.x; d1.y = l1.c2.y-l1.c1.y;
	d2.x = l2.c2.x-l2.c1.x; d2.y = l2.c2.y-l2.c1.y;
	n1 = d1.x*(l2.c1.y-l1.c1.y)-d1.y*(l2.c1.x-l1.c1.x);
	n2 = d1.y*d2.x-d1.x*d2.y;
	if( n1*n2 < 0.0000000001 || fabs(n1) >= fabs(n2) ) return 0;
	n1 = d2.x*(l1.c1.y-l2.c1.y)-d2.y*(l1.c1.x-l2.c1.x);
	return( -n1*n2 > 0.0000000001 && fabs(n1) < fabs(n2) );
}

Point LineIntersection( Line l1, Line l2 ) {
	Point i, d1, d2;
	double n1, n2;

	i.x = -1000.0; i.y = -1000.0;
	d1.x = l1.c2.x-l1.c1.x; d1.y = l1.c2.y-l1.c1.y;
	d2.x = l2.c2.x-l2.c1.x; d2.y = l2.c2.y-l2.c1.y;
	n2 = d1.y * d2.x - d1.x * d2.y;
	if( fabs(n2) < 0.0000001 ) return i;
	n1 = d1.x * (l2.c1.y-l1.c1.y) - d1.y * (l2.c1.x-l1.c1.x);
	i.x = n1 * d2.x / n2 + l2.c1.x;
	i.y = n1 * d2.y / n2 + l2.c1.y;
	return i;
}

int dcmp( double *a, double *b ) {
	if( *a > *b ) return 1;
	if( *a < *b ) return -1;
	return 0;
}

void AddWall( int n ) {
	int i, j;
	Point pt;
	double dint[50];
	int nint = 0;
	double ln = hypot( w[n].c2.x-w[n].c1.x, w[n].c2.y-w[n].c1.y );

	for( i = 0; i < nw; i++ ) if( i != n ) {
		pt = LineIntersection( w[n], w[i] );
		if( pt.x < -0.0000001 || pt.x > 100.0000001 ||
			pt.y < -0.0000001 || pt.y > 100.0000001 ) continue;
		dint[nint++] = hypot( pt.x-w[n].c1.x, pt.y-w[n].c1.y ) / ln;
	}
	qsort( dint, nint, sizeof(double), dcmp );

	for( i = 1; i < nint; i++ ) {
		ln = (dint[i-1]+dint[i])/2.0;
		vp[nv].x = w[n].c1.x+(w[n].c2.x-w[n].c1.x)*ln;
		vp[nv].y = w[n].c1.y+(w[n].c2.y-w[n].c1.y)*ln;
		vw[nv] = n;
		if( n < 4 ) {
			vc[0][nv] = 1;
		}
		nv++;
	}
}

int q[1000000], qs, qe;

main() {
	int i, j, k, x, y, z, n;
	Line l;

	scanf( " %d", &nw );
	nw += 4;
	w[0].c1.x = 0.0; w[0].c1.y = 0.0; w[0].c2.x = 100.0; w[0].c2.y = 0.0;
	w[1].c1.x = 100.0; w[1].c1.y = 0.0; w[1].c2.x = 100.0; w[1].c2.y = 100.0;
	w[2].c1.x = 100.0; w[2].c1.y = 100.0; w[2].c2.x = 0.0; w[2].c2.y = 100.0;
	w[3].c1.x = 0.0; w[3].c1.y = 100.0; w[3].c2.x = 0.0; w[3].c2.y = 0.0;
	for( i = 4; i < nw; i++ )
		scanf( " %lf %lf %lf %lf", &w[i].c1.x, &w[i].c1.y, &w[i].c2.x, &w[i].c2.y );

	nv = 2;
	vw[0] = vw[1] = -1;
	scanf( " %lf %lf", &vp[1].x, &vp[1].y );
	memset( vc, 0, sizeof(vc) );
	for( i = 0; i < nw; i++ ) AddWall( i );

	for( i = 1; i < nv; i++ ) for( j = i+1; j < nv; j++ ) {
		l.c1 = vp[i]; l.c2 = vp[j];
		for( k = 0; k < nw; k++ ) if( k != vw[i] && k != vw[j] ) {
			if( DoLinesIntersect( l, w[k] ) ) break;
		}
		if( k == nw ) vc[i][j] = vc[j][i] = 1;
	}

	for( i = 0; i < nv; i++ ) vd[i] = 1000000;
	vd[1] = 0;
	qs = 0; qe = 1;
	q[0] = 1;
	while( qs < qe ) {
		x = q[qs++];
		for( i = 0; i < nv; i++ ) if( vc[i][x] && vd[x]+1 < vd[i] ) {
			vd[i] = vd[x]+1;
			q[qe++] = i;
		}
	}
	printf( "Number of doors = %d\n", vd[0]-1 );
/*for( i = 0; i < nv; i++ ) printf( "(%.3f,%.3f) - %d\n", vp[i].x, vp[i].y, vd[i] );*/
}
