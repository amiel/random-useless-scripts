#include "err.h"


#ifdef DEBUG
    void debug(char *fmt, ...){
	va_list args;

	fflush(stdout);
	fprintf(stderr, "DEBUG: ");
	// if (progname() != NULL)
	//     fprintf(stderr, "%s: ", progname());

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	if (fmt[0] != '\0' && fmt[strlen(fmt)-1] == ':')
	    fprintf(stderr, " %s",strerror(errno));
	fprintf(stderr, "\n");
	fflush(stderr);
    }
#endif



void eprintf(char *fmt, ...){
    va_list args;

    fflush(stdout);
	//     if (progname() != NULL)
	// fprintf(stderr, "%s: ", progname());

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    if (fmt[0] != '\0' && fmt[strlen(fmt)-1] == ':')
	fprintf(stderr, " %s",strerror(errno));
    fprintf(stderr, "\n");
    exit(2);
}


void weprintf(char *fmt, ...){
    va_list args;

    fflush(stdout);
    fprintf(stderr, "WARNING: ");
	//     if (progname() != NULL)
	// fprintf(stderr, "%s: ", progname());

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    if (fmt[0] != '\0' && fmt[strlen(fmt)-1] == ':')
	fprintf(stderr, " %s",strerror(errno));
    fprintf(stderr, "\n");
}


void * emalloc(size_t n){
    void *p;

    p = malloc(n);
    if (p == NULL)
	eprintf("memory allocation failed:");
    return p;
}


char * estrdup(char *s){
    char *t;

    t = (char *) malloc(strlen(s)+1);
    if (t == NULL)
	eprintf("estrdup(\"%.20s\") failed:", s);
    strcpy(t,s);
    return t;
}





// static char *name = NULL; // progname for messages
// 
// 
// inline void setprogname(char *str){
//     name = estrdup(str);
// }
// 
// inline char * progname(){
//     return name;
// }
