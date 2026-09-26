/*
 * shm-client - client program to demonstrate shared memory.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSZ     27

main()
{
    int shmid;
    key_t key;
    char *shm, *s;

   // Pre-defined shared memory key: "1234".
    key = 1234;

    /*
     * Locate the segment.
     */
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Now read what the server put in the memory.
     */
    printf("Data in Shared memory: ");
    for (s = shm; *s != '\0'; s++)
        putchar(*s);
    putchar('\n');

    /*
     * Finally, change the first character of the 
     * segment to '*', indicating we have read 
     * the segment.
     */
    printf("Update shared memory with '*' \r\n");
    *shm = '*';

    exit(0);
}
