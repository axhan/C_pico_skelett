//██████████████████████████████████████████████████████████████████████████████████████████████████
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Import project headers. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "config.h"
#include "debug.h"
#include "globals.h"
#include "memory.h"
#include "module1.h"
#include "module2.h"
#include "timer.h"


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Import system headers. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
//#include "pico/stdlib.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Forward declarations of functions defined in this file.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void shuffle(void *array, size_t n, size_t size);
void sk_func1();


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Global variables. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Macros & defines. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#define NUM_ALLOCS 100

#define BSIZE	32*20

typedef struct {
	uint32_t	one, two;
} s2x32_t;

typedef union bajs {
	s2x32_t		s;
	uint32_t	e32[BSIZE >> 2];
	uint8_t		e8[BSIZE];
} bajs_t;

typedef union {
	s2x32_t		header;
	uint8_t		u8[64];
	uint16_t	u16[64 >> 1];
	uint32_t	u32[64 >> 2];
} uniontest_t;

void test(void)
{
	static bajs_t b;
	uint32_t i = 0;
	uint32_t j;

	db_printf(db_sN+db_cR, "%d\n", (int)sizeof(uniontest_t));
	return;

	b.s.one			= 0x01020304;
	b.s.two			= 0x05060708;
	b.e32[2]		= 0x0a0b0c0d;
	b.e8[12]		= 0xee;
	b.e8[6]			= 0xff;

	b.e32[1*5*8]	= 0xaabbccdd;
	b.e8[4*5*8+2]	= 0x99;

	do {
		for (j = 0; j < 8; j++)
		{
			db_printf(db_sN+db_cR,
					  "%02x%02x%02x%02x%s",
					  b.e8[i], b.e8[i+1], b.e8[i+2], b.e8[i+3],(j != 7) ? " " : "\n");
			i += 4;
		}
	} while (i < BSIZE);
}



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ main() function. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
int main(void)
{
	uint8_t		tmp, tmp2;
//	double		d1 = 0.1f;
//	float		f1 = 0.01f;
	void*		buf1;
	uint8_t		err;
//	uint32_t	alloci = 0;
//	void*		allocs[NUM_ALLOCS];
	uint32_t	rsize;
//	time_t		tim;

	gl_init();
	globals.debug_level = 1;
	globals.debug_colored = true;

	tm_init();

	me_init();

//	tim = time(nullptr);
//	srand((unsigned int)tim);

//	test();

//	db_printf(db_sN+db_c2, "Initial:\n");
//	me_dump(true, true, false);

//	db_print(db_sN+db_c2, "Allocating many...\n");
//	for (alloci = 0; alloci < (sizeof(allocs)/sizeof(void*)); alloci++)
//	{
//		rsize = ((rand() & 0b1111111) << 2) + 512;	// 1040..16
//		assert(allocs[alloci] = me_malloc(rsize, &err));
//	}

//	db_print(db_sN+db_c2, "Map:\n");
//	me_dump(false, false, true);

//	db_print(db_sN+db_c2, "Shuffling the many...\n");
//	shuffle(allocs, (sizeof(allocs)/sizeof(void*)), sizeof(void*));

//	db_print(db_sN+db_c2, "Freeing all the many...\n");
//	for (alloci = 0; alloci < (sizeof(allocs)/sizeof(void*)); alloci++)
//	{
//		me_free(allocs[alloci]);
//		me_dump(false, false, true);
//		db_print(0, "\n");
//	}

//	db_print(db_sN+db_c2, "Final:\n");
//	me_dump(true, true, false);

//	db_print(db_sN+db_c2, "Chunks:\n"); me_dump(false, true, false);
//	db_print(db_sN+db_c2, "Final poolheader:\n"); me_dump(true, false, false);

//	db_test("bajs ");

	sk_func1();
//	d1 = d1 * f1;

	tmp = m1_func1();
	tmp2 = m2_func1();

	me_finish();

	return (int)(tmp + tmp2);
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@ Other functions definitions. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void sk_func1()
{
	return;
}


#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))
/* arrange the N elements of ARRAY in random order.
 * Only effective if N is much smaller than RAND_MAX;
 * if this may not be the case, use a better random
 * number generator. */
/*void shuffle(void *array, size_t n, size_t size)
{
	char tmp[size];
	char *arr = array;
	size_t stride = size * sizeof(char);

	if (n > 1)
	{
		size_t i;
		for (i = 0; i < n - 1; ++i)
		{
			size_t rnd = (size_t) rand();
			size_t j = i + rnd / (RAND_MAX / (n - i) + 1);

			memcpy(tmp, arr + j * stride, size);
			memcpy(arr + j * stride, arr + i * stride, size);
			memcpy(arr + i * stride, tmp, size);
		}
	}
}
*/

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//██████████████████████████████████████████████████████████████████████████████████████████████████
