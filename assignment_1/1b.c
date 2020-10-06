#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<utmp.h>

void get_logged_in_users()
{
	struct utmp* entry;
	setutent();
	entry = getutent();
	printf("Logged in users:\n");
	while(entry)
	{
		if(entry->ut_type == USER_PROCESS);
			printf("%s\n", entry->ut_user);
		
		entry = getutent();
	}
	printf("\n");
}

int main()
{
	int pid = fork();
	if(pid < 0)
	{
		printf("Fork Error in parent process\n");
		exit(1);
	}
	else if(pid == 0)
	{
		pid = fork();
		if(pid < 0)
		{
			printf("Fork Error in child process\n");
            exit(1);	
		}
		else if(pid == 0)
		{
			printf("GrandChild Process. Roll No: CSB18060\n");
			get_logged_in_users();
			exit(0);
		}
		else
		{
			wait(NULL);
			printf("Child Process. PID: %d, PPID: %d\n", getpid(), getppid());
			exit(0);
		}
	}
	else
	{
		wait(NULL);
		printf("Parent Process. PID: %d, PPID: %d\n", getpid(), getppid());
		exit(0);
	}
}

