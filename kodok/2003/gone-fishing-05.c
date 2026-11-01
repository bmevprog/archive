/* Copyright Charlie Clarke (ACM ICPC ECNA 1999) */

#define TICKS (24*12)
#define LAKES 25

int ticks, lakes;

int distance[LAKES-1];
int initial[LAKES];
int decrease[LAKES];

int fish[TICKS][TICKS][LAKES];

struct {
  int action, fish;
} pl[TICKS][TICKS][LAKES];

void
catch()
{
  int i, j, k;

  for (k = 0; k < lakes; k++)
    for (i = 0; i < ticks; i++)
      {
        int f = initial[k];

        for (j = i; j >= 0; --j)
          {
            fish[i][j][k] = f;
            f -= decrease[k];
            if (f < 0) f = 0;
          }
      }
}

void
solve ()
{
  int i, j, k; 

  catch();

  k = lakes - 1;
  for (i = 0; i < ticks; i++)
    {
      pl[i][0][k].action = 0;
      pl[i][0][k].fish = fish[i][0][k];
      for (j = 1; j <= i; j++)
        {
          pl[i][j][k].action = 0;
          pl[i][j][k].fish = pl[i][j - 1][k].fish + fish[i][j][k];
        }
    }

  for (k = lakes - 2; k >=0; --k)
    {
      for (i = 0; i < ticks; i++)
        {
          pl[i][0][k].action = 0;
          pl[i][0][k].fish = fish[i][0][k];
          for (j = 1; j <= i; j++)
            if (j < distance[k])
              {
                pl[i][j][k].action = 0;
                pl[i][j][k].fish = pl[i][j - 1][k].fish + fish[i][j][k];
              }
          else
            {
              int d = distance[k];
              int stay = pl[i][j - 1][k].fish + fish[i][j][k];
              int change = pl[j - d][j - d][k + 1].fish;

              if (stay >= change)
                {
                  pl[i][j][k].action = 0;
                  pl[i][j][k].fish = stay;
                }
              else
                {
                  pl[i][j][k].action = d;
                  pl[i][j][k].fish = change;
                }
            }
        }
    }
}

void
report ()
{
  int i = ticks - 1, j = ticks - 1, k = 0;
  int t, space = 0;
  static int line = 0;

  if (line) printf ("\n");
  line = 1;

  t = 0;
  while (j >= 0)
    {
      int action = pl[i][j][k].action;

      if (action > 0)
        {
          if (space) printf (", ");
          space = 1;
          printf ("%d", 5*t);
          j -= action;
          i = j;
          k++;
          t = 0;
        }
      else
        {
          --j;
          t++;
        }
    }
  for (; k < lakes; k++)
    {
      if (space) printf (", ");
      space = 1;
      printf ("%d", 5*t);
      t = 0;
    }
  printf ("\n");
  printf ("Number of fish expected: %d\n", pl[ticks - 1][ticks - 1][0].fish);
}

int
read ()
{
  int i, hours;

  scanf ("%d", &lakes);
  if (lakes == 0) return 0;
  scanf ("%d", &hours);
  ticks = 12*hours;

  for (i = 0; i < lakes; i++)
    scanf ("%d", &initial[i]);

  for (i = 0; i < lakes; i++)
    scanf ("%d", &decrease[i]);

  for (i = 0; i < lakes - 1; i++)
    scanf ("%d", &distance[i]);

  return 1;
}

main ()
{
  while (read ())
    {
      solve ();
      report ();
    }
}

