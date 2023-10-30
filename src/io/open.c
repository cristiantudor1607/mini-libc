// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	va_list valist;
	va_start(valist, flags);

	int param = va_arg(valist, int);
	va_end(valist);

	int fd = syscall(__NR_open, filename, flags, param);

	if (fd < 0) {
		errno = -fd;
		return -1;
	}

	return fd;
}
