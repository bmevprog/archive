#include <cstdio>
using namespace std;

int main()
{
  int N, sum = 0, t;
  scanf("%d",&N);
  for(int i=0;i<N;++i)
  {    
    scanf("%d",&t);
    sum = (sum + t) % 1000001;
  }
  printf("%d\n",sum);
  return 0;
}