/* Copyright Charlie Clarke (ACM ICPC ECNA 1999) */

#define TICKS (24*12)
#define LAKES 25

int ticks, lakes;

int distance[LAKES-1];
int initial[LAKES];
int decrease[LAKES];

int fish[TICKS][TICKS];
int plfish[LAKES][TICKS][TICKS];
short plaction[LAKES][TICKS][TICKS];

void
catch(int k)
{
  int i, j;

  for (i = 0; i < ticks; i++)
    {
      int f = initial[k];

      for (j = i; j >= 0; --j)
        {
          fish[i][j] = f;
          f -= decrease[k];
          if (f < 0) f = 0;
        }
    }
}
void
solve ()
{
  int i, j, k; 


  k = lakes - 1;
  catch(k);
  for (i = 0; i < ticks; i++)
    {
      plaction[k][i][0] = 0;
      plfish[k][i][0] = fish[i][0];
      for (j = 1; j <= i; j++)
        {
          plaction[k][i][j] = 0;
          plfish[k][i][j] = plfish[k][i][j - 1] + fish[i][j];
        }
    }

  for (k = lakes - 2; k >=0; --k)
    {
      catch(k);
      for (i = 0; i < ticks; i++)
        {
          plaction[k][i][0] = 0;
          plfish[k][i][0] = fish[i][0];
          for (j = 1; j <= i; j++)
            if (j < distance[k])
              {
                plaction[k][i][j] = 0;
                plfish[k][i][j] = plfish[k][i][j - 1] + fish[i][j];
              }
            else
              {
                int d = distance[k];
                int stay = plfish[k][i][j - 1] + fish[i][j];
                int change = plfish[k + 1][j - d][j - d];

                if (stay >= change)
                  {
                    plaction[k][i][j] = 0;
                    plfish[k][i][j] = stay;
                  }
                else
                  {
                    plaction[k][i][j] = d;
                    plfish[k][i][j] = change;
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
      int action = plaction[k][i][j];

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
  printf ("Number of fish expected: %d\n", plfish[0][ticks - 1][ticks - 1]);
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


