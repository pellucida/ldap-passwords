/*
// @(#) ldap_sha1.c - construct ldap SSHA password
*/
# include	<stdio.h>
# include	<string.h>
# include	<unistd.h>

# include	"cvt.h"


enum	{
	SHA1BYTES	= 20,
	SEEDBYTES	= 4,
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
		size_t	hlen	= 0;
		char*	h	= argv[i];
		if (strncmp (h, "{SSHA}", 6)==0) {
			h	= &h[6];
		}
		hlen	= strlen (h);
		
		if (hlen == ((SHA1BYTES + SEEDBYTES)/3)*4) {
			byte_t	bin[hlen];
			int	blen	= cvt_base64bin (bin, sizeof(bin), h, hlen, B64_STD);
			if (!seedonly) {
				printf ("SHA-PWDHASH:  ");
				cvt_printhex (stdout, bin, blen-SEEDBYTES);
			}
			printf ("SHA-PWDSALT:  ");
			printf ("%02x%02x%02x%02x\n",
					bin [blen-SEEDBYTES],
					bin [blen-SEEDBYTES + 1],
					bin [blen-SEEDBYTES + 2],
					bin [blen-SEEDBYTES + 3]);
		}
	}
				
}
