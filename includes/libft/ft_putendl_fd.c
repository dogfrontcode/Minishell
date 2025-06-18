#include "libft.h"

void ft_putendl_fd(char *s, int fd) {
    if (s == NULL)
        return;

    while (*s) {
        write(fd, s, 1);
        s++;
    }
    write(fd, "\n", 1);
}

/*
int main()
{
	char s[] = "helloooo";
	int fd = 2;
	ft_putendl_fd(s,fd);
}
*/
