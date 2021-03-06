#include "smartcalc.h"

static int	words(char const *s, char c)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			return (counter);
		counter++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (counter);
}

static void	free_arr(char ***arr)
{
	int		i;

	i = 0;
	while (*arr[i])
		free(*arr[i++]);
	free(*arr);
	arr = NULL;
}

static char	*word_to_array(int start, int end, char *s, char *arrs)
{
	int		j;

	arrs = (char *)ft_strnew(end - start + 1);
	j = 0;
	while (start < end)
		arrs[j++] = s[start++];
	arrs[j] = '\0';
	return (arrs);
}

static int	copy_words(char *s, char c, char **arr)
{
	int		i;
	int		start;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && (char)s[i] == c)
			i++;
		start = i;
		if (!s[i])
			break ;
		while (s[i] && (char)s[i] != c)
			i++;
		arr[count] = word_to_array(start, i, (char *)s, arr[count]);
		if (!(arr[count]))
		{
			free_arr(&arr);
			return (0);
		}
		++count;
	}
	arr[count] = 0;
	return (1);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**arr;

	if (!s || !c)
		return (NULL);
	arr = (char **)ft_memalloc(sizeof(char *) * \
		(words(s, c) + 1));
	if (!copy_words((char *)s, c, arr))
		return (NULL);
	return (arr);
}
