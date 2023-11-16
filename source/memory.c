//@@@ Import own header. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include "memory.h"


//@@@ Global variables. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#ifdef CF_MEMORY_SPINLOCK
 volatile atomic_flag	sp_lock = ATOMIC_FLAG_INIT; // false; true = locked; false = unlocked
#endif

Pool_t		poo;


//@@@ Macros. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Private functions (that do not have declarations in memory.h). @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

inline void spinlock_lock(void)
{
#ifdef CF_MEMORY_SPINLOCK
	while (atomic_flag_test_and_set(&sp_lock))
		;	// Spin until lock acquired.
#endif
}


inline void spinlock_unlock(void)
{
#ifdef CF_MEMORY_SPINLOCK
	atomic_flag_clear(&sp_lock);	// Unlock spinlock.
#endif
}


//@@@ Utility functions operating on chunks. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

inline uint32_t to_offset(CHdr_t* chunk_ptr)
{	return chunk_ptr ? (uint32_t) ((uint8_t*)chunk_ptr - (uint8_t*)&poo.u8) : 0;	}
//	eq:	if (chunk_ptr) {return (uint32_t) ((uint8_t*)chunk_ptr - pool);} else {return 0;}


inline CHdr_t* to_ptr(uint32_t chunk_offset)
{	return chunk_offset ? (CHdr_t*) (&poo.u8[chunk_offset]) : nullptr;	}
//	eq. if (index) {return (CHdr_t*) (pool + index);} else {return nullptr;}


inline void* get_buffer(CHdr_t* chunk_ptr)
{	return chunk_ptr ? (void*) (chunk_ptr + CHDR_SIZE) : nullptr;	}
//	eq.	if (chunk_ptr) {return (void*) (chunk_ptr + CHDR_SIZE);} else {return nullptr;}


inline bool is_free(CHdr_t* chunk_ptr)
{	return chunk_ptr->size & 0x80000000 ? true : false;	}


inline void set_free(CHdr_t* chunk_ptr)
{	chunk_ptr->size |= 0x80000000;	}


inline void set_used(CHdr_t* chunk_ptr)
{	chunk_ptr->size &= 0x7fffffff;	}


inline uint32_t get_size(CHdr_t* chunk_ptr)
{	return chunk_ptr->size & 0x7fffffff;	}


inline void set_size(CHdr_t* chunk_ptr, uint32_t new_size)
{	chunk_ptr->size = new_size | (chunk_ptr->size & 0x80000000);	}


//@@@ Public functions (that have declarations in memory.h). @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#if CF_MEM_DUMP
void me_dump(bool show_header, bool show_chunks, bool show_fragmentation)
{
	spinlock_lock();

	CHdr_t* ichunk_ptr;
	uint32_t chunk_index = 1;

	if (show_header)
	{
		db_printf(db_sN+db_c4,	"╔══════════════════════════════════════════════════" \
								"═══════════════════════════════════════════════════╗\n║");
		db_printf(db_sN+db_sB+db_sI+db_c6, "    Total     avail  chunks    first     last  allocs" \
											"   frees  min_avail merges_p merges_n merges_pn ");
		db_printf(db_sN+db_c4,	"║\n║");

		db_printf(db_sN+db_c7,	"%6uKiB %6uKiB %7u %#8x %#8x %7u %7u  %6uKiB  %7u  %7u   %7u ",
						(uint32_t)(poo.ph.total >> 10), (uint32_t)(poo.ph.avail >> 10),
						poo.ph.chunks, poo.ph.first, poo.ph.last, poo.ph.allocs,
						poo.ph.frees, (uint32_t)(poo.ph.min_avail >> 10),
						poo.ph.merges_p, poo.ph.merges_n, poo.ph.merges_pn);
		db_printf(db_sN+db_c4,	"║\n╚════════════════════════════════════════════════════" \
								"═════════════════════════════════════════════════╝\n");
	}	// >> 10 divides by 1024
	if (show_chunks)
	{
		db_printf(db_sN+db_c4,	"╔════════════════════════════════════════════════════╗\n║");
		db_printf(db_sN+db_sB+db_sI+db_c6,	"   Chunk   address     prev     next     size  free ");
		db_printf(db_sN+db_c4,	"║\n");
		for (ichunk_ptr = to_ptr(poo.ph.first); ichunk_ptr; ichunk_ptr = to_ptr(ichunk_ptr->next))
		{
			db_printf(db_sN+db_c4,	"║");
			db_printf(db_sN+db_c7, " %7u  %#8x %#8x %#8x  %7u   %s",
						chunk_index++, to_offset(ichunk_ptr), ichunk_ptr->prev,
						ichunk_ptr->next,
						ichunk_ptr->size & 0x7fffffff,
						(ichunk_ptr->size & 0x80000000) ? "yes" : " no");
			db_printf(db_sN+db_c4,	" ║\n");
		} // for ()
		db_printf(db_sN+db_c4,	"╚════════════════════════════════════════════════════╝\n");
	}
	if (show_fragmentation)
	{
		static const double bytes_per_char = CF_MEM_POOLSIZE / CF_MEM_DUMPFRAGCHARS;
		static const double chars_per_byte = 1 / bytes_per_char;
		char* chunk_char;
		double num_chars;
		uint32_t num_chars_int;
		uint32_t char_i;

		for (ichunk_ptr = to_ptr(poo.ph.first); ichunk_ptr; ichunk_ptr = to_ptr(ichunk_ptr->next))
		{
			chunk_char = is_free(ichunk_ptr) ? CF_MEM_DUMPFRAG_FREE : CF_MEM_DUMPFRAG_USED;

			num_chars = chars_per_byte * (double)(ichunk_ptr->size & 0x7fffffff);
			num_chars_int = (uint32_t)num_chars;

			for (char_i = 0; char_i < num_chars_int; char_i++)
			{
				db_print(db_sN+db_c7, chunk_char);
			}
		} // for ()
//		db_printf(0, "%f %f\n", bytes_per_char, chars_per_byte);
		db_print(0, "\n");
	}

	spinlock_unlock();
	return;
}
#endif


