TIME(3) - Library Functions Manual

# NAME

**time** - get time of day

# LIBRARY

Standard C&#160;Library (libc, &#45;lc)

# SYNOPSIS

**#include &lt;time.h>**

*time\_t*  
**time**(*time\_t \*tloc*);

# DESCRIPTION

The
**time**()
function
returns the value of time in seconds since 0 hours, 0 minutes,
0 seconds, January 1, 1970, Coordinated Universal Time,
without including leap seconds.
If an error occurs,
**time**()
returns the value
(*time\_t*)&#45;1.

The return value is also stored in
\*&zwnj;*tloc*,
provided that
*tloc*
is non-null.

# ERRORS

The
**time**()
function may fail for any of the reasons described in
gettimeofday(2).

# SEE ALSO

gettimeofday(2),
ctime(3)

# STANDARDS

The
**time**
function conforms to
IEEE Std 1003.1-2001 (&#8220;POSIX.1&#8221;).

# HISTORY

A
**time**()
function appeared in
Version&#160;6 AT&T UNIX.

# BUGS

Neither
ISO/IEC 9899:1999 (&#8220;ISO&#160;C99&#8221;)
nor
IEEE Std 1003.1-2001 (&#8220;POSIX.1&#8221;)
requires
**time**()
to set
*errno*
on failure; thus, it is impossible for an application to distinguish
the valid time value &#45;1 (representing the last UTC second of 1969)
from the error return value.

Systems conforming to earlier versions of the C and
`POSIX`
standards (including older versions of
FreeBSD)
did not set
\*&zwnj;*tloc*
in the error case.

Mac OS X 10.12 - July 18, 2003
