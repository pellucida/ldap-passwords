/*
// @(#) ldap_sha1.c - construct ldap SSHA password
*/
# include	<stdio.h>
# include	<string.h>
# include	<stdlib.h>
# include	<unistd.h>

# include	"cvt.h"


main (int argc, char* argv[]) {
	int	i	= 0;
	int	opt	= EOF;
	

	while ((opt = getopt (argc, argv, "h")) != EOF) {
		switch (opt) {
		case	'h':
			printf ("Usage: b64_decode b64string\n");
			exit (EXIT_SUCCESS);
		break;
		}
	}
	for (i=optind; i < argc; ++i) {
		char*	arg	= argv[i];
		int	len	= strlen (arg);
		cvt_printdecoded64 (stdout, arg, len);
	}
	exit (EXIT_SUCCESS);
}
