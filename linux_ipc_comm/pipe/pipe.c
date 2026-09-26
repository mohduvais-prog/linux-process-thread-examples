#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define COUNT	10

void writer (int fd, int count)
{
    do
    {
        sleep (1);
        write(fd, &count, 1);
        printf("send: %d \r\n",count);
    } while(count--);
    printf("writer exits \r\n");
}

void reader (int fd, int count)
{
    char val;
    do
    {
        read(fd, &val, 1);
        printf("recv: %d \r\n",val);
    } while(count--);
    printf("reader exits \r\n");
}

int main ()
{
    int fds[2];
    pid_t pid;

    /* Create a pipe. File descriptors for the two ends of the pipe are
    placed in fds. */
    pipe (fds);

    /* Fork a child process. */
    pid = fork ();
    if (pid == (pid_t) 0) 
    { // Child process
        close (fds[1]); // Close the write descriptor
        reader(fds[0], COUNT);
        close(fds[0]);
    }
    else
    { // Parent process
        close (fds[0]); // Close the read descriptor
        writer (fds[1], COUNT);
        close (fds[1]);
    }

    exit(0);
}
	
