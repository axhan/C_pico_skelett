//@@@ Import own header. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "mutex.h"


//@@@ Global variables. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
volatile atomic_flag mut_mut = ATOMIC_FLAG_INIT; // false; true = locked; false = unlocked


//@@@ Public functions (that have declarations in mutex.h). @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void mut_lock(void)
{
	while (atomic_flag_test_and_set(&mut_mut))
	{
		// busy wait
	}

	return;
}


void mut_unlock(void)
{
	atomic_flag_clear(&mut_mut);

	return;
}


//@@@ Private functions (that do not have declarations in mutex.h). @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
