#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define FILE_LENGTH 0x100
#define COMMON_FILE_NAME  "/tmp/mmapFile"

main(int argc, char *argv[])
{
    int fd;
    void* file_memory;
    char *s;

    if(argc < 2)
    {
        printf("%s: <value> \r\n",argv[0]);
        exit(1);
    }

    /* Prepare a file large enough to hold an unsigned integer. */
    fd = open (COMMON_FILE_NAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    lseek (fd, FILE_LENGTH+1, SEEK_SET);
    write (fd, "", 1);
    lseek (fd, 0, SEEK_SET);

    /* Create the memory mapping. */
    file_memory = mmap (NULL, FILE_LENGTH, PROT_WRITE, MAP_SHARED, fd, 0);
    close (fd);

    printf("server file_memory: 0x%x \r\n",file_memory);
    s = file_memory;
	
    memcpy(s, argv[1], strlen(argv[1]));
    printf("Data written: %s \r\n",argv[1]);

    /* Release the memory (unnecessary because the program exits). */
    munmap (file_memory, FILE_LENGTH);

    exit(0);
}


