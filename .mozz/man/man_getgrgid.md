GETGRENT(3) - Library Functions Manual

# NAME

**getgrent**,
**getgrnam**,
**getgrnam\_r**,
**getgrgid**,
**getgrgid\_r**,
**getgruuid**,
**getgruuid\_r**,
**setgroupent**,
**setgrent**,
**endgrent** - group database operations

# LIBRARY

Standard system libraries.

# SYNOPSIS

**#include &lt;grp.h>**  
**#include &lt;uuid/uuid.h>**

*struct group \*&zwnj;*  
**getgrent**(*void*);

*struct group \*&zwnj;*  
**getgrnam**(*const char \*name*);

*int*  
**getgrnam\_r**(*const char \*name*, *struct group \*grp*, *char \*buffer*, *size\_t bufsize*, *struct group \*\*result*);

*struct group \*&zwnj;*  
**getgrgid**(*gid\_t gid*);

*int*  
**getgrgid\_r**(*gid\_t gid*, *struct group \*grp*, *char \*buffer*, *size\_t bufsize*, *struct group \*\*result*);

*int*  
**getgruuid**(*uuid\_t uuid*);

*int*  
**getgruuid\_r**(*uuid\_t uuid*, *struct group \*grp*, *char \*buffer*, *size\_t bufsize*, *struct group \*\*result*);

*int*  
**setgroupent**(*int stayopen*);

*void*  
**setgrent**(*void*);

*void*  
**endgrent**(*void*);

# DESCRIPTION

These functions obtain information from
opendirectoryd(8),
including records in
*/etc/group*
which is described
in
group(5).
Each line of the database is defined by the structure
*group*
found in the include
file
&lt;*grp.h*>:

	struct group {
		char	*gr_name;	/* group name */
		char	*gr_passwd;	/* group password */
		gid_t	gr_gid;		/* group id */
		char	**gr_mem;	/* group members */
	};

The functions
**getgrnam**(),
**getgrgid**(),
and
**getgruuid**()
search the group database for the given group name pointed to by
*name*,
the group id given by
*gid*,
or the UUID given by
*uuid*
respectively, returning the first one encountered.
Identical group
names, group gids, or uuids may result in undefined behavior.

Note that the groups file
*/etc/group*
does not contain group UUIDs.
The UUID for a group may be found using
**mbr\_gid\_to\_uuid**().

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
**getgrent**()
function
searches all available directory services on it's first invocation.
It caches the returned entries in a list
and returns group entries one at a time.

*NOTE*
that
**getgrent**()
may cause a very lengthy search for group records by
**opendirectoryd**
and may result in a large number of group records being cached
by the calling process.
Use of this function is not advised.

The functions
**getgrnam\_r**(),
**getgrgid\_r**(),
and
**getgruuid\_r**()
are alternative versions of
**getgrnam**(),
**getgrgid**(),
and
**getgruuid**()
respectively.
The caller must provide storage for the results of the search in
the
*grp*,
*buffer*,
*bufsize*,
and
*result*
arguments.
When these functions are successful, the
*grp*
argument will be filled-in, and a pointer to that argument will be
stored in
*result*.
If an entry is not found or an error occurs,
*result*
will be set to
`NULL`.

These functions will open the group file for reading, if necessary.

The
**setgroupent**()
function causes
**getgrent**()
to \`\`rewind'' to the beginning of the list of entries cached by a previous
**getgrent**()
call.
The cache is not cleared.
The
*stayopen*
parameter value is unused on OS X.

The
**setgrent**()
and
**endgrent**()
functions clear the cached results from a previous
**getgrent**()
call.

# RETURN VALUES

The functions
**getgrent**(),
**getgrnam**(),
and
**getgrgid**(),
return a pointer to a group structure on success or
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
**getgrnam\_r**(),
**getgrgid\_r**(),
and
**getgruuid\_r**()
return 0 if no error occurred, or an error number to indicate failure.
It is not an error if a matching entry is not found.
(Thus, if
*result*
is set to
`NULL`
and the return value is 0, no matching entry exists.)

**setgroupent**()
returns the value 1 if successful, otherwise the value
0 is returned.
The functions
**setgrent**(),
**endgrent**(),
and
**setgrfile**()
have no return value.

# FILES

*/etc/group*

> group database file

# COMPATIBILITY

The historic function
**setgrfile**(),
which allowed the specification of alternate group databases, has
been deprecated and is no longer available.

# SEE ALSO

getpwent(3),
group(5),
mbr\_gid\_to\_uuid(3,)
opendirectory(8),
yp(8)

# STANDARDS

The
**getgrent**(),
**getgrnam**(),
**getgrnam\_r**(),
**getgrgid**(),
**getgrgid\_r**()
and
**endgrent**()
functions conform to
ISO/IEC 9945-1:1996 (&#8220;POSIX.1&#8221;).
The
**setgrent**()
function differs from that standard in that its return type is
*int*
rather than
*void*.

# HISTORY

The functions
**endgrent**(),
**getgrent**(),
**getgrnam**(),
**getgrgid**(),
and
**setgrent**()
appeared in
Version&#160;7 AT&T UNIX.
The functions
**setgrfile**()
and
**setgroupent**()
appeared in
4\.3BSD-Reno.
The functions
**getgrnam\_r**()
and
**getgrgid\_r**()
appeared in
FreeBSD 5.1.
The functions
**getgruuid**()
and
**getgruuid\_r**()
appeared in Mac OS X 10.8.

# BUGS

The functions
**getgrent**(),
**getgrnam**(),
**getgrgid**(),
**getgruuid**(),
**setgroupent**()
and
**setgrent**()
leave their results in an internal thread-specific memory and return
a pointer to that object.
Subsequent calls to
the same function
will modify the same object.

Mac OS X 10.12 - October 26, 2011
