GETPWENT(3) - Library Functions Manual

# NAME

**getpwent**,
**getpwnam**,
**getpwnam\_r**,
**getpwuid**,
**getpwuid\_r**,
**getpwuuid**,
**getpwuuid\_r**,
**setpassent**,
**setpwent**,
**endpwent** - password database operations

# LIBRARY

Standard C&#160;Library (libc, &#45;lc)

# SYNOPSIS

**#include &lt;sys/types.h>**  
**#include &lt;pwd.h>**  
**#include &lt;uuid/uuid.h>**

*struct passwd \*&zwnj;*  
**getpwent**(*void*);

*struct passwd \*&zwnj;*  
**getpwnam**(*const char \*login*);

*int*  
**getpwnam\_r**(*const char \*name*, *struct passwd \*pwd*, *char \*buffer*, *size\_t bufsize*, *struct passwd \*\*result*);

*struct passwd \*&zwnj;*  
**getpwuid**(*uid\_t uid*);

*int*  
**getpwuid\_r**(*uid\_t uid*, *struct passwd \*pwd*, *char \*buffer*, *size\_t bufsize*, *struct passwd \*\*result*);

*struct passwd \*&zwnj;*  
**getpwuuid**(*uuid\_t uuid*);

*int*  
**getpwuuid\_r**(*uuid\_t uuid*, *struct passwd \*pwd*, *char \*buffer*, *size\_t bufsize*, *struct passwd \*\*result*);

*int*  
**setpassent**(*int stayopen*);

*void*  
**setpwent**(*void*);

*void*  
**endpwent**(*void*);

# DESCRIPTION

These functions
obtain information from
opendirectoryd(8),
including records in
*/etc/master.passwd*
which is described
in
master.passwd(5).
Each entry in the database is defined by the structure
*passwd*
found in the include
file
&lt;*pwd.h*>:

	struct passwd {
		char	*pw_name;	/* user name */
		char	*pw_passwd;	/* encrypted password */
		uid_t	pw_uid;		/* user uid */
		gid_t	pw_gid;		/* user gid */
		time_t	pw_change;	/* password change time */
		char	*pw_class;	/* user access class */
		char	*pw_gecos;	/* Honeywell login info */
		char	*pw_dir;	/* home directory */
		char	*pw_shell;	/* default shell */
		time_t	pw_expire;	/* account expiration */
		int	pw_fields;	/* internal: fields filled in */
	};

The functions
**getpwnam**(),
**getpwuid**(),
and
**getpwuuid**()
search the password database for the given login name, user uid, or user uuid
respectively, always returning the first one encountered.

Note that the password file
*/etc/master.passwd*
does not contain user UUIDs.
The UUID for a user may be found using
**mbr\_uid\_to\_uuid**().

On OS X, these routines are thread-safe and return a pointer to a
thread-specific data structure.  The contents of this data
structure are automatically released by subsequent calls to
any of these routines on the same thread, or when the thread exits.
These routines are therefore unsuitable for use in libraries or frameworks,
from where they may overwrite the per-thread data that the calling
application expects to find as a result of its own calls to these
routines. Library and framework code should use the alternative reentrant
variants detailed below.

The
**getpwent**()
function
searches all available directory services on it's first invocation.
It caches the returned entries in a list
and returns user account entries one at a time.

*NOTE*
that
**getpwent**()
may cause a very lengthy search for user account records by
**opendirectoryd**
and may result in a large number of user account records being cached
by the calling process.
Use of this function is not advised.

The functions
**getpwnam\_r**(),
**getpwuid\_r**(),
and
**getpwuuid\_r**()
are alternative versions of
**getpwnam**(),
**getpwuid**(),
and
**getpwuuid**()
respectively.
They store the results of their search in the caller-provided
*pwd*
structure, which additionally contains pointers to strings that are
stored in the caller-provided
*buffer*
of size
*bufsize*.
(The maximum required
*bufsize*
can be obtained by passing the \_SC\_GETPW\_R\_SIZE\_MAX constant to the
sysconf(3)
call. See example code below.) When these functions are successful, the
*pwd*
argument will be filled in, and a pointer to that argument will be
stored in the caller-provided
*result*.
If an entry is not found or an error occurs,
*result*
will be set to
`NULL`.

