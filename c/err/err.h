#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>



#if defined(_ERR_LIB) || defined(DEBUG)
# define DEBUG
  extern void debug(char *fmt, ...);
#else
# define debug(fmt, ...) // macro to nothing
#endif
     


extern void eprintf(char *fmt, ...);
extern void weprintf(char *fmt, ...);
extern void * emalloc(size_t n);
extern char * estrdup(char *s);
// extern inline void setprogname(char *);
extern inline char * progname();
