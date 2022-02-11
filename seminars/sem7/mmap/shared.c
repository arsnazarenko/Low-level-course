#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

struct file_in_mem {
	void * addr;
	int fd;
}; 


void error(const char *s) {
    fprintf(stderr, "%s", s);
    abort();
}

struct file_in_mem create_shared_memory(size_t size, off_t offset, char const* filename) {
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
  	
  	error("error in open(...)");
  }  
  void* addr = mmap(NULL,
              size,
              PROT_READ,
              MAP_PRIVATE,
              fd, offset);
  if (addr == NULL) {
  	error("error in mmap(...)");
  }            
  return (struct file_in_mem) {.addr = addr, .fd = fd};
}

int main() {
	struct file_in_mem a = create_shared_memory(4096, 4096, "somefile.txt");
	char const* msg = (char*) a.addr;
	printf("%s", msg);
	for(;;) {}
	return 0;
}
