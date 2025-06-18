#include <stdlib.h>

static int is_in_set(char c, const char *set) {
    while (*set) {
        if (c == *set)
            return 1;
        set++;
    }
    return 0;
}

static size_t ft_strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

char *ft_strtrim(char const *s1, char const *set) {
    size_t start, end, len;
    char *trimmed_str;

    if (!s1 || !set)
        return NULL;

    start = 0;
    end = ft_strlen(s1);

    while (s1[start] && is_in_set(s1[start], set))
        start++;

    while (end > start && is_in_set(s1[end - 1], set))
        end--;

    len = end - start;

    trimmed_str = (char *)malloc(sizeof(char) * (len + 1));
    if (!trimmed_str)
        return NULL;

    size_t i = 0;
    while (i < len) {
        trimmed_str[i] = s1[start + i];
        i++;
    }

    trimmed_str[len] = '\0';

    return trimmed_str;
}
