/* Copyright Derek Kisman (ACM ICPC ECNA 1999) */

int p[1000][4];
int n;

int lf[1000];

int Do( int x ) {
	int v[4], i, j, k, z;

	if( lf[x] > -1 ) return lf[x];
	for( i = 0; i < 4; i++ ) v[i] = Do( 4*x+1+i );
	for( i = 0; i < 4; i++ ) {
		z = 0;
		for( j = 0; j < 4; j++ ) if( v[i]>v[j] ) z++;
		p[x][z] = i;
	}
	return v[p[x][0]];
}

int g[16][16];

void Do2( int x, int x1, int y1, int x2, int y2 ) {
	int i, j;

	if( lf[x] > -1 ) {
		for( i = x1; i <= x2; i++ ) for( j = y1; j <= y2; j++ ) g[i][j] = lf[x];
		return;
	}
	Do2( 4*x+1+p[x][0], x1, y1, x1+(x2-x1)/2, y1+(y2-y1)/2 );
	Do2( 4*x+1+p[x][1], x1+(x2-x1)/2+1, y1, x2, y1+(y2-y1)/2 );
	Do2( 4*x+1+p[x][2], x1, y1+(y2-y1)/2+1, x1+(x2-x1)/2, y2 );
	Do2( 4*x+1+p[x][3], x1+(x2-x1)/2+1, y1+(y2-y1)/2+1, x2, y2 );
}

main() {
	int i, j, k, x, y, z, nprob, prob=1;

	for( scanf( " %d", &nprob ); nprob > 0; nprob-- ) {
		scanf( " %d", &n );
		scanf( " %d", &x );
		for( i = 0; i < 1000; i++ ) lf[i] = -1;
		for( i = 0; i < x; i++ ) {
			scanf( " %d %d", &k, &z );
			lf[k] = z;
		}
		Do( 0 );
		scanf( " %d", &x );
		for( i = 0; i < 1000; i++ ) lf[i] = -1;
		for( i = 0; i < x; i++ ) {
			scanf( " %d %d", &k, &z );
			lf[k] = z;
		}
		Do2( 0, 0, 0, n-1, n-1 );

		if( prob>1 ) putchar( '\n' );
		printf( "Case %d\n\n", prob++ );
		for( i = 0; i < n; i++ ) {
			for( j = 0; j < n; j++ ) printf( "%4d", g[j][i] );
			putchar( '\n' );
		}
	}
}
