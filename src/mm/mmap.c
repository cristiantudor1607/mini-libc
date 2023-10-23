// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	void *area = syscall(__NR_mmap, length, prot, flags, fd, offset);
	if (area == MAP_FAILED) {
		errno = - (long)area;
		return MAP_FAILED;
	}

	return area;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	void *area = syscall(__NR_mremap, old_size, new_size, flags);
	if (area == MAP_FAILED) {
		errno = - (long)area;
	}

	return area;
}

int munmap(void *addr, size_t length)
{
	int ret = syscall(__NR_munmap, addr, length);
	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
}
