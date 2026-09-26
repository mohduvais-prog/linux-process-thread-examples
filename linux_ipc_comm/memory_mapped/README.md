# Simple Shared Memory Example in C

A server and a client that share data through shared memory.

## Compile

```sh
gcc memory_mapped_server.c -o mmap_server
gcc memory_mapped_client.c -o mmap_client
```

## Run

Run the server first, then run the client in another terminal.

```sh
./mmap_server
./mmap_client
```
