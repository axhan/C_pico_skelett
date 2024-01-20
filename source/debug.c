//@@@ Import own header. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include "debug.h"


//@@@ Global variables. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Public functions (that have declarations in debug.h). @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void db_noop(const char* fmt, ...)
{
	return;

/*	va_list args;
	va_start(args, fmt);

	if (globals.debug_level)
	{
#if CF_HAVEPRINTF
		vprintf(fmt, args);
		fflush(stdout);
#endif // CF_HAVEPRINTF
	}

	va_end(args);
*/

}


//@@@ Private functions (that do not have declarations in debug.h). @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
