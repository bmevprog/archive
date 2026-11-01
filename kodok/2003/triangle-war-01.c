/* Copyright Charlie Clarke (ACM ICPC ECNA 1999) */

#include <stdio.h>

int m[18] = {
  0x00001, 0x00002, 0x00004, 0x00008, 0x00010, 0x00020, 0x00040, 0x00080,
  0x00100, 0x00200, 0x00400, 0x00800, 0x01000, 0x02000, 0x04000, 0x08000,
  0x10000, 0x20000
};

int a[18], b[18];

ab ()
{
  a[ 0] = m[ 1] | m[ 2]; a[ 1] = m[ 0] | m[ 2]; a[ 2] = m[ 0] | m[ 1];
  a[ 3] = m[ 4] | m[ 7]; a[ 4] = m[ 3] | m[ 7]; a[ 5] = m[ 2] | m[ 4];
  a[ 6] = m[ 5] | m[ 8]; a[ 7] = m[ 3] | m[ 4]; a[ 8] = m[ 5] | m[ 6];
  a[ 9] = m[10] | m[15]; a[10] = m[ 9] | m[15]; a[11] = m[ 7] | m[10];
  a[12] = m[11] | m[16]; a[13] = m[ 8] | m[12]; a[14] = m[13] | m[17];
  a[15] = m[ 9] | m[10]; a[16] = m[11] | m[12]; a[17] = m[13] | m[14];

  b[ 2] = m[ 4] | m[ 5]; b[ 4] = m[ 2] | m[ 5]; b[ 5] = m[ 6] | m[ 8];
  b[ 7] = m[10] | m[11]; b[ 8] = m[12] | m[13]; b[10] = m[ 7] | m[11];
  b[11] = m[12] | m[16]; b[12] = m[ 8] | m[13]; b[13] = m[14] | m[17];
}

int
completes (int state, int edge)
{
  int i = 0;

  if ((a[edge] & state) == a[edge])
    i++;
  if (b[edge] && (b[edge] & state) == b[edge])
    i++;
  return i;
}

#define STATES 256*1024

int me[STATES], u[STATES];

init ()
{
  int i;

  for (i = 0; i < STATES; i++)
    me[i] = u[i] = -1;
}

foo (int state)
{
  int i;
  int mme = -1, mu = -1;

  if (me[state] != -1) return;

  for (i = 0; i < 18; i++)
    if (!(m[i] & state))
      {
        int tme, tu, c = completes (state, i);
        int s = m[i] | state;
        foo (s);
        if (c > 0)
          {
            tme = me[s] + c;
            tu = u[s];
          }
        else
          {
            tme = u[s];
            tu = me[s];
          }
        if (tme > mme)
          {
            mme = tme;
            mu = tu;
          }
      }
  me[state] = mme;
  u[state] = mu;
}

solve ()
{
  int i;

  ab ();
  init ();

  me[STATES-1] = u[STATES-1] = 0;

  for (i = 0; i < STATES; i++)
    foo (i);
}

int
edge (int x, int y)
{
  if (x > y)
    {
      int temp = x;
      x = y;
      y = temp;
    }
  if (x == 1 && y ==  2) return  0;
  if (x == 1 && y ==  3) return  1;
  if (x == 2 && y ==  3) return  2;
  if (x == 2 && y ==  4) return  3;
  if (x == 2 && y ==  5) return  4;
  if (x == 3 && y ==  5) return  5;
  if (x == 3 && y ==  6) return  6;
  if (x == 4 && y ==  5) return  7;
  if (x == 5 && y ==  6) return  8;
  if (x == 4 && y ==  7) return  9;
  if (x == 4 && y ==  8) return 10;
  if (x == 5 && y ==  8) return 11;
  if (x == 5 && y ==  9) return 12;
  if (x == 6 && y ==  9) return 13;
  if (x == 6 && y == 10) return 14;
  if (x == 7 && y ==  8) return 15;
  if (x == 8 && y ==  9) return 16;
  if (x == 9 && y == 10) return 17;
  printf ("weird edge %d %d\n", x, y);
  exit (0);
}

main ()
{
  int N, game = 1;

  solve ();

  scanf ("%d", &N);
  while (N--)
    {
      int i, M, state = 0, cme = 0, cu = 0, turn = 1;

      scanf ("%d", &M);

      for (i = 0; i < M; i++)
        {
          int x, y, e, c;

          scanf ("%d %d\n", &x, &y);
          e = edge (x, y);
          c = completes (state, e);
          state |= m[e];
          if (turn)
            if (c)
              cme += c;
            else
              turn = 0;
          else
            if (c)
              cu += c;
            else
              turn = 1;
        }

      if (turn)
        {
          cme += me[state];
          cu += u[state];
        }
      else
        {
          cme += u[state];
          cu += me[state];
        }

      if (cme > cu)
        printf ("Game %d: A wins.\n", game);
      else if (cme < cu) 
        printf ("Game %d: B wins.\n", game);
      else 
        printf ("Game %d: Weird result.\n", game);
      game++;
    }
}
