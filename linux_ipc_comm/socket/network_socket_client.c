#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int fd;
    struct sockaddr_in addr;
    char buf[100];

    fd = socket(AF_INET, SOCK_STREAM, 0);             /* 1. create socket */

    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");    /* server IP */

    connect(fd, (struct sockaddr *)&addr, sizeof(addr));  /* 2. connect */

    write(fd, "Hello from client", 18);               /* 3. send data */

    read(fd, buf, sizeof(buf));                       /* 4. receive data */
    printf("Server says: %s\n", buf);

    close(fd);
    return 0;
}
