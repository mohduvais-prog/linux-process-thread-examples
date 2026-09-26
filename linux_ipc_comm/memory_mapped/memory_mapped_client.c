#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define FILE_LENGTH 0x100
#define COMMON_FILE_NAME  "/tmp/mmapFile"

main()
{
    int fd;
    void* file_memory;
    char *s;

    /* Prepare a file large enough to hold an unsigned integer. */
    fd = open (COMMON_FILE_NAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    lseek (fd, FILE_LENGTH+1, SEEK_SET);
    write (fd, "", 1);
    lseek (fd, 0, SEEK_SET);

    /* Create the memory mapping. */
    file_memory = mmap (0, FILE_LENGTH, PROT_WRITE, MAP_SHARED, fd, 0);
    printf("client file_memory: 0x%x \r\n",file_memory);
    close (fd);

    s = file_memory;

    printf("Content of file : ");
    for (s = file_memory; *s != '\0'; s++)
        putchar(*s);
    putchar('\n');

    /* Release the memory (unnecessary because the program exits). */
    munmap (file_memory, FILE_LENGTH);

    exit(0);
}


