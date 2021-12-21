#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#define FILE_LENGTH 0x100

int main(int argc, char* const argv[]) {
    int fd;
    void* file_memory;
    int integer;

    // mo file
    fd = open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);

    // tao bo nho anh xa
    file_memory = mmap(0, FILE_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    // doc so nguyen, in ra
    sscanf(file_memory, "%d", &integer);
    printf("Gia tri: %d\n", integer);
    sprintf((char*) file_memory, "%d\n", integer*2);

    // go bo nho
    munmap(file_memory, FILE_LENGTH);

    return 0;
}
