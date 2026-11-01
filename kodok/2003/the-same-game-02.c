/* Copyright Derek Kisman (ACM ICPC ECNA 1999) */

char g[17][12];
int gu[17][12];
int score, mv;

int cluster( int x, int y, char ch, char ch2 ) {
	if( gu[x][y] ) return 0;
	if( g[x][y] != ch ) return 0;
	g[x][y] = ch2;
	gu[x][y] = 1;
	return 1+cluster(x-1,y,ch,ch2)+cluster(x+1,y,ch,ch2)+cluster(x,y-1,ch,ch2)+cluster(x,y+1,ch,ch2);
}

void move( int x, int y ) {
	int val, pt, ch;
	int i, j, k, z;

	ch=g[x][y];
	memset( gu, 0, sizeof(gu) );
	val = cluster( x, y, ch, ' ' );
	pt = (val-2)*(val-2);
	score += pt;
	printf( "Move %d at (%d,%d): removed %d balls of color %c, got %d points.\n",
			mv++, y, x, val, ch, pt );
	for( i = 1; i <= 15; i++ ) {
		z = 1;
		for( j = 1; j <= 10; j++ ) {
			if( g[i][j] != ' ' ) {
				g[i][z++] = g[i][j];
			}
		}
		for( ; z <= 10; z++ ) g[i][z] = ' ';
	}
	z = 1;
	for( i = 1; i <= 15; i++ ) {
		if( g[i][1] != ' ' ) {
			for( j = 1; j <= 10; j++ ) g[z][j] = g[i][j];
			z++;
		}
	}
	for( ; z <= 15; z++ ) for( j = 1; j <= 10; j++ ) g[z][j] = ' ';
}

main() {
	int i, j, k, x, y, z, n, nprob, prob=1;
	int max, xmax, ymax;

	for( scanf( " %d", &nprob ); nprob > 0; nprob-- ) {
		for( i = 0; i <= 11; i++ ) for( j = 0; j <= 16; j++ ) g[j][i] = ' ';
		for( i = 10; i >= 1; i-- ) for( j = 1; j <= 15; j++ ) scanf( " %c", &g[j][i] );

		if( prob>1 ) putchar( '\n' );
		printf( "Game %d:\n\n", prob++ );
		mv = 1; score = 0;

		for(;;) {
			max = 1;
			for( x = 1; x <= 15; x++ ) for( y = 1; y <= 10; y++ ) {
				if( g[x][y] == ' ' ) continue;
				memset( gu, 0, sizeof(gu) );
				z = cluster( x, y, g[x][y], g[x][y] );
				if( z > max ) {
					max = z;
					xmax = x;
					ymax = y;
				}
			}
			if( max == 1 ) break;
			move( xmax, ymax );
		}

		x = 0;
		for( i = 1; i <= 10; i++ ) for( j = 1; j <= 15; j++ )
			if( g[j][i] != ' ' ) x++;
		if( x == 0 ) score += 1000;
		printf( "Final score: %d, with %d balls remaining.\n", score, x );
	}
}
