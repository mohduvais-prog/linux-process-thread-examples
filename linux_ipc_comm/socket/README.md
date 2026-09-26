# Simple Socket Example in C

Client and server examples using AF_INET and AF_UNIX sockets.

## Compile

```sh
gcc inet_server.c -o inet_server
gcc inet_client.c -o inet_client
gcc unix_server.c -o unix_server
gcc unix_client.c -o unix_client
```

## Run

Run the server first, then run the client in another terminal.

```sh
./inet_server
./inet_client
```

```sh
./unix_server
./unix_client
```

## AF_INET vs AF_UNIX

| | AF_INET | AF_UNIX |
|---|---|---|
| Address type | `sockaddr_in` | `sockaddr_un` |
| Address | IP + port | File path |
| Works | Across network | Same machine only |
