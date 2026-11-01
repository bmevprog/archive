/* Copyright Viet-Trung Luu (ACM ICPC ECNA 1999) */

char x[26000];

main() {
    int a, b, c, d, i, j;

    for(j = 1;; j++) {
        scanf(" %d %d %d %d", &a, &b, &c, &d);
        if(a < 0) break;
        a = (a + 368 - d) % 23;
        b = (b + 392 - d) % 28;
        c = (c + 396 - d) % 33;
        memset(x, 0, sizeof(x));
        for(i = b; i < 25000; i += 28) x[i]++;
        for(i = c; i < 25000; i += 33) x[i]++;
        for(i = a ? a : 23; i < 25000 && x[i] != 2; i += 23);
        printf("Case %d: the next triple peak occurs in %d days.\n", j, i);
    }
}

