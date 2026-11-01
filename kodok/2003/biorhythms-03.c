/* Copyright Derek Kisman (ACM ICPC ECNA 1999) */

main() {
	int p, e, i, d, prob=1;

	for(;;) {
		scanf( " %d %d %d %d", &p, &e, &i, &d );
		if( p+e+i+d==-4 ) break;
		p = (p+2300-d)%23;
		e = (e+2800-d)%28;
		i = (i+3300-d)%33;
		d = 0;
		for( d = 0; p+e+i > 0; d++ ) {
			p = (p+1)%23;
			e = (e+1)%28;
			i = (i+1)%33;
		}
		printf( "Case %d: the next triple peak occurs in %d days.\n", prob++, 21252-d );
	}
}
