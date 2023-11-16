//@@@ Import own header. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "debug.h"


//@@@ Global variables. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//char db_tmpBuf[10];


//@@@ Public functions (that have declarations in debug.h). @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void db_print(uint16_t sc, char *txt)
{
#if CF_HAVEPRINTF
	void db_scPrint(uint16_t sc);	// Defined later
#endif // CFG_HAVEPRINTF
	void db_send(char* txt);		// Defined later

	if (globals.debug_level)
	{
#if CF_HAVEPRINTF
		if (globals.debug_colored && sc)		// Any style/color changes before txt to stdout?
		{
			db_scPrint(sc);
		}
		if (txt)
		{
			printf("%s", txt);
		}
		fflush(stdout);
#endif // CF_HAVEPRINTF
//		db_send(txt);			// Send pure txt over e.g. serial.
	}
}


void db_print_uint32hex(uint16_t sc, uint32_t num)
{
#if CF_HAVEPRINTF
	void db_scPrint(uint16_t sc);	// Defined later
#endif // CF_HAVEPRINTF
	void db_send(char* txt);		// Defined later

	if (globals.debug_level)
	{
#if CF_HAVEPRINTF
		if (globals.debug_colored && sc) 		// Any style/color changes before txt to stdout?
		{
			db_scPrint(sc);
		}
		printf("%#10x", num);
		fflush(stdout);
#endif // CF_HAVEPRINTF
//		db_send(txt);			// Send pure txt over e.g. serial.
	}
}


void db_print_uint32(uint16_t sc, uint32_t num)
{
#if CF_HAVEPRINTF
	void db_scPrint(uint16_t sc);	// Defined later
#endif // CF_HAVEPRINTF
	void db_send(char* txt);		// Defined later

	if (globals.debug_level)
	{
#if CF_HAVEPRINTF
		if (globals.debug_colored && sc)	// Any style/color changes before txt to stdout?
		{
			db_scPrint(sc);
		}
		printf("%10u", num);
		fflush(stdout);
#endif // CF_HAVEPRINTF
//		db_send(txt);			// Send pure txt over e.g. serial.
	}
}


void db_printf(uint16_t sc, const char* fmt, ...)
{
#if CF_HAVEPRINTF
	void db_scPrint(uint16_t sc);	// Defined later
#endif // CF_HAVEPRINTF
	void db_send(char* txt);		// Defined later

	va_list args;
	va_start(args, fmt);

	if (globals.debug_level)
	{
#if CF_HAVEPRINTF
		if (globals.debug_colored && sc)	// Any style/color changes before txt to stdout?
		{
			db_scPrint(sc);
		}
		vprintf(fmt, args);
		fflush(stdout);
#endif // CF_HAVEPRINTF
//		db_send(txt);			// Send pure txt over e.g. serial.
	}

	va_end(args);
}


void db_test(char *txt)
{
	void db_send(char* txt);		// Defined later

#if CF_HAVEPRINTF
	for (uint16_t i = 0; i <= 7; i++)
	{
		for (uint16_t j = 4; j < 13; j++)
		{
			uint16_t sc = ((1 << j) | (i << 1) | db_sN);
			db_print(sc, txt);
		} // column
		db_print(0, "\n");
	} // row
#endif // CF_HAVEPRINTF
//	db_send(txt);
}


//@@@ Private functions (that do not have declarations in debug.h). @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#if CF_HAVEPRINTF		// Compile in only if on platform with printf().
void db_scPrint(uint16_t sc)
{
	static const char* _ANSI_pat = "\033[%sm";
	static const char* const _ANSI[] =	{	// ANSI terminal escape sequences for:
		"0",								// Use normal style (deactivate B/I/U).
		"01",	"3",	"04",				// Use Bold, I, U (can be combined).
		"39",								// Use default FG color.
		"30",	"31",	"32",	"33",		// Use FG color #0, #1, #2, #3.
		"34",	"35",	"36",	"37"		// Use FG color #4, #5, #6, #7.
	};

	// The bit number of each flag in sc equals the index in [] above by design to facilitate...:
	if (sc & 1)
	{
		printf(_ANSI_pat, _ANSI[0]);
//		fflush(stdout);
	}
	for (uint8_t i = 1; i <= 13; i++)
	{
		if (sc & (1 << i))
		{
			printf(_ANSI_pat, _ANSI[i]);
//			fflush(stdout);
		}
	}
	fflush(stdout);
}
#endif // CF_HAVEPRINTF


void db_send(char* txt)	// STUB. Intended to send txt over e.g. serial
{
	return;
}
