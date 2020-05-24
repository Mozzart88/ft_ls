/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:25:07 by tvanessa          #+#    #+#             */
/*   Updated: 2020/05/22 06:41:34 by mozzart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** INCLUDES
** @todo: Implement Debian/Ubuntu Support
*/
# include <libc.h>
# include "ft_get_next_line.h"
# include "ft_printf.h"

/*
** TYPEDEFS
*/
typedef unsigned short		t_us;
typedef unsigned int		t_uint;
typedef unsigned long long	t_ull;
/*
** STRUCTS
*/
typedef struct	s_list{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

/*
** PART #1
*/
/*
** computes the length of the string s.
** @params: {const char *s} Pointer to string.
** @return: {size_t} Numvber of characters.
*/
size_t			ft_strlen(const char *s);
/*
** Appends string src to the end of dst. It will append at most dstsize -
** strlen(dst) - 1 characters.
** It will then NUL-terminate, unless dstsize is 0 or the original dst
** string was longer than dstsize
** (in practice this should not happen as it means that either dstsize is
** incorrect or that dst is not a proper string). If the src and dst strings
** overlap, the behavior is undefined.
** @params: {const char *dst} Pointer to desgtination string.
** @params: {const char *src} Pointer to source string.
** @params: {size_t size} Number of characters to concatinate.
** @return: {char*} return the total length of the string they tried to create.
** For strlcpy() that means the length of src. For strlcat() that means the
** initial length of dst plus the length of src.
** If the return value is >= dstsize, the output string has been truncated.
** It is the caller's responsibility to handle this.
*/
size_t			ft_strlcat(char *dst, const char *src, size_t size);
/*
** Allocates sufficient memory for a copy of the string s1, does the copy,
** and returns a pointer to it.
** The pointer may subsequently be used as an argument to the function free(3).
** If insufficient memory is available, NULL is returne.
** @params: {const char *s} Pointer to source string.
** @return: {char*} a pointer to new string or NULL.
*/
char			*ft_strdup(const char *s1);
/*
** Copy the string src to dst (including the terminating `\0' character.)
** @params: {char *dst} Pointer to destination string.
** @params: {const char *src} Pointer to source string.
** @return: {char*} Return dst. The stpcpy() and stpncpy() functions return a
** pointer to the terminating `\0' character of dst. If stpncpy() does not
** terminate dst with a NUL character, it instead returns a pointer to dst[n]
** (which does not necessarily refer to a valid memory location.)
*/
char			*ft_strcpy(char *dst, const char *src);
/*
** copy at most len characters from src into dst. If src is less than len
** characters long, the remainder of dst is filled with `\0' characters.
** Otherwise, dst is not terminated. The source and destination strings should
** not overlap, as the behavior is undefined.
** @params: {char *dst} Pointer to destination string.
** @params: {const char *src} Pointer to source string.
** @params: {size_t len} Number of characters to copy.
** @return: {char*} Return dst. The stpcpy() and stpncpy() functions return a
** pointer to the terminating `\0' character of dst. If stpncpy() does not
** terminate dst with a NUL character, it instead returns a pointer to dst[n]
** (which does not necessarily refer to a valid memory location.)
*/
char			*ft_strncpy(char *dst, const char *src, size_t len);
/*
** Locates the first occurrence of the null-terminated string needle in the
** null-terminated string haystack.
** @params: {const char *haystack} Pointer to string where to search.
** @params: {const char *needle} Pointer to string that need to find.
** @return: {char*} If needle is an empty string, haystack is returned;
** if needle occurs nowhere in haystack, NULL is returned; otherwise a pointer
** to the first character of the first occurrence of needle is returned.
*/
char			*ft_strstr(const char *haystack, const char *needle);
/*
** Locates the first occurrence of the null-terminated string needle in the
** string haystack, where not more than len characters are searched. Characters
** that appear after a `\0' character are not searched. Since the strnstr()
** function is a FreeBSD specific API, it should only be used when portability
** is not a concern.
** @params: {const char *haystack} Pointer to string where to search.
** @params: {const char *needle} Pointer to string that need to find.
** @params: {size_t len} Number of characters in haystack to find.
** @return: {char*} If needle is an empty string, haystack is returned;
** if needle occurs nowhere in haystack, NULL is returned; otherwise a pointer
** to the first character of the first occurrence of needle is returned.
*/
char			*ft_strnstr(const char *haystack, const char *needle,
size_t len);
/*
** The strchr() function locates the first occurrence of c
** (converted to a char) in the string pointed to by s. The terminating null
** character is considered to be part of the string; therefore if c is `\0',
** the functions locate the terminating `\0'.
** @params: {const char *s} Pointer to string
** @params: {int c} Character to search to.
** @return: {char*} The functions strchr() and strrchr() return a pointer to
** the located character, or NULL if the character does not appear in the
** string.
*/
char			*ft_strchr(const char *s, int c);
/*
** Append a copy of the null-terminated string s2 to the end of the
** null-terminated string s1, then add a terminating `\0'. The string s1 must
** have sufficient space to hold the result.
** @params: {char *s1} Pointer to first string
** @params: {const char *s2} Pointer to second string
** @return: {char*} return the pointer s1.
*/
char			*ft_strcat(char *s1, const char *s2);
/*
** Append a copy of the null-terminated string s2 to the end of the
** null-terminated string s1, then add a terminating `\0'. The string s1 must
** have sufficient space to hold the result. The strncat() function appends not
** more than n characters from s2, and then adds a terminating `\0'.
** @params: {char *s1} Pointer to first string
** @params: {const char *s2} Pointer to second string
** @params: {size_t n} Number of chars to concatinate.
** @return: {char*} return the pointer s1.
*/
char			*ft_strncat(char *s1, const char *s2, size_t n);
/*
** The strchr() function locates the first occurrence of c
** (converted to a char) in the string pointed to by s. The terminating null
** character is considered to be part of the string; therefore if c is `\0',
** the functions locate the terminating `\0'. The strrchr() function is
** identical to strchr(), except it locates the last occurrence of c.
** @params: {const char *s} Pointer to string
** @params: {int c} Character to search to.
** @return: {char*} The functions strchr() and strrchr() return a pointer to
** the located character, or NULL if the character does not appear in the
** string.
*/
char			*ft_strrchr(const char *s, int c);
/*
** The bzero() function writes n zeroed bytes to the string s.
** If n is zero, bzero() does nothing
** @params: {void *s} Pointer to string
** @params: {size_t len} Number of bytes to set to.
** @return: {void}
*/
void			ft_bzero(void *s, size_t n);
/*
** The memset() function writes len bytes of value c
** (converted to an unsigned char) to the string b.
** @params: {void *b} Pointer to memmry to copy to
** @params: {int c} Character to set to.
** @params: {size_t len} Bytes to set to.
** @return: {void*} The memset() function returns its first argument.
*/
void			*ft_memset(void *b, int c, size_t len);
/*
** The memchr() function locates the first occurrence of c
** (converted to an unsigned char) in string s.
** @params: {void *dst} Pointer to memmry to copy to
** @params: {int c} Character to search to.
** @params: {size_t len} Bytes to search to.
** @return: {void*} he memchr() function returns a pointer to the byte located,
** or NULL if no such byte exists within n bytes.
*/
void			*ft_memchr(const void *s, int c, size_t n);
/*
** The memmove() function copies len bytes from string src to string dst.
** The two strings may overlap; the copy is always done in a
** non-destructive manner.
** @params: {void *dst} Pointer to memmry to copy to
** @params: {void *src} Pointer to memmory to copy from
** @params: {size_t len} Bytes to copy to.
** @return: {void*} The memmove() function returns the original value of dst.
*/
void			*ft_memmove(void *dst, const void *src, size_t len);
/*
** The memcpy() function copies n bytes from memory area src to memory area
** dst. If dst and src overlap, behavior is undefined. Applications in which
** dst and src might overlap should use memmove(3) instead.
** @params: {void *dst} Pointer to memmry to copy to
** @params: {void *src} Pointer to memmory to copy from
** @params: {size_t n} Bytes to copy to.
** @return: {void*} The memcpy() function returns the original value of dst.
*/
void			*ft_memcpy(void *dst, const void *src, size_t n);
/*
** The memccpy() function copies bytes from string src to string dst.
** If the character c (as converted to an unsigned char) occurs in the string
** src, the copy stops and a pointer to the byte after the copy of c in
** the string dst is returned. Otherwise, n bytes are copied, and a NULL
** pointer is returned.
** The source and destination strings should not overlap, as the behavior is
** undefined.
** @params: {void *dst} Pointer to memmry to copy to
** @params: {void *src} Pointer to memmory to copy from
** @params: {int c} Character after that stop copy
** @params: {size_t n} Bytes to copy to.
** @return: {void*} Value of dst.
*/
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
/*
** The toupper() function converts a lower-case letter to the corresponding
** upper-case letter.
** The argument must be representable as an unsigned char or the value of EOF.
** @params: {int c} Character to convert
** @return: {int} If the argument is a lower-case letter, the toupper()
** function returns the corresponding upper-case letter if there is one;
** otherwise, the argument is returned unchanged.
*/
int				ft_toupper(int c);
/*
** The tolower() function converts an upper-case letter to the corresponding
** lower-case letter.
** The argument must be representable as an unsigned char or the value of EOF.
** @params: {int c} Character to convert
** @return: {int} If the argument is an upper-case letter, the tolower()
** function returns the corresponding lower-case letter if there is one;
** otherwise, the argument is returned unchanged.
*/
int				ft_tolower(int c);
/*
** The isalpha() function tests for any character for which isupper(3) or
** islower(3) is true.
** The value of the argument must be representable as an unsigned char or
** the value of EOF.
** @params: {int c} Character to test
** @return: {int} 1 if is alphabetical character, otherwiswe 0.
*/
int				ft_isalpha(int c);
/*
** The isdigit() function tests for a decimal digit character.
** @params: {int c} Character to test
** @return: {int} 1 if is digit character , otherwiswe 0.
*/
int				ft_isdigit(int c);
/*
** The isalnum() function tests for any character for which isalpha(3) or
** isdigit(3) is true. The value of the argument must be representable as
** an unsigned char or the value of EOF.
** @params: {int c} Character to test
** @return: {int} 1 if is alphabetical or numeric character, otherwiswe 0.
*/
int				ft_isalnum(int c);
/*
** The isprint() function tests for any printing character,
** including space (` ').
** The value of the argument must be representable as an unsigned char or the
** value of EOF.
** @params: {int c} Character to test
** @return: {int} 1 if is print character, otherwiswe 0.
*/
int				ft_isprint(int c);
/*
** The isascii() function tests for an ASCII character, which is any character
** between 0 and octal 0177 inclusive.
** @params: {int c} Character to test
** @return: {int} 1 if is ascii character, otherwiswe 0.
*/
int				ft_isascii(int c);
/*
** The atoi() function converts the initial portion of the string pointed to by
** str to int representation.
** @params: {const char *str} string to convert
** @return: {int} Converted integer or 0.
*/
int				ft_atoi(const char *str);
/*
** The strcmp() function lexicographically compare the null-terminated
** strings s1 and s2.
** @params: {const char s1} First byte string to compare
** @params: {const char s2} Second byte string to compare
** @return: {int} The strcmp() function return an integer greater than,
** equal to, or less than 0, according as the string s1 is greater than,
** equal to, or less than the string s2. The comparison is done using unsigned
** characters, so that `\200' is greater than `\0'.
*/
int				ft_strcmp(const char *s1, const char *s2);
/*
** The strncmp() function compares not more than n characters.
** Because strncmp() is designed for comparing strings rather than binary data,
** characters that appear after a `\0' character are not compared.
** @params: {const char s1} First byte string to compare
** @params: {const char s2} Second byte string to compare
** @params: {siz_t n} Chars count to compare.
** @return: {int} The strcmp() and strncmp() functions return an integer
** greater than, equal to, or less than 0, according as the string s1 is
** greater than, equal to, or less than the string s2. The comparison is done
** using unsigned characters, so that `\200' is greater than `\0'.
*/
int				ft_strncmp(const char *s1, const char *s2, size_t n);
/*
** The memcmp() function compares byte string s1 against byte string s2.
** Both strings are assumed to be n bytes long.
** @params: {const void s1} First byte string to compare
** @params: {const void s2} Second byte string to compare
** @params: {siz_t n} The size of the string to be compared.
** @return: {int} The memcmp() function returns zero if the two strings are
** identical, otherwise returns the difference between the first two differing
** bytes (treated as unsigned char values, so that `\200' is greater than `\0',
** for example). Zero-length strings are always identical. This behavior is
** not required by C and portable code should only depend on the sign of the
** returned value.
*/
int				ft_memcmp(const void *s1, const void *s2, size_t n);

/*
** PART #2
*/
/*
** Allocates (with malloc(3)) and returns a “fresh” string end- ing with ’\0’.
** Each character of the string is initialized at ’\0’. If the allocation fails
** the function returns NULL.
** @params: {siz_t size} The size of the string to be allocated.
** @return: {char*} The string allocated and initialized to 0.
*/
char			*ft_strnew(size_t size);
/*
** Applies the function f to each character of the string given as argument to
** create a “fresh” new string (with malloc(3)) resulting from the successive
** applications of f.
** @params: {char const *s} The string to map.
** @params: {char (*f)(char)} The function to apply to each
** character of s.
** @return: {char*} The “fresh” string created from the successive applications
** of f.
*/
char			*ft_strmap(char const *s, char (*f)(char));
/*
** Applies the function f to each character of the string passed as argument
** by giving its index as first argument to create a “fresh” new string
** (with malloc(3)) resulting from the suc- cessive applications of f.
** @params: {char const *s} The string to map.
** @params: {char (*f)(unsogned int, char)} The function to apply to each
** character of s and its index.
** @return: {char*} The “fresh” string created from the successive applications
** of f.
*/
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/*
** Allocates (with malloc(3)) and returns a “fresh” substring from the string
** given as argument. The substring begins at indexstart and is of size len.
** If start and len aren’t refer- ing to a valid substring, the behavior is
** undefined. If the allocation fails, the function returns NULL.
** @params: {char const *s} The string from which create the substring.
** @params: {ubsigned int start} The start index of the substring.
** @params: {size_t len} The size of the substring.
** @return: {char*} The substring.
*/
char			*ft_strsub(char const *s, unsigned int start, size_t len);
/*
** Allocates (with malloc(3)) and returns a “fresh” string end- ing with
** ’\0’, result of the concatenation of s1 and s2. If the allocation fails
** the function returns NULL.
** @params: {char const *s1} The prefix string.
** @params: {char const *s2} The suffix string.
** @return: {char*} The “fresh” string result of the concatenation of the
** 2 strings.
*/
char			*ft_strjoin(char const *s1, char const *s2);
/*
** Allocates (with malloc(3)) and returns a copy of the string given as
** argument without whitespaces at the beginning or at the end of the
** string. Will be considered as whitespaces the following characters ’ ’,
** ’\n’ and ’\t’. If s has no whites- paces at the beginning or at the
** end, the function returns a copy of s. If the allocation fails the
** function returns NULL.
** @params: {char const *s} The string to be trimed.
** @return: {char*} The “fresh” trimmed string or a copy of s.
*/
char			*ft_strtrim(char const *s);
/*
** Allocates (with malloc(3)) and returns an array of “fresh” strings
** (all ending with ’\0’, including the array itself) obtained by
** spliting s using the character c as a delimiter. If the allocation
** fails the function returns NULL.
** @example: ft_strsplit("*hello*fellow***students*", ’*’)
** returns the array ["hello", "fellow", "students"].
** @params: {char const *s} The string to split.
** @params: {char c} The delimiter character.
** @return: {char**} The array of “fresh” strings result of the split.
*/
char			**ft_strsplit(char const *s, char c);
/*
** Outputs the string s to the standard output.
** @params: {char const *s} The string to output.
** @return: {void}
*/
void			ft_putstr(char const *s);
/*
** Outputs the integer n to the standard output.
** @params: {int n} The integer to output.
** @return: {void}
*/
void			ft_putnbr(int n);
/*
** Outputs the character c to the standard output.
** @params: {char *c} The character to output.
** @return: {void}
*/
void			ft_putchar(char c);
/*
** Outputs the string s to the standard output followed by a ’\n’.
** @params: {const char *s} The string to output.
** @return: {void}
*/
void			ft_putendl(char const *s);
/*
** Outputs the char c to the file descriptor fd.
** @params: {char s} The character to output.
** @params: {int n} The file descriptor.
** @return: {void}
*/
void			ft_putchar_fd(char c, int fd);
/*
** Outputs the string s to the file descriptor fd.
** @params: {const char *s} The string to output.
** @params: {int n} The file descriptor.
** @return: {void}
*/
void			ft_putstr_fd(char const *s, int fd);
/*
** Outputs the string s to the file descriptor fd followed by a ’\n’.
** @params: {const char *s} The string to output.
** @params: {int n} The file descriptor.
** @return: {void}
*/
void			ft_putendl_fd(char const *s, int fd);
/*
** Outputs the integer n to the file descriptor fd.
** @params: {int n} The integer to print.
** @params: {int n} The file descriptor.
** @return: {void}
*/
void			ft_putnbr_fd(int n, int fd);
/*
** Allocates (with malloc(3)) and returns a “fresh” memory area. The memory
** allocated is initialized to 0. If the alloca- tion fails, the function
** returns NULL.
** @params: {size_t} The size of the memory that needs to be allocated.
** @return: {void*} The allocated memory area.
*/
void			*ft_memalloc(size_t size);
/*
** Takes as a parameter the address of a memory area that needs to be freed
** with free(3), then puts the pointer to NULL.
** @params: {void **app} A pointer’s address that needs its memory freed and
** set to NULL.
** @return: {void}
*/
void			ft_memdel(void **app);
/*
** Allocate (with malloc(3)) and returns a “fresh” string end- ing with ’\0’
** representing the integer n given as argument. Negative numbers must be
** supported. If the allocation fails, the function returns NULL.
** @params: {int n} The integer to be transformed into a string.
** @return: {char*} The string representing the integer passed as argument.
*/
char			*ft_itoa(int n);
/*
** Takes as a parameter the address of a string that need to be freed with
** free(3), then sets its pointer to NULL.
** @params: {char **as} The string’s address that needs to be freed and its
** pointer set to NULL.
** @return: {void}
*/
void			ft_strdel(char **as);
/*
** Sets every character of the string to the value ’\0’.
** @params: {char *s} The string to iterate.
** @return: {void}
*/
void			ft_strclr(char *s);
/*
** Applies the function f to each character of the string passed as argument.
** Each character is passed by address to f to be modified if necessary.
** @params: {char *s} The string to iterate.
** @params: {void (*f)(char*)} The function to apply to each character of s.
** @return: {void}
*/
void			ft_striter(char *s, void (*f)(char*));
/*
** Applies the function f to each character of the string passed as argument,
** and passing its index as first argument. Each character is passed by
** address to f to be modified if necessary.
** @params: {char *s} The string to iterate.
** @params: {void (*f)(unsigned int, char*)} The function to apply to each
** character of s and its index.
** @return: {void}
*/
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
/*
** Lexicographical comparison between s1 and s2. If the 2 strings
** are identical the function returns 1, or 0 otherwise.
** @params: {char const *s1} The first string to be compared.
** @params: {char const *s2} The second string to be compared.
** @return: {int} 1 or 0 according to if the 2 strings are identical or not.
*/
int				ft_strequ(char const *s1, char const *s2);
/*
** Lexicographical comparison between s1 and s2 up to n characters
** or until a ’\0’ is reached. If the 2 strings are identical, the
** function returns 1, or 0 otherwise.
** @params: {char const *s1} The first string to be compared.
** @params: {char const *s2} The second string to be compared.
** @params: {size_t n} The maximum number of characters to be compared.
** @return: {int} 1 or 0 according to if the 2 strings are identical or not.
*/
int				ft_strnequ(char const *s1, char const *s2, size_t n);

/*
** BONUS
*/
/*
** Allocates (with malloc(3)) and returns a “fresh” link. The
** variables content and content_size of the new link are initialized
** by copy of the parameters of the function. If the pa- rameter
** content is nul, the variable content is initialized to NULL and the
** variable content_size is initialized to 0 even if the parameter
** content_size isn’t. The variable next is initialized to NULL. If
** the allocation fails, the function returns NULL.
** @params: {void const *content} The content to put in the new link.
** @params: {size_t content_size} The size of the content of the new link.
** @return: {t_list} The new link.
*/
t_list			*ft_lstnew(void const *content, size_t content_size);
/*
** Iterates a list lst and applies the function f to each link to
** create a “fresh” list (using malloc(3)) resulting from the
** successive applications of f. If the allocation fails, the
** function returns NULL.
** @params: {t_list *lst} The address of a pointer to the first link
** of a list.
** @params: {t_list *(*f)(t_list *elem)} The address of a function
** to apply to each link of a list.
** @return: {t_list} The new list.
*/
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
/*
** Adds the element new at the beginning of the list.
** @params: {t_list **alst} The address of a pointer to the first link of a
** list.
** @params: {t_list *new} The link to add at the beginning of the
** list
** @return: {void}
*/
void			ft_lstadd(t_list **alst, t_list *new);
/*
** Takes as a parameter the adress of a pointer to a link and frees
** the memory of this link and every successors of that link using
** the functions del and free(3). Finally the pointer to the link
** that was just freed must be set to NULL (quite similar to the
** function ft_memdel from the mandatory part).
** @params: {t_list **alst} The address of a pointer to the first
** link of a list that needs to be freed
** @params: {void (*f)(t_list *elem)} a pointer to function
** @return: {void}
*/
void			ft_lstdel(t_list **alst, void (*del)(void*, size_t));
/*
** Takes as a parameter a link’s pointer address and frees the memory
** of the link’s content using the function del given as a parameter,
** then frees the link’s memory using free(3). The memory of next must
** not be freed under any circumstance. Finally, the pointer to the link
** that was just freed must be set to NULL (quite similar to the function
** ft_memdel in the mandatory part)
** @params: {t_list **alst} The adress of a pointer to a link that needs
** to be freed
** @params: {void (*f)(t_list *elem)} a pointer to function
** @return: {void}
*/
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
/*
** Iterates a list lst and applies the function f to each link
** @params: {t_list *lst} a pointer to first link if list
** @params: {void (*f)(t_list *elem)} a pointer to function
** @return: {void}
*/
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));

