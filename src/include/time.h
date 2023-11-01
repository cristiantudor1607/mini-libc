#ifndef __TIME_H_
#define __TIME_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef int time_t;
struct timespec {
    time_t tv_sec;
    long tv_nsec;
};

int nanosleep(const struct timespec *req, struct timespec *rem);

#ifdef __cplusplus
}
#endif

#endif  // __TIME_H_
