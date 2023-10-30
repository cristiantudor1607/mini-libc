#include <unistd.h>
#include <time.h>

unsigned int sleep(unsigned int seconds)
{
    struct timespec req, rem;
    req.tv_nsec = 0;
    req.tv_sec = seconds;

    rem.tv_nsec = 0;
    rem.tv_sec = 0;

    // TODO: check if nanosleep fails
    nanosleep(&req, &rem);

    // return the number of seconds left
    return rem.tv_sec;
}
