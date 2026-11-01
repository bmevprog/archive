/* Copyright Charlie Clarke (ACM ICPC ECNA 1999) */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define EPSILON 0.000001
#define ABS(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))
#define EQUAL(a, b) (ABS ((a), (b)) < EPSILON)

multiFailure (
  double xp, double yp, int lx0, int ly0, int lx1, int ly1
)
{
  printf ("(%f, %f) lies on (%d, %d)-(%d, %d)\n", xp, yp, lx0, ly0, lx1, ly1);
  exit (0);
}

int
location (
  double xp, double yp, int lx0, int ly0, int lx1, int ly1
)
{
  double x0 = (double) lx0; double y0 = (double) ly0;
  double x1 = (double) lx1; double y1 = (double) ly1;
  double yy;

  if (ly0 == ly1)
    if (yp - y0 > EPSILON) 
      return 1;
    else if (yp - y0 < -EPSILON)
      return -1;
    else
      multiFailure (xp, yp, lx0, ly0, lx1, ly1);

  if (lx0 == lx1)
    if (xp - x0 > EPSILON)
      return 1;
    else if (xp - x0 < -EPSILON)
      return -1;
    else
      multiFailure (xp, yp, lx0, ly0, lx1, ly1);

  yy = (xp - x0)*(y1 - y0)/(x1 - x0) + y0;

  if (yp - yy > EPSILON)
    return 1;
  else if (yp - yy < -EPSILON)
    return -1;
  else
    multiFailure (xp, yp, lx0, ly0, lx1, ly1);
}

paraFailure (
  double ax0, double ay0, double ax1, double ay1, 
  double bx0, double by0, double bx1, double by1
)
{
  printf (
    "lines (%f, %f)-(%f, %f) and (%f, %f)-(%f, %f) are parallel or colinear\n",
    ax0, ay0, ax1, ay1, bx0, by0, bx1, by1
  );
  exit (0);
}

static inline
il (
  double ax0, double ay0, double ax1, double ay1, 
  double bx0, double by0, double bx1, double by1, 
  double *cx, double *cy
)
{
  double xx, yy;

  if (EQUAL (ax0, ax1))
    if (EQUAL(bx0,bx1))
      paraFailure (ax0, ay0, ax1, ay1, bx0, by0, bx1, by1);
    else
      {
        xx = ax0;
        yy = (xx - bx0)*(by1 - by0)/(bx1 - bx0) + by0;
      }
  else if (EQUAL (bx0,bx1))
    {
      xx = bx0;
      yy = (xx - ax0)*(ay1 - ay0)/(ax1 - ax0) + ay0;
    }
  else
    {
      double A = (ay1 - ay0)/(ax1 - ax0);
      double B = (by1 - by0)/(bx1 - bx0);

      if (EQUAL (A, B))
        paraFailure (ax0, ay0, ax1, ay1, bx0, by0, bx1, by1);

      xx = ((A*ax0 - ay0) - (B*bx0 - by0))/(A - B);
      yy = A*(xx - ax0) + ay0;
    }

  *cx = xx;
  *cy = yy;
}

int
ile (
  double ex0, double ey0, double ex1, double ey1,
  int lx0, int ly0, int lx1, int ly1,
  double *px, double *py, double *zx, double *zy, double *mx, double *my
)
{
  int loc0 = location (ex0, ey0, lx0, ly0, lx1, ly1);
  int loc1 = location (ex1, ey1, lx0, ly0, lx1, ly1);

  if (loc0 > 0)
    if (loc1 > 0)
      return 1;
    else
      {
        *px = ex0;
        *py = ey0;
        *mx = ex1;
        *my = ey1;
      }
  else if (loc1 < 0)
    return -1;
  else 
    {
      *px = ex1;
      *py = ey1;
      *mx = ex0;
      *my = ey0;
    }

  il (
    ex0, ey0, ex1, ey1, (double) lx0, (double) ly0, (double) lx1, (double) ly1,
    zx, zy
  );

  return 0;
}

