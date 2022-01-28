#include "smartcalc.h"

char	*ft_strdup(const char *src)
{
	char			*dupl;
	unsigned int	len;

	len = strlen(src);
	dupl = (char *)ft_memalloc((len + 1) * sizeof(char));
	
	len = 0;
	while (src[len])
	{
		dupl[len] = src[len];
		len++;
	}
	return (dupl);
}
