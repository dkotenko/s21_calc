#define _POSIX_C_SOURCE  200809L
#define _GNU_SOURCE
#include "smartcalc.h"
#include <unistd.h>
#include <stdio.h>

int	handle_error(char *s)
{
	dprintf(STDERR_FILENO, "ERROR:\t%s\n", s);
	exit(0);
}
