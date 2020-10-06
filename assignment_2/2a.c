#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdlib.h>

void my_sig_handler(int signum)
{
	//to create child process we call fork() system call
	int pid = fork();

	//if fork() returns an int < 0, then it implies an error. Fork did not happen
	if(pid < 0)
	{
		printf("Fork error.\n");
		exit(1);
	}

	//if fork() returns 0, then it is the child process

	else if(pid == 0)
	{
		printf("Child Process. PID: %d, PPID: %d\n",getpid(), getppid());
		exit(0);
	}

	//fork() returns the process id of the child to the parent process
	else 
	{
		wait(NULL);
		printf("Parent Process. PID: %d, PPID: %d\n",getpid(), getppid());
		exit(0);
	}
	
}

int main(int argc, char* argv[])
{
	int i=0;
	//signal system call that we use to handle the SIGINT signal
	signal(SIGINT, my_sig_handler);
	

	//prints the no. of times this while loop runs until we receive the SIGINT signal
	while(1)
	{
		printf("i = %d\n", i);
		i++;
		sleep(1);
	}

	return 0;
}
