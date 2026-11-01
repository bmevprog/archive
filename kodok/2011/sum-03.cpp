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

inline void fast_flush()
{
	fwrite(outbuf, sizeof(char), outbuf_pos, stdout);
	outbuf_pos = 0;
}

inline void fast_putc( char c )
{
	outbuf[outbuf_pos++] = c;

	if(outbuf_pos == BUFFER_SIZE )
		fast_flush();
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

int main()
{
  int N, sum = 0, t;
  N = fast_getint();
  for(int i=0;i<N;++i)
  {    
    t = fast_getint();
    sum = (sum + t) % 1000001;
  }
  fast_putint(sum);
  fast_putc('\n');
  fast_flush();  
  return 0;
}