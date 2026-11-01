#include <stdio.h>
#include <string.h>
#include <ctype.h>

void preorder(char **leaves, int levels)
{
  //  printf("[%d]\n",levels);
  int i;
    while (levels > 0 && !isalpha(leaves[levels-1][0]) ) levels--;  
    if (levels == 0) return; // no root
    levels--;  // now have max levels in subtrees under root
    char root = leaves[levels][0]; // last leaf is the root
    char *left[levels];  // leaves for left subtree
    char *right[levels]; // leaves for right subtree
    for (i = 0; i < levels; i++) { // for each String in leaves
      int past = 0; // past will be index of char in leaves[i] past root
      while (past < strlen(leaves[i]) && leaves[i][past] < root)
        past++;
      left[i]=new char[30];
      right[i]=new char[30];
      strcpy(left[i],leaves[i]); left[i][past]=0;
      strcpy(right[i],leaves[i]+past);
    }
    fputc(root,stdout);
    preorder(left, levels);
    preorder(right, levels);
    for (i=0;i<levels;i++) {delete [] left[i];delete [] right[i];}
  
}
         


int main()
{
    char *leaves[26];
    for (;;)
	{
	    char buf[100];
	    gets(buf);
	    int levels = 0;
	    while (buf[0] != '*' && buf[0]!= '$')
		{
		  //		  		  printf("{%s}\n",buf);
		  leaves[levels]=new char[30];
		    strcpy(leaves[levels],buf);
	    levels++;
		    
	    gets(buf);
		}
	    preorder(leaves,levels);
	    printf("\n");
	    if (buf[0]=='$') break;
	}
  }
    
          
