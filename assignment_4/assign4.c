#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    struct flock fl;

    fl.l_type = F_WRLCK;        //Write lock
    fl.l_whence = SEEK_SET;     //lock starting relative to the beginning of the file
    fl.l_start = 0;             //offset 0
    fl.l_len = 0;               //lock to end-of-file
    fl.l_pid = getpid();        //get the process id of this process

    //opening the file "flock_example.txt", 
    //fd is the file descriptor
    int fd = open("flock_example.txt", O_RDWR);

    if(fd == -1)        //error in file opening
    {
        perror("\nError in opening the file!\n");
        exit(1);
    }

    //Setting the write lock
    if(fcntl(fd, F_SETLKW, &fl) == -1)         //error in lock
    {
        perror("Error in fcntl-lock\n");
        exit(1);
    }

    printf("Write lock is set.\n");

    char file_string[200];        //buffer to hold the string read from file
    int end = read(fd, file_string, sizeof(file_string));          //reading the string in file, and, storing it in file_string
    file_string[end] = '\0';      //adding the termination

    printf("THE STRING READ FROM THE FILE: ");
    printf("%s\n", file_string);     //print what is retrieved from the file 

    // Unlock the file
    printf("Press Enter to Unlock the file.\n");
    getchar();
    fl.l_type = F_UNLCK;

    //unlocking
    if(fcntl(fd, F_SETLK, &fl) == -1)      //if error in unlocking
    {
        perror("Error in fcntl-unlock\n");
        exit(1);
    }
    printf("Unlocked.\n");

    // close the file
    close(fd);
    return 0;
}