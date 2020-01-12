DIRECTORY(3) - Library Functions Manual

# NAME

**opendir**,
**fdopendir**,
**readdir**,
**readdir\_r**,
**telldir**,
**seekdir**,
**rewinddir**,
**closedir**,
**dirfd** - directory operations

# LIBRARY

Standard C&#160;Library (libc, &#45;lc)

# SYNOPSIS

**#include &lt;dirent.h>**

*DIR \*&zwnj;*  
**opendir**(*const char \*filename*);

*DIR \*&zwnj;*  
**fdopendir**(*int fd*);

*struct dirent \*&zwnj;*  
**readdir**(*DIR \*dirp*);

*int*  
**readdir\_r**(*DIR \*dirp*, *struct dirent \*entry*, *struct dirent \*\*result*);

*long*  
**telldir**(*DIR \*dirp*);

*void*  
**seekdir**(*DIR \*dirp*, *long loc*);

*void*  
**rewinddir**(*DIR \*dirp*);

*int*  
**closedir**(*DIR \*dirp*);

*int*  
**dirfd**(*DIR \*dirp*);

# DESCRIPTION

The
**opendir**()
function
opens the directory named by
*filename*,
associates a
*directory stream*
with it
and
returns a pointer to be used to identify the
*directory stream*
in subsequent operations.
The pointer
`NULL`
is returned if
*filename*
cannot be accessed, or if it cannot
malloc(3)
enough memory to hold the whole thing,
and sets the global variable
*errno*
to indicate the error.

The
**fdopendir**()
function is equivalent to the
**opendir**()
function except that the directory is specified by a file descriptor
*fd*
rather than by a name.

Upon successful return from
**fdopendir**(),
the file descriptor is under the control of the system,
and if any attempt is made to close the file descriptor,
or to modify the state of the associated description other than by means
of
**closedir**(),
**readdir**(),
**readdir\_r**(),
or
**rewinddir**(),
the behavior is undefined.
Upon calling
**closedir**()
the file descriptor is closed.
The
`FD_CLOEXEC`
flag is set on the file descriptor by a successful call to
**fdopendir**().

The
**readdir**()
function
returns a pointer to the next directory entry.
It returns
`NULL`
upon reaching the end of the directory or on error.
In the event of an error,
*errno*
may be set to any of the values documented for the
getdirentries(2)
system call.

The
**readdir\_r**()
function
provides the same functionality as
**readdir**(),
but the caller must provide a directory
*entry*
buffer to store the results in.
If the read succeeds,
*result*
is pointed at the
*entry*;
upon reaching the end of the directory
*result*
is set to
`NULL`.
The
**readdir\_r**()
function
returns 0 on success or an error number to indicate failure.

The
**telldir**()
function
returns the current location associated with the named
*directory stream*.
Values returned by
**telldir**()
are good only for the lifetime of the
`DIR`
pointer,
*dirp*,
from which they are derived.
If the directory is closed and then
reopened, prior values returned by
**telldir**()
will no longer be valid.

The
**seekdir**()
function
sets the position of the next
**readdir**()
operation on the
*directory stream*.
The new position reverts to the one associated with the
*directory stream*
when the
**telldir**()
operation was performed.

The
**rewinddir**()
function
resets the position of the named
*directory stream*
to the beginning of the directory.

The
**closedir**()
function
closes the named
*directory stream*
and frees the structure associated with the
*dirp*
pointer,
returning 0 on success.
On failure, &#45;1 is returned and the global variable
*errno*
is set to indicate the error.

The
**dirfd**()
function
returns the integer file descriptor associated with the named
*directory stream*,
see
open(2).
On failure, &#45;1 is returned and the global variable
*errno*
is set to indicate the error.

Sample code which searches a directory for entry \`\`name'' is:

	dirp = opendir(".");
	if (dirp == NULL)
		return (ERROR);
	len = strlen(name);
	while ((dp = readdir(dirp)) != NULL) {
		if (dp->d_namlen == len && strcmp(dp->d_name, name) == 0) {
			(void)closedir(dirp);
			return (FOUND);
		}
	}
	(void)closedir(dirp);
	return (NOT_FOUND);

# SEE ALSO

close(2),
lseek(2),
open(2),
read(2),
dir(5)

# HISTORY

The
**opendir**(),
**readdir**(),
**telldir**(),
**seekdir**(),
**rewinddir**(),
**closedir**(),
and
**dirfd**()
functions appeared in
4\.2BSD.
The
**fdopendir**()
function appeared in
FreeBSD 8.0.

Mac OS X 10.12 - April 16, 2008
