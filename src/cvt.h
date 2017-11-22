
# if	!defined( CVT_H)
# define	CVT_H
# include	<stddef.h>
# include	<stdio.h>

enum	{
	HEXBITS	= 4,
	HEXMASK	= ~(~0u << HEXBITS),
	B64BITS	= 6,
	B64MASK	= ~(~0u << B64BITS),
	BYTBITS	= 8,
	BYTMASK	= ~(~0u << BYTBITS),
};
enum b64encoding	{
	B64_PASSWD	= 'P',
	B64_STD		= 'S',
};
typedef	unsigned char	byte_t;

unsigned int	cvt_hex2bin (byte_t ch);
size_t	cvt_hexbin (byte_t* dst, size_t dlen, const char* s, size_t len);
int	cvt_binhex (char* dst, size_t dlen, const byte_t* s, size_t len);
void	cvt_printhex (FILE* output, const byte_t buffer[], size_t len);

int	cvt_base64bin (byte_t* dst, size_t dlen, const char* s, size_t slen, int enc_type);
int	cvt_binbase64 (char* dst, size_t dlen, const byte_t* s, size_t len , int enc_type);
void	cvt_printbase64 (FILE* output, const byte_t* buffer, size_t len);
void	cvt_printdecoded64 (FILE* output, const byte_t* buffer, size_t len);
void	cvt_printpasswd64 (FILE* output, const byte_t* buffer, size_t len);

# endif
