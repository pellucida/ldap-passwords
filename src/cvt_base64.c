
# include	<stddef.h>
# include	<stdio.h>
# include	<string.h>


# include	"cvt.h"

// Convert string to base64 - really dumb implementation.

// Unix Password hash encoding
static	const char	p64[]	= 
			 "./0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

// Standard Base64 encoding
static	const char	b64[]	= "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			  "abcdefghijklmnopqrstuvwxyz"
			  "0123456789+/";

static	byte_t	decode (byte_t ch, const char enc[64]) {
	char*	t	= strchr (enc, ch);
	if (t) {
		return (byte_t)(t - enc);
	}
	return	0;
}

//	Convert base64 (s) to binary (dst) using encoding (enc_type)

int	cvt_base64bin (byte_t* dst, size_t dlen, const char* s, size_t slen, int enc_type) {
	int	i	= 0;
	int	j	= 0;
	int	k	= slen;
	const char*	enc	= (enc_type == B64_PASSWD) ? p64 : b64;

	if (BYTBITS*dlen < slen*B64BITS) { // truncate input to fit output
		slen	= (dlen/B64BITS)*BYTBITS;
	}
	while (i != k && j < dlen) {
		unsigned long	w	= 0;
		int	l	= 0;
		int	ll	= 0;
		int	lend	= (4 < (slen-i))? 4 : (slen-i);
		byte_t	ch[4];
		while (l != lend) {
			byte_t	t	= s[i+l];
			if (t != '=') {
				ch[l]	= s [i+l];	
				++l;
			}
			else	{
				lend	= l;
				k	= i+l;
			}
		}
		w	= 0;
		for (ll=0; ll < l; ++ll) {
			byte_t	dc	= decode(ch[ll], enc);
			w	|= (dc << (B64BITS*(3-ll)));
		}
		dst[j++]        = (w>>(2*BYTBITS)) & BYTMASK;
                dst[j++]        = (w>>  (BYTBITS)) & BYTMASK;
                dst[j++]        = (w) & BYTMASK;
		i		+= l;
	}
	return	j;
}

//	Convert binary (s) to base64 (dst) using encoding (enc_type)

int	cvt_binbase64 (char* dst, size_t dlen, const byte_t* s, size_t len , int enc_type) {
	unsigned	ch1, ch2, ch3, ch4;
	int	i	= 0;
	int	j	= 0;
	const	char*	enc	= (enc_type == B64_PASSWD) ? p64 : b64;
	
	if (dlen*B64BITS < BYTBITS*len) {// truncate input to fit output
		len	= (dlen * B64BITS)/BYTBITS - 1;
	}

	 for (i=0; (i+2) < len; i+=3) {
		unsigned long	w	= s[i]<<(2*BYTBITS);

		if ((i+1) < len)
			w	= w | (s[i+1] << BYTBITS);
		if ((i+2) < len)
			w	= w | s[i+2];

		ch1	= enc[(w >> (3*B64BITS)) & B64MASK];
		ch2	= enc[(w >> (2*B64BITS)) & B64MASK];
		ch3	= enc[(w >> (  B64BITS)) & B64MASK];
		ch4	= enc[(w               ) & B64MASK];
		dst [j++]	= ch1;
		dst [j++]	= ch2;
		dst [j++]	= ch3;
		dst [j++]	= ch4;

	}
	if (i < len) { // Handle the padding  !!FIX!! for B64_PASSWD
		unsigned long	w	= s[i]<<(2*BYTBITS);
		ch3	= '=';
		if ((i+1) < len) {
			w	= w | (s[i+1] << BYTBITS);
			ch3	= enc[(w >> B64BITS) & B64MASK];
		}
		ch1	= enc[(w >> (3*B64BITS)) & B64MASK];
		ch2	= enc[(w >> (2*B64BITS)) & B64MASK];
		dst [j++]	= ch1;
		dst [j++]	= ch2;
		dst [j++]	= ch3;
		dst [j++]	= '=';
	}	
	dst [j++]	= '\0';
}
void	cvt_printbase64 (FILE* output, const byte_t* buffer, size_t len) {
	char	pbuf [2*len+1];
	cvt_binbase64 (pbuf, sizeof(pbuf), buffer, len, B64_STD);
	fprintf (output, "%s\n", pbuf);
}
void	cvt_printpasswd64 (FILE* output, const byte_t* buffer, size_t len) {
	char	pbuf [2*len+1];
	cvt_binbase64 (pbuf, sizeof(pbuf), buffer, len, B64_PASSWD);
	fprintf (output, "%s\n", pbuf);
}
void	cvt_printdecoded64 (FILE* output, const byte_t* buffer, size_t len) {
	char	pbuf [len+1];
	cvt_base64bin (pbuf, sizeof(pbuf), buffer, len, B64_STD);
	fprintf (output, "%s\n", pbuf);
}
# if defined(TEST)
main(int argc, char* argv[]) {
	char	buf[64];
	cvt_base64bin (buf,64, argv[1], strlen(argv[1]), B64_STD);
	printf ("%s\n", buf);
}
# endif
