#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char s[81];

int main()
{
  int N;
  scanf("%d",&N);
  for(int i=1;i<=N;++i)
  {    
    int tmp;
    scanf("%d%80s",&tmp,s);
    if(next_permutation(s,s+strlen(s)))
    {
      printf("%d %s\n",i,s);
    }
    else
    {
      printf("%d BIGGEST\n",i);
    }
  }
  return 0;
}