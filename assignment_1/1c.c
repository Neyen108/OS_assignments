#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char* argv[])
{
	int pid = fork();
	int child_pid;
	char* prog_name = argv[0];
	if(pid < 0)
	{
		printf("Fork Error in Parent process.\n");
		exit(1);
	}
	else if(pid == 0)
	{
		printf("Child Process. PID: %d, PPID: %d\n", getpid(), getppid());
		child_pid = getpid();
		char* params[] = {prog_name,NULL};
		execv("./user_prog", params);
	}
	else
	{
		int status;
		wait(&status);
		printf("Parent Process. PID: %d, PPID: %d\n",getpid(), getppid());
		if(WIFEXITED(status))
		{
			printf("Exit status of child process: %d\n", WEXITSTATUS(status));
		}
		exit(0);
	}
}

