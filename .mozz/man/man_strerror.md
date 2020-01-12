STRERROR(3) - Library Functions Manual

# NAME

**perror**,
**strerror**,
**strerror\_r**,
**sys\_errlist**,
**sys\_nerr** - system error messages

# LIBRARY

Standard C&#160;Library (libc, &#45;lc)

# SYNOPSIS

**#include &lt;stdio.h>**

*void*  
**perror**(*const char \*s*);

*extern const char \* const sys\_errlist\[]*;  
*extern const int sys\_nerr*;

**#include &lt;string.h>**

*char \*&zwnj;*  
**strerror**(*int errnum*);

*int*  
**strerror\_r**(*int errnum*,
*char \*strerrbuf*,
*size\_t buflen*);

# DESCRIPTION

The
**strerror**(),
**strerror\_r**(),
and
**perror**()
functions look up the error message string corresponding to an
error number.

The
**strerror**()
function accepts an error number argument
*errnum*
and returns a pointer to the corresponding
message string.

The
**strerror\_r**()
function renders the same result into
*strerrbuf*
for a maximum of
*buflen*
characters and returns 0 upon success.

The
**perror**()
function finds the error message corresponding to the current
value of the global variable
*errno*
(intro(2))
and writes it, followed by a newline, to the
standard error file descriptor.
If the argument
*s*
is
non-`NULL`
and does not point to the null character,
this string is prepended to the message
string and separated from it by
a colon and space
("`:`");
otherwise, only the error message string is printed.

If the error number is not recognized, these functions return an error message
string containing
"`Unknown error:`"
followed by the error number in decimal.
The
**strerror**()
and
**strerror\_r**()
functions return
`EINVAL`
as a warning.
Error numbers recognized by this implementation fall in
the range 0 &lt;=
*errnum*
&lt;
*sys\_nerr*.

If insufficient storage is provided in
*strerrbuf*
(as specified in
*buflen*)
to contain the error string,
**strerror\_r**()
returns
`ERANGE`
and
*strerrbuf*
will contain an error message that has been truncated and
`NUL`
terminated to fit the length specified by
*buflen*.

The message strings can be accessed directly using the external
array
*sys\_errlist*.
The external value
*sys\_nerr*
contains a count of the messages in
*sys\_errlist*.
The use of these variables is deprecated;
**strerror**()
or
**strerror\_r**()
should be used instead.

# SEE ALSO

intro(2),
psignal(3)

# STANDARDS

The
**perror**()
and
**strerror**()
functions conform to
ISO/IEC 9899:1999 (&#8220;ISO&#160;C99&#8221;).
The
**strerror\_r**()
function conforms to
IEEE Std 1003.1-2001 (&#8220;POSIX.1&#8221;).

# HISTORY

The
**strerror**()
and
**perror**()
functions first appeared in
4\.4BSD.
The
**strerror\_r**()
function was implemented in
FreeBSD 4.4
by
Wes Peters &lt;wes@FreeBSD.org&gt;.

# BUGS

For unknown error numbers, the
**strerror**()
function will return its result in a static buffer which
may be overwritten by subsequent calls.

The return type for
**strerror**()
is missing a type-qualifier; it should actually be
*const char \*&zwnj;*.

Programs that use the deprecated
*sys\_errlist*
variable often fail to compile because they declare it
inconsistently.

Mac OS X 10.12 - October 12, 2004
