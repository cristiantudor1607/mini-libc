#include <unistd.h>
#include <time.h>

unsigned int sleep(unsigned int seconds)
{
    /* Set the variable to call nanosleep with seconds field and nanoseconds
    set to 0 */
    struct timespec req, rem;
    req.tv_nsec = 0;
    req.tv_sec = seconds;

    rem.tv_nsec = 0;
    rem.tv_sec = 0;
    nanosleep(&req, &rem);
    
    /* Return the number of seconds left */
    return rem.tv_sec;
}
