#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#define MSGSZ 128
typedef struct msgbuf
{
	long mtype;
	char mtext[MSGSZ];
} message_buf;
void main()
{
	int msqid;
	key_t key;
	message_buf rbuf;
	key = 1234;
	msqid = msgget(key, 0666);
	msgrcv(msqid, &rbuf, MSGSZ, 1, 0);
	printf("%s\n", rbuf.mtext);
}
