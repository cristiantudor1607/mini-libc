#include <internal/syscall.h>
#include <time.h>
#include <errno.h>

int nanosleep(const struct timespec *req, struct timespec *rem)
{
    // Call the nanosleep system call
    int ret_val = syscall(__NR_nanosleep, req, rem);

    if (ret_val < 0) {
        errno = -ret_val;
        return -1;
    }

    return 0;
}