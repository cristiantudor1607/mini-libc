// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>
#include <sys/stat.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	// check the file descriptor
	struct stat file_status;
	if (fstat(fd, &file_status) == -1 && fd != -1) {
		errno = EBADF;
		return MAP_FAILED;
	}

	void *area = (void *)syscall(__NR_mmap, addr, length, prot, flags, fd, offset);
	if (area == MAP_FAILED) {
		errno = - (long)area;
		return MAP_FAILED;
	}

	return area;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	void *area = (void *)syscall(__NR_mremap, old_address, old_size, new_size, flags);
	if (area == MAP_FAILED) {
		errno = - (long)area;
		return MAP_FAILED;
	}

	return area;
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
