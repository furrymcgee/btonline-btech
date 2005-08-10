
/* config.h */

/* $Id: config.h,v 1.4 2005/06/24 04:39:04 av1-op Exp $ */

#ifndef CONFIG_H
#define CONFIG_H

#include "copyright.h"
#include "autoconf.h"

/* ---------------------------------------------------------------------------
 * Setup section:
 *
 * Load system-dependent header files.
 */

/* Prototype templates for ANSI C and traditional C */

#ifdef __STDC__
#define	NDECL(f)	f(void)
#define	FDECL(f,p)	f p
#ifdef STDC_HEADERS
#define	VDECL(f,p)	f p
#else
#define VDECL(f,p)	f()
#endif
#else
#define NDECL(f)	f()
#define FDECL(f,p)	f()
#define VDECL(f,p)	f()
#endif

#ifdef STDC_HEADERS
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#else
#include <varargs.h>
extern int	    FDECL(atoi, (const char *));
extern double   FDECL(atof, (const char *));
extern long	    FDECL(atol, (const char *));
#endif

#ifdef NEED_MEMORY_H
#include <memory.h>
#endif

#if defined(USG) || defined(STDC_HEADERS)
#include <string.h>
#else
#include <strings.h>
extern char *	FDECL(strtok, (char *, char *));
extern char *	FDECL(strchr, (char *, char));
extern void	FDECL(bcopy, (char *, char *, int));
extern void	FDECL(bzero, (char *, int));
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_SYS_RUSAGE_H
#include <sys/rusage.h>
#endif

#ifdef TIME_WITH_SYS_TIME
#include <sys/time.h>
#include <time.h>
#else
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#else
#include <time.h>
#endif
#endif

#if defined(HAVE_SETRLIMIT) || defined(HAVE_GETRUSAGE)
#include <sys/resource.h>
#endif

#include <sys/param.h>
#ifndef HAVE_GETPAGESIZE
#include "getpagesize.h"
#else
#ifndef HAVE_UNISTD_H
extern int	NDECL(getpagesize);
#endif /* HAVE_UNISTD_H */
#endif /* HAVE_GETPAGESIZE_H */

#ifdef HAVE_ERRNO_H
#include <errno.h>
#else
extern int errno;
extern void	FDECL(perror, (const char *));
#endif

#ifndef HAVE_TIMELOCAL

#ifndef HAVE_MKTIME
#define NEED_TIMELOCAL
extern time_t	FDECL(timelocal, (struct tm *));
#else
#define timelocal mktime
#endif /* HAVE_MKTIME */

#endif /* HAVE_TIMELOCAL */

#ifndef tolower
extern int	FDECL(tolower, (int));
#endif
#ifndef toupper
extern int	FDECL(toupper, (int));
#endif

#ifndef HAVE_SRANDOM
#define random rand
#define srandom srand
#endif /* HAVE_SRANDOM */

#include <sys/types.h>
#include <stdio.h>
#include <ctype.h>

#ifndef VMS
#include <fcntl.h>
#else
#include <sys/fcntl.h>
#endif

#include <sys/socket.h>

typedef int	    dbref;
typedef int	    FLAG;
typedef int     POWER;
typedef char    boolexp_type;
typedef char    IBUF[16];

/* TEST_MALLOC:	Defining this makes a malloc that keeps track of the number
 *		of blocks allocated.  Good for testing for Memory leaks.
 * ATR_NAME:	Define if you want name to be stored as an attribute on the
 *		object rather than in the object structure.
 */

/* Compile time options */

#define CONF_FILE           "netmux.conf"	/* Default config file */
#define FILEDIR             "files/"	    /* Source for @cat */

/* #define TEST_MALLOC */                   /* Keep track of block allocs */
#define SIDE_EFFECT_FUNCTIONS	            /* Those neat funcs that should be
				                             * commands */
#define ENTERLEAVE_PARANOID	                /* Enter/leave commands
				                               require opposite locks succeeding
				                               as well */
#define PLAYER_NAME_LIMIT   22	            /* Max length for player names */
#define NUM_ENV_VARS        10	            /* Number of env vars (%0 et al) */
#define MAX_ARG	            100	            /* max # args from command processor */
#define MAX_GLOBAL_REGS	    10	            /* r() registers */

#define HASH_FACTOR	        2	            /* How much hashing you want. */

#define PLUSHELP_COMMAND	"+help"	        /* What you type to see the +help file */
#define OUTPUT_BLOCK_SIZE	16384
#define StringCopy		    strcpy
#define StringCopyTrunc		strncpy

/* define DO_PARSE_WIZNEWS if wiznews.txt should be parsed like news.txt */
/* #define DO_PARSE_WIZNEWS */

/* define ARBITRARY_LOGFILES if you want (wiz-only) access to arbitrary
   logfiles in game/logs/, through @log and logf(). */