// To be called ONCE only. Stub for now.
void me_finish(void)
{
	return;
}

//	Да эта правда
//	Э


// Free memory block at buffer, previously returned by mem_malloc().
void me_free(void* buffer)
{
	spinlock_lock();

	CHdr_t* this_chunk_ptr	=	(CHdr_t*) buffer - sizeof(CHdr_t);
	uint32_t this_chunk		=	to_offset(this_chunk_ptr);
	uint32_t prev_chunk		=	this_chunk_ptr->prev;
	uint32_t next_chunk		=	this_chunk_ptr->next;
	CHdr_t* prev_chunk_ptr	=	to_ptr(prev_chunk);
	CHdr_t* next_chunk_ptr	=	to_ptr(next_chunk);
	bool merged_prev		=	false;
	bool merged_next		=	false;

	if (is_free(prev_chunk_ptr))
	{ // Chunk immediately before is free. We meld.
		prev_chunk		=	prev_chunk_ptr->prev;
		prev_chunk_ptr	=	to_ptr(prev_chunk);
		poo.ph.avail	+=	CHDR_SIZE;	// One chunk header less will exist.
		poo.ph.chunks	-=	1;
		merged_prev		=	true;
	}

	if (is_free(next_chunk_ptr))
	{ // Chunk immediately after is free. We meld.
		next_chunk		=	next_chunk_ptr->next;
		next_chunk_ptr	=	to_ptr(next_chunk);
		poo.ph.avail	+=	CHDR_SIZE;	// One chunk header less will exist.
		poo.ph.chunks	-=	1;
		merged_next		=	true;
	}

	if (merged_prev && merged_next)	{ poo.ph.merges_pn += 1;	}
	else if (merged_prev)			{ poo.ph.merges_p += 1;		}
	else if (merged_next)			{ poo.ph.merges_n += 1;		}

	poo.ph.avail += this_chunk_ptr->size;	// The middle chunk's buffer space will be available.

	// prev, next are first non-free chunks before, after
	this_chunk				=	prev_chunk + CHDR_SIZE + prev_chunk_ptr->size;
	this_chunk_ptr			=	to_ptr(this_chunk);

	prev_chunk_ptr->next	=	next_chunk_ptr->prev = this_chunk;

	this_chunk_ptr->prev	=	prev_chunk;
	this_chunk_ptr->next	=	next_chunk;

	this_chunk_ptr->size	=	(next_chunk - this_chunk - CHDR_SIZE);	// Calc bufsize of
																		// melded chunk.
	this_chunk_ptr->size	|=	0x80000000;	// Mark as free.
	poo.ph.frees			+=	1;

	spinlock_unlock();
	return;
}


