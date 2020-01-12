IOCTL(2) - System Calls Manual

# NAME

**ioctl** - control device

# SYNOPSIS

**#include &lt;sys/ioctl.h&gt;**

*int*  
**ioctl**(*int fildes*,
*unsigned long request*,
*...*);

# DESCRIPTION

The
**ioctl**()
function manipulates the underlying device parameters of special files.
In particular, many operating
characteristics of character special files (e.g. terminals)
may be controlled with
**ioctl**()
requests.
The argument
*fildes*
must be an open file descriptor.

An  ioctl
*request*
has encoded in it whether the argument is an
"in"
parameter
or
"out"
parameter, and the size of the argument
*argp*
in bytes.
Macros and defines used in specifying an ioctl
*request*
are located in the file
&lt;*sys/ioctl.h*&gt;.

# RETURN VALUES

If an error has occurred, a value of -1 is returned and
*errno*
is set to indicate the error.

# ERRORS

**ioctl**()
will fail if:

\[`EBADF`]

> *fildes*
> is not a valid descriptor.

\[`EINVAL`]

> *Request*
> or
> *argp*
> is not valid.

\[`ENOTTY`]

> *fildes*
> is not associated with a character
> special device.

\[`ENOTTY`]

> The specified request does not apply to the kind
> of object that the descriptor
> *fildes*
> references.

# SEE ALSO

cdio(1),
chio(1),
mt(1),
execve(2),
fcntl(2),
intro(4),
tty(4)

# HISTORY

An
**ioctl**()
function call appeared in
Version&#160;7 AT&T UNIX.

BSD 4 - December 11, 1993
