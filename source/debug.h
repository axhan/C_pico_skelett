#ifndef debug_H
#define debug_H
//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//@@@ Notes. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

/*
 * Prefix:	DB_	db_ _DB
*/


//@@@ Import project headers needed in debug.h + debug.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include "config.h"
#include "globals.h"


//@@@ Import system headers needed in debug.h + debug.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//#include <stdarg.h>
#include <stdint.h>
#if cfDEBUG
#include <stdio.h>
#endif
#include <pico/types.h>
#include "pico/stdlib.h"


//@@@ Macros. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#if cfDEBUG
#define _DBf printf
#define db_printf printf
#else
#define _DBf db_noop
#define db_printf db_noop
#endif


//@@@ Type declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Function declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// Preprocessor logic to check if function declarations need 'extern' attribute.
// (The Makefile invokes compiler with e.g. clang -DSRC_FILE_foo -c srcdir/foo.c -o builddir/foo.o")
#ifndef SRC_FILE_debug
	#define F_EXT_ATTRIB extern		// Importer is not debug.c, declare functions extern
#else
	#define F_EXT_ATTRIB			// Importer is debug.c, don't declare functions extern
#endif

F_EXT_ATTRIB	void db_noop(const char* fmt, ...);

#undef F_EXT_ATTRIB
#undef SRC_FILE_debug


//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif
