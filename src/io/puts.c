#include <internal/types.h>
#include <internal/io.h>
#include <errno.h>
#include <string.h>

int puts(const char *s)
{
    size_t num = strlen(s);

    int ret = write(1, s , num);
    if (ret < 0) {
        errno = -ret;
        return -1;
    }

    int newln = write(1, "\n", 1);
    if (newln < 0) {
        errno = -ret;
        return -1;
    }

    return ret;

}