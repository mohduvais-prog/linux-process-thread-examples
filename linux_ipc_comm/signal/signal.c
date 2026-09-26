#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void siguser_handler()
{
	printf("Received SIGUSR1 \r\n");
}

void sigterm_handler()
{
	printf("Received SIGTERM \r\n");
}

main()
{
	printf("Register the signals \r\n");

       signal(SIGTERM,sigterm_handler);
       signal(SIGUSR1 ,siguser_handler);

       printf("Waiting for signal to occur \r\n");
       while(1)
       {
       	sleep(1000);
       }
}
