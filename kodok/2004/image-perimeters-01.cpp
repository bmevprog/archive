#include <stdio.h>

   #define MAXDIM  20
   #define  IMAGE_NEIGHBORS  8
   #define  SIDES  4
int del[8][2] = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
   char  grid[MAXDIM][MAXDIM];
  char EMPTY_CHAR = '.';
 char FILL_CHAR = 'I';
 int rows, cols,rstart,cstart;

   int fill(int r, int c){
    // Fills for 8 neighbors and counts the number of neighbors that share
    // boundary sides rather than a vertex.
    // Assume r,c are row and column of a place to be filled (an 'X')
    int count = 0;
    grid[r][c] = FILL_CHAR;
//    int dir;
    for (int dir = 0; dir < IMAGE_NEIGHBORS; dir++) {
      int rn = r+del[dir][0], cn = c+del[dir][1];
      if (( rn < 0 || rn >= rows || cn < 0 || cn >= cols
             || grid[rn][cn] == EMPTY_CHAR ) ) {
        if (dir < SIDES)
          count++;
      }
      else if (grid[rn][cn] != FILL_CHAR)
          count += fill(rn, cn);
    }
    return count;
  }


  int main()
    {
      for (;;)
	{
	  scanf("%d %d %d %d\n",&rows,&cols,&rstart,&cstart);
	  if (!rows) break;
	   int r, c;
	   rstart--;cstart--;
	   char buf[cols+200];
	   //	   printf("%d %d\n",rows,cols);
	   for (r = 0; r < rows; r++) //grid with minimum 0 components, not 1
	     {
	       fgets(buf,cols+200,stdin);
	       //	       printf("[%s]\n",buf);
	       for (c = 0; c < cols; c++) grid[r][c] = buf[c];
	     }
	       if(grid[rstart][cstart] != 'X') printf("Bad start pt\n");
	       printf("%d\n",fill(rstart, cstart));
	}
    }