typedef struct edgeStruct {
  struct edgeStruct *next;
  double x0, y0, x1, y1;
  int room;
} *edge;

#define newEdge() ((edge) malloc (sizeof (struct edgeStruct)))

int
divide (edge room, int lx0, int ly0, int lx1, int ly1, edge *room0, edge *room1){
  edge rp = (edge) 0, rm = (edge) 0, e0;
  int i = 0, j;
  double xx[2], yy[2];
  double px, py, zx, zy, mx, my;

  while (room)
    {
      e0 = room;
      room = room->next;
      j =
        ile (
          e0->x0, e0->y0, e0->x1, e0->y1, lx0, ly0, lx1, ly1,
          &px, &py, &zx, &zy, &mx, &my
        );
      if (j < 0)
        {
          e0->next = rm;
          rm = e0;
        }
      else if (j > 0)
        {
          e0->next = rp;
          rp = e0;
        }
      else
        {
          e0->x0 = px; e0->y0 = py; e0->x1 = zx; e0->y1 = zy;
          e0->next = rp;
          rp = e0;
          e0 = newEdge ();
          e0->x0 = mx; e0->y0 = my; e0->x1 = zx; e0->y1 = zy;
          e0->next = rm;
          rm = e0;
          xx[i] = zx;
          yy[i] = zy;
          i++;
        }
    }

  if (rp)
    {
      if (rm)
        {
          assert (i == 2);
          e0 = newEdge ();
          e0->x0 = xx[0]; e0->y0 = yy[0]; e0->x1 = xx[1]; e0->y1 = yy[1];
          e0->next = rp;
          rp = e0;
          e0 = newEdge ();
          e0->x0 = xx[0]; e0->y0 = yy[0]; e0->x1 = xx[1]; e0->y1 = yy[1];
          e0->next = rm;
          rm = e0;
          *room0 = rp;
          *room1 = rm;
          return 1;
        }
      else
        {
          *room0 = rp;
          return 0;
        }
    }
  else if (rm)
    {
      *room0 = rm;
      return 0;
    }
  else
    {
      printf ("Room disappeared\n");
      exit (0);
    }
}

edge roomStorage0[1000];
edge roomStorage1[1000];
edge *room0 = roomStorage0, *room1 = roomStorage1;
int rooms;

initialRoom ()
{
  edge e0, r0 = (edge) 0;
  e0 = newEdge();
  e0->x0 = 0; e0->y0 = 0; e0->x1 = 0; e0->y1 = 100;
  e0->next = r0; r0 = e0;
  e0 = newEdge();
  e0->x0 = 0; e0->y0 = 100; e0->x1 = 100; e0->y1 = 100;
  e0->next = r0; r0 = e0;
  e0 = newEdge();
  e0->x0 = 100; e0->y0 = 100; e0->x1 = 100; e0->y1 = 0;
  e0->next = r0; r0 = e0;
  e0 = newEdge();
  e0->x0 = 100; e0->y0 = 0; e0->x1 = 0; e0->y1 = 0;
  e0->next = r0; r0 = e0;
  room0[0] = r0;
  rooms = 1;
}

applyLine (int lx0, int ly0, int lx1, int ly1)
{
  int i, j = 0;
  edge r0, r1, *temp;

  for (i = 0; i < rooms; i++)
    {
      if (divide (room0[i], lx0, ly0, lx1, ly1, &r0, &r1))
        room1[j++] = r1;
      room1[j++] = r0;
    }
  temp = room0;
  room0 = room1;
  room1 = temp;
  rooms = j;
}

int
containedIn (edge room, double x, double y)
{
  edge e0;
  int i = 0;

  for (e0 = room; e0; e0 = e0->next)
    if (
      (x > e0->x0 && x < e0->x1) || (x < e0->x0 && x > e0->x1)
      || (x == e0->x0 && e0->x0 < e0->x1) || (x == e0->x1 && e0->x1 < e0->x0)
    )
      {
        double yy = (x - e0->x0)*(e0->y1 - e0->y0)/(e0->x1 - e0->x0) + e0->y0;
        if (yy > y) i++;
      }

  return i == 1;
}

