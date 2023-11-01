#include <internal/types.h>
#include <internal/io.h>
#include <errno.h>
#include <string.h>

int puts(const char *s)
{
    size_t num = strlen(s);

    /* write to stdout the string */
    int ret = write(1, s , num);
    if (ret < 0) {
        errno = -ret;
        return -1;
    }

    /* write to stdout the extra '\n' */
    int newln = write(1, "\n", 1);
    if (newln < 0) {
        errno = -newln;
        return -1;
    }

    return 0;
}
