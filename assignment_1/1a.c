#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/wait.h>
int main()
{
	int pid;
	int child_count=0;
	int gchild_count=0;
	pid = fork();
	if(pid < 0)
	{
		printf("Fork Error.\n");
		exit(1);
	}
	else if(pid == 0)
	{
		pid = fork();
		if(pid < 0)
		{
			printf("Fork Error.\n");
			exit(1);
		}
		else if(pid == 0)
		{
			gchild_count++;
			printf("Grandchild process. Roll NO: CSB18060. Grandchild count: %d\n", gchild_count);
			exit(0);
		}
		else
		{
			child_count++;
			printf("Child Process. PID: %d, PPID: %d, Child count: %d\n", getpid(), getppid(), child_count);
			exit(0);
		}
		
	}
	else
	{	
		printf("Parent process. PID: %d, PPID: %d\n", getpid(), getppid());
		exit(0);
	}
	return 0;
}

