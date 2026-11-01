/*
    1997 East-Central ACM regional programming contest
    Held on November 8, 1997

    Nonstop Travel -- Problem 4

    Sample solution by Ed Karrels, Ed@tool.com
    November 1997
*/
#include <stdio.h>
#include <math.h>

typedef struct {
    double dist;
    int g, y, r;   /* actually, all you need is g + y, they are equivalent */
} Light;


int LightIsGreenishYellow(Light *light, double time) {
        /* mod out any complete cycles
           for example, if the timings for green, yellow and red
           are 1, 2, 3, then a cycle is 6 seconds long.  If the
           time is 20 seconds, then 20=(6*3)+2, so it is 2 seconds
           into the cycle */
    time = fmod(time, light->g + light->y + light->r);

        /* if we are in the green or yellow parts of the cycle,
           we're all good */
    return time <= (light->g + light->y);
}


    /* check if a given speed will work for the given pattern
       of traffic lights */
int MustGoFaster_MustGoFaster(Light lights[6], int n_lights, int speed) {
    double time;
    int light_no;

    for (light_no = 0; light_no < n_lights; light_no++) {
            /* compute the time at which Fast Eddie, I mean,
               Fast Phil, will hit this light */
        time = lights[light_no].dist / speed * 3600.0;

            /* check what part of its cycle this light will be
               at at that time */
        if ( ! LightIsGreenishYellow(lights+light_no, time)) return 0;
    }
    return 1;
}



int main() {
    int c=1, n, i, speed;
    Light lights[6];
    int speeds[62];     /* a flag for each valid speed, with [61]==0 */
    int any;            /* were there any speeds that worked? */
    FILE *inf = stdin;//fopen("prob_4.in", "r");
    double f;           /* need to declare this just to the floating
                           point formats get linked */

    while (fscanf(inf, "%d", &n), n != -1) {
            /* read in the light definitions */
        for (i=0; i<n; i++) {
            fscanf(inf, "%lf %d %d %d", &f, &lights[i].g,
                  &lights[i].y, &lights[i].r);
            lights[i].dist = f;
        }
        any = 0;
        speeds[61] = 0;         /* put a terminator at the end so
                               the exit condition is easier */

                            /* try each possible speed */
        for (speed=30; speed <= 60; speed++) {
            speeds[speed] = MustGoFaster_MustGoFaster(lights, n, speed);
            any = any || speeds[speed];
        }

        printf("Case %d: ", c++);

        if (!any) {
            printf("No acceptable speeds.\n");
        } else {
            int span_start, span_end, first = 1;
            speed = 30;

                /* find all the spans of valid speeds */
            while (speed <= 60) {
                while (!speeds[speed] && speed <= 60) speed++;
                if (speed > 60) break;
                span_start = speed;
                while (speeds[speed]) span_end = speed++;

                if (first) {
                    first = 0;
                } else {
                    printf(", ");
                }

                if (span_start == span_end) {
                    printf("%d", span_start);
                } else {
                    printf("%d-%d", span_start, span_end);
                }
            }
            putchar('\n');
        }
    }

    return 0;
}