int
whichRoom (double x, double y)
{
  int i, ri;

  for (i = 0; i < rooms; i++)
    if (containedIn (room0[i], x, y))
      ri = i;

  return ri;
}

struct edgeStruct ed[200000];
int eds;

int
compareEdges (const void *v0, const void *v1)
{
  edge e0 = (edge) v0;
  edge e1 = (edge) v1;

  if (e0->x0 < e1->x0) return -1;
  if (e0->x0 > e1->x0) return 1;
  if (e0->y0 < e1->y0) return -1;
  if (e0->y0 > e1->y0) return 1;
  if (e0->x1 < e1->x1) return -1;
  if (e0->x1 > e1->x1) return 1;
  if (e0->y1 < e1->y1) return -1;
  if (e0->y1 > e1->y1) return 1;
  return 0;
}

sortEdges ()
{
  int i;
  edge e0;

  for (i = 0; i < rooms; i++)
    for (e0 = room0[i]; e0; e0 = e0->next)
      {
        if (e0->x0 < e0->x1)
          {
            ed[eds].x0 = e0->x0; ed[eds].y0 = e0->y0;
            ed[eds].x1 = e0->x1; ed[eds].y1 = e0->y1;
          }
        else if (e0->x0 > e0->x1)
          {
            ed[eds].x0 = e0->x1; ed[eds].y0 = e0->y1;
            ed[eds].x1 = e0->x0; ed[eds].y1 = e0->y0;
          }
        else if (e0->y0 < e0->y1)
          {
            ed[eds].x0 = e0->x0; ed[eds].y0 = e0->y0;
            ed[eds].x1 = e0->x1; ed[eds].y1 = e0->y1;
          }
        else
          {
            ed[eds].x0 = e0->x1; ed[eds].y0 = e0->y1;
            ed[eds].x1 = e0->x0; ed[eds].y1 = e0->y0;
          }
        ed[eds++].room = i;
      }

  qsort (ed, eds, sizeof (struct edgeStruct), compareEdges);
}

int graph[1000][1000];

buildGraph ()
{
  int i = 0;

  sortEdges();

  while (i < eds)
    if (
      i < eds - 1
      && compareEdges ((void *) (ed + i), (void *) (ed + i + 1)) == 0
    )
      {
        graph[ed[i].room + 1][ed[i+1].room + 1] = 1;
        graph[ed[i+1].room + 1][ed[i].room + 1] = 1;
        i += 2;
      }
    else
      {
        graph[ed[i].room + 1][0] = 1;
        graph[0][ed[i].room + 1] = 1;
        i++;
      }

  rooms++;
}

int seen[1000];
int depth[1000];
int queue[1000];
int head, tail;

int
searchGraph (double tx, double ty)
{
  int sr = whichRoom (tx, ty) + 1;

  seen[sr] = 1;
  queue[tail] = sr;
  tail = 1;

  while (head != tail)
    {
      int i, ri = queue[head];
      head = (head + 1)%1000;

      if (graph[0][ri])
        return depth[ri] + 1;
      for (i = 1; i < rooms; i++)
        if (seen[i] == 0 && graph[i][ri])
          {
            seen[i] = 1;
            depth[i] = depth[ri] + 1;
            queue[tail] = i;
            tail = (tail + 1)%1000;
          }
    }
  printf ("No way out?!\n");
  exit (0);
}

main ()
{
  int i, n, lx0, ly0, lx1, ly1;
  double tx, ty;

  initialRoom ();

  scanf ("%d", &n);
  for (i = 0; i < n; i++)
    {
      scanf ("%d %d %d %d", &lx0, &ly0, &lx1, &ly1);
      applyLine (lx0, ly0, lx1, ly1);
    }
  buildGraph ();
  scanf ("%lf %lf", &tx, &ty);
  printf ("Number of doors = %d\n", searchGraph ((double) tx, (double) ty));
}