// To be called ONCE only, before calling mem_malloc, mem_free, mem_dump or mem_finish.
void me_init(void)
{
	static const uint32_t chunk1		= PHDR_SIZE;					// Fencepost at start.
	static const uint32_t chunk2		= PHDR_SIZE + CHDR_SIZE;
	static const uint32_t chunk3		= CF_MEM_POOLSIZE - CHDR_SIZE;	// Fencepost at end.
	static const uint32_t chunk2_size	= (CF_MEM_POOLSIZE - PHDR_SIZE - 3 * CHDR_SIZE);

	CHdr_t*	chunk1_ptr	=	to_ptr(chunk1);
	CHdr_t*	chunk2_ptr	=	to_ptr(chunk2);
	CHdr_t*	chunk3_ptr	=	to_ptr(chunk3);

//	memset(&poo, 0, PHDR_SIZE);

	poo.ph.total		=	CF_MEM_POOLSIZE;
	poo.ph.chunks		=	3;
	poo.ph.first		=	chunk1;
	poo.ph.last			=	chunk3;
	poo.ph.avail		=	chunk2_size;
	poo.ph.min_avail	=	chunk2_size;

	chunk1_ptr->prev	=	0;
	chunk1_ptr->next	=	chunk2;
	chunk1_ptr->size	=	0;	// The fencepost chunks have 0 bufsize and are permanently marked
								// non-free.

	chunk2_ptr->prev	=	chunk1;
	chunk2_ptr->next	=	chunk3;
	chunk2_ptr->size	=	0x80000000 | chunk2_size;

	chunk3_ptr->prev	=	chunk2;
	chunk3_ptr->next	=	0;
	chunk3_ptr->size	=	0;	// The fencepost chunks have 0 bufsize and are permanently marked
								// non-free.

	return;
}


// Returns pointer to memory block of size size, rounded up to closest multiple of 4,
// or NULL, and sets merrno to relevant return code (MEM_EOK, MEM_EOUT).
void*	me_malloc(uint32_t size, uint8_t* merrno)
{
	register CHdr_t* ichunk_ptr;
	register CHdr_t* sploff_ptr;

	uint32_t uprounded_size = (size + 3) &~ 3;	// Round up to closest multiple of 4 by adding 3,
												// then clearing lowest two bits.
	uint32_t ichunk;
	uint32_t ichunk_oldsize;
	uint32_t min_size = uprounded_size + CHDR_SIZE + 4;	// Target chunk to be split in two
														// must have at least 4 bytes of buffer
														// remaining after splitting.
	uint32_t sploff;
	uint32_t sploff_size;


	spinlock_lock();
	for (ichunk = poo.ph.last; ichunk; ichunk = ichunk_ptr->prev) // Iterate backw.
	{
		ichunk_ptr = to_ptr(ichunk);
		ichunk_oldsize = ichunk_ptr->size & 0x7fffffff;
		if (is_free(ichunk_ptr))
		{	// Chunk is free.
			if (ichunk_oldsize == uprounded_size)
			{	// Is exact size.
				set_used(ichunk_ptr);			// Mark as non-free.
				poo.ph.avail		-=	uprounded_size;
				if (poo.ph.avail < poo.ph.min_avail)
				{
					poo.ph.min_avail = poo.ph.avail;
				}
				poo.ph.allocs		+=	1;
				spinlock_unlock();
				*merrno				=	ME_EOK;	// Set error code to <No error>
				return get_buffer(ichunk_ptr);	// and return the buffer pointer.
			}
			else if (ichunk_oldsize > min_size)
			{	// Larger than needed, so we split off.
				sploff				=	ichunk + CHDR_SIZE + uprounded_size;
				sploff_ptr			=	to_ptr(sploff);

				ichunk_ptr->size	=	uprounded_size;
				sploff_ptr->size	=	ichunk_oldsize - CHDR_SIZE - uprounded_size;
				sploff_ptr->size	|=	0x80000000;

				sploff_ptr->prev	=	ichunk;
				sploff_ptr->next	=	ichunk_ptr->next;
				ichunk_ptr->next	=	sploff;
				to_ptr(sploff_ptr->next)->prev = sploff;
				poo.ph.chunks		++;
				poo.ph.avail		-=	(CHDR_SIZE + uprounded_size);
				if (poo.ph.avail < poo.ph.min_avail)
				{
					poo.ph.min_avail = poo.ph.avail;
				}
				poo.ph.allocs		++;
				spinlock_unlock();
				*merrno				=	ME_EOK;	// Set error code to <No error>
				return get_buffer(ichunk_ptr);	// and return the buffer pointer.
			}
			else
				;	// Too small.
		}
	} // Iteration for(...)

	// Traversed entire chunk list with no free chunk large enough found.
	spinlock_unlock();
	*merrno = ME_EOUT;	// Set error code to <Out of memory>
	return nullptr;		// and return null.
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
