/* Copyright Howard Cheng (ACM ICPC ECNA 1999) */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void)
{
  int d, a[3], m[3], M, i, case_num;

  m[0] = 23;
  m[1] = 28;
  m[2] = 33;
  M = 23*28*33;

  for (case_num = 1; 
       scanf("%d %d %d %d", a, a+1, a+2, &d) == 4 && 
	 a[0] != -1 && a[1] != -1 && a[2] != -1 && d != -1;
       case_num++) {
    for (i = d+1; (i-a[0]) % m[0] || (i-a[1]) % m[1] || (i-a[2]) % m[2]; i++)
      ;

    printf("Case %d: the next triple peak occurs in %d days.\n", case_num,
	   i-d);
  }

  return 0;
}

