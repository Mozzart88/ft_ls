READLINK(2) - System Calls Manual

# NAME

**readlink**,
**readlinkat** - read value of a symbolic link

# SYNOPSIS

**#include &lt;unistd.h&gt;**

*ssize\_t*  
**readlink**(*const char \*restrict path*,
*char \*restrict buf*,
*size\_t bufsize*);

*ssize\_t*  
**readlinkat**(*int fd*, *const char \*restrict path*, *char \*restrict buf*, *size\_t bufsize*);

# DESCRIPTION

**readlink**()
places the contents of the symbolic link
*path*
in the buffer
*buf*,
which has size
*bufsize*.
**Readlink**
does not append a
`NUL`
character to
*buf*.

The
**readlinkat**()
system call is equivalent to
**readlink**()
except in the case where
*path*
specifies a relative path.
In this case the symbolic link whose content is read relative to the
directory associated with the file descriptor
*fd*
instead of the current working directory.
If
**readlinkat**()
is passed the special value
`AT_FDCWD`
in the
*fd*
parameter, the current working directory is used and the behavior is
identical to a call to

# RETURN VALUES

The call returns the count of characters placed in the buffer
if it succeeds, or a -1 if an error occurs, placing the error
code in the global variable
*errno*.

# ERRORS

**readlink**()
will fail if:

\[`EACCES`]

> Search permission is denied for a component of the path prefix.

\[`EFAULT`]

> *Buf*
> extends outside the process's allocated address space.

\[`EINVAL`]

> The named file is not a symbolic link.

\[`EIO`]

> An I/O error occurred while reading from the file system.

\[`ELOOP`]

> Too many symbolic links are encountered in translating the pathname.
> This is taken to be indicative of a looping symbolic link.

\[`ENAMETOOLONG`]

> A component of a pathname exceeded
> `{NAME_MAX}`
> characters, or an entire path name
> (possibly expanded by a symbolic link) exceeded
> `{PATH_MAX}`
> characters.

\[`ENOENT`]

> The named file does not exist.

\[`ENOTDIR`]

> A component of the path prefix is not a directory.

In addition to the errors returned by the
**readlink**(),
the
**readlinkat**()
may fail if:

\[`EBADF`]

> The
> *path*
> argument does not specify an absolute path and the
> *fd*
> argument is neither
> `AT_FDCWD`
> nor a valid file descriptor open for searching.

\[`ENOTDIR`]

> The
> *path*
> argument is not an absolute path and
> *fd*
> is neither
> `AT_FDCWD`
> nor a file descriptor associated with a directory.

# LEGACY SYNOPSIS

**#include &lt;unistd.h&gt;**

*int*  
**readlink**(*const char \*path*,
*char \*buf*,
*int bufsize*)
;

The function type and the type of
*bufsize*
have changed.

# SEE ALSO

lstat(2),
stat(2),
symlink(2),
compat(5),
symlink(7)

# STANDARDS

The
**readlinkat**()
system call is expected to conform to POSIX.1-2008 .

# HISTORY

The
**readlink**()
function call appeared in
4\.2BSD.
The
**readlinkat**()
system call appeared in OS X 10.10

BSD 4.2 - June 4, 1993
