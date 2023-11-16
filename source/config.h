#ifndef config_H
#define config_H
//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Notes. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


/*
 * Prefix:	CF_	cf_
 */


//@@@ Import project headers needed in config.h + config.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Import system headers needed in config.h + config.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Defines. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define CF_HAVEPRINTF				false		// Compile for platform that has printf().
#define CF_DEFAULT_COLOREDPRINTF	true		// Print debug output with colors.
#define CF_DEFAULT_DEBUGLEVEL		1			// Default debuglevel [0, 1].
#define CF_MEM_DUMP					false		// Compile-in debug dump in memory.c
#define CF_MEM_DUMPFRAGCHARS		(80*25)		// Size of mem frag display in characters.
#define CF_MEM_DUMPFRAG_FREE		"🞎"			// Char to represent free memory.
#define CF_MEM_DUMPFRAG_USED		"🞕"			// Char to represent used memory.
#define CF_MEM_POOLSIZE				100000		// Size of memory pool in bytes.
#define CF_MEM_SPINLOCK				true		// Compile-in spinlock protection support
												// in memory.c
//@@@ Function declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// Preprocessor logic to check if function declarations need 'extern' attribute.
// (The Makefile invokes compiler with e.g. clang -DSRC_FILE_foo -c srcdir/foo.c -o builddir/foo.o")
#ifndef SRC_FILE_config
	#define F_EXT_ATTRIB extern		// Importer is not config.c, declare functions extern
#else
	#define F_EXT_ATTRIB			// Importer is config.c, don't declare functions extern
#endif

// F_EXT_ATTRIB type function1(blabla);

#undef F_EXT_ATTRIB
#undef SRC_FILE_config


//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif
