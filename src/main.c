//Using Pipes in Linux Processes
//https://linuxprograms.wordpress.com/category/pipes/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSGLEN  64

int main(void)
{
	int result;

	//Pipe
	int fd[2];

	//Process
	pid_t pid;

	//Creating a pipe
	result = pipe (fd);
	if (result < 0)
	{
		//failure in creating a pipe
		perror("pipe");
		exit (1);
	}

	//Creating a child process
	pid = fork();
	if (pid < 0)
	{
		 //failure in creating a child
		 perror ("fork");
		 exit(2);
	}

	if (pid == 0)
	{
		//Child process
		char message[MSGLEN];

		while(1)
		{
			//Clearing the message
			memset (message, 0, sizeof(message));
			printf ("Enter a message: ");
			scanf ("%s",message);

			//Writing message to the pipe
			write(fd[1], message, strlen(message));
		}
		exit (0);
	}
	else
	{
		//Parent Process
		char message[MSGLEN];

		while (1)
		{
			//Clearing the message buffer
			memset (message, 0, sizeof(message));

			//Reading message from the pipe
			read (fd[0], message, sizeof(message));
			printf("Message entered %s\n",message);
		}

		exit(0);
	}

	printf("...\n");

	return 0;
}
