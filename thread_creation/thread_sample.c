#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define handle_error_en(en, msg) \
	   do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

typedef enum _thread_cancel_type
{
	ASYNC = 0,
	SYNC = 1,
	UNCANCEL = 2
}thread_cancel_type;


thread_cancel_type g_thread_cancel;
static int done = 0;
static int cleanup_pop_arg = 0;
static int cnt = 0;

static void
cleanup_handler1(void *arg)
{
   printf("Called clean-up handler 1\n");
   cnt = 0;
}

static void
cleanup_handler2(void *arg)
{
   printf("Called clean-up handler 2\n");
   cnt = 0;
}


static void *
thread_start(void *arg)
{
   thread_cancel_type thread_cancel;
   time_t start, curr;

   printf("New thread started\n");

   // TODO: Thread argument usage
   thread_cancel = *((thread_cancel_type *) arg);

   if(thread_cancel == ASYNC)
   {
	printf("ASYNC Cancel method testing \r\n");
   	// TODO: Thread cancel state set
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
   	// TODO: Thread cancel type set
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
   }
   else if(thread_cancel == UNCANCEL)
   {
	printf("UNCANCEL Cancel method testing \r\n");
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
   }
   else if(thread_cancel == SYNC)
   {
	printf("SYNC Cancel method testing \r\n");
       // Thread default state is sync cancel
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
   }
   else
   {
	thread_cancel = SYNC;
   	printf("Invalid value, default SYNC method  \r\n");
   }

   // TODO: Thread cleanup handler push
   pthread_cleanup_push(cleanup_handler1, NULL);
   pthread_cleanup_push(cleanup_handler2, NULL);

   curr = start = time(NULL);

   // FIXME: Terminating thread normally
   while (!done) {
	   // TODO: Cancellation point

	   if (curr < time(NULL)) 
	   {
	   	if(thread_cancel == SYNC) // Call cacellation point only iff SYNC mode
	   	{ 
		   printf("Cancellation point \r\n");
		   pthread_testcancel();           /* A cancellation point */
	   	}
		curr = time(NULL);
		printf("cnt = %d\n", cnt);
		cnt++;
	   }
   }

   printf("end of function, call cleanup pop \r\n");
   sleep(1);

   // TODO: Thread cleanup handler pop 
   pthread_cleanup_pop(cleanup_pop_arg); // macro type, so must be called
   pthread_cleanup_pop(cleanup_pop_arg);

   return NULL;
}

int main(int argc, char *argv[])
{
   pthread_t thr;
   int s;
   void *res;

   // TODO: Thread creation API
   printf("argc: %d\r\n",argc);
   if(argc > 1)
   {
	g_thread_cancel = atoi(argv[1]);
   }
   else
   {
	printf("Usage: %s <Thread cancel type 0-ASYNC, 1-SYNC, 2-UNCANCEL>  <Theread cancel value (optional)>\r\n",argv[0]);
	exit(0);
   }

   s = pthread_create(&thr, NULL, thread_start, &g_thread_cancel);
   if (s != 0)
	   handle_error_en(s, "pthread_create");

   sleep(2);           /* Allow new thread to run a while */

   if (argc > 2) {
	   cleanup_pop_arg = atoi(argv[2]);
	   done = 1;
   } else {
	   printf("Canceling thread\n");
           // TODO: Thread cancellation API
	   s = pthread_cancel(thr);
	   if (s != 0)
		   handle_error_en(s, "pthread_cancel");
   }

   // TODO: Thread Join API
   printf("Wait for join \r\n");
   s = pthread_join(thr, &res);
   if (s != 0)
	   handle_error_en(s, "pthread_join");
   printf("join done \r\n");

   if (res == PTHREAD_CANCELED)
	   printf("Thread was canceled; cnt = %d\n", cnt);
   else
	   printf("Thread terminated normally; cnt = %d\n", cnt);
   exit(EXIT_SUCCESS);
}





