#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
	int pipefd[2];
	pid_t pid1,pid2;
	if (pipe(pipefd)==-1)
	{
		printf("Pipe Failed");
		exit (0);
	}
	pid1=fork();
	if (pid1<0)
	{
		printf("fork failed");
		exit(0);
	}
	if (pid1==0)
	{
		close(pipefd[0]);
		dup2(pipefd[1],STDOUT_FILENO);
		close(pipefd[1]);
		execlp("ls","ls","-l",NULL);
		printf("execlp is failed");
		exit(0);
	}
	pid2=fork();
	if (pid2<0)
	{
		printf("fork failed");
		exit(0);
	}
	if (pid2==0)
	{
		close(pipefd[1]);
		dup2(pipefd[0],STDIN_FILENO);
		close(pipefd[0]);
		execlp("wc","wc","-l",NULL);
		printf("execlp is failed");
		exit(0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1,NULL,0);
	waitpid(pid2,NULL,0);
	return 0;
}
