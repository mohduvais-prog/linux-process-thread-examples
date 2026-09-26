#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

int main()
{
    int fd;
    struct sockaddr_un addr;
    char buf[100];

    fd = socket(AF_UNIX, SOCK_STREAM, 0);             /* 1. create socket */

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/tmp/mysocket");           /* same path as server */

    connect(fd, (struct sockaddr *)&addr, sizeof(addr));  /* 2. connect */

    write(fd, "Hello from client", 18);               /* 3. send data */

    read(fd, buf, sizeof(buf));                       /* 4. receive data */
    printf("Server says: %s\n", buf);

    close(fd);
    return 0;
}
