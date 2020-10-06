#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdlib.h>

int done = 1;

//user signal handler that shows which signal was received from 2b
void my_sig_handler(int signum)
{	
	switch(signum)
	{
		case SIGINT:
			printf("Received signal SIGINT from 2b.\n");
			break;
		case SIGTERM:
			printf("Received signal SIGTERM from 2b.\n");
			break;
		case SIGQUIT:
			printf("Received signal SIGQUIT from 2b.\n");
			break;
	}		
	done = 0;
}

int main(int argc, char* argv[])
{
	int i=0;

	//signal system calls that we use to handle the signal 
	//received from 2b
	//my_sig_handler is the user signal handler
	signal(SIGINT, my_sig_handler);
	signal(SIGTERM, my_sig_handler);
	signal(SIGQUIT, my_sig_handler);


	//this while loop will continue to run until a signal is received from 2b
	while(done)
	{
		printf("i = %d\n", i);
		i++;
		sleep(1);
	}

	return 0;
}
