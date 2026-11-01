/* Copyright Derek Kisman (ACM ICPC ECNA 1999) */

int prev[16*12+1][26];
int g[16*12+1][26];
int f[26], d[26], t[26];
int n, h;

void Pr( int i, int j, int com ) {
	if( j == 0 ) return;
	Pr( prev[i][j], j-1, 1 );
	printf( "%d", (i-prev[i][j]-t[j])*5 );
	if( com ) printf( ", " );
}

main() {
	int i, j, k, x, y, z, max, jmax, prob=1;

	for(;;) {
		if( scanf( " %d %d", &n, &h ) != 2 ) break;
		h *= 12;
		for( i = 1; i <= n; i++ ) scanf( " %d", &f[i] );
		for( i = 1; i <= n; i++ ) scanf( " %d", &d[i] );
		for( i = 2; i <= n; i++ ) scanf( " %d", &t[i] );
		t[1] = 0;

		for( i = 0; i <= h; i++ ) for( j = 0; j <= n; j++ ) g[i][j] = -1000000000;
		g[0][0] = 0;
		prev[0][0] = -1;

		for( i = 1; i <= n; i++ ) {
			for( j = h; j >= t[i]; j-- ) if( g[j-t[i]][i-1] != -1000000000 ) {
				x = g[j-t[i]][i-1]; y = f[i]; k = j;
				while( k <= h ) {
					if( x > g[k][i] ) {
						g[k][i] = x;
						prev[k][i] = j-t[i];
					}
					x += y;
					y = (y<d[i]) ? 0 : y-d[i];
					k++;
				}
			}
		}

		max = -1000000000;
		for( j = 0; j <= n; j++ )
			if( g[h][j] > max ) {
				max = g[h][j];
				jmax = j;
			}

		if( prob++ > 1 ) putchar( '\n' );
		Pr( h, jmax, 0 );
		for( ; jmax <= n-1; jmax++ ) printf( ", 0" );
		putchar( '\n' );
		printf( "Number of fish expected: %d\n", max );
	}
}
