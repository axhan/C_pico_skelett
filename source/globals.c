//@@@ Import own header. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "globals.h"


//@@@ Global variables. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
gl_Globals_t globals;


//@@@ Public functions (that have declarations in globals.h). @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void gl_init(void)
{
	globals.debug_level = CF_DEFAULT_DEBUGLEVEL;
	globals.debug_colored = CF_DEFAULT_COLOREDPRINTF;
}
