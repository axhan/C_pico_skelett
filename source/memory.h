#ifndef memory_H
#define memory_H
//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Notes. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

/*
 * Prefix:	ME_	me_
*/


//@@@ Import project headers needed in memory.h + memory.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "config.h"
#include "debug.h"
#include "globals.h"


//@@@ Import system headers needed in memory.h + memory.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include <stdatomic.h>
#include <stdint.h>
#include <string.h>


//@@@ Type declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
typedef struct {
	uint32_t total;		// Total size of mempool in bytes. Must be <= 0x1fffffff.
	uint32_t avail;		// Number of available, free bytes in pool.
	uint32_t chunks;	// Number of chunks in pool.
	uint32_t allocs;	// Accumulated number of allocations. Statistics.
	uint32_t frees;		// Accumulated number of deallocations. Statistics.

	uint32_t merges_p;
	uint32_t merges_n;
	uint32_t merges_pn;
	uint32_t min_avail;

	uint32_t first; 	// Offset from mem_buffer to first chunk.
	uint32_t last;		// Offset from mem_buffer to last chunk.
} PHdr_t;


typedef struct {
	uint32_t prev;		// Offset in bytes from start of poolheader to previous chunk.
	uint32_t size;		// Highest bit is set if chunk is free.
						// Bottom 31 bits = the size in bytes. Calculated at
						// allocation by rounding up
						// the requested size to closest multiple-of-4.
	uint32_t next;		// Offset in bytes from start of poolheader to next chunk.
} CHdr_t;


typedef union {
	PHdr_t	 ph;
	uint8_t	 u8[CF_MEM_POOLSIZE];
	uint16_t u16[CF_MEM_POOLSIZE >> 1];
	uint32_t u32[CF_MEM_POOLSIZE >> 2];
} Pool_t;


//@@@ Defines. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define ME_EOK			1	// Success.
#define ME_EOUT			-1	// No memory block >= requested size.
#define ME_EARG			-2	// Requested size out of range.	// TODO: Implement

#define PHDR_SIZE	(uint32_t)sizeof(PHdr_t)
#define CHDR_SIZE	(uint32_t)sizeof(CHdr_t)


//@@@ Function declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// Preprocessor logic to check if function declarations need 'extern' attribute.
// (The Makefile invokes compiler with e.g. clang -DSRC_FILE_foo -c srcdir/foo.c -o builddir/foo.o")
#ifndef SRC_FILE_memory
	#define F_EXT_ATTRIB extern		// Importer is not memory.c, declare functions extern
#else
	#define F_EXT_ATTRIB			// Importer is memory.c, don't declare functions extern
#endif

#ifdef CF_MEM_DUMP
 F_EXT_ATTRIB	void	me_dump(	bool show_header,
									bool show_chunks,
									bool show_fragmentation);
#endif
F_EXT_ATTRIB	void	me_finish(	void);
F_EXT_ATTRIB	void	me_free(	void* buffer);
F_EXT_ATTRIB	void	me_init(	void);
F_EXT_ATTRIB	void*	me_malloc(	uint32_t size,
									uint8_t* merrno);

#undef F_EXT_ATTRIB
#undef SRC_FILE_memory


//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif
