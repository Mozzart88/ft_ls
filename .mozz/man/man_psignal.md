PSIGNAL(3) - Library Functions Manual

# NAME

**psignal**,
**strsignal**,
**sys\_siglist**,
**sys\_signame** - system signal messages

# LIBRARY

Standard C&#160;Library (libc, &#45;lc)

# SYNOPSIS

**#include &lt;signal.h>**

*void*  
**psignal**(*unsigned sig*, *const char \*s*);

*extern const char \* const sys\_siglist\[]*;  
*extern const char \* const sys\_signame\[]*;

**#include &lt;string.h>**

*char \*&zwnj;*  
**strsignal**(*int sig*);

# DESCRIPTION

The
**psignal**()
and
**strsignal**()
functions locate the descriptive message
string for a signal number.

The
**strsignal**()
function accepts a signal number argument
*sig*
and returns a pointer to the corresponding message string.

The
**psignal**()
function accepts a signal number argument
*sig*
and writes it to the standard error.
If the argument
*s*
is
non-`NULL`
and does not point to the null character,
*s*
is written to the standard error file descriptor
prior to the message string,
immediately followed by a colon and a space.
If the signal number is not recognized
(sigaction(2)),
the string
"Unknown signal"
is produced.

The message strings can be accessed directly
through the external array
*sys\_siglist*,
indexed by recognized signal numbers.
The external array
*sys\_signame*
is used similarly and
contains short, lower-case abbreviations for signals
which are useful for recognizing signal names
in user input.
The defined variable
`NSIG`
contains a count of the strings in
*sys\_siglist*
and
*sys\_signame*.

# RETURN VALUES

**strsignal**()
a pointer to the desired message or a NULL value indicating an error.  This
string is not to be freed by the caller.  Beginning with Mac OSX 10.7, this
string is unique to each thread.

# ERRORS

**strsignal**()
will fail and no additional memory will be allocated if
one of the following are true:

\[`ENOMEM`]

> There was insufficient memory to allocate storage space for the return value in the running thread.

# SEE ALSO

sigaction(2),
perror(3),
strerror(3)

# HISTORY

The
**psignal**()
function appeared in
4\.2BSD.

Mac OS X 10.12 - February 27, 1995
