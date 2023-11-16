#ifndef mutex_H
#define mutex_H
//ɅɅɅ Include guard. ɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅɅ


//@@@ Import project headers needed in mutex.h + mutex.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Import system headers needed in mutex.h + mutex.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include <stdatomic.h>
//#include <stdint.h>


//@@@ Defines. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Type declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Function declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// Preprocessor logic to check if function declarations need 'extern' attribute.
// (The Makefile invokes compiler with e.g. clang -DSRC_FILE_foo -c srcdir/foo.c -o builddir/foo.o")
#ifndef SRC_FILE_mutex
	#define F_EXT_ATTRIB extern		// Importer is not mutex.c, declare functions extern
#else
	#define F_EXT_ATTRIB			// Importer is mutex.c, don't declare functions extern
#endif

F_EXT_ATTRIB	void		mut_lock(void);
F_EXT_ATTRIB	void		mut_unlock(void);

#undef F_EXT_ATTRIB
#undef SRC_FILE_mutex


//VVV Include guard. VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
#endif
