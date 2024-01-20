#ifndef module1_H
#define module1_H
//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Notes. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

/*
 * Prefix:	M1_	m1_
*/


//@@@ Import project headers needed in module1.h + module1.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include "config.h"
#include "globals.h"


//@@@ Import system headers needed in module1.h + module1.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include <stdint.h>


//@@@ Function declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// Preprocessor logic to check if function declarations need 'extern' attribute.
// (The Makefile invokes compiler with e.g. clang -DSRC_FILE_foo -c srcdir/foo.c -o builddir/foo.o")
#ifndef SRC_FILE_module1
	#define F_EXT_ATTRIB	extern		// Importer is not module1.c, declare functions extern
#else
	#define F_EXT_ATTRIB			// Importer is module1.c, don't declare functions extern
#endif

F_EXT_ATTRIB uint8_t m1_func1(void);

#undef F_EXT_ATTRIB
#undef SRC_FILE_module1


//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif
