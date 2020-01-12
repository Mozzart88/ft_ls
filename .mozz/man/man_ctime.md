CTIME(3) - Library Functions Manual

# NAME

**asctime**,
**asctime\_r**,
**ctime**,
**ctime\_r**,
**difftime**,
**gmtime**,
**gmtime\_r**,
**localtime**,
**localtime\_r**,
**mktime**,
**timegm** - transform binary date and time values

# LIBRARY

Standard C&#160;Library (libc, &#45;lc)

# SYNOPSIS

**#include &lt;time.h>**

*extern char \*tzname\[2]*;

*char \*&zwnj;*  
**asctime**(*const struct tm \*timeptr*);

*char \*&zwnj;*  
**asctime\_r**(*const struct tm \*restrict timeptr*, *char \*restrict buf*);

*char \*&zwnj;*  
**ctime**(*const time\_t \*clock*);

*char \*&zwnj;*  
**ctime\_r**(*const time\_t \*clock*, *char \*buf*);

*double*  
**difftime**(*time\_t time1*, *time\_t time0*);

*struct tm \*&zwnj;*  
**gmtime**(*const time\_t \*clock*);

*struct tm \*&zwnj;*  
**gmtime\_r**(*const time\_t \*clock*, *struct tm \*result*);

*struct tm \*&zwnj;*  
**localtime**(*const time\_t \*clock*);

*struct tm \*&zwnj;*  
**localtime\_r**(*const time\_t \*clock*, *struct tm \*result*);

*time\_t*  
**mktime**(*struct tm \*timeptr*);

*time\_t*  
**timegm**(*struct tm \*timeptr*);

# DESCRIPTION

The functions
**ctime**(),
**gmtime**(),
and
**localtime**()
all take as an argument a time value representing the time in seconds since
the Epoch (00:00:00
`UTC`,
January 1, 1970; see
time(3)).
When encountering an error, these functions return
`NULL`
and set
`errno`
to an appropriate value.

The function
**localtime**()
converts the time value pointed at by
*clock*.
It returns a pointer to a
"*struct*, *tm*"
(described below), which contains
the broken-out time information for the value after adjusting for the current
time zone (and any other factors such as Daylight Saving Time).
Time zone adjustments are performed as specified by the
`TZ`
environment variable (see
tzset(3)).
The function
**localtime**()
uses
tzset(3)
to initialize time conversion information, if
tzset(3)
has not already been called by the process.

After filling in the tm structure,
**localtime**()
sets the
*tm\_isdst*'th
element of
*tzname*
to a pointer to an
`ASCII`
string containing the time zone abbreviation to be
used with
**localtime**()'s
return value.

The function
**gmtime**()
also converts the time value, but makes no time zone adjustment.
It returns a pointer to a tm structure (described below).

The
**ctime**()
function
adjusts the time value for the current time zone, in the same manner as
**localtime**().
It returns a pointer to a 26-character string of the form:

	Thu Nov 24 18:22:48 1986\n\0

All of the fields have constant width.

The
**ctime\_r**()
function
provides the same functionality as
**ctime**(),
except that the caller must provide the output buffer
*buf*
(which must be at least 26 characters long) to store the result.
The
**localtime\_r**()
and
**gmtime\_r**()
functions
provide the same functionality as
**localtime**()
and
**gmtime**(),
respectively, except the caller must provide the output buffer
*result*.

The
**asctime**()
function
converts the broken-out time in the structure
*tm*
(pointed at by
*\*timeptr*)
to the form
shown in the example above.

The
**asctime\_r**()
function
provides the same functionality as
**asctime**(),
except that the caller provides the output buffer
*buf*
(which must be at least 26 characters long) to store the result.

The functions
**mktime**()
and
**timegm**()
convert the broken-out time
(in the structure pointed to by
*\*timeptr*)
into a time value with the same encoding as that of the
values returned by the
time(3)
function (that is, seconds from the Epoch,
`UTC`).
The
**mktime**()
function
interprets the input structure according to the current timezone setting
(see
tzset(3)).
The
**timegm**()
function interprets the input structure
as representing Universal Coordinated Time
(`UTC`).

