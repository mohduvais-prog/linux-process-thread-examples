# Simple Shared Memory Example in C

A server and a client that share data through shared memory.

## Compile

```sh
gcc shared_memory_server.c -o shm_server
gcc shared_memory_client.c -o shm_client
```

## Run

Run the server first, then run the client in another terminal.

```sh
./shm_server
./shm_client
```
