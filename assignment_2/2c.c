#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void *PrintHello()
{	
	//this will be printed by the thread created 
	printf("HELLO WORLD\n");
}

int main(int argc, char *argv[])
{
	pthread_t thread_id; 
	int rc = pthread_create(&thread_id, NULL, PrintHello, NULL);
	if(rc)
	{
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	} 
	pthread_exit(NULL);
}