The original values of the
*tm\_wday*
and
*tm\_yday*
components of the structure are ignored. The original values of the
other components are not restricted to their normal ranges and will be
normalized, if need be.
For example,
October 40 is changed into November 9,
a
*tm\_hour*
of &#45;1 means 1 hour before midnight,
*tm\_mday*
of 0 means the day preceding the current month, and
*tm\_mon*
of &#45;2 means 2 months before January of
*tm\_year*.
(A positive or zero value for
*tm\_isdst*
causes
**mktime**()
to presume initially that summer time (for example, Daylight Saving Time)
is or is not (respectively) in effect for the specified time.
A negative value for
*tm\_isdst*
causes the
**mktime**()
function to attempt to divine whether summer time is in effect for the
specified time.
The
*tm\_isdst*
and
*tm\_gmtoff*
members are forced to zero by
**timegm**().)

On successful completion, the values of the
*tm\_wday*
and
*tm\_yday*
components of the structure are set appropriately, and the other components
are set to represent the specified calendar time, but with their values
forced to their normal ranges; the final value of
*tm\_mday*
is not set until
*tm\_mon*
and
*tm\_year*
are determined.
The
**mktime**()
function
returns the specified calendar time; if the calendar time cannot be
represented, it returns &#45;1;

The
**difftime**()
function
returns the difference between two calendar times,
(*time1*
\-
*time0*),
expressed in seconds.

External declarations, as well as the tm structure definition,
are contained in the
&lt;*time.h*>
include file.
The tm structure includes at least the following fields:

	int tm_sec;	/* seconds (0 - 60) */
	int tm_min;	/* minutes (0 - 59) */
	int tm_hour;	/* hours (0 - 23) */
	int tm_mday;	/* day of month (1 - 31) */
	int tm_mon;	/* month of year (0 - 11) */
	int tm_year;	/* year - 1900 */
	int tm_wday;	/* day of week (Sunday = 0) */
	int tm_yday;	/* day of year (0 - 365) */
	int tm_isdst;	/* is summer time in effect? */
	char *tm_zone;	/* abbreviation of timezone name */
	long tm_gmtoff;	/* offset from UTC in seconds */

The
field
*tm\_isdst*
is non-zero if summer (i.e., Daylight Saving) time is in effect.

The field
*tm\_gmtoff*
is the offset (in seconds) of the time represented from
`UTC`,
with positive
values indicating locations east of the Prime Meridian.

# SEE ALSO

date(1),
gettimeofday(2),
getenv(3),
time(3),
tzset(3),
tzfile(5)

# STANDARDS

The
**asctime**(),
**ctime**(),
**difftime**(),
**gmtime**(),
**localtime**(),
and
**mktime**()
functions conform to
ISO/IEC 9899:1990 (&#8220;ISO&#160;C90&#8221;),
and conform to
ISO/IEC 9945-1:1996 (&#8220;POSIX.1&#8221;)
provided the selected local timezone does not contain a leap-second table
(see
zic(8)).

The
**asctime\_r**(),
**ctime\_r**(),
**gmtime\_r**(),
and
**localtime\_r**()
functions are expected to conform to
ISO/IEC 9945-1:1996 (&#8220;POSIX.1&#8221;)
(again provided the selected local timezone does not contain a leap-second
table).

The
**timegm**()
function is not specified by any standard; its function cannot be
completely emulated using the standard functions described above.

# HISTORY

This manual page is derived from
the time package contributed to Berkeley by
Arthur Olson
and which appeared in
4\.3BSD.

# BUGS

Except for
**difftime**(),
**mktime**(),
and the
**\_r**()
variants of the other functions,
these functions leaves their result in an internal static object and return
a pointer to that object.
Subsequent calls to these
function will modify the same object.

The C Standard provides no mechanism for a program to modify its current
local timezone setting, and the
`POSIX`-standard
method is not reentrant.
(However, thread-safe implementations are provided
in the
`POSIX`
threaded environment.)

The
*tm\_zone*
field of a returned
*tm*
structure points to a static array of characters,
which will also be overwritten by any subsequent calls (as well as by
subsequent calls to
tzset(3)
and
tzsetwall(3)).

Use of the external variable
*tzname*
is discouraged; the
*tm\_zone*
entry in the tm structure is preferred.

Mac OS X 10.12 - January 2, 1999
