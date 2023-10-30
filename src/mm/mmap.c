// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	// Because syscall returns a long value, it will later be casted to void *
	long chunk = syscall(__NR_mmap, addr, length, prot, flags, fd, offset);
	if (chunk < 0) {
		errno = -chunk;
		return MAP_FAILED;
	}

	return (void *) chunk;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	void *rechunk = (void *)syscall(__NR_mremap, old_address, old_size, new_size, flags);
	if (rechunk == MAP_FAILED) {
		errno = - (long)rechunk;
		return MAP_FAILED;
	}

	return rechunk;
}

int munmap(void *addr, size_t length)
{
	int syscall_ret = syscall(__NR_munmap, addr, length);
	if (syscall_ret < 0) {
		errno = -syscall_ret;
		return -1;
	}

	return syscall_ret;
}
