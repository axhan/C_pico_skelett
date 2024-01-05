#ifndef config_H
#define config_H
//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Notes. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


/*
 * Prefix:	CF_	cf_ cf
 */


//@@@ Import project headers needed in config.h + config.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Import system headers needed in config.h + config.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Defines. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define cfBUTT_GPIOS			{22}	// GPIO nums of buttons, e.g. {22, 23, 24}
#define cfNUM_BUTT				sizeof((uint8_t[])cfBUTT_GPIOS)/sizeof(uint8_t)
#define cfINPUT_QUEUE_LEN		100

#define cfBUTT_CONSEC_MIN		20		// Minimum number of identical consecutive gpio reads
										// before a button is deemed debounced. <= 64 !
#define cfINPUT_POLL_HZ			1000	// Frequency at which the callback in input.c is run.
#define cfBUTT_REPT_HZ			10		// Button repeat rate in Hz.
#define cfBUTT_REPT_DELAY		400		// Button repeat delay in ms.

#define cfDEBUG					true	// Debug mode.

// Number of times the callback must run between repetitions of repeating buttons.
//#define cfBUTT_REPT_INTVAL		(uint16_t)(cfINPUT_POLL_HZ / cfBUTT_REPT_HZ)

// Number of callback runs required before held buttons start repeating.
//#define cfBUTT_REPT_THRES		(uint16_t)((1000*cfBUTT_REPT_DELAY)/(1000000/cfINPUT_POLL_HZ))

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

#define XSTR(x) STR(x)
#define STR(x) #x

//The value of a macro can then be displayed with:

//#pragma message "intval: " XSTR(cfBUTT_REPT_INTVAL)
//#pragma message "thres: " XSTR(cfBUTT_REPT_THRES)


//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif
