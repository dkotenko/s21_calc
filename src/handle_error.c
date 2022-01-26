#include "smartcalc.h"

int	handle_error(char *s)
{
	dprintf(STDERR_FILENO, "ERROR:\t%s\n", s);
	exit(0);
}