The
**setpassent**()
function causes
**getpwent**()
to \`\`rewind'' to the beginning of the list of entries cached by a previous
**getpwent**()
call.
The cache is not cleared.
The
*stayopen*
parameter value is unused on OS X.

The
**setpwent**()
and
**endpwent**()
functions clear the cached results from a previous
**getpwent**()
call.

These routines have been written to
'`shadow`'
the password of user records created on Mac OS X 10.3 or later,
by returning a structure whose password field points to the string
'`********`'.
Legacy crypt passwords are still returned for user records created on
earlier versions of Mac OS X whose
opendirectoryd(8)
attribute contains the value
'`;basic;`'.

Note that
opendirectoryd(8)
allows user records from some sources which may not include all the component
fields present in a passwd structure.
Only the name, uid, and gid of a user record are required.
Default values will be supplied as follows:

	pw_passwd = "*"
	pw_change = 0
	pw_class = ""
	pw_gecos = ""
	pw_dir = "/var/empty"
	pw_shell = "/usr/bin/false"
	pw_expire = 0

# RETURN VALUES

The functions
**getpwent**(),
**getpwnam**(),
**getpwuid**(),
and
**getpwuuid**()
return a valid pointer to a passwd structure on success
or
`NULL`
if the entry is not found or if an error occurs.
If an error does occur,
*errno*
will be set.
Note that programs must explicitly set
*errno*
to zero before calling any of these functions if they need to
distinguish between a non-existent entry and an error.
The functions
**getpwnam_r**(),
**getpwuid_r**(),
and
**getpwuuid_r**()
return 0 if no error occurred, or an error number to indicate failure.
It is not an error if a matching entry is not found.
(Thus, if
*result*
is
`NULL`
and the return value is 0, no matching entry exists.)

The
**setpassent**()
function returns 0 on failure and 1 on success.
The
**endpwent**()
and
**setpwent**()
functions
have no return value.

# EXAMPLES

To print the current user's home directory without depending on per-thread storage:

	#include <sys/types.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <pwd.h>
	
	int bufsize;
	
	if ((bufsize = sysconf(_SC_GETPW_R_SIZE_MAX)) == -1)
	    abort();
	
	char buffer[bufsize];
	struct passwd pwd, *result = NULL;
	if (getpwuid_r(getuid(), &pwd, buffer, bufsize, &result) != 0 || !result)
	    abort();
	
	printf("%s\n", pwd.pw_dir);

# FILES

The secure password database file

*/etc/master.passwd*

	The current password file

*/etc/passwd*

	A Version 7 format password file

# ERRORS

These routines may fail for any of the errors specified in
open(2),
dbopen(3),
socket(2),
and
connect(2),
in addition to the following:

[`ERANGE`]

	The buffer specified by the
	*buffer*
	and
	*bufsize*
	arguments was insufficiently sized to store the result.
	The caller should retry with a larger buffer.

# SEE ALSO

getlogin(2),
getgrent(3),
passwd(5),
mbr_uid_to_uuid(3,)
opendirectoryd(8),
yp(8)

# STANDARDS

The
**getpwent**(),
**getpwnam**(),
**getpwnam_r**(),
**getpwuid**(),
**getpwuid_r**(),
**setpwent**(),
and
**endpwent**()
functions conform to
ISO/IEC 9945-1:1996 ("POSIX.1").

# HISTORY

The
**getpwent**(),
**getpwnam**(),
**getpwuid**(),
**setpwent**(),
and
**endpwent**()
functions appeared in
Version7 AT&T UNIX.
The
**setpassent**()
function appeared in
4.3BSD-Reno.
The
**getpwnam_r**()
and
**getpwuid_r**()
functions appeared in
FreeBSD 5.1.
The functions
**getpwuuid**()
and
**getpwuuid_r**()
appeared in Mac OS X 10.8.

# BUGS

The functions
**getpwent**(),
**getpwnam**(),
**getpwuid**(),
and
**getpwuuid**(),
leave their results in an internal thread-specific memory and return
a pointer to that object.
Subsequent calls to
the same function
will modify the same object.

Mac OS X 10.12 - October 26, 2011
