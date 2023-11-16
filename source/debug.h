#ifndef debug_H
#define debug_H
//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//@@@ Notes. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

/*
 * Prefix:	DB_	db_
*/


//@@@ Import project headers needed in debug.h + debug.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "config.h"
#include "globals.h"


//@@@ Import system headers needed in debug.h + debug.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include <stdarg.h>
#include <stdint.h>
#ifdef CF_HAVEPRINTF
#include <stdio.h>
#endif


//@@@ Macros. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define _DB db_print
#define _DBf db_printf


//@@@ Type declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//	style Normal
//		Bold, Italics, Underscore,
//	color Reset
//		0, 1, 2, 3,
//		4, 5, 6, 7
typedef enum
{
	db_sN = 1 << 0,
	db_sB = 1 << 1,	db_sI = 1 << 2,		db_sU = 1 << 3,
	db_cR = 1 << 4,
	db_c0 = 1 << 5,	db_c1 = 1 << 6,		db_c2 = 1 << 7,		db_c3 = 1 << 8,
	db_c4 = 1 << 9,	db_c5 = 1 << 10,	db_c6 = 1 << 11,	db_c7 = 1 << 12
} db_scFlags_Enum;


#define db_sNormal		db_sN
#define db_sDefault		db_sN
#define db_sReset		db_sN
#define db_sNone		db_sN

#define db_sBold		dbg_sB
#define db_sItalics		db_sI
#define db_sItalic		db_sI
#define db_sUnderscore	db_sU

#define db_cReset		db_cR
#define db_cDefault		db_cR
#define db_cNormal		db_cR


//@@@ Function declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// Preprocessor logic to check if function declarations need 'extern' attribute.
// (The Makefile invokes compiler with e.g. clang -DSRC_FILE_foo -c srcdir/foo.c -o builddir/foo.o")
#ifndef SRC_FILE_debug
	#define F_EXT_ATTRIB extern		// Importer is not debug.c, declare functions extern
#else
	#define F_EXT_ATTRIB			// Importer is debug.c, don't declare functions extern
#endif

F_EXT_ATTRIB	void db_print(uint16_t sc, char* txt);
F_EXT_ATTRIB	void db_printf(uint16_t sc, const char* fmt, ...);
F_EXT_ATTRIB	void db_print_uint32hex(uint16_t sc, uint32_t num);
F_EXT_ATTRIB	void db_print_uint32(uint16_t sc, uint32_t num);
F_EXT_ATTRIB	void db_test(char *txt);

#undef F_EXT_ATTRIB
#undef SRC_FILE_debug


//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif
