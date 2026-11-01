#include <cstdio>
#include <algorithm>
using namespace std;

#define	BUFFER_SIZE	64*1024
 
char buf[BUFFER_SIZE];
int buf_size = 0;
int buf_pos = 0;

char	outbuf[BUFFER_SIZE];
int		outbuf_pos = 0;
 
inline int fast_getc()
{
	if( buf_pos >= buf_size )
	{
		buf_pos = 0;
		buf_size = fread( buf, sizeof(char), BUFFER_SIZE, stdin );
 
		if( buf_size == 0 )
			return EOF;
	}
 
	return buf[buf_pos++];
}
 
inline int fast_getint()
{
	int c;
	while( (c=fast_getc()) < '0' )
		;
 
	int r = c - '0';
	while( (c=fast_getc()) >= '0' )
		r = r*10 + (c-'0');
 
	return r;
}

inline void flush()
{
	fwrite(outbuf, sizeof(char), outbuf_pos, stdout);
	outbuf_pos = 0;
}

inline void fast_putc( char c )
{
	outbuf[outbuf_pos++] = c;

	if(outbuf_pos == BUFFER_SIZE )
		flush();
}


inline void fast_putint( int n )
{
	char* p = outbuf + outbuf_pos;
	do
	{
		*p++ = (n%10) + '0';
	} while( (n/=10) );

	std::reverse( outbuf + outbuf_pos, p );

	outbuf_pos = p-outbuf;
}

inline void fast_puts( char* s )
{
	while( *s != 0 )
		outbuf[outbuf_pos++] = *s++;
}

int A[1001], B[1001], C[2002];
bool T[1001];

int main()
{
	int N, M;

	for(;;)
	{
		N = fast_getint();
		M = fast_getint();

		if(N == 0 && M == 0)
			break;

		for( int i=1; i<=N; ++i ) A[i] = fast_getint();
		for( int i=1; i<=M; ++i ) B[i] = fast_getint();
		for( int i=1; i<=N+M; ++i ) C[i] = fast_getint();
		
		// Ezen itt még lehetne javítani azért komplexitásban valószínûleg, de így se lassú.
		T[0] = true;
		for( int i=1; i<=M; ++i ) T[i] = (T[i-1] && (C[i] == B[i]));
		for( int j=1; j<=N; ++j )
		{
			T[0] = T[0] && (C[j] == A[j]);
			for( int i=1; i<=M; ++i )
			{
				T[i] = (T[i-1] && C[i+j] == B[i]) || (T[i] && C[i+j] == A[j]);
			}
		}

		if(T[M]) fast_puts("possible\n");
		else fast_puts("not possible\n");
	}

	flush();

	return 0;
}