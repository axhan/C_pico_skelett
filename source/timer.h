#ifndef timer_H
#define timer_H
//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//@@@ Notes. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

/*
 * Prefix:	TM_	tm_
*/


//@@@ Import project headers needed in timer.h + timer.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "config.h"
#include "globals.h"


//@@@ Import system headers needed in timer.h + timer.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include <sys/types.h>
#include <stdint.h>


//@@@ Function declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// Preprocessor logic to check if function declarations need 'extern' attribute.
// (The Makefile invokes compiler with e.g. clang -DSRC_FILE_foo -c srcdir/foo.c -o builddir/foo.o")
#ifndef SRC_FILE_timer
	#define F_EXT_ATTRIB	extern		// Importer is not timer.c, declare functions extern
#else
	#define F_EXT_ATTRIB			// Importer is timer.c, don't declare functions extern
#endif

F_EXT_ATTRIB	void tm_init(void);
F_EXT_ATTRIB	void tm_tick(void);

#undef F_EXT_ATTRIB
#undef SRC_FILE_timer


//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif
