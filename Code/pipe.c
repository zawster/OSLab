#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main(){
	int pfds[2], pid;
	char buf[30];
	pipe(pfds);
	if(pid = fork()){
		close(pfds[1]);
		printf("Parent: Reading to the pipe\n");
		read(pfds[0], buf, 5);
		printf("Parent : read %s \n", buf);
		wait(NULL);
		}
	else{
		close(pfds[0]);
		printf("Child: Writing to the pipe\n");
		write(pfds[1], "test", 5);
		printf(" Child : exiting\n");
		exit(0); 
		}
}
