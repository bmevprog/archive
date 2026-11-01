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
 
inline int fast_getdigits(int* digits)
{
	int c;
	while( (c=fast_getc()) != EOF && !(c>='0' && c<='9') )
		;
 
	if( c == EOF )
		return -1;
 	
	int len = 0;
	digits[len++] = c - '0';
	while( (c=fast_getc()) != EOF && (c>='0' && c<='9') )
		digits[len++] = (c-'0');
 
	return len;
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

inline int parse(int* digits, int len)
{
	int n=0;
	for( int i=0; i<len; ++i )
	{
		n = n*10 + digits[i];
	}
	return n;
}

inline int rev_number(int n, int len)
{
	int nrev=0;
	for( int i=0; i<len; ++i )
	{
		nrev = nrev*10 + n%10;
		n /= 10;
	}
	return nrev;
}

int limits[] = {1,10,100,1000,10000};

int main()
{
	int digits[10];
	int len;

	while((len=fast_getdigits(digits)) >= 2)
	{
		int delta;

		// A tényleges feladatmegoldás ennyi, a többi csak a gyors I/O miatt kell.
		{
			int halflen = len/2;
			int odd = len % 2;
			
			int upperHalf = parse(digits,halflen);
			int lowerHalf = parse(digits + halflen + odd,halflen);

			int upperHalfRev = rev_number(upperHalf, halflen);
			if( lowerHalf <= upperHalfRev )
			{
				delta = upperHalfRev - lowerHalf;
			}
			else if( odd && digits[halflen] < 9 )
			{
				delta = limits[halflen] - (lowerHalf - upperHalfRev); // - rev_number(upperHalf
			}
			else
			{
				delta = limits[halflen] - (lowerHalf - rev_number(upperHalf+1, halflen));
			}
		}

		fast_putint(delta);
		fast_putc('\n');
	}

	flush();

	return 0;
}