#include "smartcalc.h"

#define ERR_MALLOC "MALLOC FAILED"
#define ERR_MALLOC_SIZE "INVALID MALLOC SIZE"

static void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char	*s;

	s = (unsigned char *)destination;
	while (n > 0)
	{
		*(s++) = (unsigned char)c;
		n--;
	}
	return (destination);
}

void	*ft_memalloc(size_t size)
{
	void	*a;

	if (size + 1 < size)
		handle_error(ERR_MALLOC_SIZE);
	a = malloc(size);
	if (!a)
		handle_error(ERR_MALLOC);
	ft_memset(a, 0, size);
	return (a);
}
