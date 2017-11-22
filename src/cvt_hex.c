/*
// 	@(#) printhex.c
*/
# include	<stddef.h>
# include	<stdio.h>

# include	"cvt.h"

static	const char	hex[]	= "0123456789abcdef";

unsigned int	cvt_hex2bin (byte_t ch) {
	if ('0' <= ch && ch <= '9') 
		return	ch - '0';
	else if ('a' <= ch && ch <= 'f')
		return	ch - 'a' + 10;
	else if ('A' <= ch && ch <= 'F')
		return	ch - 'A' + 10;
	else
		return 0;
}
size_t	cvt_hexbin (byte_t* dst, size_t dlen, const char* s, size_t len) {
	int	i	= 0;
	int	j	= 0;
	int	rem	= len % 2;
	if (2*dlen < len) {
		len	= dlen*2;
	}
	for (i=0; i < (len - rem); i+=2) {
		byte_t	b1	= s[i];
		byte_t	b2	= s[i+1];
		dst [j++]	= (cvt_hex2bin (b1)<<HEXBITS)| cvt_hex2bin(b2);
	}
	if (rem) {
		byte_t	b1	= s[i-1];
		dst [j++]	=  cvt_hex2bin(b1);
	}
	return	j;
}
int	cvt_binhex (char* dst, size_t dlen, const byte_t* s, size_t len) {
	int	i	= 0;
	int	j	= 0;
	if (dlen < 2*len) {
		len	= dlen/2-1;
	}
	for (i=0; i < len; ++i) {
		unsigned	ch	= s[i];
		dst [j++]	= hex[(ch>>HEXBITS)&HEXMASK];
		dst [j++]	= hex[ch&HEXMASK];
	}
	dst [j++]	= '\0';
}
void	cvt_printhex (FILE* output, const byte_t buffer[], size_t len) {
	char	pbuf [2*len+1];
	cvt_binhex (pbuf, sizeof(pbuf), buffer, len);
	fprintf (output, "%s\n", pbuf);
}
