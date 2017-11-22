/*
// @(#) ldap_sha1.c - construct ldap SSHA password
*/
# include	<stdio.h>
# include	<string.h>
# include	<unistd.h>

# include	"cvt.h"


enum	{
	MD5BYTES	= 16,
	SEEDBYTES	= 4,
};
enum	{
	MD5	= '5',
	SMD5	= 'V',
};
main (int argc, char* argv[]) {
	int	i	= 0;
	int	seedonly= 0;
	int	opt	= EOF;
	
	while ((opt = getopt (argc, argv, "s")) != EOF) {
		switch (opt) {
		case	's':
			++seedonly;
		break;
		}
	}
	for (i=optind; i < argc; ++i) {
		int	type	= SMD5;
		size_t	hlen	= 0;
		char*	h	= argv[i];
		if (strncmp (h, "{SMD5}", 6)==0) {
			h	= &h[6];
		}
		else if (strncmp (h, "{MD5}", 5)==0) {
			h	= &h[5];
			type	= MD5;
			seedonly	= 0;
		}
		hlen	= strlen (h);
		
		if (hlen > 0) {
			byte_t	bin[hlen];
			int	blen	= cvt_base64bin (bin, sizeof(bin), h, hlen, B64_STD);
			switch (type) {
			case	SMD5:
				if (!seedonly) {
					printf ("SMD5-PWDHASH:  ");
					cvt_printhex (stdout, bin, MD5BYTES+SEEDBYTES);
				}
			
				printf ("SMD5-PWDSALT:  ");
				printf ("%02x%02x%02x%02x\n",
					bin [MD5BYTES],
					bin [MD5BYTES+1],
					bin [MD5BYTES+2],
					bin [MD5BYTES+3]);
			break;
			case	MD5:
				printf ("MD5-PWDHASH:  ");
				cvt_printhex (stdout, bin, MD5BYTES);
			break;

			}
		}
	}			
}