/* Changed to ARBITRARY_LOGGFILES_MODE as part of Exile source tree
 * merge in order to utilize #if expression evaluation for more than 2
 * exclusive modes. Define as one of the following :
 * 0 : As if undefined before. No @log/logf() at all.
 * 1 : As if defined before. @log/logf(), but the MUX process
 *     blocks until file writes complete. Bad for heavy use.
 * 2 : @log/logf() exist as 1, but a fileslave process is used 
 *     for all I/O. Makes good for heavy usage.
 * NOTE : All old #ifdef ARBITRARY_LOGS checks updated to #if expression
 * checks. The 'fileslave' program will always be compiled, but if 0 or 1
 * are used it will never be expected in /bin for use.
 */
#define ARBITRARY_LOGFILES_MODE 2

/* Define SQL_SUPPORT for sqlslave process to exist for @query/sql calls.
 * The makefile will contain building sqlslave if you have libdbi installed,
 * but this needs to be on for the netmux process's code to be aware of starting
 * it, letting you use it, reading the socket's, etc....
 */
/* #define SQL_SUPPORT */

/* Define EXTENDED_DEFAULT_PARENTS to have room_parent and exit_parent mudconf
 * value (0 for none, default) to set a default exit and room parent. Usefull for some.
 */
#define EXTENDED_DEFAULT_PARENTS

#ifdef MYFIFO
#define CHANNEL_HISTORY
#define CHANNEL_HISTORY_LEN     20	/* at max 20 last msgs */
#define COMMAND_HISTORY_LEN     10	/* at max 10 last msgs */
#endif


/* ---------------------------------------------------------------------------
 * Database R/W flags.
 */

#define MANDFLAGS       (V_LINK|V_PARENT|V_XFLAGS|V_ZONE|V_POWERS|V_3FLAGS|V_QUOTED)

#define OFLAGS1		(V_GDBM|V_ATRKEY)	/* GDBM has these */

#define OFLAGS2		(V_ATRNAME|V_ATRMONEY)

#define OUTPUT_VERSION	1	/* Version 1 */
#ifdef MEMORY_BASED
#define OUTPUT_FLAGS	(MANDFLAGS)
#else
#define OUTPUT_FLAGS	(MANDFLAGS|OFLAGS1|OFLAGS2)
						/* format for dumps */
#endif				/* MEMORY_BASED */

#define UNLOAD_VERSION	1	/* verison for export */
#define UNLOAD_OUTFLAGS	(MANDFLAGS)	/* format for export */

/* magic lock cookies */
#define NOT_TOKEN       '!'
#define AND_TOKEN       '&'
#define OR_TOKEN        '|'
#define LOOKUP_TOKEN    '*'
#define NUMBER_TOKEN    '#'
#define INDIR_TOKEN     '@'	/* One of these two should go. */
#define CARRY_TOKEN     '+'	/* One of these two should go. */
#define IS_TOKEN        '='
#define OWNER_TOKEN	    '$'

/* matching attribute tokens */
#define AMATCH_CMD      '$'
#define AMATCH_LISTEN   '^'

/* delimiters for various things */
#define EXIT_DELIMITER  ';'
#define ARG_DELIMITER   '='
#define ARG_LIST_DELIM  ','

/* These chars get replaced by the current item from a list in commands and
 * functions that do iterative replacement, such as @apply_marked, dolist,
 * the eval= operator for @search, and iter().
 */

#define BOUND_VAR       "##"
#define LISTPLACE_VAR   "#@"

/* amount of object endowment, based on cost */
#define OBJECT_ENDOWMENT(cost) (((cost)/mudconf.sacfactor) +mudconf.sacadjust)

/* !!! added for recycling, return value of object */
#define OBJECT_DEPOSIT(pennies) \
    (((pennies)-mudconf.sacadjust)*mudconf.sacfactor)


#ifdef VMS
#define unlink delete
#define gmtime localtime
#define DEV_NULL "NL:"
#define READ socket_read
#define WRITE socket_write
#else
#define DEV_NULL "/dev/null"
#define READ read
#define WRITE write
#endif

#ifdef BRAIN_DAMAGE		/* a kludge to get it to work on a mutant
				         * DENIX system */
#undef toupper
#endif

#ifdef TEST_MALLOC
extern int malloc_count;

#define XMALLOC(x,y) (fprintf(stderr,"Malloc: %s\n", (y)), malloc_count++, \
                    (char *)malloc((x)))
#define XFREE(x,y) (fprintf(stderr, "Free: %s\n", (y)), \
                    ((x) ? malloc_count--, free((x)), (x)=NULL : (x)))
#else
#define XMALLOC(x,y) (char *)malloc((x))
#define XFREE(x,y) (free((x)), (x) = NULL)
#endif				/* TEST_MALLOC */

#ifdef ENTERLEAVE_PARANOID
#define ENTER_REQUIRES_LEAVESUCC	/* Enter checks leaveloc of player's
					                   origin */
#define LEAVE_REQUIRES_ENTERSUCC	/* Leave checks enterlock of player's
					                   origin */
#endif

#define EVAL_ALL_NEWS 1

#endif /* CONFIG_H */
