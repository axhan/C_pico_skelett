#ifndef input_H
#define input_H
//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@ Notes. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

/*
 * Prefix:	IN_	in_
*/


//@@@ Import project headers needed in input.h + input.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "config.h"
#include "globals.h"


//@@@ Import system headers needed in input.h + input.c @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "limits.h"
#include <pico/time.h>
#include <pico/types.h>
#include <pico/util/queue.h>
#include <stdint.h>
#include <stdio.h>


//@@@ Type declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
typedef enum : uint8_t {
	evtPRESS, evtRELEASE, evtREPEAT
} in_EventType_t;


typedef struct {
	uint8_t			id;
	in_EventType_t	type;
} in_Event_t;


//@@@ Function and global variable declarations. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// Preprocessor logic to check if function declarations need 'extern' attribute.
// (The Makefile invokes compiler with e.g. clang -DSRC_FILE_foo -c srcdir/foo.c -o builddir/foo.o")
#ifndef SRC_FILE_input
	extern const uint8_t in_gpios[cfNUM_BUTT];
	#define F_EXT_ATTRIB	extern	// Importer is not input.c, declare functions extern
#else
	#define F_EXT_ATTRIB			// Importer is input.c, don't declare functions extern
#endif

F_EXT_ATTRIB void in_init(void);
F_EXT_ATTRIB void in_dump(in_Event_t* event);
F_EXT_ATTRIB bool in_get_pending(in_Event_t* event);

#undef F_EXT_ATTRIB
#undef SRC_FILE_input


//@@@ Include guard. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif
