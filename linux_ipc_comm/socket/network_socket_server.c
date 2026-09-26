#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in addr;
    char buf[100];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);      /* 1. create socket */

    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);                      /* port 5000 */
    addr.sin_addr.s_addr = INADDR_ANY;                /* any local IP */

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));  /* 2. attach address */
    listen(server_fd, 1);                             /* 3. wait for clients */
    printf("Server waiting...\n");

    client_fd = accept(server_fd, NULL, NULL);        /* 4. accept client */

    read(client_fd, buf, sizeof(buf));                /* 5. receive data */
    printf("Client says: %s\n", buf);

    write(client_fd, "Hello from server", 18);        /* 6. send data */

    close(client_fd);
    close(server_fd);
    return 0;
}
