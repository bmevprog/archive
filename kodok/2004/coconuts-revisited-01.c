/*
    1997 East-Central ACM regional programming contest
    Held on November 8, 1997

    Coconuts, Revisited -- Problem 3

    Sample solution by Ed Karrels, Ed@tool.com
    November 1997
*/

#include <stdio.h>

    /* return 1 if this number of coconuts can be divided up
       properly between this number of people */
int SplitCoco(long n_coco, long n_people) {
    long i;

    for (i=0; i<n_people; i++) {
            /* check that the coconuts divide by the number of people
               plus one remainder */
        if (n_coco % n_people != 1) return 0;
            /* remove 1 for the monkey, and one person's share */
        n_coco = n_coco - 1 - (n_coco / n_people);
    }
        /* check that the remaining coconuts divide evenly among
           the people */
    return (n_coco % n_people) == 0;
}

int main() {
    long n_coco;
    long n_people;
    long i, j, k;

    /* FILE *inf = fopen("prob_3.in", "r"); */
    FILE *inf = stdin;

    while (fscanf(inf, "%ld", &n_coco), n_coco!=-1) {
            /* starting at the # of coconuts-1, count down until
               a number of people is found that works */
        for (n_people=n_coco-1; n_people > 1; n_people--) {
            if (SplitCoco(n_coco, n_people)) {
                printf("%ld coconuts, %ld persons and 1 monkey\n",
                    n_coco, n_people);
                goto found;

                /* OK, so yea, I put a 'goto' in my code :-)
                   it was quick and it works.  I don't do
                   it often, I swear. */

            }
        }
            /* if no number of people greater than 1 works, there is
               no solution */
        printf("%ld coconuts, no solution\n", n_coco);
        found:
    }
    return 0;
}
