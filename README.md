# ldap-passwords
Explore LDAP passwords

<p>
Self contained C code to pull apart the salted passwords {SSHA} and {SMD5}
created by slappasswd(8) and unsalted versions {SSH}, {MD5}
</p>
<p>
See <em>doc/</em>  for very brief explanation.
</p>
The SHA1 and MD5 routines are from:
<pre>
Steve Reid &lt;steve@edmweb.com&gt; <em>100% Public Domain</em> sha1.h sha1.c
L Peter Deutsch &lt;ghost@aladdin.com&gt; <em>Fair dealing</em> md5.h md5.c
</pre>
