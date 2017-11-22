
# include	<string.h>
# include	<stdio.h>
# include	"md5.h"

enum	{ MD5BYTES	= 16, };
MD5 (unsigned char* hashout, unsigned char* src, size_t slen) {
	md5_state_t state;
	md5_byte_t digest[MD5BYTES];
	md5_init(&state);
	md5_append(&state, (const md5_byte_t *)src, slen);
	md5_finish(&state, digest);
	memcpy (hashout, digest, MD5BYTES);
	return	0;
}

# if	defined(TEST)
# include	"cvt.h"
main (int argc, char* argv[]) {
	char	buffer [BUFSIZ];
	MD5 (buffer, argv[1], strlen(argv[1]));
	cvt_printhex (stdout, buffer, MD5BYTES);
	
}
# endif

