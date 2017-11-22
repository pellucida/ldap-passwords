/*
// @(#) ssha_mkpass - construct ldap SSHA password
*/
# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>
# include	<unistd.h>

# include	"cvt.h"


enum	{
	SHA1BYTES	= 20,
	SEEDBYTES	= 4,
};

main (int argc, char* argv[]) {
	byte_t	buffer [BUFSIZ];
	size_t	buflen 	= SHA1BYTES;

	int	x_flag	= 0;	// Salt in HEX
	char*	xsalt	= 0;

	size_t	slen	= 0;	// Salt in BINARY
	byte_t	seed [BUFSIZ];	// Binary SALT

	int	k_flag	= 0;	// 'key' = pass + salt
	char	key [BUFSIZ];
	size_t	klen;
	char*	pass	= 0; 	// Cleartext password

	int	opt	= EOF;
	
	while ((opt = getopt (argc, argv, "x:k:")) != EOF) {
		switch (opt) {
		case	'x':
			x_flag++;
			xsalt	= optarg;
		break;
		case	'k':
			k_flag++;
			pass	= optarg;
		break;
		}
	}
	if (k_flag) {
		strcpy (key, pass);
		klen	= strlen (key);
	}
	else	{
		fprintf (stderr, 
		"Usage: ssha_mkpass [-x four-bytes-of-salt-as-8-hexits] -k 'clear-text-password'\n\nExample: ssha_mkpass -x 224f14d0 -k 'an example'\n");
		exit (EXIT_FAILURE);	
	}

	if (x_flag) {
		int	j	= 0;
		int	xlen	= strlen(xsalt);
		slen	= cvt_hexbin (seed, sizeof(seed), xsalt, xlen);
		
		seed [slen]	= '\0';
		memcpy (&key[klen], seed, slen);
		klen	+= slen;
	}

	SHA1 (buffer, key, klen);

	if (x_flag){
		memcpy (&buffer[buflen], seed, slen);
		buflen	+= slen;
		fprintf (stdout, "{SSHA}");
	}
	else	{
		fprintf (stdout, "{SHA}");
	}	
	cvt_printbase64 (stdout, buffer, buflen);
	exit (EXIT_SUCCESS);
}
