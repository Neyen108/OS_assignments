#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>

int main(int argc, char* argv[])
{
	/*
	 * use command : 
	 * ps -Af | grep "2a_modified"
	 * to get the process id of the modified 2a assignment 
	*/ 
	
	int pid;
	printf("Enter the pid: ");
	scanf("%d", &pid);
	int signal_no;

	//here i am handling SIGINT,SIGQUIT and SIGTERM signals,
	// so enter 2,3 or 15 as Signal No
	printf("\nValid Signal nos: 2, 3, 15\n"); 
	printf("\nEnter the Signal No: ");
	scanf("%d", &signal_no);

	//kill() system call returns 0 if it is successful, 
	//else the returned value is negative
	int status = kill(pid, signal_no);
	printf("\nKill Status: %d\n", status);	
}
