
INSTDIR	= ..
BINDIR	= $(INSTDIR)/bin
INSTALL	= /bin/install

CVT	= cvt_hex.o cvt_base64.o
OBJ	=  sha1.o MD5.o md5.o $(CVT)

CFLAGS	+= -g
LDFLAGS	+= -g

PROGS	= b64_decode ldap_sha1 ssha_info ssha_mkpass smd5_info smd5_mkpass
ALL: $(PROGS)

ldap_sha1:	$(OBJ)

b64_decode:	b64_decode.o $(CVT)

ssha_info:	ssha_info.o $(CVT)

smd5_info:	smd5_info.o $(CVT)

ssha_mkpass:	ssha_mkpass.o $(OBJ)

smd5_mkpass:	smd5_mkpass.o $(OBJ)


install:	
	mkdir -p $(BINDIR)
	$(INSTALL) --mode=0755  $(PROGS) $(BINDIR)

clean:
	rm -f *.o a.out $(PROGS)
