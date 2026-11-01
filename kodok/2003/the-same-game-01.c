/* Copyright Charlie Clarke (ACM ICPC ECNA 1999) */

#include <stdio.h>

#define N 100

char board[N][N];
int cluster[N][N]; 
int csize[N*N];
int rows, cols;

fill (int i, int j, char b, int c)
{
  if (
    i >= 0 && i < rows && j >= 0 && j < cols && cluster[i][j] == -1
    && board[i][j] == b
  )
    {
      cluster[i][j] = c;
      fill (i + 1, j, b, c);
      fill (i - 1, j, b, c);
      fill (i, j + 1, b, c);
      fill (i, j - 1, b, c);
    }
}

int score, balls;
char removed;
int gotWhere, rowWhere, colWhere;

int
move ()
{
  int i, j, k, l, c = 0;

  gotWhere = 0;

  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++)
      cluster[i][j] = -1;

  for (j = 0; j < cols; j++)
    for (i = 0; i < rows; i++)
      if (cluster[i][j] == -1 && board[i][j] != ' ')
        fill (i, j, board[i][j], c++);

  if (c == 0) {
    score = 1000;
    return 0;
  }

  for (i = 0; i < c; i++)
    csize[i] = 0;

  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++)
      if (cluster[i][j] != -1)
        csize[cluster[i][j]]++;

  k  = 0;
  for (i = 1; i < c; i++)
    if (csize[i] > csize[k])
      k = i;

  if (csize[k] < 2) {
    score = 0;
    return 0;
  }
  balls = csize[k];
  score = csize[k] - 2;
  score *= score;

  for (j = 0; j < cols; j++)
    for (i = 0; i < rows; i++)
      if (cluster[i][j] == k) {
        if (gotWhere == 0)
          {
            rowWhere = i + 1;
            colWhere = j + 1;
            gotWhere = 1;
          }
        removed = board[i][j];
        board[i][j] = ' ';
      }

  l = 0;
  for (j = 0; j < cols; j++)
    {
      k = c = 0;
      for (i = 0; i < rows; i++)
        {
          char temp = board[i][j];
          board[i][j] = ' ';
          if (temp != ' ')
            {
              board[k][l] = temp;
              k++;
              c = 1;
            }
        }
      if (c) l++;
    }

  return 1;
}

int
remaining ()
{
  int i, j, n = 0;

  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++)
      if (board[i][j] != ' ')
        n++;
  return n;
}

int game = 1;

doit ()
{
  int i, j, total;
  int mv = 1;

  if (game > 1) printf ("\n");
  printf ("Game %d:\n\n", game);

  cols = 15;
  rows = 10;
  while (getchar () != '\n');

  for (i = rows - 1; i >= 0; --i)
    {
      for (j = 0; j < cols; j++)
        board[i][j] = getchar ();
      getchar ();
    }

  total = 0;
  while (move ())
    {
      total += score;
      printf (
        "Move %d at (%d,%d): removed %d balls of color %c, got %d points.\n",
        mv, rowWhere, colWhere, balls, removed, score
      );
      mv++;
    }
  total += score;
  printf ("Final score: %d, with %d balls remaining.\n", total, remaining());
  game++;
}

main ()
{
  int n;

  scanf ("%d", &n);
  while (getchar () != '\n');
  while (n--)
    doit ();
}
