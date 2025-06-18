#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	words;
	int	in_word;

	i = 0;
	words = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c && in_word == 0)
		{
			in_word = 1;
			words++;
		}
		else if (s[i] == c)
		{
			in_word = 0;
		}
		i++;
	}
	return (words);
}

static char	*make_word(char const *s, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		word_count;
	int		start;
	int		word_index;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	word_index = 0;
	while (s[i] && word_index < word_count)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			result[word_index] = make_word(s, start, i);
			if (!result[word_index])
			{
				while (word_index > 0)
					free(result[--word_index]);
				free(result);
				return (NULL);
			}
			word_index++;
		}
	}
	result[word_index] = NULL;
	return (result);
}