/*
** EXTRA
*/
/*
** Convert ASCII string to long or long long integer
** The atol() function converts the initial portion of the string
** pointed to by str to long integer representation.
** @params: {const char *str} string to convert to
** @return: {long int}
*/
long int		ft_atol(const char *str);
/*
** Free given pointer and sets it to NULL
** @params: {void **arr} pointer to free
** @return: {NULL}
*/
void			*ft_free(void **arr);
/*
** Convert all alphabtical chars in string to upper case
** @params: {char *s} string to convert
** @return: {void}
*/
void			ft_strtoupper(char *s);
/*
** Convert all alphabtical chars in string to lower case
** @params: {char *s} string to convert
** @return: {void}
*/
void			ft_strtolower(char *s);
/*
** Insert (with replace) new element to list on given index
** @params: {t_list **lst} pointer to list to update
** @params: {t_list *new} element to insert
** @params: {size_t n} index
** @return: {void}
*/
void			ft_lstinsert(t_list **lst, t_list *new, size_t n);
/*
** Append new element to list
** @params: {t_list **lst} pointer to list to update
** @params: {t_list *new} list to append
** @return: {void}
*/
void			ft_lstappend(t_list **lst, t_list *new);
/*
** Print all element of list of typre t_list in std output
** @params: {t_list *lst} list to print to
** @return: {void}
** @todo:	add feature, that will print all properties of all elements
*/
void			ft_lstprint(t_list *lst);
/*
** Convert ASCII string to integer (RECURSIVELY)
** The function converts the initial portion of the string pointed
** to by str to int representation.
** @params: {const char *str} string to convert to
** @return: {int} number in int representation
*/
int				ft_atoi_recursive(const char *str);
/*
** Convert Int value to string
** The function converts Int value to string in giving base.
** @params: {int value} integer to convert
** @params: {int base} base to convert to (from 2 to 16)
** @return: {char*} string representation of given integer in given base
*/
char			*ft_itoa_base(t_ull n, int base);
/*
** Calculate the power of x.
** @params: {t_ull x} value to power
** @params: {int p} power
** @return: {t_ull} Power of x
*/
t_ull			ft_pow(t_ull x, int p);
/*
** Count digits in given number.
** @params: {t_us n} Number to count digits to
** @return: {t_ull} Number of counted digits
*/
t_us			ft_count_digits(t_ull n);

#endif
