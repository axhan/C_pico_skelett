#ifndef globals_H
#define globals_H
//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Notes. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

/*
 * Prefix:	GL_	gl_
*/


//@@@ Import project headers needed in globals.h + globals.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include "config.h"


//@@@ Import system headers needed in globals.h + globals.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include <stdint.h>


//@@@ Type declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

typedef struct {
	uint32_t	a;
	uint32_t	b;
	uint8_t		c;
	uint8_t		d;
} gl_Globals_t;


//@@@ File scope global variables. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Function and global variable declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// Preprocessor logic to check if function declarations need 'extern' attribute.
// (The Makefile invokes compiler with e.g. clang -DSRC_FILE_foo -c srcdir/foo.c -o builddir/foo.o")
#ifndef SRC_FILE_globals
	extern gl_Globals_t globals;		// if globals.h imported by other than globals.c
	#define F_EXT_ATTRIB	extern		// Importer is not globals.c, declare functions extern
#else
	#define F_EXT_ATTRIB			// Importer is globals.c, don't declare functions extern
#endif

F_EXT_ATTRIB void gl_init(void);

#undef F_EXT_ATTRIB
#undef SRC_FILE_globals


//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif
