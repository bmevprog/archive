/* Copyright Derek Kisman (ACM ICPC ECNA 1999) */

int tri[9][3] = {{1, 2, 3}, {2, 3, 5}, {2, 4, 5},
                                 {3, 5, 6}, {4, 7, 8}, {4, 5, 8},
                                 {5, 8, 9}, {5, 6, 9}, {6, 9, 10}};
int sd[18][2] = {{1, 2}, {1, 3}, {2, 3}, {2, 4}, {2, 5}, {3, 5},
                                 {3, 6}, {4, 5}, {5, 6}, {4, 7}, {4, 8}, {5, 8},                                 {5, 9}, {6, 9}, {6, 10}, {7, 8}, {8, 9}, {9, 10}};
int tsdb[9][3];

int score[0x40000];

int ntri( int tb, int x ) {
        int i, j, y, z=0;

        for( i = 0; i < 9; i++ ) {
                for( j = 0; j < 3; j++ ) if( tsdb[i][j] == x ) break;
                if( j == 3 ) continue;
                y = 0;
                for( j = 0; j < 3; j++ ) if( tb&tsdb[i][j] ) y++;
                if( y == 2 ) z++;
        }
        return z;
}

int SC( int tb ) {
        int i, j, k, x, y, z, max;

        if( score[tb] > -100 ) return score[tb];
        max = -100;
        for( x = 1; x < 0x40000; x *= 2 ) if( !(tb&x) ) {
                z = ntri( tb, x );
                if( z == 0 ) y = -SC( tb | x ); else y = z + SC( tb | x );
                if( y > max ) max = y;
        }
        return( score[tb] = max );
}

main() {
        int i, j, k, x, y, z, n, nprob, prob=1, pl, tb, sc;

        for( i = 0; i < 9; i++ ) {
                for( x = 1, j = 0; j < 18; j++, x *= 2 )
                        if( sd[j][0] == tri[i][0] && sd[j][1] == tri[i][1] ) break;
                tsdb[i][0] = x;
                for( x = 1, j = 0; j < 18; j++, x *= 2 )
                        if( sd[j][0] == tri[i][0] && sd[j][1] == tri[i][2] ) break;
                tsdb[i][1] = x;
                for( x = 1, j = 0; j < 18; j++, x *= 2 )
                        if( sd[j][0] == tri[i][1] && sd[j][1] == tri[i][2] ) break;
                tsdb[i][2] = x;
        }
        for( i = 0; i < 0x40000; i++ ) score[i] = -100;
        score[0x3FFFF] = 0;

        for( scanf( " %d", &nprob ); nprob > 0; nprob-- ) {
                scanf( " %d", &n );
                pl = 1; sc = 0; tb = 0;
                for( i = 0; i < n; i++ ) {
                        scanf( " %d %d", &y, &z );
                        for( x = 1, j = 0; j < 18; j++, x *= 2 )
                                if( y == sd[j][0] && z == sd[j][1] ) break;
                        z = ntri( tb, x );
                        if( z == 0 ) pl = -pl; else sc += z*pl;
                        tb = tb | x;
                } 
                printf( "Game %d: %c wins.\n", prob++, (sc+pl*SC(tb)>0)?'A':'B' );
        }
}

