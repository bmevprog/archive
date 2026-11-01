/* Copyright Viet-Trung Luu (ACM ICPC ECNA 1999) */

#define mod(a, b) (((a) < 0) ? ((b) + ((a) % (b))) : ((a) % (b)))


/*
 * Extended Euclidean algorithm. Computes d, x, y such that gcd(a, b) =
 * d = ax + by.
 */
void exeuclid(int a, int b, int *d, int *x, int *y) {
    int x2, y2;

    if(b == 0) {
        *d = a;
        *x = 1;
        *y = 0;
        return;
    }

    exeuclid(b, mod(a, b), d, &x2, &y2);
    *x = y2;
    *y = x2 - (a / b) * y2;
}


/*
 * Solves the modular linear equation ax = b (mod n) for x (a, b
 * integers, and n positive). Returns a positive solution (0 <= x < n),
 * and -1 if no solution. If there is a solution, *inc is set to the
 * value such that x + i * inc is also a solution (mod n) for all i.
 */
int modsolve(int a, int b, int n, int *inc) {
    int d, x, y;

    exeuclid(a, n, &d, &x, &y);

    if(b % d)
        return -1;

    *inc = mod(n / d, n);
    return mod(x * (b / d), n);
}

/*
 * Computes a^-1 (mod m), assuming it exists (a and m must be relatively
 * prime). Returns -1 if no inverse, otherwise 0 <= a^-1 < m.
 */
int modinv(int a, int m) {
    int i;
    return modsolve(a, 1, m, &i);
}


/*
 * Solves for x = a_1 (mod m_1), ..., x = a_n (mod m_n), where m_1, ...,
 * m_n are pairwise relatively prime. Returns x mod m_1 * ... * m_n.
 */
int crt(int *a, int *m, int n) {
    int i, A, M;

    if(n < 1)
        return -1;

    A = a[0];
    M = m[0];

    for(i = 1; i < n; i++) {
        A = A * m[i] * modinv(m[i], M) + a[i] * M * modinv(M, m[i]);
        M *= m[i];
        A = mod(A, M);
    }

    return A;
}


main() {
    int a, b, c, d, i, j;
    int A[3], M[3] = { 23, 28, 33 };

    for(j = 1;; j++) {
        scanf(" %d %d %d %d", &a, &b, &c, &d);
        if(a < 0) break;
        A[0] = (a + 368 - d) % 23;
        A[1] = (b + 392 - d) % 28;
        A[2] = (c + 396 - d) % 33;
        i = crt(A, M, 3);
        if(!i) i = 23 * 28 * 33;

        printf("Case %d: the next triple peak occurs in %d days.\n", j, i);
    }
}

