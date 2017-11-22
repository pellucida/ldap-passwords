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
	byte_t	buffer [BUFSIZ];
	byte_t	seed [BUFSIZ];
	int	i	= 0;
	int	r_flag	= 0;	/* raw */
	int	s_flag	= 0;
	int	x_flag	= 0;
	int	H_flag	= 0;
	int	B_flag	= 0;
	int	b_flag	= 0;
	int	S_flag	= 0;
	int	D_flag	= 0;
	int	flagset	= 0;
	char*	sp	= 0;

	int	opt	= EOF;
	

	while ((opt = getopt (argc, argv, "Drx:s:bHBS")) != EOF) {
		switch (opt) {
		case	'D':
			D_flag++;
		break;
		case	'r':
			r_flag++;
		break;
		case	's':
			sp	= optarg;
			s_flag++;
		break;
		case	'x':
			x_flag++;
			sp	= optarg;
		break;
		case	'b':
			b_flag++;
			++flagset;
		break;
		case	'B':
			B_flag++;
			++flagset;
		break;
		case	'S':
			S_flag++;
			++flagset;
		break;
		case	'H':
			H_flag++;
			++flagset;
		break;
		}
	}
	for (i=optind; i < argc; ++i) {
		int	slen	= 0;
		char*	arg	= argv[i];
		int	len	= strlen (arg);
		size_t	buflen	= SHA1BYTES;
		char	key [BUFSIZ];
		strcpy (key, arg);
		if (x_flag) {
			int	j	= 0;
			int	xlen	= strlen(sp);
			for(j=0; j < xlen; j+=2) {
				byte_t	x1	= sp[j];
				byte_t	x2	= sp[j+1];
				seed [slen++]	= (cvt_hex2bin(x1)<<HEXBITS)|cvt_hex2bin(x2);
			}
			seed [slen]	= '\0';
			memcpy (&key[len], seed, slen);
			len	+= slen;
		}
			
		if (s_flag) {
			slen	= strlen (sp);
			strcpy (seed, sp);
			memcpy (&key[len], seed, slen);
			len	+= slen;
		}
		if (D_flag) {
			char*	p	= arg;
			size_t	plen	= 0;
			if (strncmp (arg, "{SSHA}", 6)==0) {
				p	= &arg[6];
			}
			plen	= strlen (p);
			if (plen == ((SHA1BYTES + SEEDBYTES)/3)*4) {
				byte_t	bin[plen];
				int	blen	= cvt_base64bin (bin, sizeof(bin), p, plen, B64_STD);
				printf ("SHA-PWD:   ");
				cvt_printpasswd64 (stdout, bin, blen-SEEDBYTES);
				printf ("SHA-SALT:  ");
				cvt_printpasswd64 (stdout, &bin[blen-SEEDBYTES], SEEDBYTES);
				printf ("SSHA-Key:  ");
				cvt_printbase64 (stdout, bin, blen-SEEDBYTES);
				printf ("SSHA-Seed: %02x%02x%02x%02x\n",
					bin [blen-SEEDBYTES],
					bin [blen-SEEDBYTES + 1],
					bin [blen-SEEDBYTES + 2],
					bin [blen-SEEDBYTES + 3]);
			}
		}
				
		SHA1 (buffer, key, len);
		if (r_flag) {
			write (STDOUT_FILENO, buffer, buflen);
			if (s_flag || x_flag)
				write (STDOUT_FILENO, seed, slen);
		}
		else	{
			if (b_flag) {
				if (flagset > 1) 
					fprintf (stdout, "Base64:      ");
				cvt_printbase64 (stdout, key, len);
			}
			if (H_flag) {
				if (flagset > 1) 
					fprintf (stdout, "SHA1-SUM:    ");
				cvt_printhex (stdout, buffer, buflen);
			}
			if (B_flag) {
				if (flagset > 1) 
					fprintf (stdout, "SHA1-BASE64: ");
				cvt_printbase64 (stdout, buffer, buflen);
			}
			if (S_flag) {
				if (flagset > 1) 
					fprintf (stdout, "LDAP_SHA1:   ");
				if (s_flag || x_flag) {
					fprintf (stdout, "{SSHA}");
					memcpy (&buffer[buflen], seed, slen);
					buflen	+= slen;
				}
				else	{
					fprintf (stdout, "{SHA}");
				}
				cvt_printbase64 (stdout, buffer, buflen);
			}
		}
	}
}
