#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

void myhandler(int signum)
{   
    int fd[2];
    int readbuffer[100];    //buffer for reading from pipe

    // Creation of pipe
    if(pipe(fd) < 0)         //pipe() returns -1 in case of error
    {
        printf("Pipe Failed.\n"); 
        exit(1);
    }

    //Calling fork() to create the child process
    int pid = fork();

    if(pid < 0)    // fork failure 
    {
        printf("Fork Failed.\n");
        exit(1);
    }

    // child process
    else if(pid == 0)
    {
        int n;
        printf("Enter N(the no of fibonacci terms): ");
        scanf("%d", &n);


        int child_pid = getpid();
        close(fd[0]);             //close the read end of the pipe
        write(fd[1], &child_pid, sizeof(int));     //send the child_pid to parent via pipe

        // fibonacci terms 
        int fibo1 = 0;
        int fibo2 = 1;
        int fibo3 = 0;

        write(fd[1], &n, sizeof(int));   //sending the number of terms to the parent

        for(int i=0; i<n; i++)
        {
            // writing the fibonacci terms one by one in  the pipe
            write(fd[1], &fibo1, sizeof(int));     
            fibo3 = fibo1 + fibo2;
            fibo1 = fibo2;
            fibo2 = fibo3;
        }

        // writing the SignalID of the received signal 
        write(fd[1], &signum, sizeof(int));

        close(fd[1]);     //close the write end of the pipe

        exit(0);

    }

    // parent process
    else
    {
        wait(NULL);
        close(fd[1]);   //close the write end of pipe

        read(fd[0], &readbuffer[0], sizeof(int));     //reading the child pid and storing it in readbuffer[0]
        printf("The Child pid is : %d\n", readbuffer[0]);


        int limit=0;
        read(fd[0], &limit, sizeof(int));        //reading the no. of fibonacci terms and storing it in limit


        printf("The fibonacci series is: \n");
        int i = 0;
        // keep on reading till values are returned for fibonacci series
        while(i < limit)
        {
            read(fd[0], &readbuffer[i], sizeof(int));
            printf("%d\n", readbuffer[i]);
            i++;
        }


        // for signalID
        read(fd[0], &readbuffer[i], sizeof(int));
        printf("Signal ID is: %d\n", readbuffer[i]);

        // closing the read end of pipe 
        close(fd[0]);  

        exit(0);
    }
    

}


int main(int argc, char* argv[])
{
    printf("To send signal press Ctrl + C\n");
    signal(SIGINT, myhandler);
    while(1);
}

