/* Copyright Viet-Trung Luu (ACM ICPC ECNA 1999) */

char bd[20][30];
char bd2[20][30];

int clust(int x, int y, char c) {
    if(bd[y][x] != c) return 0;
    bd[y][x] = 0;
    return 1 + clust(x+1, y, c) + clust(x-1, y, c) + clust(x, y+1, c) + clust(x, y-1, c);
}

main() {
    int n, game, sc, mv, bl, i, j, k, l, b, bi, bj;
    char buf[100];

    gets(buf);
    sscanf(buf, "%d", &n);
    for(game = 1; game <= n; game++) {
        gets(buf);
        for(i = 10; i >= 1; i--) {
            gets(bd[i]+1);
            bd[i][0] = bd[i][16] = 0;
        }

        if (game > 1) {
            printf("\n");
        }
        printf("Game %d:\n\n", game);

        for(sc = 0, mv = 1, bl = 150;; mv++) {
            memcpy(bd2, bd, sizeof(bd));
            for(i = 1, b = 0; i <= 15; i++) {
                for(j = 1; j <= 10; j++) {
                    if(bd[j][i] && (k = clust(i, j, bd[j][i])) > b) {
                        b = k;
                        bi = i;
                        bj = j;
                    }
                }
            }
            if(b <= 1) break;
            memcpy(bd, bd2, sizeof(bd));
            printf("Move %d at (%d,%d): removed %d balls of color %c, got %d points.\n", mv, bj, bi, b, bd[bj][bi], (b-2)*(b-2));
            bl -= b;
            sc += (b-2)*(b-2);
            clust(bi, bj, bd[bj][bi]);

            for(i = 1; i <= 15; i++) {
                for(j = 1, l = 0; j <= 10; j++) l += (bd[j][i] != 0);
                for(j = 1; j <= l;) {
                    if(bd[j][i]) j++;
                    else for(k = j; k <= 10; k++) bd[k][i] = bd[k+1][i];
                }
            }

            for(i = 1, l = 0; i <= 15; i++) l += (bd[1][i] != 0);
            for(i = 1; i <= l;) {
                if(bd[1][i]) i++;
                else for(j = i; j <= 15; j++) for(k = 1; k <= 10; k++) bd[k][j] = bd[k][j+1];
            }
        }
        if(!bl) sc += 1000;
        printf("Final score: %d, with %d balls remaining.\n", sc, bl);
    }
}
