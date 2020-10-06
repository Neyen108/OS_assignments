#include<stdio.h>

int main(int argc, char* argv[])
{
	printf("execv() system call executed by Child process\n");
	printf("This is the User designed program.\n");
	printf("The information received via argument vector: \n");
	
	printf("The main program name: %s\n", argv[0]);
}
