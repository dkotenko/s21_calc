#include "smartcalc.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*dst;
	size_t	i;

	dst = (char *)calloc(ft_strnlen(src, n) + 1, sizeof(char));
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
