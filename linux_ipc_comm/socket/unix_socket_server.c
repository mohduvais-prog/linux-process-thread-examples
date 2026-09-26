#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

int main()
{
    int server_fd, client_fd;
    struct sockaddr_un addr;
    char buf[100];

    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);      /* 1. create socket */

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/tmp/mysocket");           /* socket file */
    unlink("/tmp/mysocket");                          /* remove old file */

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));  /* 2. attach path */
    listen(server_fd, 1);                             /* 3. wait for clients */
    printf("Server waiting...\n");

    client_fd = accept(server_fd, NULL, NULL);        /* 4. accept client */

    read(client_fd, buf, sizeof(buf));                /* 5. receive data */
    printf("Client says: %s\n", buf);

    write(client_fd, "Hello from server", 18);        /* 6. send data */

    close(client_fd);
    close(server_fd);
    unlink("/tmp/mysocket");
    return 0;
}
