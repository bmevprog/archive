#include <cstdio>
#include <algorithm>

using namespace std;

int V[200], X[200];

int main()
{
	int C;
	scanf("%d",&C);

	int tcc = 1;
	while(C--)
	{
		int N, K, B, T;
		scanf("%d%d%d%d",&N,&K,&B,&T);
		
		for( int i=0; i<N; ++i )
			scanf("%d",&X[i]);

		for( int i=0; i<N; ++i )		
			scanf("%d",&V[i]);
		
		int pt = 0;
		int sc = 0;
		int done = 0;
		for( int i=N-1; i>=0; --i )
		{
			if( X[i] + V[i]*T >= B )
			{
				sc += pt;
				if( ++done >= K )
					break;
			}
			else
			{
				++pt;
			}			
		}

		if( done >= K )
			printf("Case #%d: %d\n", tcc, sc );
		else
			printf("Case #%d: IMPOSSIBLE\n", tcc );

		++tcc;
	}
	return 0;
}