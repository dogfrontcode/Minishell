#include "libft.h"

void ft_putnbr_fd(int n, int fd) {
    char c;

    if (n < 0) {
        ft_putstr_fd("-", fd);
        n = -n;
    }

    if (n >= 10) {
        ft_putnbr_fd(n / 10, fd);
    }

    c = (n % 10) + '0';
    write(fd, &c, 1);
}

/*
int main() {
    ft_putnbr_fd(1234567890, 1);
    ft_putnbr_fd(-9, 1);
    return 0;
}
*/
